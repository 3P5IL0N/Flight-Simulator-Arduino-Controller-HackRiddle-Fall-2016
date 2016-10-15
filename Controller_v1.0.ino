#include <BMI160.h>
#include <CurieIMU.h>

double totX=0, totY=0;

void setup() {
  // put your setup code here, to run once:
  CurieIMU.begin();
  Serial.begin(9600);
  CurieIMU.autoCalibrateGyroOffset();
  CurieIMU.setGyroRate(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  int rawX, rawY, trash;
  double X,Y;
  CurieIMU.readGyro(rawX, rawY, trash);
  X=(rawX/32768.9)*CurieIMU.getGyroRange();
  Y=(rawY/32768.9)*CurieIMU.getGyroRange();
  if (-3<X && X<3)
    X=0;
  if (-3<Y && Y<3)
    Y=0;
  totX+=(X*.01);
  totY+=(Y*.01);
  Serial.print(totX);
  Serial.print(" ");
  Serial.println(totY);
}
