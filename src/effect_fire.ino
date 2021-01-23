/*byte fireLut[LED_COUNT] = {
51, 50, 49, 48, 47, 54, 53, 52, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,
0, 0, 0, 0, 0, 0, 0,
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 50, 49, 51, 54, 55, 60, 52, 53, 61, 62, 56, 57, 58, 59, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
};

void fire() {
  int short_t = abs(t) % (LED_COUNT / 4);
  
  RGBW rgbw = color_slots[0];
  RGBW rgbw2 = color_slots[2];
  RGBW rgbw3 = color_slots[3];
  RGBW rgbwB = color_slots[1];

  if (Color::isBlack(rgbw2)) {
    rgbw2 = Color::mixRgbw(rgbw, Color::getWhite(), 0.3);
  }
  
  fill_rgbw(rgbwB);

  for (int i = 0; i < 51+7+73; i++) {
    if (fireLut[i] < random(67,73)) {
      //strip.color(i,rgbw.r,rgbw.g,rgbw.b,rgbw.w);
    }
    if (fireLut[i] < random(25,34)) {
      //strip.color(i,rgbw2.r,rgbw2.g,rgbw2.b,rgbw2.w);
    }
    if (fireLut[i] < random(10,13)) {
      //strip.color(i,rgbw3.r,rgbw3.g,rgbw3.b,rgbw3.w);
    }
  }
}*/
