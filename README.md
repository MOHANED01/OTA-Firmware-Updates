<h1>🔄 OTA Firmware Update System (STM32)</h1>
<p>
  A reliable <strong>Over-The-Air (OTA)</strong> firmware update system for STM32 microcontrollers. 
  This project allows one MCU (Transmitter) to send and flash a new firmware (HEX file) 
  onto another MCU (Receiver) via the <strong>USART protocol</strong>, removing the need for a hardware programmer.
</p>

<hr />

<h2>🚀 Project Overview</h2>
<p>
  This system demonstrates <strong>remote firmware updating</strong> for embedded devices through a custom bootloader 
  on the receiver MCU. It is ideal for automotive ECUs, IoT, and industrial controllers where field updates are essential.
</p>

<h3>🎯 Key Objectives</h3>
<ul>
  <li>Enable <strong>firmware updates via USART</strong></li>
  <li>Implement a <strong>custom bootloader</strong> on the receiver MCU</li>
  <li>Parse and flash <strong>Intel HEX</strong> files safely into Flash memory</li>
  <li>Ensure reliable communication between Transmitter and Receiver</li>
  <li>Follow a <strong>layered architecture</strong> (MCAL, HAL, APP)</li>
</ul>

<hr />

<h2>⚙️ System Architecture</h2>
<pre><code> ┌─────────────────────┐        USART        ┌───────────────────────┐
 │   Transmitter MCU   │  <----------------> │    Receiver MCU       │
 │ (Application Board) │                    │ (Bootloader System)   │
 └─────────────────────┘                    └───────────────────────┘
          │                                            │
          ▼                                            ▼
     [HEX Parser]                             [Flash Memory Writer]
</code></pre>

<hr />

<h2>🧩 Features</h2>
<ul>
  <li><strong>Receiver (Bootloader)</strong>:
    <ul>
      <li>Erases previous firmware</li>
      <li>Writes new firmware to Flash line-by-line</li>
      <li>Validates data integrity via checksum</li>
    </ul>
  </li>
  <li><strong>Transmitter</strong>:
    <ul>
      <li>Reads and parses the HEX file</li>
      <li>Sends structured data packets over USART</li>
    </ul>
  </li>
  <li><strong>Drivers Implemented:</strong> RCC, GPIO, NVIC, SysTick, USART, FMI</li>
  <li><strong>Architecture:</strong> MCAL → HAL → APP</li>
</ul>

<hr />

<h2>🧱 Project Structure</h2>
<pre><code>OTA-Firmware-Update/
├── inc/          # Header files
├── src/          # Source files
├── bootloader/   # Bootloader logic
├── parser/       # HEX file parser
├── drivers/      # Peripheral drivers
├── configs/      # MCU and system configuration
├── README.md
└── .gitignore
</code></pre>

<hr />

<h2>🔧 Technical Specifications</h2>
<table>
  <thead>
    <tr><th>Component</th><th>Details</th></tr>
  </thead>
  <tbody>
    <tr><td>Microcontroller</td><td>STM32F401CC</td></tr>
    <tr><td>Protocol</td><td>USART</td></tr>
    <tr><td>Language</td><td>Embedded C</td></tr>
    <tr><td>IDE / Toolchain</td><td>STM32CubeIDE / IAR</td></tr>
    <tr><td>Bootloader Start</td><td>0x08000000 → 0x08004000 (App)</td></tr>
    <tr><td>Firmware Format</td><td>Intel HEX (.hex)</td></tr>
    <tr><td>Architecture</td><td>Layered (MCAL → HAL → APP)</td></tr>
  </tbody>
</table>

<hr />

<h2>🧠 How It Works</h2>
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

<h2>🧪 Testing &amp; Validation</h2>
<ul>
  <li>Verified on NUCLEO-F401CC and STM32F103C8 (“Blue Pill”)</li>
  <li>Serial output monitored for transfer integrity</li>
  <li>Flash operations confirmed via ST-Link Utility</li>
</ul>

<hr />

<h2>🧰 Build &amp; Flash Instructions</h2>
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

<h2>📁 Example Output</h2>
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

<h2>🚀 Future Enhancements</h2>
<ul>
  <li>CRC validation before jump</li>
  <li>Wireless OTA (ESP8266 / BLE)</li>
  <li>Multi-MCU family support (F4, F7, L4)</li>
  <li>Progress tracking &amp; error recovery</li>
</ul>

<hr />

<h2>📚 References</h2>
<ul>
  <li>STM32 Reference Manual RM0368 (Flash programming)</li>
  <li>ARM Cortex-M4 Architecture Docs</li>
  <li>Intel HEX File Format Specification</li>
</ul>

<hr />

<h2>👨‍💻 Author</h2>
<p>
  <strong>Mohaned Hossam</strong><br />
  Embedded Software Engineer<br />
  📧 <a href="mailto:mohanedtohamy444@gmail.com">mohanedtohamy444@gmail.com</a><br />
  🔗 <a href="https://www.linkedin.com/in/mohaned-hossam-8593041b3">LinkedIn</a><br />
  💻 <a href="https://github.com/MOHANED01">GitHub</a>
</p>

<hr />

<p><strong>⭐ “Empowering embedded systems with intelligent, updatable firmware.”</strong></p>
