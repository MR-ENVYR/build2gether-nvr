#include <M5StickC.h>
// #include <Keyboard.h>
// #include <hidkeyboard.h>
// #include <TinyUSB_Mouse_and_Keyboard.h>
using namespace std;
// using namespace esptinyusb;
// USBkeyboard Keyboard;

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll = 0.0F;
float yaw = 0.0F;

static const uint8_t buttBpin = 33;
static const uint8_t buttApin = 32;
int prog_pause = 1;

string rolling = "Flat";
string pitching = "Flat";
string Astr = "No press";
string Bstr = "No press";

void keywrites(){
  if (rolling == "left"){
    // Keyboard.press(KEY_LEFT_ARROW);
    
  }
  else if (rolling == "right"){
    // Keyboard.press(KEY_RIGHT_ARROW);
  }
  else {}

  if (pitching == "front"){
    // Keyboard.press(KEY_UP_ARROW);
  }
  else if (pitching == "back"){
    // Keyboard.press(KEY_BACK_ARROW);
  }
  else {}

  // Other buttons
  if (Astr=="pressed"){
    // Keyboard.press(KEY_LEFT_SHIFT);
  }
  
  if (Bstr=="pressed") {
  // Keyboard.press(KEY_LEFT_CTRL)
  }
}

void butt_pause(){
  if(prog_pause == 1){
    prog_pause = 0;
  }
  else{
    prog_pause = 1;
  }
}

void setup() {
  M5.begin();
  pinMode(buttBpin, INPUT);
  pinMode(buttApin, INPUT);
  M5.Lcd.fillScreen(BLACK);
  M5.Axp.ScreenBreath(15);
  M5.update();
  M5.IMU.Init();
  M5.Lcd.setRotation(1);
  M5.Lcd.setCursor(40, 0);
  M5.Lcd.println("Overall TEST");
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.println("   X       Y       Z");
  M5.Lcd.setCursor(0, 50);
  M5.Lcd.println("  Pitch   Roll    Yaw");
  Serial.begin(115200);
  // Keyboard.begin();
  // Keyboard.init();
  // Keyboard.begin(3);

}

void loop() {
  while(prog_pause == 1){
    if(digitalRead(M5_BUTTON_HOME) == 0){
      butt_pause();
    }
  }
  rolling = "Flat";
  pitching = "Flat";
  float temp = 0;

  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);
  M5.IMU.getTempData(&temp);

  int buttApress;
  int buttBpress;
  buttApress = !digitalRead(buttApin);
  buttBpress = !digitalRead(buttBpin);
  Astr = "No press";
  Bstr = "No press";

  if (buttApress == 1) {
    Astr = "Pressed";
  } 
  else {
    Astr = "No press";
  }

  if (buttBpress == 1) {
    Bstr = "Pressed";
  } 
  else {
    Bstr = "No press";  
  }

  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("%6.2f  %6.2f  %6.2f o/s\n", gyroX, gyroY, gyroZ);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f G\n\n\n\n", accX, accY, accZ);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f\n", pitch, roll, yaw);
  M5.Lcd.printf("Temperature : %.2f C", temp);
  
  // Serial.printf("%6.2f  %6.2f  %6.2f o/s\n", gyroX, gyroY, gyroZ);
  // Serial.printf(" %5.2f   %5.2f   %5.2f G\n\n\n\n", accX, accY, accZ);
  // Serial.printf(" %5.2f   %5.2f   %5.2f\n", pitch, roll, yaw);
  // Serial.printf("Temperature : %.2f C", temp);

  // Right and left tilts with roll
  if (roll > 15.0){
    rolling = "right";
  }
  else if (roll < -15.0) {
    rolling = "left";
  }
  else {
    rolling = "flat";
  }

  // Front and back tilts with pitch
  if (pitch > 15.0){
    pitching = "front";
  }
  else if (pitch < -15.0) {
    pitching = "back";
  }
  else {
    pitching = "flat";
  }

  // string serprint = "Roll: " + rolling + "\t" + "Pitch: " + pitching + "\t" + "Rbutt: " + Astr + "\t" + "Bbutt: " + Bstr + "\t";
  // Serial.println(serprint);
  Serial.printf("Roll: %s\tPitch: %s\tRbutt: %s\tBbutt: %s \n", rolling.c_str(), pitching.c_str(), Astr.c_str(), Bstr.c_str());

  // keywrites();

  delay(10);

}
