// #include <Arduino.h>
#include <M5StickC.h>

static const uint8_t buttBpin = 33;
static const uint8_t buttApin = 32;
// int buttApress=0;
// int buttBpress=0;
void setup() {
  M5.begin();
  pinMode(buttBpin, INPUT);
  pinMode(buttApin, INPUT);
  M5.Lcd.fillScreen(BLACK);
  M5.Axp.ScreenBreath(15);
  M5.Lcd.setRotation(1);
  M5.update();
  M5.Lcd.setCursor(40, 0);
  M5.Lcd.println("Button Pressed:");
  M5.Lcd.setCursor(40, 20);

  Serial.begin(115200);
}

void loop() {
  int buttApress=0;
  int buttBpress=0;
  buttApress = !digitalRead(buttApin);
  buttBpress = !digitalRead(buttBpin);
  M5.update();
  M5.Lcd.setCursor(40, 0);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.println("Button Pressed:");
  M5.Lcd.setCursor(40, 20);
  if (buttApress == 1) {
    M5.Lcd.setTextColor(RED);
    M5.Lcd.print("Red butt pressed!");
    Serial.println("Red butts!");
  } else if (buttBpress == 1) {
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.print("Blue butt pressed!");
    Serial.println("Blue butts!");
  } else if (buttApress == 1 and buttBpress == 1) {
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.print("Both butts pressed!");
    Serial.println("Both butts!");
  } else {
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print("NO butt pressed :(");
    Serial.println("NOH butts :(");
  }
  delay(100);
  M5.Lcd.fillScreen(BLACK);

}
