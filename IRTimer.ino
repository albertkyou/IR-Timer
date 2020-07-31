int IRSensorLeft = 2;
int IRSensorRight = 3;
int LED = 13;
unsigned long time;

void setup()
{
  
  pinMode (IRSensorLeft, INPUT);
  pinMode (LED, OUTPUT);
  Serial.begin(9600);
  
}
int idle = 1; //initial stage is idle and not armed
int armed = 0;
unsigned long start_time=0;
unsigned long stop_time=0;
unsigned long elapsed_time=0;
unsigned long trigger_time=0;

void loop()
{
  int statusSensorLeft = digitalRead (IRSensorLeft);
  int statusSensorRight = digitalRead (IRSensorRight);
  
  if (statusSensorLeft == 0 && statusSensorRight == 0) // trigger the IR sensor
  {
    if (idle == 1)
    {
      trigger_time = millis();
      digitalWrite(LED, HIGH);
      //Serial.println("armed"); //armed
      armed = 1; // arm the timer
      idle = 0; // timer is no longer idle
    }
    
    // timer stop
    if (idle == 0 && armed == 0)
    {
      //Serial.println("ended");
      stop_time = millis();
      elapsed_time = stop_time - start_time;
      //Serial.println(stop_time);
      //Serial.println(start_time);
      Serial.println(elapsed_time);
      idle = 1;
      delay(1000);
    }
    
  }
  
  else if (statusSensorLeft == 1 || statusSensorRight == 1) {
    digitalWrite(LED, LOW);
    if (millis()-trigger_time < 300) //release too early
    {
      armed = 0;
      idle = 1; //resets timer
    }
    
    else if (idle == 0 && armed == 1) //timer start
    {
      //Serial.println("started");
      start_time = millis();
      armed = 0;
      delay(100);
    }
    
  }
}
