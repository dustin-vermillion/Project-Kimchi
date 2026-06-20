#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

enum Emotion
{
  IDLE,
  HAPPY,
  EXCITED,
  CONFUSED,
  LOVE,
  SHOCKED,
  ANGRY,
  SHY,
  SAD
};

Emotion currentEmotion = IDLE;
Emotion temporaryEmotion = IDLE;
const int TOUCH_PIN = 4;

bool lastTouchState = LOW;

unsigned long lastTouchTime = 0;
unsigned long lastMoodDecay = 0;
unsigned long angerStartTime = 0;
bool angerActive = false;
unsigned long temporaryEmotionEnd = 0;
unsigned long lastPetTime = 0;
int touchCount = 0;

int reunionStage = 0;
unsigned long reunionTimer = 0;

struct Mood
{
  int affection;
  int energy;
  int social;
  int stress;
};

Mood kimchi =
{
  50, // affection
  50, // energy
  50, // social
  0   // stress
};

// ======================================================
// FUNCTION DECLARATIONS
// ======================================================

void drawIdle();
void drawHappy();
void drawExcited();
void drawConfused();
void drawLove();
void drawShocked();
void drawAngry();
void drawShy();
void drawSad();
void updateMood();
void drawFace(Emotion emotion);
void setEmotion(Emotion emotion);
Emotion decideEmotion();
const char* emotionToString(Emotion emotion);
void printMood();
void updateMood();
void triggerEmotion(Emotion emotion, int duration);

void handleTouch();
// ======================================================
// SETUP
// ======================================================

void setup()
{
  Serial.begin(115200);

  Wire.begin(21, 22);

  if (!display.begin(0x3C, true))
  {
    while (1);
  }

  display.clearDisplay();
  display.display();
  pinMode(TOUCH_PIN, INPUT);
}

// ======================================================
// LOOP
// ======================================================

void loop()
{
  handleTouch();

  updateMood();

  // SHOCKED -> SHY -> LOVE sequence
  if (reunionStage == 1 &&
      millis() - reunionTimer > 1500)
  {
    reunionStage = 2;
    reunionTimer = millis();

    triggerEmotion(SHY, 2500);
  }

  if (reunionStage == 2 &&
      millis() - reunionTimer > 2500)
  {
    reunionStage = 3;
    reunionTimer = millis();

    triggerEmotion(LOVE, 2000);
  }

  if (reunionStage == 3 &&
      millis() - reunionTimer > 2000)
  {
    reunionStage = 0;
  }

  currentEmotion = decideEmotion();

  drawFace(currentEmotion);

  printMood();

  delay(100);
}

// ======================================================
// EMOTION ENGINE
// ======================================================

void setEmotion(Emotion emotion)
{
  currentEmotion = emotion;
  drawFace(currentEmotion);
}

void triggerEmotion(Emotion emotion, int duration)
{
  temporaryEmotion = emotion;
  temporaryEmotionEnd = millis() + duration;
}

void drawFace(Emotion emotion)
{
  switch (emotion)
  {
    case IDLE:
      drawIdle();
      break;

    case HAPPY:
      drawHappy();
      break;

    case EXCITED:
      drawExcited();
      break;

    case CONFUSED:
      drawConfused();
      break;

    case LOVE:
      drawLove();
      break;

    case SHOCKED:
      drawShocked();
      break;

    case ANGRY:
      drawAngry();
      break;

    case SHY:
      drawShy();
      break;

    case SAD:
      drawSad();
      break;
  }
}

Emotion decideEmotion()
{
  if (temporaryEmotion != IDLE &&
      millis() < temporaryEmotionEnd)
  {
    return temporaryEmotion;
  }

  if (angerActive)
{
  if (millis() - angerStartTime < 5000)
  {
    return ANGRY;
  }

  angerActive = false;
  kimchi.stress = 40;
}

  if (kimchi.social < 20)
  {
    return SAD;
  }

  if (millis() - lastPetTime > 60000)
{
  return SAD;
}

return IDLE;

  return IDLE;
}

const char* emotionToString(Emotion emotion)
{
  switch (emotion)
  {
    case IDLE: return "IDLE";
    case HAPPY: return "HAPPY";
    case EXCITED: return "EXCITED";
    case CONFUSED: return "CONFUSED";
    case LOVE: return "LOVE";
    case SHOCKED: return "SHOCKED";
    case ANGRY: return "ANGRY";
    case SHY: return "SHY";
    case SAD: return "SAD";
    default: return "UNKNOWN";
  }
}

