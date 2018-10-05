# DbRadioDumper
Small application that downloads radio streams and splits them by every hour.

[![Build Status](https://travis-ci.org/0xFEEDC0DE64/DbRadioDumper.svg?branch=master)](https://travis-ci.org/0xFEEDC0DE64/DbRadioDumper) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/e83ffe49ed204a0c92c7888828ba34cc)](https://www.codacy.com/app/0xFEEDC0DE64/DbRadioDumper?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=0xFEEDC0DE64/DbRadioDumper&amp;utm_campaign=Badge_Grade)

## Building from source
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
