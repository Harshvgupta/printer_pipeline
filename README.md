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

## Run command
.\bin\Debug\<executbale_name>.exe <printer job name> <output folder name> <supervised or automatic>
