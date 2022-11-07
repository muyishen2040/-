#include <SoftwareSerial.h>   // 引用程式庫

#define YELLOW_WARN 4 
#define GREEN_WARN 3
#define RED_WARN 2

// 定義連接藍牙模組的序列埠
SoftwareSerial BT(8, 9); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數
int greenState;
int yellowState;
int redState;

void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");

  pinMode(YELLOW_WARN, INPUT);
  pinMode(GREEN_WARN, INPUT);
  pinMode(RED_WARN, INPUT);

  // 藍牙透傳模式的預設連線速率。
  BT.begin(38400);
}

void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  greenState = digitalRead(GREEN_WARN);
  yellowState = digitalRead(YELLOW_WARN);
  redState = digitalRead(RED_WARN);
  
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
    val = 'i';
  }

  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
  }

  if(greenState == HIGH){
    BT.print('g');
    delay(2000);
    return;
  }

  if(yellowState == HIGH){
    BT.print('y');
    delay(2000);
    return;
  }

  if(redState == HIGH){
    BT.print('r');
    delay(2000);
    return;
  }

}