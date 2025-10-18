<h1> OTA Firmware Update System (STM32)</h1>
<p>
   <strong>Over-The-Air (OTA)</strong> firmware update system for STM32 microcontrollers. 
  This project allows one MCU (Transmitter) to send and flash a new firmware (HEX file) 
  onto another MCU (Receiver) via the <strong>USART protocol</strong>, removing the need for a hardware programmer.
</p>

<hr />

<h2>📌 Project Overview</h2>
<p>
  This system demonstrates <strong>firmware updating</strong> for STM32 through a custom bootloader 
  on the receiver MCU. It is ideal for automotive ECUs, IoT, and industrial controllers where field updates are essential.
</p>

<h3>📌 Key Objectives</h3>
<ul>
  <li>Enable <strong>firmware updates via USART</strong></li>
  <li>Implement a <strong>custom bootloader</strong> on the receiver MCU</li>
  <li>Parse and flash <strong>HEX</strong> files safely into Flash memory</li>
  <li>Ensure reliable communication between Transmitter and Receiver(USART)</li>
  <li>Follow a <strong>layered architecture</strong> (MCAL, HAL, APP)</li>
</ul>

<hr />

<h2>📌 System Architecture</h2>
<pre><code> ┌─────────────────────┐        USART       ┌───────────────────────┐
 │   Transmitter MCU   │  <---------------->│    Receiver MCU       │
 │ (Application Board) │                    │ (Bootloader System)   │
 └─────────────────────┘                    └───────────────────────┘
                                                      │
                                                      ▼
                                            [Flash Memory Writer]
</code></pre>

<hr />

<h2>📌 Features</h2>
<ul>
  <li><strong>Receiver (Bootloader)</strong>:
    <ul>
      <li>Erases application area firmware  </li>
      <li>Writes new firmware to Flash line-by-line</li>
    </ul>
  </li>
  <li><strong>Transmitter</strong>:
    <ul>
      <li>Reads the HEX file</li>
      <li>Sends structured data packets over USART</li>
    </ul>
  </li>
  <li><strong>Drivers Implemented:</strong> RCC, GPIO, NVIC, SysTick, USART, HEXPARSER, FMI</li>
  <li><strong>Architecture:</strong> MCAL → HAL → APP</li>
</ul>

<hr />


<h2>📌 Technical Specifications</h2>
<table>
  <thead>
    <tr><th>Component</th><th>Details</th></tr>
  </thead>
  <tbody>
    <tr><td>Microcontroller</td><td>STM32F401CC</td></tr>
    <tr><td>Protocol</td><td>USART</td></tr>
    <tr><td>Language</td><td>Embedded C</td></tr>
    <tr><td>IDE / Toolchain</td><td>STM32CubeIDE / ST-LINK Utility </td></tr>
    <tr><td>Bootloader Start</td><td>0x08000000 → 0x08004000 (App)</td></tr>
    <tr><td>Firmware Format</td><td>Intel HEX (.hex)</td></tr>
    <tr><td>Architecture</td><td>Layered (MCAL → HAL → APP)</td></tr>
  </tbody>
</table>

<hr />

<h2>📌 How It Works</h2>
<ol>
  <li><strong>Transmitter MCU</strong>
    <ul>
      <li>Reads HEX records line-by-line</li>
      <li>Parses and converts ASCII HEX to binary</li>
      <li>Sends frames to Receiver via USART</li>
    </ul>
  </li>
  <li><strong>Receiver MCU</strong>
    <ul>
      <li>Receives and validates packets</li>
      <li>Programs Flash using FMI driver</li>
      <li>Jumps to new application after success</li>
    </ul>
  </li>
  <li><strong>Verification:</strong> checksum validation (CRC optional)</li>
</ol>

<hr />

<h2>📌 Testing &amp; Validation</h2>
<ul>
  <li>Verified on NUCLEO-F401CC and STM32F103C8 (“Blue Pill”)</li>
  <li>Serial output monitored for transfer integrity</li>
  <li>Flash operations confirmed via ST-Link Utility</li>
</ul>

<hr />

<h2>📌 Build &amp; Flash Instructions</h2>
<h3>Requirements</h3>
<ul>
  <li>STM32CubeIDE / IAR Embedded Workbench</li>
  <li>ST-Link programmer (for bootloader flashing)</li>
  <li>Serial terminal (USART monitor)</li>
  <li>Two STM32 boards (Transmitter &amp; Receiver)</li>
</ul>

<h3>Steps</h3>
<ol>
  <li>Flash <strong>bootloader</strong> onto Receiver MCU</li>
  <li>Flash <strong>application/transmitter</strong> onto Sender MCU</li>
  <li>Connect UART lines: TX→RX, RX→TX, GND→GND</li>
  <li>Power both boards and start transmission</li>
  <li>Observe update progress through terminal logs</li>
</ol>

<hr />

<h2>📌 Example Output</h2>
<pre><code># Transmitter sends HEX records
:10000000020000200D0000004D00000021000000C1
:1000100000000000000000000000000000000000E0
...
# Receiver output
[Bootloader] Erasing old firmware...
[Bootloader] Writing new firmware...
[Bootloader] Done. Jumping to Application.
</code></pre>

<hr />

<h2>📌 Future Enhancements</h2>
<ul>
  <li>CRC validation before jump</li>
  <li>Wireless OTA (ESP8266 / BLE)</li>
  <li>Multi-MCU family support (F4, F7, L4)</li>
  <li>Progress tracking &amp; error recovery</li>
</ul>


