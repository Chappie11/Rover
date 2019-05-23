void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(random(0,500));
  Serial.print(",");
  Serial.print(random(0,500));
  Serial.print(",");
  Serial.print(random(0,500));
  Serial.print(",");
  Serial.print(random(0,500));
  Serial.print(",");
  Serial.println(random(0,1000));
  delay(2);
}
