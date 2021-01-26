# PINE64 Rock64 Bare-Metal Example

## Features

**Kernel**

+ Basic device handling
+ Basic syscall support

**Userland**

+ Minimalistic **libc**

## TODO

* MMU support (currently disabled)
* Implement more syscalls
* Add fully interrupt support
* Add fully exception support
* Add SMP support
* Add Kerne thread support
* Add ELF support
* Add more **libc** functions

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

## Run (U-Boot)
```
=> fatload mmc 1 0x10000000 main.elf
=> bootelf 0x10000000
```

## LICENSE
> Copyright (c) 2020-2021 [Johannes Krottmayer](mailto:krjdev@gmail.com)  
>  
> Permission to use, copy, modify, and/or distribute this software for any  
> purpose with or without fee is hereby granted, provided that the above  
> copyright notice and this permission notice appear in all copies.  
>  
> THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES  
> WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF  
> MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR  
> ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES  
> WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN  
> ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF  
> OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. 
