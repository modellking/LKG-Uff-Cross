void hue_rotate() {
  byte divisions = 3;
  int short_t = t / 16;
  for (int i = 0; i < LED_COUNT; i++) {
    RGBW baseColor = Color::hsvwToRgbw(HSVW(1.0f * (i+short_t) / (LED_COUNT/divisions), 1.0f, 1.0f));
    RGBW mixColor = Color::mixRgbw(baseColor, color_slots[0], argument_slots[color_slot] / 255.0f);
    strip.color32(i, Color::rgbwToBits(mixColor));
  }
}
