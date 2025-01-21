# Project Readme

## Overview

This project involves a solution compiled using the **MSVC compiler** and **MSBuild version 17.6**, targeting the **Windows x86_64** platform. The project utilizes **HTML** for a simple GUI interface and **JSON** for efficient data handling and structured representation.

The repository contains the source code, build files, and a working executable to run the solution.

---

## Table of Contents

1. [Setup Instructions](#setup-instructions)  
2. [Build Commands](#build-commands)  
3. [Running the Program](#running-the-program)  
4. [Libraries Used](#libraries-used)  
5. [Attachments](#attachments)  

---

## Setup Instructions

1. Clone the repository or download the source code as a ZIP file.
2. Ensure **CMake** and the **MSVC compiler** (with MSBuild version 17.6) are installed on your system.
3. Open a terminal or command prompt and navigate to the directory containing the project.

---

## Build Commands

Use the following commands to build the executable:

```bash
cmake ..
cmake --build .
```
---
## Running the Program

To execute the compiled program, use the following example command:

```bash
.\bin\Debug\formlabs.exe "printname5" "output" supervised
Arguments:
"printname5": Specifies the name of the input or operation.
"output": Specifies the output file or folder.
supervised: Specifies the mode or configuration for the program.
```
---
## Libraries Used
The project utilizes the following libraries:

HTML: Used to display a graphical user interface (GUI) for better visualization of the code’s output.
JSON: Employed for handling data efficiently in a structured and hierarchical format.
These libraries are crucial for the functionality and data representation within the project.
