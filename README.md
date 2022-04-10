# TVE-countdown 統測倒數器
.
THIS REPO HAS NOT FINISHED YET
這個項目尚未完成
.
.
中文(zh_TW)：
這是一個使用簡易C++、arduino及常見模組的統測倒數器。

功能：
-- 顯示統測倒數天數
-- 顯示時間
-- 顯示日期

材料：
-- 一塊至少有11個孔位的arduino開法版(包含按鈕兩顆--調節亮度及開關螢幕)
-- 燒錄模組（如果是用的板子沒有usb介面，如arduino pro mini）
-- 時鐘模組DS1302
-- 數字顯示模組TM-1637
-- 麵包板或是可連接元件之任何器具
-- 其他(eg. 電烙鐵、杜邦線...)

軟體：
-- Arduino IDE (Arduino 燒錄軟體)或任何可以燒錄之軟體，如果不是avr板子（非官方版），請自行尋找驅動。

使用函式庫：
-- TM1637.h (Grove 4-Digit Display by Seeed Studio, 1.0.0, 新版可能不會怎樣)
-- Wire.h (arduino IDE內建)
-- ThreeWire.h (Rtc by Makuna, 2.3.4, 新版可能不會怎樣)
-- RtcDS1302.h (Rtc by Makuna, 2.3.4, 新版可能不會怎樣)

程式語言：
-- 100% C/C++

有任何問題？歡迎新增Issues！



------------------------------------------------------------------------------------------------------------------------


EN(en):
This is a TVE(Gerenal test for volcational highschool in Taiwan to get a collage) countdown.

Feature:
--Display TVE countdown time
--Display current time
--Display date

Components:
-- A at least 11 port aviable arduino board(2 for buttons, 1 brightness adjustment and 1 for tuen screen on and off)
-- A buring module (If using a board WITHOUT a USB port like pro mini)
-- A clock module DS1302
-- A 4-Digit Display TM-1637
-- Bread board or other that can connect these components.
-- Others(eg. soldering iron, hook-up wire, etc.)

Software:
-- Arduino IDE or other software which is able to do the same job. Please find the driver yourself if not avr boards.

Library Used：
-- TM1637.h (Grove 4-Digit Display by Seeed Studio, 1.0.0, newer version may be fine)
-- Wire.h (arduino IDE內建)
-- ThreeWire.h (Rtc by Makuna, 2.3.4, newer version may be fine)
-- RtcDS1302.h (Rtc by Makuna, 2.3.4, newer version may be fine)

Language:
-- 100% C/C++


Any issues? Please create a issue in Issues!
