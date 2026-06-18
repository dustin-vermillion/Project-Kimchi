#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
  Wire.begin(21, 22);

  if (!display.begin(0x3C, true))
  {
    while (1);
  }

  display.clearDisplay();

  // =====================
  // LEFT EYE ˃
  // =====================

  display.drawLine(22, 22, 30, 24, SH110X_WHITE);
  display.drawLine(22, 26, 30, 24, SH110X_WHITE);

  // =====================
  // RIGHT EYE ˂
  // =====================

  display.drawLine(98, 24, 106, 22, SH110X_WHITE);
  display.drawLine(98, 24, 106, 26, SH110X_WHITE);

  // =====================
  // LEFT BLUSH //
  // =====================

  display.drawLine(14, 36, 17, 33, SH110X_WHITE);
  display.drawLine(20, 36, 23, 33, SH110X_WHITE);

  // =====================
  // RIGHT BLUSH //
  // =====================

  display.drawLine(105, 36, 108, 33, SH110X_WHITE);
  display.drawLine(111, 36, 114, 33, SH110X_WHITE);

  // =====================
  // MOUTH ᵕ
  // =====================

  display.drawLine(59, 40, 62, 43, SH110X_WHITE);
  display.drawLine(62, 43, 66, 43, SH110X_WHITE);
  display.drawLine(66, 43, 69, 40, SH110X_WHITE);

  // =====================
  // HEART OUTLINE ♡
  // Bottom-right corner
  // =====================

  display.drawCircle(112, 54, 2, SH110X_WHITE);
  display.drawCircle(118, 54, 2, SH110X_WHITE);

  display.drawLine(110, 56, 115, 62, SH110X_WHITE);
  display.drawLine(120, 56, 115, 62, SH110X_WHITE);

  display.display();
}

void loop()
{
}