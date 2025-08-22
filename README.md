# candlesdk-win-driver
WinUSB driver installer for CANdle device for windows systems.


# Dependencies

- WDK 8 redistributable (installed via `Visual Studio Installer`)
- MYSYS2 with MINGW64
- MINGW64 toolchain and autotools packages

# Usage

Using `mysys-mingw64` runtime environment with installed `toolchain` and `autotools` packages in the directory libwdi run:
```
./autogen.sh
./configure --enable-examples-build --enable-toggable-debug --disable-32bit --enable-log --with-wdkdir="C:/Program Files (x86)/Windows Kits/8.0"
make
```

The library files will be located inside `libwdi/libwdi/.lib` path.

Than enter main directory and execute:
```
mkdir build
cd build
cmake ..
ninja
```
