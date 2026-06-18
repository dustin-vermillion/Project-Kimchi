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
  // ANGER SYMBOL 💢
  // =====================

  // Vertical
  display.drawLine(114, 4, 114, 16, SH110X_WHITE);

  // Horizontal
  display.drawLine(108, 10, 120, 10, SH110X_WHITE);

  // Diagonal \
  display.drawLine(109, 5, 119, 15, SH110X_WHITE);

  // Diagonal /
  display.drawLine(119, 5, 109, 15, SH110X_WHITE);

  // =====================
  // LEFT EYEBROW
  // =====================

  display.drawLine(
    26, 14,
    42, 18,
    SH110X_WHITE
  );

  // =====================
  // RIGHT EYEBROW
  // =====================

  display.drawLine(
    86, 18,
    102, 14,
    SH110X_WHITE
  );

  // =====================
  // LEFT EYE
  // =====================

  display.fillCircle(
    34, 24,
    3,
    SH110X_WHITE
  );

  // =====================
  // RIGHT EYE
  // =====================

  display.fillCircle(
    94, 24,
    3,
    SH110X_WHITE
  );

  // =====================
  // CUTE ANGRY MOUTH ᴖ
  // =====================

  display.drawLine(
    58, 42,
    62, 38,
    SH110X_WHITE
  );

  display.drawLine(
    62, 38,
    66, 38,
    SH110X_WHITE
  );

  display.drawLine(
    66, 38,
    70, 42,
    SH110X_WHITE
  );

  display.display();
}

void loop()
{
}