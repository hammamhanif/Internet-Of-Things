
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL619Xllb8"
#define BLYNK_DEVICE_NAME "Projek"
#define BLYNK_AUTH_TOKEN "6-3D1EFiBBvSIQEUBLV5-s9BS3v7Ek52"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <HCSR04.h>
#include <Stepper.h>

#define trigPin D7
#define echoPin D6

#define D0 16
#define D1 5
#define D2 4
#define D3 0

const float STEPS_PER_REV = 32;
//  Amount of Gear Reduction
const float GEAR_RED = 64;
// Number of steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;
Stepper steppermotor(STEPS_PER_REV, D0, D2, D1, D3);
int StepsRequired = 0;
//int StepRequired2 =0;

int dataSwitch;
long duration;
int distance;

//PASTE KODE TOKEN EMAIL
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "realme 7i";       // NAMA WIFI
char pass[] = "123456789";// PAS WIFI

SimpleTimer timer; 


//void myTimerEvent() {
//  Blynk.virtualWrite(V3, millis() / 1000);
//}
void setup()
{
  Serial.begin(115200);
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Blynk.begin(auth, ssid, pass,"blynk.cloud", 8080);
  timer.setInterval(1000L, ultraSonic);
//   timer.setInterval(5000L, BLYNK_WRITE(V0));
}
void ultraSonic(){
    
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.println(distance);
  
  String buka = "Terbuka"; 
  String tutup = "Tertutup";
  if(distance < 5){
    Blynk.virtualWrite(V1,tutup);
  }
  else{
    Blynk.virtualWrite(V1,buka);
    }
  }

BLYNK_WRITE(V0) {
  dataSwitch = param.asInt();
  if (dataSwitch == 1 ) {
   StepsRequired  =  1100;
   steppermotor.setSpeed(1000);  
   steppermotor.step(StepsRequired);
   delay(3000);
   if(distance < 10){
    steppermotor.step(-1100);

  }
  else {
   steppermotor.step(0);
  }
}
}
BLYNK_WRITE(V2) {
  dataSwitch = param.asInt();
  if (dataSwitch == 1) {
   StepsRequired  =  2600;
   steppermotor.setSpeed(1000);  
   steppermotor.step(StepsRequired);
   delay(3000);
   if(distance < 10){
    steppermotor.step(-2600);
  }
  else {
   steppermotor.step(0);
  }
}
}

void loop()
{
  Blynk.run();
  timer.run();
}
