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

  // LEFT EYE
  display.fillCircle(26, 24, 3, SH110X_WHITE);

  // LEFT BLUSH //
  display.drawLine(12, 35, 15, 31, SH110X_WHITE);
  display.drawLine(18, 35, 21, 31, SH110X_WHITE);

  // RIGHT EYE
  display.fillCircle(102, 24, 3, SH110X_WHITE);

  // RIGHT BLUSH //
  display.drawLine(107, 35, 110, 31, SH110X_WHITE);
  display.drawLine(113, 35, 116, 31, SH110X_WHITE);

  // MOUTH ___
  display.drawLine(58, 42, 70, 42, SH110X_WHITE);

  // QUESTION MARK
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(112, 10);
  display.print("?");

  display.display();
}

void loop()
{
}