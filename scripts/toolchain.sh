#!/bin/bash

GCC_AARCH64_VERSION="10.2-2020.11"
GCC_AARCH64="gcc-arm-$GCC_AARCH64_VERSION-x86_64-aarch64-none-elf"
GCC_AARCH64_TAR="$GCC_AARCH64.tar"
GCC_AARCH64_XZ="$GCC_AARCH64_TAR.xz"
GCC_AARCH64_ARM="https://developer.arm.com"
GCC_AARCH64_LINK="$GCC_AARCH64_ARM/-/media/Files/downloads/gnu-a/$GCC_AARCH64_VERSION/binrel/$GCC_AARCH64_XZ"

mkdir toolchain
cd toolchain
wget $GCC_AARCH64_LINK
unxz $GCC_AARCH64_XZ
tar -xf $GCC_AARCH64_TAR
rm $GCC_AARCH64_TAR
mv $GCC_AARCH64 aarch64-none-elf
