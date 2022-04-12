/*
TVE-countdown 統測倒數器，詳請請見readme.md
此程式有按鈕，如不要按鈕功能請改燒錄無按鈕功能之程式
code by SamWang8891
*/

/*
tm.display 對照表：數字對數字，10->A,11->b,12->C,13->d,14->E,15->F
位數從0開始
中間冒號tm.point(1); OR tm.point(0);
*/

//!!請自行定義 變數 或 腳位
//#define 腳位名稱 實際腳位
//----數字模組----
#define NCLK 3   //前綴N為Number之縮寫，用以避免與後者RTC模組CLK相衝。實際腳位標示為CLK。
#define DIO 2
//---------------

//----RTC模組----
#define CLK 6
#define DAT 5
#define RST 4
//--------------

//----按鈕----
#define bt_bright 8
#define bt_mode 7
//-----------

//----變數----
#define brinit 3 //亮度由按到最亮為0~7，預設初始亮度3
#define debug true //是否啟用序列監控？ 預設為true，不要則改為false
#define baudrate 9600 //設定序列監控波特率，預設9600。
#define testdisaply true //設定是否開啟每次通電時自動全亮三秒以便檢查。預設true，否則false。
#define t_year  2023 //輸入欲倒數之西元年
#define t_month  04 //輸入欲倒數之月份（1~12)
#define t_day   30 //輸入欲倒數之日
//-----------

#include <TM1637.h> 
#include <Wire.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>  //Rtc by Makuna


ThreeWire myWire(DAT, CLK, RST); // DAT,CLK,RST or IO,SCLK,CE
RtcDS1302<ThreeWire> Rtc(myWire);

TM1637 tm(NCLK, DIO);

int h; //hour
int m; //minute 
char csdate;
char cstime;
int sdate; //set date read from serial
int stime; //set time read from serial
int timeleft;
int runn;
bool runnian;
int num1;
int num2;
int hr;
int min;
int yr;
int dy;
int mn;
int a[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int bright = brinit;
int mode = 2; //1 for clock, 2 for countdown, 3 for date, 4 for Year
bool point = true;


//   ╭━━━━━━╮   ╭━━━━━╮   ╭━━━━━━━╮   ╭━╮  ╭━╮   ╭━━━━━━╮
//   ┃ ╭━━╮ ┃   ┃ ╭━━━╯   ┃ ╭╮ ╭╮ ┃   ┃ ┃  ┃ ┃   ┃ ╭━━╮ ┃
//   ┃ ╰━━━━╮   ┃ ╰━━━╮   ╰━╯┃ ┃╰━╯   ┃ ┃  ┃ ┃   ┃ ╰━━╯ ┃
//   ╰━━━━╮ ┃   ┃ ╭━━━╯      ┃ ┃      ┃ ┃  ┃ ┃   ┃ ╭━━━━╯
//   ┃ ╰━━╯ ┃   ┃ ╰━━━╮      ┃ ┃      ┃ ╰━━╯ ┃   ┃ ┃
//   ╰━━━━━━╯   ╰━━━━━╯      ╰━╯      ╰━━━━━━╯   ╰━╯








void setup(){
    pinMode(bt_bright, INPUT_PULLUP);
    pinMode(bt_mode, INPUT_PULLUP);

    tm.init();
    tm.set(brinit);

    Serial.begin(baudrate);

    Serial.print("現在時間（編譯器）：");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    //Serial.print("If you want to set t_day and time, just type 'Mon dd yyyy' then hit enter and type 'hh:mm:ss', t_month is like Jan, Feb....etc");

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    Serial.println(compiled);
    Serial.println();



    //判斷DS1302是否接好
    if (!Rtc.IsDateTimeValid()){
    // Common Causes:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing

        Serial.println("RTC 時間失去可靠度！\n");
        Serial.println("常見問題：電池沒電或是沒裝電池。\n");
        Rtc.SetDateTime(compiled);
    
        tm.display(0, 10);
        tm.display(1, 10);
        tm.display(2, 10);
        tm.display(3, 10);

    }


    for(int i=0; i<4; i++){
        tm.display(i, 0);
    }

    Rtc.SetIsRunning(true);
    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled || compiled < now){
    Serial.println("RTC 的時間比編譯器晚／早，正在更新...");
    //編譯時間比較新，把DS1302上的時間改成編譯的時間
    Rtc.SetDateTime(compiled);
    }
    Serial.println("RTC 時間已經與編譯器相同！");

    if(testdisaply == true){
        for(int i=0; i<4; i++){
            tm.display(i, 8);
        }
        tm.point(1);
        delay (1000);
        for(int i=0; i<4; i++){
            tm.display(i, 0);
        }
        tm.point(0);
    }









}



