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
  // LEFT T
  // =====================

  display.drawLine(
    22, 18,
    38, 18,
    SH110X_WHITE
  );

  display.drawLine(
    30, 18,
    30, 34,
    SH110X_WHITE
  );

  // =====================
  // RIGHT T
  // =====================

  display.drawLine(
    90, 18,
    106, 18,
    SH110X_WHITE
  );

  display.drawLine(
    98, 18,
    98, 34,
    SH110X_WHITE
  );

  // =====================
  // MOUTH ___
  // =====================

  display.drawLine(
    56, 46,
    72, 46,
    SH110X_WHITE
  );

  display.display();
}

void loop()
{
}