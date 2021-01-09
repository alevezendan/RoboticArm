void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int val1 = analogRead(A0);
  int voltage1 = map(val1,0,1023,0,180);
  Serial.print(voltage1);
  Serial.print(";");
  
  int val2 = analogRead(A2);
  int voltage2 = map(val2,0,1023,0,180);
  Serial.print(voltage2);
  Serial.print(";");
  
  int val3 = analogRead(A4);
  int voltage3 = map(val3,0,1023,0,180);
  Serial.print(voltage3);
  Serial.println(";");

  delay (50);
}
