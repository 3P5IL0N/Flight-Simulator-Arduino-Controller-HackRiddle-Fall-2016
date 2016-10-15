#include <BMI160.h>
#include <CurieIMU.h>


void setup() {
  // put your setup code here, to run once:
  CurieIMU.begin();
  Serial.begin(9600);
  CurieIMU.autoCalibrateGyroOffset();
}

void loop() {
  // put your main code here, to run repeatedly:
  int rawX, rawY, trash;
  double X,Y;
  CurieIMU.readGyro(rawX, rawY, trash);
  X=(rawX/32768.9)*CurieIMU.getGyroRange();
  Y=(rawY/32768.9)*CurieIMU.getGyroRange();
  Serial.print(X);
  Serial.print(" ");
  Serial.println(Y);
}
