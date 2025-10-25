//reg number :23-ntu-cs-1042
// name : mahnoor shahid 
//week 5 buzzer task 

#include <Arduino.h>

// Pins
#define BUZZER_PIN 27
#define LED1_PIN   18
#define LED2_PIN   19

// LEDC channels
#define CH_BUZZER  0   // buzzer channel
#define CH_LED1    1   // LED on pin 18
#define CH_LED2    2   // LED on pin 19

// Channel settings (different frequencies)
#define BUZZER_BASE_FREQ  2000   // Hz
#define LED1_FREQ         3000   // Hz
#define LED2_FREQ         1000   // Hz

// Resolution for PWM
#define BUZZER_RES 10    // 10-bit = 0–1023
#define LED_RES     8    // 8-bit = 0–255

// LED fade step
const uint8_t LED_STEP = 2;

// Globals for LED states
int led1_brightness = 0;
int led2_brightness = 255;
int led1_dir = 1; // 1 = up, -1 = down
int led2_dir = -1;

// Function to smoothly fade LEDs
void updateLEDsStep() {
  // update LED1
  if (led1_dir == 1) {
    led1_brightness += LED_STEP;
    if (led1_brightness >= 255) {
      led1_brightness = 255;
      led1_dir = -1;
    }
  } else {
    led1_brightness -= LED_STEP;
    if (led1_brightness <= 0) {
      led1_brightness = 0;
      led1_dir = 1;
    }
  }
  ledcWrite(CH_LED1, led1_brightness);

  // update LED2
  if (led2_dir == 1) {
    led2_brightness += LED_STEP;
    if (led2_brightness >= 255) {
      led2_brightness = 255;
      led2_dir = -1;
    }
  } else {
    led2_brightness -= LED_STEP;
    if (led2_brightness <= 0) {
      led2_brightness = 0;
      led2_dir = 1;
    }
  }
  ledcWrite(CH_LED2, led2_brightness);
}

void setup() {
  // --- Setup buzzer ---
  ledcSetup(CH_BUZZER, BUZZER_BASE_FREQ, BUZZER_RES);
  ledcAttachPin(BUZZER_PIN, CH_BUZZER);

  // --- Setup LEDs with different base frequencies ---
  ledcSetup(CH_LED1, LED1_FREQ, LED_RES);
  ledcAttachPin(LED1_PIN, CH_LED1);

  ledcSetup(CH_LED2, LED2_FREQ, LED_RES);
  ledcAttachPin(LED2_PIN, CH_LED2);

  // Initialize LEDs
  ledcWrite(CH_LED1, led1_brightness);
  ledcWrite(CH_LED2, led2_brightness);
}

void loop() {
  // --- 1. Simple beep pattern (3 beeps) ---
  for (int i = 0; i < 3; i++) {
    ledcWriteTone(CH_BUZZER, 1500 + i * 500);  // different frequency pattern for buzzer
    for (int t = 0; t < 15; t++) {
      updateLEDsStep();
      delay(10);
    }

    ledcWrite(CH_BUZZER, 0);
    for (int t = 0; t < 15; t++) {
      updateLEDsStep();
      delay(10);
    }
  }

  delay(300);

  // --- 2. Frequency sweep for buzzer ---
  for (int f = 400; f <= 3000; f += 100) {
    ledcWriteTone(CH_BUZZER, f);
    updateLEDsStep();
    delay(20);
  }
  ledcWrite(CH_BUZZER, 0);
  delay(400);

  // --- 3. Melody with LED variations ---
  int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
  const int notes = sizeof(melody) / sizeof(melody[0]);
  for (int i = 0; i < notes; i++) {
    ledcWriteTone(CH_BUZZER, melody[i]);

    // While tone plays, vary LED frequencies slightly for effect
    ledcSetup(CH_LED1, LED1_FREQ + i * 200, LED_RES);
    ledcSetup(CH_LED2, LED2_FREQ + i * 100, LED_RES);

    for (int t = 0; t < 25; t++) {
      updateLEDsStep();
      delay(10);
    }

    ledcWrite(CH_BUZZER, 0);
    for (int t = 0; t < 5; t++) {
      updateLEDsStep();
      delay(10);
    }
  }

  ledcWrite(CH_BUZZER, 0);

  // pause before repeating
  for (int t = 0; t < 100; t++) {
    updateLEDsStep();
    delay(10);
  }
}
