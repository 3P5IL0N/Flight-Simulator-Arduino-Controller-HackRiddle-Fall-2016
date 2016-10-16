#include <BMI160.h>
#include <CurieIMU.h>

double totX=0, totY=0;
int i=0, c=0, Accpos=2;

void setup() {
  // put your setup code here, to run once:
  CurieIMU.begin();
  Serial.begin(9600);
  CurieIMU.autoCalibrateGyroOffset();
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.setGyroRate(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  int rawX, rawY, Acc, trash;
  double X,Y;
  int Xpos, Ypos;
  
  CurieIMU.readGyro(rawX, rawY, trash);
  X=(rawX/32768.9)*CurieIMU.getGyroRange();
  Y=(rawY/32768.9)*CurieIMU.getGyroRange();
  
  if (-8<X && X<8)
    X=0;
  if (-8<Y && Y<8)
    Y=0;
  
  totX += X*.005;
  totY += Y*-.005;
  
  Xpos=(totX+270)/135;
  Ypos=(totY+270)/135;
  
  if (Xpos>4)Xpos=4;
  else if (Xpos<0)Xpos=0;
  if (Ypos>4)Ypos=4;
  else if (Ypos<0)Ypos=0;

  CurieIMU.readAccelerometer(Acc, trash, trash);
  if ((Acc>10000 || Acc<-10000) && c==0)
    c=300;
  if (Acc>10000 && Accpos<4 && c==300)
    Accpos+=1;
  else if (Acc<-10000 && Accpos>0 && c==300)
    Accpos-=1;

  if (c!=0) c--;
  else Accpos=2;


    
  i++;
  if (i%10==0)
  {
    i-=10;
    Serial.print(Xpos);
    Serial.print(" ");
    Serial.print(Ypos);
    Serial.print(" ");
    Serial.println(Accpos);
  }
}
