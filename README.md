# Drip irrigation controller

## Introduction

This is the second controller I've built for my house plants.
The first was written in Python in a rush before going out on
a trip and worked perfectly. It had a dot matrix screen with
a setup menu through microswitches; a real-time clock module,
etc. But some years later it hangs a lot, outdoor installation
always takes its toll.

So I've decided to implement a new version that loses the screen
in favor of a WiFi connection for keep-alive signaling,
configuration and commands.

This repository includes all the code and scripts to built the
program in a Raspberry Pi Pico (1) W board. The schematics for
the external hardware is also included.

Luis Luque - 2025

## Building instructions

Clone repository from:

https://github.com/lluque42/drip_irrigation_controller.git



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

