#TVE-countdown 統測倒數器，詳請請見readme.md

//#define 腳位名稱 實際腳位
----數字模組----
#define NCLK    //前綴N為Number之縮寫，用以避免與後者RTC模組CLK相衝。實際腳位標示為CLK。
#define DIO 
---------------


----RTC模組----
#define CLK 
#define DAT
#define RST
--------------

ThreeWire myWire(DAT, CLK) // DAT,CLK,RST or IO,SCLK,CE

#include <TM1637.h> 
#include <Wire.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>  //Rtc by Makuna


