/*
 * Partially from https://github.com/ratkins/RGBConverter
 */
class RGBW {
  public:
    RGBW() {}
    RGBW(byte R, byte G, byte B, byte W = 0) {
      r = R; g = G; b = B; w = W;
    }
    byte r,g,b,w = 0;
};
class HSVW {
  public:
    HSVW() {}
    HSVW(float H, float S, float V, byte W = 0) {
      h = H; s = S; v = V; w = W;
    }
    float h,s,v;
    byte w;
};

class Color {
  public:
static RGBW getBlack()     {return RGBW(0,0,0,0);}
static RGBW getWhite()     {return RGBW(0xff,0xff,0xff,0xff);}
static RGBW getWarmWhite() {return RGBW(0xff,0x22,0,0xff);}
static RGBW getColdWhite() {return RGBW(0xee,0xff,0xff);}
static RGBW getRGBWhite()  {return RGBW(0xff,0xff,0xff);}

static RGBW bitsToRgbw(uint32_t bits) {
  byte* bytes = (byte*) &bits;
  return RGBW(bytes[0],bytes[1],bytes[2],bytes[3]);
}
static HSVW rgbwToHsvw(RGBW rgbw) {
  double rd = (double) rgbw.r/255;
  double gd = (double) rgbw.g/255;
  double bd = (double) rgbw.b/255;
  double max = threeway_max(rd, gd, bd), min = threeway_min(rd, gd, bd);
  double h, s, v = max;

  double d = max - min;
  s = max == 0 ? 0 : d / max;

  if (max == min) { 
      h = 0; // achromatic
  } else {
      if (max == rd) {
          h = (gd - bd) / d + (gd < bd ? 6 : 0);
      } else if (max == gd) {
          h = (bd - rd) / d + 2;
      } else if (max == bd) {
          h = (rd - gd) / d + 4;
      }
      h /= 6;
  }

  return HSVW(h,s,v,rgbw.w);
}
static RGBW hsvwToRgbw(HSVW hsvw) {
  float h = hsvw.h;
  float s = hsvw.s;
  float v = hsvw.v;
  double r, g, b;

  int i = int(h * 6);
  double f = h * 6 - i;
  double p = v * (1 - s);
  double q = v * (1 - f * s);
  double t = v * (1 - (1 - f) * s);

  switch(i % 6){
      case 0: r = v, g = t, b = p; break;
      case 1: r = q, g = v, b = p; break;
      case 2: r = p, g = v, b = t; break;
      case 3: r = p, g = q, b = v; break;
      case 4: r = t, g = p, b = v; break;
      case 5: r = v, g = p, b = q; break;
  }

  return RGBW(r*255,g*255,b*255,hsvw.w);
}
static RGBW mixRgbw(RGBW colOne, RGBW colTwo, float fac) {
  return RGBW(
    fac * colOne.r + (1.0f-fac) * colTwo.r,
    fac * colOne.g + (1.0f-fac) * colTwo.g,
    fac * colOne.b + (1.0f-fac) * colTwo.b,
    fac * colOne.w + (1.0f-fac) * colTwo.w
  );
}
static uint32_t rgbwToBits(RGBW rgbw) {
  uint32_t  kleur=0;
  kleur |= ((uint32_t)rgbw.g<<24);
  kleur |= ((uint32_t)rgbw.r<<16);
  kleur |= ((uint32_t)rgbw.b<<8);
  kleur |= (uint32_t)rgbw.w; 
  return kleur;
}
static bool isBlack(RGBW rgbw) {
  return 0 == (rgbw.r + rgbw.g + rgbw.b + rgbw.w);
}
private:
static double hue2rgb(double p, double q, double t) {
    if(t < 0) t += 1;
    if(t > 1) t -= 1;
    if(t < 1/6.0) return p + (q - p) * 6 * t;
    if(t < 1/2.0) return q;
    if(t < 2/3.0) return p + (q - p) * (2/3.0 - t) * 6;
    return p;
}
static double threeway_max(double a, double b, double c) {
    return max(a, max(b, c));
}

static double threeway_min(double a, double b, double c) {
    return min(a, min(b, c));
}
};
