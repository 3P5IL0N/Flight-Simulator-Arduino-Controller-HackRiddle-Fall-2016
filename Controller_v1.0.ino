#include <BMI160.h>
#include <CurieIMU.h>


void setup() {
  // put your setup code here, to run once:
  CurieIMU.begin();
  Serial.begin(9600);
  CurieIMU.autoCalibrateGyroOffset();
  CurieIMU.setGyroRate(100);
  double totX=0, totY=0;
}

void loop() {
  // put your main code here, to run repeatedly:
  int rawX, rawY, trash;
  double X,Y;
  CurieIMU.readGyro(rawX, rawY, trash);
  X=(rawX/32768.9)*CurieIMU.getGyroRange();
  Y=(rawY/32768.9)*CurieIMU.getGyroRange();
  if (-10<X && X<10)
    X=0;
  if (-10<Y && Y<10)
    Y=0;
  totX+=X;
  totY+=Y;
  Serial.print(totX);
  Serial.print(" ");
  Serial.println(totY);
}