void printMood()
{
  static unsigned long lastPrint = 0;

  if (millis() - lastPrint < 1000)
    return;

  lastPrint = millis();

  Serial.print("Emotion: ");
  Serial.print(emotionToString(currentEmotion));

  Serial.print(" | Affection: ");
  Serial.print(kimchi.affection);

  Serial.print(" | Energy: ");
  Serial.print(kimchi.energy);

  Serial.print(" | Social: ");
  Serial.print(kimchi.social);

  Serial.print(" | Stress: ");
  Serial.println(kimchi.stress);
}

void handleTouch()
{
  bool touchState = digitalRead(TOUCH_PIN);

  if (touchState == HIGH && lastTouchState == LOW)
  {
    // Sad reunion sequence
    if (millis() - lastPetTime > 60000)
    {
      reunionStage = 1;
      reunionTimer = millis();

      triggerEmotion(SHOCKED, 1500);
    }
    else
    {
      touchCount++;

      if (touchCount >= 5)
      {
        triggerEmotion(EXCITED, 3000);
        touchCount = 0;
      }
      else
      {
        triggerEmotion(LOVE, 2000);
      }
    }

    kimchi.social = 100;

    if (millis() - lastTouchTime < 1000)
    {
      kimchi.stress += 15;

      if (kimchi.stress > 80 && !angerActive)
      {
        angerActive = true;
        angerStartTime = millis();
      }
    }

    lastTouchTime = millis();
    lastPetTime = millis();

    kimchi.stress = constrain(kimchi.stress, 0, 100);
  }

  lastTouchState = touchState;
}

void updateMood()
{
  if (millis() - lastMoodDecay < 10000)
    return;

  lastMoodDecay = millis();

  kimchi.social -= 1;
  kimchi.energy -= 1;

  if (kimchi.stress > 0)
    kimchi.stress -= 2;

  kimchi.affection = constrain(kimchi.affection, 0, 100);
  kimchi.energy = constrain(kimchi.energy, 0, 100);
  kimchi.social = constrain(kimchi.social, 0, 100);
  kimchi.stress = constrain(kimchi.stress, 0, 100);
}

// ======================================================
// IDLE
// ======================================================

void drawIdle()
{
  display.clearDisplay();

  display.drawLine(20, 28, 26, 20, SH110X_WHITE);
  display.drawLine(26, 20, 32, 28, SH110X_WHITE);

  display.drawLine(96, 28, 102, 20, SH110X_WHITE);
  display.drawLine(102, 20, 108, 28, SH110X_WHITE);

  display.drawLine(58, 42, 70, 42, SH110X_WHITE);

  display.display();
}

// ======================================================
// HAPPY
// ======================================================

void drawHappy()
{
  display.clearDisplay();

  display.drawLine(20, 28, 26, 20, SH110X_WHITE);
  display.drawLine(26, 20, 32, 28, SH110X_WHITE);

  display.drawLine(96, 28, 102, 20, SH110X_WHITE);
  display.drawLine(102, 20, 108, 28, SH110X_WHITE);

  display.fillCircle(64, 42, 2, SH110X_WHITE);

  display.display();
}

// ======================================================
// EXCITED
// ======================================================

void drawExcited()
{
  display.clearDisplay();

  display.drawLine(20, 28, 26, 20, SH110X_WHITE);
  display.drawLine(26, 20, 32, 28, SH110X_WHITE);

  display.drawLine(96, 28, 102, 20, SH110X_WHITE);
  display.drawLine(102, 20, 108, 28, SH110X_WHITE);

  display.drawCircle(64, 42, 4, SH110X_WHITE);

  display.display();
}

// ======================================================
// CONFUSED
// ======================================================

void drawConfused()
{
  display.clearDisplay();

  display.fillCircle(26, 24, 3, SH110X_WHITE);

  display.drawLine(12, 35, 15, 31, SH110X_WHITE);
  display.drawLine(18, 35, 21, 31, SH110X_WHITE);

  display.fillCircle(102, 24, 3, SH110X_WHITE);

  display.drawLine(107, 35, 110, 31, SH110X_WHITE);
  display.drawLine(113, 35, 116, 31, SH110X_WHITE);

  display.drawLine(58, 42, 70, 42, SH110X_WHITE);

  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(112, 10);
  display.print("?");

  display.display();
}

// ======================================================
// LOVE
// ======================================================

