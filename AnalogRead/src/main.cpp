#include <Arduino.h>

double Vin= 3286.0;
double R2= 3.3;
double buffer;
double R1op = 197800.0;
double R2op = 19900.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(G36,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int opampv = analogRead(G36);

  opampv = ((opampv/4095.0)*3300.0);

  buffer = ((R1op/R2op + 1.0)*(Vin*R2))/opampv;
  double opamp = buffer - R2;

  Serial.print("Voltage: ");Serial.println(opampv);
  Serial.print("Ohms: ");Serial.println(opamp);
  delay(500);
}