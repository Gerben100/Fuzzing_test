#include <string>
#include <cstdint>
#include <cstring>

int foo(const char* str) {
  char buf[4];
  memcpy(buf, str, sizeof(buf));
  if (buf[0] == 'F' && buf[1] == 'U' && buf[2] == 'Z' && buf[3] == 'Z') {
    return 1;
  }
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Call the vulnerable function with the input data
  foo(reinterpret_cast<const char*>(data));
  return 0;
}
