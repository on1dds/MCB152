# MCB152
The MCB152 is a microcontroller board that can load and debug programs in RAM and then run them. The device contains an Intel processor, which is a derivate of the 80C51BH and respects the standard Intel memory architecture. This ensures a 100 percent compatibility with most existing 8051 software. In addition to the standard 8051 functionality, the 80C152jb has an on-board multi-protocol communication controller called the Global Serial Channel (GSC). This makes the MCB152 exceptionally suitable for wired and wireless high-speed communication at up to 2Mbit.

The MCB152 Kickstart firmware is contained in an 8kbytes EPROM and offers a full functioning Intel-HEX loader, ASCII-dumper, disassembler, debugger and an entire library of functions which is copied to CODE memory at power-on.

This approach makes the MCB152 a must have for on the flow development of both hardware and software.

Check out the Hardware and Firmware sections for an extended overview of the MCB152 architecture. Schematics and sourcecodes can be found in the download section.

MCB152 projects
---
- How to build the hardware
- Kickstart firmware with integrated:
  - IntelHEX loader
  - Disassembler
  - Standard Library
- KISS: AX.25 Packet Radio communication
- SLIP: AX.25 implementation in modem emulation

Related links
---
- Assembler: http://john.ccac.rwth-aachen.de:8000/as/
