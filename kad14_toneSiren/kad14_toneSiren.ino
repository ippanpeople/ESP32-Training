#define LEDC_CHANNEL_0      0       //LEDCのPWMチャネル０から１５
#define LEDC_TIMER_13_BIT   13      //LEDCタイマーの精度13ビット
#define LEDC_BASE_FREQ      5000    //LEDCのベース周波数5000Hz

const int buzPin = 23;              //圧電ブザーのピン番号GPIO IO23pin
const int btnPin = 17;              //GPIO IO17pin
int noteDuration = 1000/8;          //八分音符の長さ
int flag = 0;

void setup(){
    Serial.begin(115200);
    ledcSetup(LEDC_CHANNEL_0, LEDC_TIMER_13_BIT, LEDC_BASE_FREQ);
    ledcAttachPin(buzPin, LEDC_CHANNEL_0);
    pinMode(btnPin, INPUT);
}

void loop(){
    for(int i=500; i<= 2380; i+=20){
        Serial.printf("%3d ", i);
    }
    for(int i=2400; i>=500; i-=20){
        Serial.printf("%3d ", i);
    }
    Serial.println("\n");
}