#include <M5StickC.h>
int avg[10] = {0};
long timer,timer2;
boolean fix = 1;
boolean now = 1;
boolean wait = 0;
int start[10];
int ending[10];
double slope;
double avgstart, avgend;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  M5.begin();
  pinMode(G36,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int adc = analogRead(G36);

  for(int i = 0; i < 9; i++){
    avg[i] = avg[i+1];
  }

  avg[9] = adc;

  double average = 0;
  for(int i = 0; i < 10; i++){
    average = average + avg[i];
  }

  average = average/10.0;

  double diff = 0;

  for(int j = 0; j < 2 ;j++){
    diff = (average - avg[j]) * (average - avg[j]) + diff;
  }

  diff = diff/10.0;
  diff = sqrt(diff);

  /*
  if(diff < 5 && fix){
    fix = 0;
    //Serial.println("Calculating Drift Slope");
    int start[10];
    for(int i = 0; i < 10; i++){
      start[i] = analogRead(G36);
    }
    delay(5000);
    int ending[10];
    for(int i = 0; i < 10; i++){
      ending[i] = analogRead(G36);
    }

    
    
    for(int j = 0; j < 10; j++){
      avgstart = start[j]; 
      avgend = ending[j];
    }

    avgstart = avgstart/10;
    avgend = avgend/10;

    slope = (avgend - avgstart)/5000;
    timer = millis();
  }
  */
  

  if(now && (diff < 5)){
    now = 0;
    for(int i = 0; i < 10; i++){
      start[i] = analogRead(G36);
    }
    wait = 1;
    timer2 = millis(); 
    timer = millis();
  
  }

  if(((millis() - timer2) > 5000) && wait){
    wait = 0;
    for(int i = 0; i < 20; i++){
      ending[i] = analogRead(G36);
    }
    avgstart = avgend = 0;
    for(int j = 0; j < 20; j++){
      avgstart = avgstart + start[j]; 
      avgend = avgend + ending[j];
    }
    
    avgstart = avgstart/20;
    avgend = avgend/20;

    slope = (avgend - avgstart)/5000.0;
    timer = millis();
  }
  
  double adjust = slope*(millis() - timer);
  double adjusted = adc - adjust;
  if ((millis() - timer) > 20000)
    now = 1;

  
  /*
  //Serial.print("adc: ");Serial.println(adc);
  //Serial.print("adc adjusted: "); Serial.println(adjusted);

  Serial.print("X1: "); Serial.println(avgstart);
  Serial.print("X2: "); Serial.println(avgend);
  //Serial.print("slope: "); Serial.println(slope);
  Serial.println(now);
  //Serial.print("average: ");Serial.println(average);
  Serial.print("diff: ");Serial.println(diff);
  Serial.println(" ");
  */
   
  Serial.print("adc:");Serial.print(adc);
  Serial.print("\t");
  Serial.print("adjusted:");Serial.println(adjusted);
  
  delay(100);
  
}
