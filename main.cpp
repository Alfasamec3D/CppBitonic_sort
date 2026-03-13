#include <CL/opencl.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string loadKernel(const std::string& name) {
  std::ifstream file(name);
  if (!file) throw std::runtime_error("Could not open file");
  return std::string(std::istreambuf_iterator<char>(file),
                     std::istreambuf_iterator<char>());
}

int main() {
  std::string source;
  std::string kernel_directory;
  kernel_directory = std::string(PROJECT_ROOT) + "/kernel/bi_sort.cl";
  try {
    source = loadKernel(kernel_directory);
  } catch (const std::runtime_error& e) {
    std::cerr << "Error " << e.what() << std::endl;
    return 1;
  }
  int N;

  std::cin >> N;

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

  cl::Program program(context, source);
  program.build({device});

  cl::Kernel kernel(program, "bitonic_sort");

  cl::Buffer buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                    sizeof(int) * N, input.data());

  auto start = std::chrono ::high_resolution_clock::now();

  for (unsigned int k = 2; k <= N; k <<= 1) {
    for (unsigned int j = k >> 1; j > 0; j >>= 1) {
      kernel.setArg(0, buffer);
      kernel.setArg(1, j);
      kernel.setArg(2, k);

      queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(N),
                                 cl::NullRange);
      queue.finish();
    }
  }
  auto end = std::chrono::high_resolution_clock::now();

  queue.enqueueReadBuffer(buffer, CL_TRUE, 0, sizeof(int) * N, input.data());

  double timeGPU = std::chrono::duration<double>(end - start).count();

  start = std::chrono::high_resolution_clock::now();

  std::sort(copy_input.begin(), copy_input.end());

  end = std::chrono::high_resolution_clock::now();

  double timeCPU = std::chrono::duration<double>(end - start).count();

  // std::cout << timeGPU << std::endl << timeCPU << std::endl;

  for (int i = 0; i < N; ++i) std::cout << input[i] << " ";
  // std::cout << std::endl;
  // for (int i = 0; i < N; ++i) std::cout << copy_input[i] << " ";
  return 0;
}