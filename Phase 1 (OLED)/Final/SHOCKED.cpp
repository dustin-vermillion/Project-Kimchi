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
  // LEFT EYE °
  // =====================

  display.drawCircle(26, 24, 3, SH110X_WHITE);

  // =====================
  // RIGHT EYE °
  // =====================

  display.drawCircle(102, 24, 3, SH110X_WHITE);

  // =====================
  // MOUTH ㅁ
  // =====================

  display.drawRect(
    58, 36,   // x, y
    12, 12,   // width, height
    SH110X_WHITE
  );

  // =====================
  // !!
  // =====================

  // First !
  display.drawLine(
    110, 48,
    110, 58,
    SH110X_WHITE
  );

  display.fillCircle(
    110, 62,
    1,
    SH110X_WHITE
  );

  // Second !
  display.drawLine(
    118, 48,
    118, 58,
    SH110X_WHITE
  );

  display.fillCircle(
    118, 62,
    1,
    SH110X_WHITE
  );

  display.display();
}

void loop()
{
}