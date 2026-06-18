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

  // LEFT ^
  display.drawLine(20, 28, 26, 20, SH110X_WHITE);
  display.drawLine(26, 20, 32, 28, SH110X_WHITE);

  // RIGHT ^
  display.drawLine(96, 28, 102, 20, SH110X_WHITE);
  display.drawLine(102, 20, 108, 28, SH110X_WHITE);

  // HAPPY MOUTH .
  display.fillCircle(64, 42, 2, SH110X_WHITE);

  display.display();
}

void loop()
{
}