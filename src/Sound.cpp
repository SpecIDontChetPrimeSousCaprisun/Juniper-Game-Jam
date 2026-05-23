#include "Sound.h"

ma_engine Sound::engine;

void Sound::init() {
  if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
    std::cout << "Failed to initialize audio\n";
    return;
  }
}

void Sound::unInit() {
  ma_engine_uninit(&engine);
}

void Sound::playSound(const char* path) {
  ma_result result =
  ma_engine_play_sound(&engine, path, NULL);

  if (result != MA_SUCCESS) {
      std::cout << "Error: " << result << '\n';
  }
}


