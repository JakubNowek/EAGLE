<br />
<div align="center">
  <h2 align="center">Electronics in Automation</h3>

  <p align="center">
    7-Segment Display Clock Project
    <br />
    <br />
    <a href="https://github.com/JakubNowek/EAGLE/issues">Report Bug</a>
    ·
    <a href="https://github.com/JakubNowek/EAGLE/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li><a href="#finished-project">Finished Project</a>
    </li>
    <li><a href="#pcb-layout">PCB layout</a></li>
    <li><a href="#arduino-code">Arduino Code</a></li>
    <li><a href="#bill-of-materials">Bill of materials</a></li>
  </ol>
</details>

## About the Project
The ESP-01s module connects to NTP server and retrives information about the current date from it. Next data is forwarded towards Arduino Pro-Mini which extracts the time in hours, minutes and seconds and sends them towards 7-segments display through shift register.
Everything is powered up by a 7.5-25V power supply, the power of which is reduced to 5V by a voltage stabilizer.

## Finished Project
![photo](https://i.imgur.com/30RqNAv.jpg)

## PCB layout
Layout was auto generated using Altium Designer.
![pcb layout](https://i.imgur.com/HhZoBhG.png)

## Arduino Code
Used code for ESP module and Pro-Mini board can be found [here](projects/Serial_NTP_clock/ESP8266_with_NTP_code.ino) and [here](projects/Serial_NTP_clock/Pro_mini_code.ino).

## Bill of materials
| Qty | Value       | Device              |
|-----|-------------|---------------------|
| 2   |             | 7SEG-CA             |
| 6   |             | BC556A-PNP-TO92-EBC |
| 2   | 0.1u        | C-EU025-025X050     |
| 6   | 100         | R-EU_0414/15        |
| 1   | 10u         | C-EU025-025X050     |
| 10  | 220         | R-EU_0414/15        |
| 1   | 2k2         | R-EU_0414/15        |
| 2   | 470u/25V    | CPOL-EUE5-8.5       |
| 1   | 74HC595N    | 74HC595N            |
| 1   | 7805T       | 7805T               |
| 1   | DCJ0202     | DCJ0202             |
| 1   | ESP-01      | ESP-01              |
| 1   | LD117AV     | LD117AV             |
| 1   | LDQ-M3604RI | LDQ-M3604RI         |
| 1   | PRO-MINI    | PRO-MINI            |