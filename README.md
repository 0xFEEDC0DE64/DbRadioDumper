# DbRadioDumper
Small application that downloads radio streams and splits them by every hour.

# Building from source
This project can only be built as part of the project structure [DbSoftware](https://github.com/0xFEEDC0DE64/DbSoftware)

```Shell
git clone https://github.com/0xFEEDC0DE64/DbSoftware.git
cd DbSoftware
git submodule update --init --recursive DbRadioDumper
cd ..
mkdir build_DbSoftware
cd build_DbSoftware
qmake CONFIG+=ccache ../DbSoftware
make -j$(nproc) sub-DbRadioDumper
make sub-DbRadioDumper-install_subtargets
./bin/radiodumper
```
