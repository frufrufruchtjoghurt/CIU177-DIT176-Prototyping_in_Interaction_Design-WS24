#include <Arduino.h>
#include <FastLED.h>

#define STAYING_ALIVE_BPM 104
#define SAD_SONG_BPM 60

#define NUM_LEDS 32
#define LED_STRIP_PIN 2
#define LED_TYPE NEOPIXEL
#define COLOR_ORDER GRB
#define BRIGHTNESS 255
#define UPDATES_PER_SECOND 100
CRGB leds[NUM_LEDS];

#define VIBRATION_PIN 3
#define VIBRATION_STRENGTH 135
#define VIBRATION_TIME 200

CRGBPalette16 currentPalette;
TBlendType currentBlending;

uint16_t bpm;
uint16_t bpmInterval;

// put function declarations here:
uint16_t bpmToTime(uint16_t bpm);
uint8_t calculateBrightness();
uint8_t calculateColorIndex();
void FillLEDsFromPaletteColors(uint8_t colorIndex, uint8_t brightness);
CRGBPalette16 generateRedAndPurplePalette();
CRGBPalette16 generateBlueAndDarkVioletPalette();

void setup()
{
  pinMode(VIBRATION_PIN, OUTPUT);

  // put your setup code here, to run once:
  FastLED.addLeds<LED_TYPE, LED_STRIP_PIN>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxRefreshRate(UPDATES_PER_SECOND);
  FastLED.clear();
  FastLED.show();

  currentPalette = generateRedAndPurplePalette();
  currentBlending = LINEARBLEND;

  bpm = STAYING_ALIVE_BPM;
  bpmInterval = bpmToTime(bpm);
}

void loop()
{
  // change brightness and color according to the beat
  uint8_t brightness = beatsin8(bpm, 5, 255);
  uint8_t colorIndex = beatsin8(bpm, 0, 16);
  uint8_t vibrate = beatsin8(bpm, 0, 100, -(bpmInterval / 90));

  if (vibrate > 70)
  {
    analogWrite(VIBRATION_PIN, VIBRATION_STRENGTH);
  }
  else
  {
    analogWrite(VIBRATION_PIN, 0);
  }

  FillLEDsFromPaletteColors(colorIndex, brightness);

  FastLED.show();

  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

uint16_t bpmToTime(uint16_t bpm)
{
  uint16_t interval = 60000 / bpm;
  return interval;
}

uint8_t calculateBrightness()
{
  // Use a sine wave to create a smooth fade in and out effect
  uint8_t brightness = (sin8(millis() / 10) + 2) / 2; // Adjust the divisor for speed
  return brightness;
}

uint8_t calculateColorIndex()
{
  // Use the same sine wave to sync color change with brightness
  uint8_t colorIndex = sin8(millis() / 10); // Adjust the divisor for speed
  return colorIndex;
}

void FillLEDsFromPaletteColors(uint8_t colorIndex, uint8_t brightness)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
  }
}

CRGBPalette16 generateRedAndPurplePalette()
{
  CRGBPalette16 palette = CRGBPalette16(
      CRGB::Red,
      CRGB::Purple,
      CRGB::Red);
  return palette;
}

CRGBPalette16 generateBlueAndDarkVioletPalette()
{
  CRGBPalette16 palette = CRGBPalette16(
      CRGB::Blue,
      CRGB::DarkViolet,
      CRGB::Blue);
  return palette;
}
