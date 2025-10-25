//week 4
//name :mahnoor shahid 
//reg number: 23-ntu-cs-1042

#include <Wire.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// ---- OLED setup ----
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Wire.begin(21, 22); // ESP32 default I2C pins (SDA=21, SCL=22)

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    // If initialization fails
    for (;;);
  }

  display.clearDisplay();

  // ---- Display Name and ID ----
  display.setTextSize(1);              // Normal text size
  display.setTextColor(SSD1306_WHITE); // White color
  display.setCursor(20, 20);           // Adjusted a little for name width
  display.println("Mahnoor");
  display.setCursor(10, 35);
  display.println(" 23-ntu-cs-1042");

  // Draw rectangle box around text
  display.drawRect(5, 15, 118, 40, SSD1306_WHITE);
  
  display.display();
}

void loop() {
  // Nothing to loop — static display
}
