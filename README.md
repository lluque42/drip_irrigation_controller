# Drip irrigation controller

## Content

* Introduction
* Building instructions
* Directory tree
* Hardware

## Introduction

This is the second controller I've built for my house plants.
The first was written in Python in a rush before going out on
a trip and worked perfectly. It had a dot matrix screen with
a setup menu through microswitches; a real-time clock module,
etc. But some years later it hangs a lot, outdoor installation
always takes its toll.

So I've decided to implement a new version that loses the screen
in favor of a WiFi connection for keep-alive signaling against
a server, configuration and commands.

This repository includes all the code and scripts to built the
program in a Raspberry Pi Pico (1) W board. The schematics for
the external hardware is also included.

Luis Luque - 2025

## Building instructions

REMEMBER: This code was made for and tested on a Pico W (first
family of the Raspberry Pi Pico series). Use at your own risk in
other platforms.

Clone repository from:

https://github.com/lluque42/drip_irrigation_controller.git

Two files are included to allow an easy customization:
* wlan_setup_data.cmake.template (rename to wlan_setup_data.cmake)
    * To enter the wifi SSID, password.
* timers_default_data.cmake
    * To enter the time of the day, frequency and duration for
    the relays activation.

Create a build directory and enter to it:
`
drip_irrigation_controller $ mkdir build
drip_irrigation_controller $ cd build
drip_irrigation_controller/build $
`
Once inside, execute cmake against the parent directory (where
the CMakeLists.txt is):
`
drip_irrigation_controller/build $ cmake ..
drip_irrigation_controller/build $
`
If no errors occurred, then a Makefile file should have been created
in the build directory. Execute it to build the binaries.
`
drip_irrigation_controller/build $ make
`
If everything ok, a number of binary files should've been produced,
among them a drip.elf or drip.uf2 ready to be loaded into the Pico W
board.





If some error occur check the pre-requisites:
* The PICO_SDK_VARIABLE environment variable should exist and point to
the root of the pico-sdk directory.
* Is your board really a Pico W (first generation)?
* ?
TODO



## Directory tree

TODO


    ./  
    ├── .gitignore				(to prevent undesired files to be stagged)
    ├── Doxyfile				(doxygen config file for doc generation)  
    ├── Makefile				(use 'make help' for instructions)  
    ├── README.md				(brief documentation)  
    ├── doc/					(documentation extracted from comments in .h)  
    │   ├── html/				(html documentation)  
    │   │   ├── ...  
    │   │   ├── index.html		(entry point for html documentation)  
    │   │   ├── ...  
    │   └── man/				(man pages documentation)  
    │       └── man3/  
    │           └── ...			(example of use: 'man -l ft_string.h.3')  
    ├── include/				(directory for public header files (.h))  
    │   ├── ...  
    │   └── ...  
    ├── src/					(dir for source code and private header files)  
    │   ├── ...  
    │   │   ├── ...  				
    │   │   └── ...  
    │   └── ...					(may be structured in several directories)  
    │       ├── ...  
    │       └── ...  
    ├── lib/					(external libraries)  
    │   ├── ...  
    │   └── libft				(each library in its own directory)  
    ├── bin/					(directory for project's binaries and tester)  
    │   ├── ...  
    │   └── ...					(may be structured in several directories)  
    ├── obj/					(dir for source code and private header files)  
    │   ├── ...  
    │   │   ├── ...  
    │   │   └── ...  
    │   └── ...					(structured as in ./src)  
    │       ├── ...  
    │       └── ...  
    ├── data/					(directory for non-source files)  
    └── test/					(test program src code, compiles to .bin/tester)
        ├── ...  
        ├── tester.c  
        └── ...  

## Hardware

TODO

Volts across led: 2,5 V 
	With a 10K resistance and driven through the 2n3904 (100KOhm base to gpio)


With USB 5V directly fed, the relay coil consumes 70mA
	The pico restarts everytime te coil de-energizes, the diode requirement is
	real.

Had to replace the 100K base resistor with a 10K because with the realy coil
current I guess the transistor couldn't remain polarized.
