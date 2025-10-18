<h1>📌 OTA Firmware Update System (STM32)</h1>
<p> <strong>Over-The-Air (OTA)</strong> firmware update system designed for STM32 microcontrollers.
This project enables one microcontroller (Transmitter) to send and flash a new firmware (HEX file) onto another microcontroller (Receiver) via the <strong>USART communication protocol</strong> — eliminating the need for a physical programmer.</p>

<hr />

<h2>📌 Project Overview</h2>
<p>This system demonstrates <strong> firmware updating</strong> for embedded devices, using a bootloader implemented on the receiver MCU.


<h3>📌 Key Objectives</h3>
<ul>
  <li>Enable <strong>firmware update via serial communication (USART)</strong></li>
  <li>Implement <strong>custom bootloader</strong> on the receiver MCU</li>
  <li>Parse and flash <strong>HEX</strong> files safely to Flash memory</li>
  <li>Follow <strong>layered architecture</strong> for code organization (MCAL, HAL, APP)</li>
</ul>

<hr />

<h2>⚙️ System Architecture</h2>
<pre><code> ┌─────────────────────┐        USART      ┌───────────────────────┐
 │   Transmitter MCU   │  &lt;----------------&gt;│    Receiver MCU       │
 │ (Application board) │                    │ (Bootloader system)   │
 └─────────────────────┘                    └───────────────────────┘
                                                      │
                                                      │
                                                      ▼
                                           [Flash Memory Writer]

</ul>
<hr />

<h2>📌 Features</h2>
<p> Bootloader on receiver MCU handles:</p>
<ul>
  <li>Erasing old firmware</li>
  <li>Writing new firmware line-by-line to Flash memory</li>
</ul>

<p> 📌Transmitter MCU handles:</p>
<ul>
  <li>Reading and parsing the HEX file</li>
  <li>Sending structured data frames through USART</li>
</ul>

<p> Drivers Implemented:</p>
<ul>
  <li><strong>RCC</strong> (Clock Control)</li>
  <li><strong>GPIO</strong></li>
  <li><strong>NVIC</strong></li>
  <li><strong>SysTick</strong></li>
  <li><strong>USART</strong></li>

</ul>

<p>✅ Designed with <strong>layered architecture</strong>:</p>
<ul>
  <li><strong>MCAL</strong> (Microcontroller Abstraction Layer)</li>
  <li><strong>HAL</strong> (Hardware Abstraction Layer)</li>
  <li><strong>APP</strong> (Application Layer)</li>
</ul>

<hr />



<hr />

<h2>🔧 Technical Specifications</h2>
<table>
  <thead>
    <tr>
      <th>Component</th>
      <th>Details</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>Microcontroller</strong></td>
      <td>STM32F401CC</td>
    </tr>
    <tr>
      <td><strong>Communication Protocol</strong></td>
      <td>USART</td>
    </tr>
    <tr>
      <td><strong>Programming Language</strong></td>
      <td>Embedded C</td>
    </tr>
    <tr>
      <td><strong>IDE / Toolchain</strong></td>
      <td>STM32CubeIDE / IAR Embedded Workbench</td>
    </tr>
    <tr>
      <td><strong>Bootloader Memory Start</strong></td>
      <td>Configurable (e.g., 0x08000000 → 0x08004000 for app)</td>
    </tr>
    <tr>
      <td><strong>Firmware Format</strong></td>
      <td>Intel HEX (.hex)</td>
    </tr>
    <tr>
      <td><strong>Architecture</strong></td>
      <td>Layered (MCAL → HAL → APP)</td>
    </tr>
  </tbody>
</table>

<hr />

<h2>📌 How It Works</h2>
<ol>
  <li><strong>Transmitter MCU:</strong>
    <ul>
      <li>Reads the HEX file line by line.</li>
      <li>Parses records and converts ASCII HEX data into binary.</li>
      <li>Sends data packets over USART to the receiver.</li>
    </ul>
  </li>
  <li><strong>Receiver MCU:</strong>
    <ul>
      <li>Receives packets, validates checksum.</li>
      <li>Writes data to Flash memory via FMI driver.</li>
      <li>After completion, jumps to the new application address.</li>
    </ul>
  </li>
  <li><strong>Verification:</strong>
    <ul>
      <li>The system ensures data integrity through simple checksum validation.</li>
      <li>Optional CRC checks can be added for production-grade reliability.</li>
    </ul>
  </li>
</ol>

<hr />

<h2>🧪 Testing &amp; Validation</h2>
<ul>
  <li>Tested on <strong>STM32F401CC</strong> and <strong>STM32F401CC</strong> boards.</li>
  <li>Verified through <strong>serial monitoring</strong> and <strong>in-memory comparison</strong> post-update.</li>
  <li>Flash write and erase operations confirmed using STM32 ST-Link Utility.</li>
</ul>

<hr />

<h2>🧰 Build &amp; Flash Instructions</h2>

<h3>🧩 Requirements</h3>
<ul>
  <li>STM32CubeIDE </li>
  <li>ST-Link programmer (for initial bootloader flashing)</li>
  <li>Serial terminal (for monitoring USART)</li>
  <li>Two STM32 boards (Tx and Rx)</li>
</ul>

<h3>⚙️ Steps</h3>
<ol>
  <li>Build and flash the <strong>bootloader project</strong> onto the receiver MCU.</li>
  <li>Build and flash the <strong>transmitter project</strong> onto the sender MCU.</li>
  <li>Connect Tx/Rx lines between both MCUs:
    <ul>
      <li>TX → RX</li>
      <li>RX → TX</li>
      <li>GND → GND</li>
    </ul>
  </li>
  <li>Power both boards and start transmission.</li>
  <li>Observe flashing progress via terminal.</li>
</ol>

<hr />

<h2>📁 Example Workflow</h2>
<pre><code># Transmitter sends HEX records
:10000000020000200D0000004D00000021000000C1
:1000100000000000000000000000000000000000E0
...
# Receiver writes each line to Flash
[Bootloader] Erasing old firmware...
[Bootloader] Writing new firmware...
[Bootloader] Done. Jumping to Application.
</code></pre>

<hr />

<h2>🧠 Future Enhancements</h2>
<ul>
  <li>Add <strong>CRC validation</strong> before executing new firmware</li>
  <li>Implement <strong>wireless OTA (ESP8266 / BLE)</strong></li>
  <li>Support <strong>multiple MCU families </strong></li>
  <li>Add <strong>progress tracking</strong> and error recovery</li>
</ul>



