#define LOCAL_SIZE 256

__kernel void bitonic_sort(__global int* data) {
  __local int shared[LOCAL_SIZE];

  uint gid = get_global_id(0);
  uint lid = get_local_id(0);
  uint group = get_group_id(0);

  uint base = group * LOCAL_SIZE;

  shared[lid] = data[base + lid];

  barrier(CLK_LOCAL_MEM_FENCE);

  for (uint k = 2; k <= LOCAL_SIZE; k <<= 1) {
    for (uint j = k >> 1; j > 0; j >>= 1) {
      uint ixj = lid ^ j;
      if (ixj > lid) {
        if ((gid & k) == 0) {
          if (shared[lid] > shared[ixj]) {
            int tmp = shared[lid];
            shared[lid] = shared[ixj];
            shared[ixj] = tmp;
          }
        } else {
          if (shared[lid] < shared[ixj]) {
            int tmp = shared[lid];
            shared[lid] = shared[ixj];
            shared[ixj] = tmp;
          }
        }
      }
      barrier(CLK_LOCAL_MEM_FENCE);
    }
  }
  data[base + lid] = shared[lid];
}