//   ╭━╮       ╭━━━━━╮   ╭━━━━━╮   ╭━━━━━╮
//   ┃ ┃       ┃ ╭━╮ ┃   ┃ ╭━╮ ┃   ┃ ╭━╮ ┃
//   ┃ ┃       ┃ ┃ ┃ ┃   ┃ ┃ ┃ ┃   ┃ ╰━╯ ┃
//   ┃ ┃ ╭━╮   ┃ ┃ ┃ ┃   ┃ ┃ ┃ ┃   ┃ ╭━━━╯
//   ┃ ╰━╯ ┃   ┃ ╰━╯ ┃   ┃ ╰━╯ ┃   ┃ ┃
//   ╰━━━━━╯   ╰━━━━━╯   ╰━━━━━╯   ╰━╯







void loop(){


/*    
  if(Serial.available()){
    csdate = Serial.read();
    Serial.print("Time?");
    cstime = Serial.read();
    sdate = (int)csdate;
    stime = (int)cstime;
    RtcDateTime manual = RtcDateTime(123, 123);
    Rtc.SetDateTime(manual);
    
    }

*/
  RtcDateTime now = Rtc.GetDateTime();
  yr=now.Year();
  mn=now.Month();
  dy=now.Day();
  hr=now.Hour();
  min=now.Minute();




  if(digitalRead(bt_bright) == LOW){
    delay(300);
    if(digitalRead(bt_bright) == LOW){
      Serial.println("bright pressed");
      bright++;
      if(bright>7)
        bright = 0;
      tm.set(bright);
    }  
  }


  if(digitalRead(bt_mode) == LOW){
    delay(300);
    if(digitalRead(bt_mode) == LOW){
      Serial.println("mode pressed");
      mode ++;
      if(mode == 5)
        mode = 1;
      if(mode == 1)
        point = true;
    }
  }  



 
  if(t_year >= now.Year() ){
      timeleft = 0;
    for(int i = 1; i<now.Month(); i++){
      timeleft = timeleft + a[i];
    }
    timeleft = timeleft + now.Day();
    Serial.print("今天是今年的第：");
    Serial.print(timeleft);
    Serial.print("天\n");
    timeleft = 365-timeleft+120;
  }
  else{
    for(int i = 1; i<now.Month(); i++){
      timeleft = timeleft + a[i];
    }
    timeleft = timeleft + now.Day();
    timeleft = 120-timeleft;
  
  }



  //Serial.print(now);
  Serial.print(now.Month());
  Serial.print("/");
  Serial.print(now.Day());
  Serial.print("/");
  Serial.print(now.Year());
  Serial.print("  ");
  Serial.print(now.Hour());
  Serial.print(":");
  Serial.print(now.Minute());
  Serial.print(":");
  Serial.print(now.Second());
  Serial.println("");

  //ITS SHOW TIME
  h = now.Hour();
  m = now.Minute();  
  
  if(mode == 2){
    tm.display(0,0);
    tm.display(1,timeleft /100 % 10);
    tm.display(2,timeleft / 10 % 10 );
    tm.display(3,timeleft % 10);
  }
  else if(mode == 1){
    tm.display(0,h / 10 % 10);
    tm.display(1,h % 10);
    tm.display(2,m / 10 % 10 );
    tm.display(3,m % 10);
    tm.point(point);
    point = !point;
  }
  else if(mode == 3){
    tm.display(0, now.Month() /10 % 10);
    tm.display(1, now.Month() % 10);
    tm.display(2, now.Day() / 10 % 10 );
    tm.display(3, now.Day() % 10);
  }
  else if(mode == 4){
    tm.display(0,now.Year() /1000 % 10);
    tm.display(1,now.Year() /100 % 10);
    tm.display(2,now.Year() / 10 % 10 );
    tm.display(3,now.Year() % 10);
  }
  
  Serial.println(timeleft);
  
  

  //判斷DS1302是否正常，如果不正常，一般是線沒接好，或是電池沒電了
  if (!now.IsValid())
  {
    for(int i=0; i<4; i++){
        tm.display(i, 10);
    }
    Serial.println("RTC lost confidence in the DateTime!");
    delay(1000);
  }

  delay(1000); // 1秒更新一次


  }
