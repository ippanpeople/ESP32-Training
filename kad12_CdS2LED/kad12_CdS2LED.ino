const int pwmPin1 = 4;  // GPIO IO4ping
const int pwmPin2 = 16; // GPIO IO16ping
const int analogPin = A17;
int darkLevel = 1000; //暗さのしきい値

void setup()
{
  Serial.begin(115200);
  ledcSetup(0, 12899, 8);
  ledcSetup(1, 12899, 8);
  ledcAttachPin(pwmPin1, 0);
  ledcAttachPin(pwmPin2, 1);
}

void loop()
{
  int a = analogRead(analogPin);
  if (a < darkLevel)
  {
    ledcWrite(0, 255);
    ledcWrite(1, 255);
  }
  else
  {
    ledcWrite(0, 0);
    ledcWrite(1, 0);
  }
  Serial.println(a);
  delay(10);
}
