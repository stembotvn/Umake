#include "MakerKit.h"

MakerKit Umake;

void setup() {
  Serial.begin(115200);
}

void loop() {
  Umake.run();
}
