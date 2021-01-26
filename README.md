# PINE64 Rock64 Simple Bare-Metal Example

**ATTENTION**

This branch is a development branch. Building currently fails
because some required files are not checked in.

**Features**

* Basic MMU support
* Basic exception handling
* Minimalistic **libc**

## Build

### Bare-Metal Example
#### Required Tools:

* **GCC** for AArch64  
[Offical Toolchains from ARM](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads)  
#### Bare-Metal Example - Get the source code
```
$ git clone https://github.com/krjdev/rock64_bare-metal.git
$ cd rock64_bare-metal
```
#### Bare-Metal Example - Build the example
```
$ make CROSS_COMPILE=/path/to/gcc/bin/aarch64-none-elf-
```

### U-Boot
#### Required Tools:

* **GCC** for AArch64  
[Offical Toolchains from ARM](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads)  
* Device Tree Compiler

#### ATF - Get the source code from ARM Trusted Firmware
```
$ git clone https://github.com/ARM-software/arm-trusted-firmware.git
$ cd arm-trusted-firmware
```
#### ATF - Build ATF for PINE64 ROCK64
```
$ make distclean
$ make CROSS_COMPILE=/path/to/gcc/bin/aarch64-none-elf- PLAT=rk3328
```
#### ATF - Export ELF for U-Boot
```
$ export BL31=/path/to/arm-trusted-firmware/build/rk3328/release/bl31/bl31.elf
```

**NOTE**
Might be not required for starting the Bare-Metal Example.

#### U-Boot - Get the source code from U-Boot
```
$ git clone https://github.com/u-boot/u-boot.git
$ cd u-boot
```
#### U-Boot - Build U-Boot for PINE64 ROCK64
```
$ make mrproper
$ make rock64-rk3328_defconfig
$ make CROSS_COMPILE=/path/to/gcc/bin/aarch64-none-elf-
```

## Run
```
=> fatload mmc 1 0x10000000 main.elf
=> bootelf 0x10000000
``` 

## TODO

* Add fully interrupt support
* Add SMP support
* Add Thread support
