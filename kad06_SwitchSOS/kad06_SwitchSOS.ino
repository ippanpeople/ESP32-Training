void setup() {
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
  int b = digitalRead(17);
  int sos[9] = {0, 0, 0, 1, 1, 1, 0, 0, 0};

  if(b == 1){
    for(int i = 0; i < sizeof(sos) / sizeof(int); i++){
      if(sos[i] == 0) {
        led(200);
      }else{
        led(600);
      }
    }
  }
}
