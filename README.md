# Minesweeper Reverse Engineering

透過 C 編寫的 Windows 踩地雷外掛。

## 簡介

覺得 Windows 踩地雷太困難嗎？使用此工具透視地雷吧！

### 透視工具（Scanner.dll）

#### 正常版踩地雷：
![](https://i.imgur.com/LEEZjU3.gif)


#### 注入透視工具後的踩地雷：
![](https://i.imgur.com/nOJa4qi.gif)


### Bad Apple（Apple.dll）

如果你覺得還是太無聊，也可以用它來播放影片。
原影片連結：[【東方】Bad Apple!! ＰＶ【影絵】(YouTube)](https://www.youtube.com/watch?v=FtutLA63Cp8&ab_channel=kasidid2)

![](https://i.imgur.com/dQuSTtQ.gif)

## 使用方法

因為此外掛是透過 DLL 注入來實現的，因此 Injector.exe 可能被防毒軟體判斷為有毒。

1. 下載 Injector.exe、Scanner.dll、Apple.dll。
2. 開啟 WindowsXP 踩地雷（[下載網址]((https://minesweepergame.com/download/windows-xp-minesweeper.php))）。
3. 打開工作管理員->詳細資料->找到踩地雷的 PID（每次執行都會不一樣）。
   ![](https://i.imgur.com/js2nuIm.png)
5. 打開 cmd 輸入以下指令，Scanner.dll 是透視功能，Apple 是播放影片的功能。
   ```
   [path]/Injector.exe [path]/[Scanner.dll/Apple.dll] [PID]
   ```
   **範例：**
   若這三個檔案都放在 C 槽裡面的 Minesweeper 資料夾內，如以下結構
   ```
   C:
   └─Minesweeper
     ├─Injector.exe
     ├─Scanner.dll
     └─Apple.dll
   ```
   若要啟用的是透視功能，則執行以下指令（假設踩地雷的 PID 是 7836）
   ```
   C:/Minesweeper/Injector.exe C:/Minesweeper/Scanner.dll 7836
   ```
   如果執行成功，則會印出以下字樣
   ```
   InjectDll("C:/Minesweeper/Scanner.dll") success!!!
   ```
   失敗則會印出
   ```
   InjectDll("C:/Minesweeper/Scanner.dll") failed!!!
   ```

## 開發環境

- Windows 10 家用版

## 開發工具

- Visual Studio 2019

## 輔助工具

- [IDA Pro](https://hex-rays.com/ida-pro/)
  用於反編譯與分析程式碼。
- [OllyDbg](https://www.ollydbg.de/)
  設置執行中斷點，測試各個函數的功能。
- [Cheat Engine](https://www.cheatengine.org/)
  對記憶體進行觀察/修改，方便測試。
