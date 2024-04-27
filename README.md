# Floatwheel Light Control Module

This code is a continuation of the stock Floatwheel LCM (Light Control Module). This version offers added features. On the side off the LCM an expended messaging structure was added (to work in combination with the Comm bridge that was created in a custom Float Package).
EEPROM writes and reads, store settings on the LCM without having to flash again. This brings some features such as changing the preset lighting profiles, remembering which profile was last used, changing boot animation and cell type and more.

TODO:
Include Float package buzzer support (let the vesc control the buzzer).

## Building with GCC / Makefile (Linux)

### Requirements

* Programmer
  * PyOCD: DAPLink, J-Link or ST-LINK
* PyOCD [https://pyocd.io/](https://pyocd.io/)
* GNU Arm Embedded Toolchain

### Building

#### 1. Install GNU Arm Embedded Toolchain

On debian based systems simply use

```bash
sudo apt install gcc-arm-none-eabi
```

or

Download the toolchain from [Arm GNU Toolchain Downloads](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) according to your pc architecture, extract the files

```bash
cd ~/Downloads
curl  https://developer.arm.com/-/media/Files/downloads/gnu/12.2.mpacbti-rel1/binrel/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi.tar.xz -L -o arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi.tar.xz
tar xvf arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi.tar.xz
sudo mkdir -p /opt/gcc-arm 
cd /opt/gcc-arm/
sudo mv ~/Downloads/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi/ .
sudo chown -R root:root arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi/
```

add /opt/gcc-arm/arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi/bin to you `PATH` or define `ARM_TOOCHAIN` in `Makefile`

#### 2. Install PyOCD

Install from pip instead of apt repository because the version is 0.13.1+dfsg-1, which is too low to recognize J-Link probe

```bash
pip install pyocd
```

#### 3. Clone This Repository

Clone this repository to local workspace

#### 4. Compiling And Flashing

```bash
# clean source code
make clean
# build
make
# or make with verbose output
V=1 make
# flash
make flash
```

#### 5. Troubleshooting

* Image is too big, make sure you are not using double functions
