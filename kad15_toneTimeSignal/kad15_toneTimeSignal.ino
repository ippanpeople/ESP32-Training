#define LEDC_CHANNEL_0      0//LEDCのPWMチャネル0から15
#define LEDC_TIMER_13_BIT   13//LEDCタイマーの精度13ビット
#define LEDC_BASE_FREQ      5000//LEDCのベース周波数5000Hz

const int buzPin = 23;//圧電ブザーのビン番号GP10 1023pin
const int btnPin = 17;// GP10 1017pin
int noteDuration = 1000/8;//八分音符♪の長さ

void setup(){
  ledcSetup (LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(buzPin,LEDC_CHANNEL_0);
  pinMode(btnPin,INPUT);
}

void loop(){
  if(digitalRead(btnPin) == HIGH){
    timeSignal();
  }
  ledcWriteTone(LEDC_CHANNEL_0, 0);
}

void timeSignal(void){
  double note_half = noteDuration*4;//2分音符
  double note_whole = noteDuration*8;//全音符
  double note_16th = noteDuration/2;//16分休符
  
  ledcWriteTone(LEDC_CHANNEL_0, 440);
  delay(note_half);
  ledcWriteTone(LEDC_CHANNEL_0, 0);
  delay(note_16th);
  ledcWriteTone(LEDC_CHANNEL_0, 440);
  delay(note_half);
  ledcWriteTone(LEDC_CHANNEL_0, 0);
  delay(note_16th);
  ledcWriteTone(LEDC_CHANNEL_0, 440);
  delay(note_half);
  ledcWriteTone(LEDC_CHANNEL_0, 0);
  delay(note_16th);
  ledcWriteTone(LEDC_CHANNEL_0, 880);
  delay(note_whole);
  
}
