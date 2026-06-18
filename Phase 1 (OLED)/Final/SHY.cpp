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
  // LEFT EYE >
  // =====================

  display.drawLine(22, 22, 30, 24, SH110X_WHITE);
  display.drawLine(22, 26, 30, 24, SH110X_WHITE);

  // =====================
  // RIGHT EYE <
  // =====================

  display.drawLine(98, 24, 106, 22, SH110X_WHITE);
  display.drawLine(98, 24, 106, 26, SH110X_WHITE);

  // =====================
  // LEFT BLUSH ///
  // =====================

  display.drawLine(10, 38, 14, 34, SH110X_WHITE);
  display.drawLine(16, 38, 20, 34, SH110X_WHITE);
  display.drawLine(22, 38, 26, 34, SH110X_WHITE);

  // =====================
  // RIGHT BLUSH ///
  // =====================

  display.drawLine(102, 34, 106, 38, SH110X_WHITE);
  display.drawLine(108, 34, 112, 38, SH110X_WHITE);
  display.drawLine(114, 34, 118, 38, SH110X_WHITE);

  // =====================
  // MOUTH ﹏
  // =====================

  display.drawLine(58, 40, 61, 43, SH110X_WHITE);
  display.drawLine(61, 43, 64, 40, SH110X_WHITE);
  display.drawLine(64, 40, 67, 43, SH110X_WHITE);
  display.drawLine(67, 43, 70, 40, SH110X_WHITE);

  display.display();
}

void loop()
{
}