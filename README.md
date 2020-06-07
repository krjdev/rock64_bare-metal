# PINE64 Rock64 Simple Bare-Metal Example

**Required tools**

* GCC for AArch64

## How to build

* Get the sources  
``
$ git clone https://github.com/krjdev/rock64_bare-metal.git
``  
* Build the example  
``
$ cd rock64_bare-metal
``  
``
$ make
``

## How to start (U-Boot)

* Load the example into memory  
``
=> fatload mmc 1 0x30000000 hello.elf
``  
* Execute example  
``
=> bootelf 0x30000000
``

## Output

![alt text](https://github.com/krjdev/rock64_bare-metal/blob/master/img/output.png)

## TODO

* Add interrupt support