void drawLove()
{
  display.clearDisplay();

  display.drawLine(22, 22, 30, 24, SH110X_WHITE);
  display.drawLine(22, 26, 30, 24, SH110X_WHITE);

  display.drawLine(98, 24, 106, 22, SH110X_WHITE);
  display.drawLine(98, 24, 106, 26, SH110X_WHITE);

  display.drawLine(14, 36, 17, 33, SH110X_WHITE);
  display.drawLine(20, 36, 23, 33, SH110X_WHITE);

  display.drawLine(105, 36, 108, 33, SH110X_WHITE);
  display.drawLine(111, 36, 114, 33, SH110X_WHITE);

  display.drawLine(59, 40, 62, 43, SH110X_WHITE);
  display.drawLine(62, 43, 66, 43, SH110X_WHITE);
  display.drawLine(66, 43, 69, 40, SH110X_WHITE);

  display.drawCircle(112, 54, 2, SH110X_WHITE);
  display.drawCircle(118, 54, 2, SH110X_WHITE);

  display.drawLine(110, 56, 115, 62, SH110X_WHITE);
  display.drawLine(120, 56, 115, 62, SH110X_WHITE);

  display.display();
}

// ======================================================
// SHOCKED
// ======================================================

void drawShocked()
{
  display.clearDisplay();

  display.drawCircle(26, 24, 3, SH110X_WHITE);
  display.drawCircle(102, 24, 3, SH110X_WHITE);

  display.drawRect(58, 36, 12, 12, SH110X_WHITE);

  display.drawLine(110, 48, 110, 58, SH110X_WHITE);
  display.fillCircle(110, 62, 1, SH110X_WHITE);

  display.drawLine(118, 48, 118, 58, SH110X_WHITE);
  display.fillCircle(118, 62, 1, SH110X_WHITE);

  display.display();
}

// ======================================================
// ANGRY
// ======================================================

void drawAngry()
{
  display.clearDisplay();

  display.drawLine(114, 4, 114, 16, SH110X_WHITE);
  display.drawLine(108, 10, 120, 10, SH110X_WHITE);
  display.drawLine(109, 5, 119, 15, SH110X_WHITE);
  display.drawLine(119, 5, 109, 15, SH110X_WHITE);

  display.drawLine(26, 14, 42, 18, SH110X_WHITE);
  display.drawLine(86, 18, 102, 14, SH110X_WHITE);

  display.fillCircle(34, 24, 3, SH110X_WHITE);
  display.fillCircle(94, 24, 3, SH110X_WHITE);

  display.drawLine(58, 42, 62, 38, SH110X_WHITE);
  display.drawLine(62, 38, 66, 38, SH110X_WHITE);
  display.drawLine(66, 38, 70, 42, SH110X_WHITE);

  display.display();
}

// ======================================================
// SHY
// ======================================================

void drawShy()
{
  display.clearDisplay();

  display.drawLine(22, 22, 30, 24, SH110X_WHITE);
  display.drawLine(22, 26, 30, 24, SH110X_WHITE);

  display.drawLine(98, 24, 106, 22, SH110X_WHITE);
  display.drawLine(98, 24, 106, 26, SH110X_WHITE);

  display.drawLine(10, 38, 14, 34, SH110X_WHITE);
  display.drawLine(16, 38, 20, 34, SH110X_WHITE);
  display.drawLine(22, 38, 26, 34, SH110X_WHITE);

  display.drawLine(102, 34, 106, 38, SH110X_WHITE);
  display.drawLine(108, 34, 112, 38, SH110X_WHITE);
  display.drawLine(114, 34, 118, 38, SH110X_WHITE);

  display.drawLine(58, 40, 61, 43, SH110X_WHITE);
  display.drawLine(61, 43, 64, 40, SH110X_WHITE);
  display.drawLine(64, 40, 67, 43, SH110X_WHITE);
  display.drawLine(67, 43, 70, 40, SH110X_WHITE);

  display.display();
}

// ======================================================
// SAD
// ======================================================

void drawSad()
{
  display.clearDisplay();

  display.drawLine(22, 18, 38, 18, SH110X_WHITE);
  display.drawLine(30, 18, 30, 34, SH110X_WHITE);

  display.drawLine(90, 18, 106, 18, SH110X_WHITE);
  display.drawLine(98, 18, 98, 34, SH110X_WHITE);

  display.drawLine(56, 46, 72, 46, SH110X_WHITE);

  display.display();
}