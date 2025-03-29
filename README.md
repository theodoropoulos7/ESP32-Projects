# ESP32-S3-DevKitC-1-N8R8 Setup on Ubuntu 22 Using VS Code and ESP-IDF Extension

This guide explains how to set up your **ESP32-S3-DevKitC-1-N8R8** on Ubuntu 22 using Visual Studio Code with the ESP-IDF extension. Follow the steps below to install ESP-IDF, configure the environment, create a project, and run preliminary tests.

---

## 1. Overview

You will:
- Install the Espressif IoT Development Framework (ESP-IDF) and its prerequisites.
- Configure the environment on Ubuntu 22.
- Set up Visual Studio Code with the ESP-IDF extension.
- Build, flash, and monitor a sample project to verify your board.

---

## 2. Prerequisites

- **Operating System:** Ubuntu 22
- **Board:** ESP32-S3-DevKitC-1-N8R8
- **Connection:** USB cable (ensure it’s a data-capable cable)
- **Required Tools:** Git, Python 3, CMake, Ninja, and other build utilities

---

## 3. Installing ESP-IDF on Ubuntu

### 3.1 Install Required Packages

Open a terminal and run:

```bash
sudo apt update
sudo apt install git wget flex bison gperf python3 python3-pip python3-setuptools cmake ninja-build ccache libffi-dev libssl-dev dfu-util
sudo apt install python3.10-venv
```

### 3.2 Download ESP-IDF
Clone the ESP-IDF repository (using a stable version as an example):

```bash
mkdir -p ~/esp
cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf
git checkout v5.2.5  # Or choose the latest stable version
git submodule update --init --recursive
```

### 3.3 Set Up the Environment
Source the export script to set up the necessary environment variables:

```bash
. $HOME/esp/esp-idf/export.sh
```

Tip: Add the above line to your ~/.bashrc or ~/.zshrc so the environment is set automatically when you open a terminal.

For more details, refer to the ESP-IDF Programming Guide for Linux.

## 4. Setting Up Visual Studio Code with the ESP-IDF Extension
### 4.1 Install VS Code
Download and install Visual Studio Code.

### 4.2 Install the ESP-IDF Extension
Open VS Code.
Go to the Extensions view (Ctrl+Shift+X) and search for ESP-IDF.
Install the official ESP-IDF Extension.

### 4.3 Configure the Extension
Open the Command Palette (Ctrl+Shift+P) and select ESP-IDF: Configure ESP-IDF extension.
Enter the path to your ESP-IDF folder (e.g., ~/esp/esp-idf).
The extension will auto-detect the toolchain and configure the necessary paths. Accept any prompts to install missing Python packages.

## 5. Creating a New Project and Running Preliminary Tests

### 5.1 Create a Sample Project
Open the Command Palette (Ctrl+Shift+P) and type ESP-IDF: Show Examples Projects.
Select a basic example such as hello_world or blink.
Click Create Project using Example to set up the project structure.

### 5.2 Configure the Project
In the VS Code status bar, set:
Serial Port: (e.g., /dev/ttyUSB0 or another appropriate port)
Device Target: esp32s3
Flash Method: Typically choose UART

### 5.3 Build, Flash, and Monitor
Build: Click the build icon (checkmark/gear icon) to compile your project.
Flash: Click the flash icon (usually a “rocket” icon) to program your board.
Monitor: Click the monitor icon to open the serial monitor and view the output (e.g., “Hello World” messages or an LED blink).
For a detailed walkthrough, see Hutscape’s Hello World Tutorial.

## 6. Verifying Connectivity and Running Commands

### 6.1 USB Connection Check
Verify that your board is recognized by running:

```bash
dmesg | grep tty
```
or 
```bash
ls /dev/ttyUSB* /dev/ttyACM*
```

You should see an entry such as /dev/ttyUSB0 of /dev/ttyACM0.

### 6.2 Using idf.py from the Terminal
After sourcing the ESP-IDF environment, you can also use the command-line tools:

```bash
idf.py --version
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/ttyACM0 flash monitor
```
If you get a warning for mismached flash size, adjust it using:
```bash
idf.py menuconfig
# → Serial flasher config → Flash size → 8MB
```
**Remember** before flashing you need to get the board into flash mode.\
**Press and hold** the `boot` button, then **press** `reset` once and **release** the `boot` button.\
The LED should become a solid color.

### 6.3 Modify and Test
Modify the sample project (for example, adjust the blink interval) and rebuild the project to ensure that the changes are reflected on your board.

### 6.4 Debugging
Monitor the board

```bash
idf.py -p /dev/ttyACM0 monitor
```
Note that only one terminal can be connected at any time.

Clean project
```bash
idf.py fullclean
or 
rm -r build/
```

Create a new project form example
```bash
cp -r $IDF_PATH/examples/get-started/hello_world {new_project_name}
cd {new_project_name}
mv main/hello_world_main.c main/main.cpp
```

## 7. Additional Resources
ESP-IDF Official Documentation:
Getting Started with ESP-IDF (​
[DOCS.ESPRESSIF.COM](https://docs.espressif.com/projects/esp-idf/en/v5.4/esp32s3/get-started/index.html)
)

ESP-IDF VS Code Extension Documentation:
ESP-IDF VS Code Extension (​
[DOCS.ESPRESSIF.COM](https://docs.espressif.com/projects/esp-idf/en/v4.4.1/esp32s3/get-started/vscode-setup.html)
)

Hutscape ESP32-S3 Hello World Tutorial:
Hello World with ESP-IDF in VS Code (​
[HUTSCAPE.COM](https://docs.espressif.com/projects/esp-idf/en/v4.4.1/esp32s3/get-started/vscode-setup.html)
)

Community Support:
[Espressif Forum](https://www.esp32.com/) and [r/esp32 on Reddit](https://www.reddit.com/r/esp32/)\
ESP-IDF YouTube tutorials [playlist](https://www.youtube.com/watch?v=5IuZ-E8Tmhg&list=PLHX2-9M57aE5LVZnGwbo2cjnqvLqtu2OS)

By following these steps, you will have a fully functional development environment for your ESP32-S3 board on Ubuntu 22 using VS Code and ESP-IDF. Happy coding!
