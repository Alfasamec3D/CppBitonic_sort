__kernel void bitonic_sort(__global int* data, const uint j, const uint k) {
  uint i = get_global_id(0);
  uint ixj = i ^ j;
  if (ixj > i) {
    if ((i & k) == 0) {
      if (data[i] > data[ixj]) {
        int tmp = data[i];
        data[i] = data[ixj];
        data[ixj] = tmp;
      }
    } else {
      if (data[i] < data[ixj]) {
        int tmp = data[i];
        data[i] = data[ixj];
        data[ixj] = tmp;
      }
    }
  }
}