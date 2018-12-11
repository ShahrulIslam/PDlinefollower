
#include "MotorClassL.h"
long durationF, distanceF;

int ML=120;
int MR=120;
int MBL = 100;//left
   int MBR =100 ;//right
int sensorPin[]={A0,A1,A2,A3,A4,A5,A6,A7};
int a[8];
int lle=0;
int lre=0;
#define echoPinF 39       // Echo Pin
#define trigPinF 33 
MotorClassL mc;
void setup() {
 Serial.begin(115200);
 
   // sensorInit();
   
//    M1 = 70;
//    M2 = 110;
    //isMotorEnabled=true;
  pinMode(trigPinF, OUTPUT);
    pinMode(echoPinF, INPUT);
    
  for(int i=0;i<8;i++){
    pinMode(sensorPin[i],INPUT);
    
  }
//  int  KP=0.7;//.4
//  int  KD=0.6;// .6// put your setup code here, to run once:

}

void loop() {
  
 for(int i=0;i<8;i++)
{  if(analogRead(sensorPin[i])>550){
a[i]=0;//black
}
else{a[i]=1;}//white
Serial.print("\t");
Serial.print(a[i]);
} // put your main code here, to run repeatedly
int le=lefterror();
int re=righterror();
detection();
  if(distanceF<=15)
  {
 mc.motorForward(110,0);
 
  delay(500);
  mc.brake();
  delay(200);
  
  
  mc.motorForward(90,90);
  delay(500);
  mc.motorForward(90,140);
  delay(500);
   mc.motorForward(0,140);
  delay(200);
   mc.brake();
  delay(100);
  mc.motorForward(90,90);
delay(200);
  mc.motorForward(0,140);
  delay(500);
  mc.motorForward(90,90);
  delay(200);
  
  }
if(a[0]==0&&a[1]==0&&a[2]==0&&a[3]==0&&a[4]==0&&a[5]==0&&a[6]==0&&a[7]==0)
{
  
  while((a[0]==0&&a[1]==0&&a[2]==0&&a[3]==0&&a[4]==0&&a[5]==0&&a[6]==0&&a[7]==0))
{ for(int i=0;i<8;i++)
{  if(analogRead(sensorPin[i])>550){
a[i]=0;//black
}
else{a[i]=1;}}
Serial.println("left motr");
Serial.print(ML);
Serial.println("right motor");
Serial.print(MR);
if(ML>MR+20){
mc.motorForward(120,-50);}
if(MR>ML+20){mc.motorForward(-50,120);}
}
}
Serial.println();

//lle=lle-le;
//lre=lre-re;

MR=MBR+2.5*(le-re);
ML=MBL+2.5*(re-le);
Serial.println("left motr");
Serial.print(ML);
Serial.println("right motor");
Serial.print(MR);
mc.motorForward(ML,MR);
Serial.println();
 lle=le;
 lre=re;
}
int lefterror()
{int c=0;
  int ler=30*a[0]+20*a[1]+10*a[2];//+5*a[3];
return ler;}
int righterror()
{int c=0;
int rer=30*a[7]+20*a[6]+10*a[5];//+5*a[4];

return rer;}
void detection()
{
   digitalWrite(trigPinF, LOW); 
   delayMicroseconds(2); 
   digitalWrite(trigPinF, HIGH);
   delayMicroseconds(10); 
   digitalWrite(trigPinF, LOW);
   durationF = pulseIn(echoPinF, HIGH, 15000);
   distanceF = durationF/58.2;
   if(distanceF >= 0 && distanceF<=6) distanceF = 200;
}
