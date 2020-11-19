void full() {
  fill_rgbw(color_slots[0]);
}

void fill_rgbw(RGBW rgbw) {
  fill_rgbw_between(rgbw, 0, LED_COUNT);
}

void fill_rgbw_between(RGBW rgbw, int start, int limit) {
  for (int i = start; i < limit; i++) {
    strip.color32(i,Color::rgbwToBits(rgbw));
  }
}

void feathered_fill(RGBW rgbw, float start, float limit, RGBW background) {
  fill_rgbw_between(rgbw, start +1, limit-1);
  int int_start = start;
  int int_limit = limit;
  
  strip.color32(int_start, Color::rgbwToBits(Color::mixRgbw(rgbw, background, start - int_start)));
  strip.color32(int_limit, Color::rgbwToBits(Color::mixRgbw(rgbw, background, limit - int_limit)));
}

void hue_rotate() {
  byte divisions = 3;
  int short_t = t / 16;
  for (int i = 0; i < LED_COUNT; i++) {
    RGBW baseColor = Color::hsvwToRgbw(HSVW(1.0f * (i+short_t) / (LED_COUNT/divisions), 1.0f, 1.0f));
    RGBW mixColor = Color::mixRgbw(baseColor, color_slots[0], argument_slots[color_slot] / 255.0f);
    strip.color32(i, Color::rgbwToBits(mixColor));
  }
}
