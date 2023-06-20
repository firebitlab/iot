#define p_ledtick 13

void setup() 
{
  Serial.begin(115200);
  pinMode(p_ledtick, OUTPUT);
}


int ledState = LOW; 
unsigned long previousMillis = 0;
const long interval = 1000;
void loop() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;

    if (ledState) ledState = LOW;
    else ledState = HIGH;

    Serial.println(ledState);
    digitalWrite(p_ledtick, ledState);
  }
}
