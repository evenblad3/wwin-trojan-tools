# Wwin
Winapi x86 trojan utilities.
Original author - [wzrterfx](https://github.com/wzrterfx)

## DISCLAIMER ⚠️
This tool is intended for **EDUCATIONAL PURPOSES** only. Use this at your own risk. The developers of this tool are NOT responsible for any damage caused by THIS tool.

## WWin Functions

* ## `WWin::Icon` 
  ```cpp
  IconNoise(int number, int delay);
  IconSizebleNoise(int number, int maxIconSize, int delay);
  IconCursorNoise(int number, int delay);
  ```

* ## `WWin::Screen`
  ```cpp
  ScreenDistortion(int number, int delay);
  ScreenCrazyDistortion(int number, int delay);
  ScreenBuffer(int number, int delay);
  ScreenBlink(int number, int delay);
  ScreenSlice(int number, int delay);
  ScreenZoom(int number, int delay);
  ```

* ## `WWin::Sound`
  ```cpp
  SoundPlayFromFile(const wchar_t* filePath);
  SoundPlayFromMemory(const unsigned char* data, size_t dataSize);
  SoundStop();
  ```
 
* ## `WWin::Utils`
  ```cpp
  UtilsAddStartup();
  UtilsRemoveStartup();
  UtilsRestartSystem();
  UtilsShutdownSystem();
  UtilsMuteVolume();
  UtilsUnmuteVolume();
  UtilsCheckProcessRunning(const wchar_t* processName);
  UtilsKillProcessByName(const wchar_t* processName);
  UtilsChangeWindowsTitle(const wchar_t* title);
  UtilsExecuteCommand(const wchar_t* command);
  UtilitsBlueScreen();
  ```
