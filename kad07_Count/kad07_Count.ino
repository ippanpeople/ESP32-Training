const int swPin = 17; //const...初期化した後代入されない 
int count = 0; //カウンタ変数
int flag = 0; //フラグ初期値 0:押されていない状態

void setup() {
    Serial.begin(115200);
    pinMode(swPin, INPUT); // Switch デジタル入力
}

void loop() {
    int b = digitalRead(swPin);
    if(b == 1 && flag == 0){
        count ++;
        flag = 1;
        Serial.println(count);
    }else if(b == 0 && flag == 1){
        flag = 0;
    }
    delay(10);
}