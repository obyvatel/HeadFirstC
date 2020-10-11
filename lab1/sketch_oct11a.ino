int LED_state = 0;
int ADC_0 = 0;
  
void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (LED_state)
  {
    digitalWrite(13, HIGH);
    LED_state = 0;
  }
  else
  {
    digitalWrite(13, LOW);
    LED_state = 1;
  }

  ADC_0 = analogRead(0);
  Serial.println("Hi, dude!, %i");
  Serial.println(ADC_0);
  delay (1000);
}
