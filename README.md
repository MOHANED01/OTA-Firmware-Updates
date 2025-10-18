# 🔄 OTA Firmware Update System (STM32)

A reliable **Over-The-Air (OTA)** firmware update system designed for STM32 microcontrollers.  
This project enables one microcontroller (Transmitter) to send and flash a new firmware (HEX file) onto another microcontroller (Receiver) via the **USART communication protocol** — eliminating the need for a physical programmer.

---

## 🚀 Project Overview

This system demonstrates **remote firmware updating** for embedded devices, using a bootloader implemented on the receiver MCU.  
It’s an essential feature for modern embedded systems where field updates are required (e.g., automotive ECUs, IoT devices, industrial controllers).

### 🎯 Key Objectives
- Enable **firmware update via serial communication (USART)**  
- Implement **custom bootloader** on the receiver MCU  
- Parse and flash **Intel HEX** files safely to Flash memory  
- Provide robust communication between transmitter and receiver  
- Follow **layered architecture** for code organization (MCAL, HAL, APP)

---

## ⚙️ System Architecture

```plaintext
 ┌─────────────────────┐        USART        ┌───────────────────────┐
 │   Transmitter MCU   │  <----------------> │    Receiver MCU       │
 │ (Application board) │                    │ (Bootloader system)   │
 └─────────────────────┘                    └───────────────────────┘
          │                                            │
          │                                            │
          ▼                                            ▼
     [HEX Parser]                             [Flash Memory Writer]
🧩 Features

✅ Bootloader on receiver MCU handles:

Erasing old firmware

Writing new firmware line-by-line to Flash memory

Verifying data integrity

✅ Transmitter MCU handles:

Reading and parsing the HEX file

Sending structured data frames through USART

✅ Drivers Implemented:

RCC (Clock Control)

GPIO

NVIC

SysTick

USART

FMI (Flash Memory Interface)

✅ Designed with layered architecture:

MCAL (Microcontroller Abstraction Layer)

HAL (Hardware Abstraction Layer)

APP (Application Layer)

🧱 Project Structure
OTA-Firmware-Update/
├── inc/                     # Header files
├── src/                     # Source files
├── bootloader/              # Bootloader logic for receiver MCU
├── parser/                  # HEX file parser
├── drivers/                 # Peripheral drivers (GPIO, RCC, NVIC, USART, etc.)
├── configs/                 # System and MCU configuration files
├── README.md
└── .gitignore

🔧 Technical Specifications
Component	Details
Microcontroller	STM32F401CC
Communication Protocol	USART
Programming Language	Embedded C
IDE / Toolchain	STM32CubeIDE / IAR Embedded Workbench
Bootloader Memory Start	Configurable (e.g., 0x08000000 → 0x08004000 for app)
Firmware Format	Intel HEX (.hex)
Architecture	Layered (MCAL → HAL → APP)
🧠 How It Works

Transmitter MCU:

Reads the HEX file line by line.

Parses records and converts ASCII HEX data into binary.

Sends data packets over USART to the receiver.

Receiver MCU:

Receives packets, validates checksum.

Writes data to Flash memory via FMI driver.

After completion, jumps to the new application address.

Verification:

The system ensures data integrity through simple checksum validation.

Optional CRC checks can be added for production-grade reliability.

🧪 Testing & Validation

Tested on NUCLEO-F401CC and Blue Pill (STM32F103C8) boards.

Verified through serial monitoring and in-memory comparison post-update.

Flash write and erase operations confirmed using STM32 ST-Link Utility.

🧰 Build & Flash Instructions
🧩 Requirements

STM32CubeIDE or IAR

ST-Link programmer (for initial bootloader flashing)

Serial terminal (for monitoring USART)

Two STM32 boards (Tx and Rx)

⚙️ Steps

Build and flash the bootloader project onto the receiver MCU.

Build and flash the transmitter project onto the sender MCU.

Connect Tx/Rx lines between both MCUs:

TX → RX

RX → TX

GND → GND

Power both boards and start transmission.

Observe flashing progress via terminal.

📁 Example Workflow
# Transmitter sends HEX records
:10000000020000200D0000004D00000021000000C1
:1000100000000000000000000000000000000000E0
...
# Receiver writes each line to Flash
[Bootloader] Erasing old firmware...
[Bootloader] Writing new firmware...
[Bootloader] Done. Jumping to Application.

🧠 Future Enhancements

Add CRC validation before executing new firmware

Implement wireless OTA (ESP8266 / BLE)

Support multiple MCU families (F4, F7)

Add progress tracking and error recovery

📚 References

STM32 Reference Manual RM0368 (Flash programming section)

ARM Cortex-M4 Architecture Documentation

Intel HEX File Format Specification
