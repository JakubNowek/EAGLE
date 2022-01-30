<br />
<div align="center">
  <h3 align="center">Electronics in automation</h3>

  <p align="center">
    7-Segment-Digital-Clock-Project
    <br />
    <br />
    <a href="https://github.com/othneildrew/Best-README-Template/issues">Report Bug</a>
    ·
    <a href="https://github.com/othneildrew/Best-README-Template/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li><a href="#Finished Project">Finished Project</a></li>
    <li><a href="#PCB layout">PCB layout</a></li>
    <li><a href="#PCB layout">Bill of materials</a></li>
  </ol>
</details>

## About the Project
The ESP-01s module connects to NTP server and retrives information about the current date from it. Next data is forwarded towards Arduino Pro-Mini which extracts the time in hours, minutes and seconds and sends them towards 7-segments display through shift register.
Everything is powered up by a 12V power supply, the power of which is reduced to 5V by a voltage stabilizer.

## Finished Project
![photo](https://i.imgur.com/30RqNAv.jpg)

## PCB layout
![pcb layout](https://i.imgur.com/HhZoBhG.png)


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