#define LEDC_CHANNEL_0      0//LEDCのPWMチャネル0から15
#define LEDC_TIMER_13_BIT   13//LEDCタイマーの精度13ビット
#define LEDC_BASE_FREQ      5000//LEDCのベース周波数5000Hz

const int buzPin = 23;//圧電ブザーのビン番号GP10 1023pin
const int NOTE_NONE = NOTE_MAX;//休符
//各音符の音程（音の高さ）
int melody[] = {
  NOTE_E, NOTE_C, NOTE_D, NOTE_G, NOTE_NONE, NOTE_G, NOTE_D, NOTE_E, NOTE_C,NOTE_NONE
};

//各音符の音階（オクターブ）
int noteOctaves[] = { 4, 4, 4, 3, 0, 3, 4, 4, 4, 0 };
//各音符の長さ
int noteDurations[] = { 2, 2, 2, 1, 4, 2, 2, 2, 1, 4 };

void setup(){
  Serial.begin(115200);
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(buzPin, LEDC_CHANNEL_0);
  pinMode(17,INPUT);//点击
}

void loop(){
  int b = digitalRead(17);
  if (b == 1){
    Serial.println(b);
    for (int thisNote = 0; thisNote < 10; thisNote++){
      ledcWriteNote(LEDC_CHANNEL_0, (note_t)melody[thisNote], noteOctaves[thisNote]);
      int pauseBetweenNotes = 1000 / noteDurations[thisNote] * 1.30;
      delay (pauseBetweenNotes);
      ledcWriteTone(LEDC_CHANNEL_0,0);  //演奏を止める。
    }
  }
  delay(10);
}