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
