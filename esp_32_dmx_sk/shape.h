#ifndef SH_H
#define SH_H 1

#include "LUTBuilder.h"
#include "preferences.cpp"

const int order[] = { SHds-SH_off, SHos, SHds, \
  SHrs, SHos, SHrs, \
  SHts, SHos, SHts, \
  SHls, SHos, SHls, \
  SH_off
};
int sum[sizeof(order) / sizeof(order[0])];

LUTBuilder maskb, maskr, maskt, maskl;

void shapeInit() {
  int runningSum = 0;
  for (int j = 0; runningSum < LED_COUNT; j++) {
    runningSum += order[j];
    sum[j] = runningSum;
  }

  maskb.addDescriptor(1, 0, sum[2]-1);
  maskb.addDescriptor(1, sum[11], sum[12]-1);

  maskr.addDescriptor(1, sum[2], sum[5]-1);
  
  maskt.addDescriptor(1, sum[5], sum[8]-1);
  
  maskl.addDescriptor(1, sum[8], sum[11]-1);
}
#endif
