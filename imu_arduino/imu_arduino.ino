#include <M5StickC.h>
// #include <M5Stack.h>
float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll = 0.0F;
float yaw = 0.0F;

void setup() {
  M5.begin();
  // M5.setTextColor(RED);
  // M5.Lcd.print("Program init...");
  M5.Lcd.fillScreen(BLACK);
  M5.Axp.ScreenBreath(15);
  // M5.Lcd.setBrightness(10);
  // M5.Lcd.print("Press btn...");
  M5.update();
  // while (!M5.BtnA.wasReleased())
  //   ;

  M5.IMU.Init();
  M5.Lcd.setRotation(3);
  M5.Lcd.setCursor(40, 0);
  M5.Lcd.println("IMU TEST");
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.println("   X       Y       Z");
  M5.Lcd.setCursor(0, 50);
  M5.Lcd.println("  Pitch   Roll    Yaw");
  
  Serial.begin(115200);
}

void loop() {
  float temp = 0;
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);
  M5.IMU.getTempData(&temp);

  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("%6.2f  %6.2f  %6.2f o/s\n", gyroX, gyroY, gyroZ);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f G\n\n\n\n", accX, accY, accZ);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f\n", pitch, roll, yaw);
  M5.Lcd.printf("Temperature : %.2f C", temp);
  
  Serial.printf("%6.2f  %6.2f  %6.2f o/s\n", gyroX, gyroY, gyroZ);
  Serial.printf(" %5.2f   %5.2f   %5.2f G\n\n\n\n", accX, accY, accZ);
  Serial.printf(" %5.2f   %5.2f   %5.2f\n", pitch, roll, yaw);
  Serial.printf("Temperature : %.2f C", temp);

  delay(10);
}
