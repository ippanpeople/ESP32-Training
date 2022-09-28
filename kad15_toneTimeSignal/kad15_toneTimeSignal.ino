#define LEDC_CHANNEL_0      0       //LEDCのPWMチャネル０から１５
#define LEDC_TIMER_13_BIT   13      //LEDCタイマーの精度13ビット
#define LEDC_BASE_FREQ      5000    //LEDCのベース周波数5000Hz

const int buzPin = 23;              //圧電ブザーのピン番号GPIO IO23pin
const int btnPin = 17;              //GPIO IO17pin
int noteDuration = 1000/8;          //八分音符の長さ
int flag = 0;

void setup(){
    ledcSetup(LEDC_CHANNEL_0, LEDC_TIMER_13_BIT, LEDC_BASE_FREQ);
    ledcAttachPin(buzPin, LEDC_CHANNEL_0);
    pinMode(btnPin, INPUT);
}

void timeSignal(void){
    double note_half = noteDuration*4;
    double note_whole = noteDuration*8;
    double note_16_th = noteDuration/2;
}

void loop(){
    if(digitalRead(btnPin) == HIGH){

    }

}