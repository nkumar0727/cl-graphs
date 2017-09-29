#include <cstdio>

typedef unsigned u;

typedef struct bitf_1 {
  u u0  : 1; u u1  : 1; u u2  : 1; u u3  : 1;
  u u4  : 1; u u5  : 1; u u6  : 1; u u7  : 1;
  u u8  : 1; u u9  : 1; u u10 : 1; u u11 : 1;
  u u12 : 1; u u13 : 1; u u14 : 1; u u15 : 1;
  u u16 : 1; u u17 : 1; u u18 : 1; u u19 : 1;
  u u20 : 1; u u21 : 1; u u22 : 1; u u23 : 1;
  u u24 : 1; u u25 : 1; u u26 : 1; u u27 : 1;
  u u28 : 1; u u29 : 1; u u30 : 1; u u31 : 1;
} bitf_1;

bitf_1 arr[32];

int main() {
  bitf_1 field;
  printf("%lu\n",sizeof(arr));
  field.u0 = 1;
  printf("b0: %u\n",field.u0);
  return 0;
}
