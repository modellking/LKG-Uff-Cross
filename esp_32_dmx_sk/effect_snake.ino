void simple_snake(RGBW color, byte argu, int offs = 0) {
  int short_t = (t / 64 + offs) % LED_COUNT;
  
  unsigned int maxi = short_t + argu;
  
  if (short_t + argu > LED_COUNT) {
    // run once for the overflowing pixels
    maxi = short_t + argu - LED_COUNT;
    for (int i = 0; i < maxi; i++) {
      strip.color(i,color.r,color.g,color.b,color.w);
    }
    // and stop overflow by restricting
    maxi = LED_COUNT;
  }
  
  for (int i = short_t; i < maxi; i++) {
    strip.color(i,color.r,color.g,color.b,color.w);
  }
}

/**
 * Displays up to 3 Snakes on a background with variable length and time
 */
void simple_snakes() {
  // Set background ( black for now
  fill_rgbw(color_slots[1]);
  auto colors = std::vector<RGBW>(3);
  if (!Color::isBlack(color_slots[0])) {
    colors[0] = color_slots[0];
  }
  if (!Color::isBlack(color_slots[2])) {
    colors[1] = color_slots[2];
  }
  if (!Color::isBlack(color_slots[3])) {
    colors[2] = color_slots[3];
  }
  int colorsSize = colors.size();
  byte argu = (argument_slots[color_slot] * LED_COUNT) / (255 * colorsSize);
  for (int i = 0; i < colorsSize; i++) {
    simple_snake(colors[i], argu, i * LED_COUNT / colorsSize);
  }
}
