#include <SoftwareSerial.h>   // 引用程式庫

#define PLAY_PIN 10
#define FORWARD_PIN 11
#define REC_NUM 3

// 定義連接藍牙模組的序列埠
SoftwareSerial BT(8, 9); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數
const byte LED_PIN = 13;  // 定義LED腳位
int curRec = 0;

void setup() {
  // 設定HC-05藍牙模組，AT命令模式的連線速率。
  Serial.begin(9600);   // 與電腦序列埠連線
  BT.begin(38400);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PLAY_PIN, OUTPUT);
  pinMode(FORWARD_PIN, OUTPUT);

  digitalWrite(PLAY_PIN, HIGH);
  digitalWrite(FORWARD_PIN, HIGH);
}

void loop() {
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」 
  if (BT.available()) {
    val = BT.read();
    Serial.println(val);
    switch(val){
      
      case 'g':
        play(0);
      break;
      
      case 'y':
        play(1);
      break;

      case 'r':
        play(2);
      break;

      case 'd':
        play_test();
      break;

      case '1':
        digitalWrite(LED_PIN, HIGH);
        // 回應命令發送端，告知「已開燈」
        BT.println("LED ON");
      break;

      case '0':
        digitalWrite(LED_PIN, LOW);
        // 回應命令發送端，告知「已關燈」
        BT.println("LED OFF");
      break;

      default:

      break;
    }
  }
}

void play(int btnType){
  for(int i=0;i<btnType;i++){
    digitalWrite(FORWARD_PIN, LOW);
    delay(1000);
    digitalWrite(FORWARD_PIN, HIGH);
    delay(1000);    
  }
  
  digitalWrite(PLAY_PIN, LOW);
  delay(1000);
  digitalWrite(PLAY_PIN, HIGH);
  delay(1000);
  val='i';
  if(btnType==0)
    return;

  for(int i=0;i<REC_NUM - btnType;i++){
    digitalWrite(FORWARD_PIN, LOW);
    delay(1000);
    digitalWrite(FORWARD_PIN, HIGH);
    delay(1000);
  }

  return;
}

void play_test(){
  digitalWrite(PLAY_PIN, LOW);
  delay(1000);
  digitalWrite(PLAY_PIN, HIGH);
}