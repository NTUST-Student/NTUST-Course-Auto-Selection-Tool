# NTUST Course Auto Selection Tool v1.3
# 台科 自動選課 工具 v1.3
<div align="center">
  <img src="./logo.png">
</div>

&ensp;免責聲明 :
```
* 本程式碼和電腦程式僅供參考和學習使用，並不保證其準確性和可靠性。作者不承擔任何因使用或無法使用本程式碼和電腦程式而導致的任何直接或間接損失、損害、成本或費用。

* 本程式碼和電腦程式所提供的功能，可能會被人用於非法或不當用途。作者強烈反對任何違反法律、道德或倫理的行為。如有人使用本程式碼和電腦程式進行任何不當行為，後果自負，作者不承擔任何責任。

* 任何使用本程式碼和電腦程式的人士，即表示已閱讀、理解並同意以上免責聲明。
```

[下載連結(Windows執行檔)](https://github.com/NTUST-Student/NTUST-Course-Auto-Selection-Tool/releases/tag/v1.3)

## Usage 
 Read `NTUST_Course_Auto_Selection_Tool_Guide.pdf` for more infomation
1.	Execute `SelectionTool.exe` (double click it)
2.	Choose the selection type : ( Adding or Droping / Pre-registration(After the draw) )
3.	Enter the course code you want to select, multiple code must split by comma.
4.	Go to https://courseselection.ntust.edu.tw/ grab your cookie. (See tutorial below)
5.	Adjust the time interval for selection. **(Warning : too frequently will be banned by system, recommend is 30 seconds)**
6.	Click "Start Auto Selection" button, and the program keep select course for you.
7.	If you want to stop or change some setting, click "Stop Auto Selection".
8.	The latest selection time and count will show on GUI and black window.
9.	After a period of time, expired cookies must be updated so that the program can continue to run. It is recommended to update them every 12 hours.

## Tutorial For Get Your Cookie
 Read `NTUST_Course_Auto_Selection_Tool_Guide.pdf` for more infomation
1.	Go to https://courseselection.ntust.edu.tw/AddAndSub/B01/B01
2.	Press F12 -> Network -> toggle "Preserve log" option
3.	Enter any course code and click "Add" or add the course in your course list.
4.	"ExtraJoin" / "Join" will shows up on DevsTool (F12 window)
5.	Click on it and scroll down find the cookie place inside request
6.	Right click on cookie, and press "Copy value"
7.	Paste into GUI input field

## 使用方法
 請閱讀 `NTUST_Course_Auto_Selection_Tool_Guide.pdf`
1.	執行 `SelectionTool.exe` (點兩下)
2.	選擇選課類型 : ( Adding or Droping->加退選課 / Pre-registration(After the draw)->電腦抽選後選課 )
3.	輸入課程代碼，多個的話使用逗號分隔
4.	去選課網站 https://courseselection.ntust.edu.tw/ 獲取cookie. (詳情請見下面的教學)
5.	調整時間間隔(幾秒選一次課) **(警告 : 太頻繁會被系統封鎖，建議每30秒選一次)**
6.	點擊 "Start Auto Selection" 按鈕，接著程式就會自動幫你不斷地選課
7.	如果想要停止或是改變設定，點擊 "Stop Auto Selection" 按鈕.
8.	最新的加選時間與加選次數會顯示於GUI與黑視窗中.
9.	cookie是會過期的，建議每12小時更新一次

## 獲取Cookie教學
 請閱讀 `NTUST_Course_Auto_Selection_Tool_Guide.pdf`
1.	前往加退選網站 https://courseselection.ntust.edu.tw/AddAndSub/B01/B01
2.	按 F12 -> Network -> 將 “Preserve log" 選項打勾
3.	加選任何課程，用課碼或待選清單加選都可以
4.	"ExtraJoin" / "Join" 會出現在 DevsTool 視窗上 (按F12後跑出來的右側視窗)
5.	點擊它然後往下滑找到存放Cookie的位置
6.	右鍵點擊Cookie，按下"Copy value"
7.	貼到GUI上的Cookie欄位