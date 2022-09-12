void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  pinMode(17, INPUT);
}

void led(int time) {
  digitalWrite(16, HIGH);
  delay(time);
  digitalWrite(16, LOW);
  delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int b = digitalRead(17);
  if(b == 1){
    Serial.println("押された");
  }else{
    Serial.println(" ");
  }
  delay(10);
}
