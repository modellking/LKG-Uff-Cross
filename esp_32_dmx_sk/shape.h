#ifndef SH_H
#define SH_H 1

#include "LUTBuilder.h"
#include "preferences.h"
#include "utility.h"

const int sh_order[] = { SHds-SH_off, SHos, SHds, \
  SHrs, SHos, SHrs, \
  SHts, SHos, SHts, \
  SHls, SHos, SHls, \
  SH_off
};
int sh_sum[SIZEOF(sh_order)];

LUTBuilder maskb, maskr, maskt, maskl;

void shapeInit() {
  int runningSum = 0;
  for (int j = 0; runningSum < LED_COUNT; j++) {
    runningSum += sh_order[j];
    sh_sum[j] = runningSum;
  }

  maskb.addDescriptor(1, 0, sh_sum[2]-1);
  maskb.addDescriptor(1, sh_sum[11], sh_sum[12]-1);

  maskr.addDescriptor(1, sh_sum[2], sh_sum[5]-1);
  
  maskt.addDescriptor(1, sh_sum[5], sh_sum[8]-1);
  
  maskl.addDescriptor(1, sh_sum[8], sh_sum[11]-1);
}

class Pointf {
  public:
      float x, y;
      Point() : x(0f), y(0f) {}
      Point(float x, float y) : x(x), y(y) {}
}

static Pointf[] shapePoints = SHAPEPOINTS;

static (void (*)(void)) shapeEffectToEffect(float (*shape) (float,float,float)) {
  
}

#endif
