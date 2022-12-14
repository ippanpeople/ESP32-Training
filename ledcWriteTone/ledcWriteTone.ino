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

void loop(){
    if(digitalRead(btnPin) == HIGH && flag == 0){
        flag = 1;
        //低い周波数から高い周波数へ
        for(int i=25; i<120; i++){
            ledcWriteTone(LEDC_CHANNEL_0, 20*i);
            delay(noteDuration);
            if(digitalRead(btnPin) == HIGH && flag == 1){
                //第２引数の周波数を０にすると音が消える
                //ledcWriteTone(LEDC_CHANNEL_0, 0);
                break;
            }
        }
        
        //高い周波数から低い周波数へ
        for(int i=120; i>=25; i--){
            ledcWriteTone(LEDC_CHANNEL_0, 20*i);
            delay(noteDuration);
            if(digitalRead(btnPin) == HIGH && flag == 1){
                //第２引数の周波数を０にすると音が消える
                //ledcWriteTone(LEDC_CHANNEL_0, 0);
                break;
            }
        }
        flag = 0;
    }

}