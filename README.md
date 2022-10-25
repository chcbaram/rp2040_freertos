# rp2040_freertos
---
## 준비
sudo python3 -m pip install pyserial

## CMake 설정 for Windows 
cmake -S . -B build -G "MinGW Makefiles" -DPICO_BOARD=pico

## CMake 설정 for macOS 
cmake -S . -B build -DPICO_BOARD=pico -DPICO_SDK_PATH="~/dev/pico/pico-sdk"

## CMake 빌드
cmake --build build -j20

## 다운로드
python .\down.py
