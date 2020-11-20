void feathered_snake(RGBW color, RGBW background, float argu, int offs = 0) {
  float short_t = fmod((t / 64.0 + offs), LED_COUNT);
  float maxi = fmod(short_t + argu, LED_COUNT);
  feathered_wraping_fill(color, short_t, maxi, background);
}

void simple_snake(RGBW color, float argu, int offs = 0) {
  float short_t = fmod((t / 64 + offs), LED_COUNT);
  float maxi = fmod(short_t + argu, LED_COUNT);
  fill_rgbw_between_wrapping(color, short_t, maxi);
}

/**
 * Displays up to 3 Snakes on a background with variable length and time
 */
void snakes() {
  // Set background
  fill_rgbw(color_slots[1]);
  auto colors = std::vector<RGBW>(0);
  if (!Color::isBlack(color_slots[0])) {
    colors.push_back(color_slots[0]);
  }
  if (!Color::isBlack(color_slots[2])) {
    colors.push_back(color_slots[2]);
  }
  if (!Color::isBlack(color_slots[3])) {
    colors.push_back(color_slots[3]);
  }
  int colorsSize = colors.size();
  float argu = (argument_slots[color_slot] * LED_COUNT) / (255.0 * colorsSize);
  if (argu < 2) {
    fill_rgbw(color_slots[1]);
  } else if (LED_COUNT - argu * colorsSize < 2) {
    // todo this doesn't interpolate! (If you must interpolate only one snake with the next as background)
    for (int i = 0; i < colorsSize; i++) {
      simple_snake(colors[i], LED_COUNT / colorsSize, i * LED_COUNT / colorsSize);
    }
  } else {
    for (int i = 0; i < colorsSize; i++) {
      feathered_snake(colors[i], color_slots[1], argu, i * LED_COUNT / colorsSize);
    }
  }
}
