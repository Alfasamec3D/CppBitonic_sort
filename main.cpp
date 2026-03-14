#include <CL/opencl.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include<cassert>

std::string loadKernel(const std::string& name) {
  std::ifstream file(name);
  if (!file) throw std::runtime_error("Could not open file");
  return std::string(std::istreambuf_iterator<char>(file),
                     std::istreambuf_iterator<char>());
}

int main() {
  const int LOCAL = 256;
  std::string source_local;
  std::string source_merge;

  std::string kernel_local_directory;
  std::string kernel_merge_directory;
  kernel_local_directory = std::string(PROJECT_ROOT) + "/kernel/bi_sort.cl";
  kernel_merge_directory =
      std::string(PROJECT_ROOT) + "/kernel/bi_sort_merge.cl";
  try {
    source_local = loadKernel(kernel_local_directory);
    source_merge = loadKernel(kernel_merge_directory);
  } catch (const std::runtime_error& e) {
    std::cerr << "Error " << e.what() << std::endl;
    return 1;
  }

  int N;
  std::cin >> N;
  assert((N & (N - 1)) == 0);
  assert(N >= LOCAL);
  std::vector<int> input(N);

  for (int i = 0; i < N; ++i) {
    std::cin >> input[i];
  }

  std::vector<int> copy_input = input;

  std::vector<cl::Platform> platforms;

  cl::Platform::get(&platforms);

  // get list of platforms:
  cl::Platform platform = platforms.front();

  std::vector<cl::Device> devices;

  // get list of devices on this platform:
  platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);

  cl::Device device = devices.front();

  // construct a context including a list of specified devices:
  cl::Context context(device);

  cl::CommandQueue queue(context, device);

  cl::Program programLocal(context, source_local);
  cl::Program programMerge(context, source_merge);
  
  programLocal.build({device});
  programMerge.build({device});

  cl::Kernel kernelLocal(programLocal, "bitonic_sort");
  cl::Kernel kernelMerge(programMerge, "bitonic_merge");

  cl::Buffer buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                    sizeof(int) * N, input.data());

  cl::NDRange global(N);
  cl::NDRange local(LOCAL);

  auto start = std::chrono ::high_resolution_clock::now();

  kernelLocal.setArg(0, buffer);

  queue.enqueueNDRangeKernel(kernelLocal, cl::NullRange, global, local);

  for (unsigned int k = LOCAL * 2; k <= N; k <<= 1) {
    for (unsigned int j = k >> 1; j > 0; j >>= 1) {
      kernelMerge.setArg(0, buffer);
      kernelMerge.setArg(1, j);
      kernelMerge.setArg(2, k);

      queue.enqueueNDRangeKernel(kernelMerge, cl::NullRange, global, local);
    }
  }
  queue.finish();
  auto end = std::chrono::high_resolution_clock::now();

  queue.enqueueReadBuffer(buffer, CL_TRUE, 0, sizeof(int) * N, input.data());


  for (int i = 0; i < N; ++i) std::cout << input[i] << " ";

  return 0;
}