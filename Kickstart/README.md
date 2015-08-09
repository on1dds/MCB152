# MCB152-Kickstart
firmware for Intel 80c152jb based microcontroller


Kickstart is the MCB152 application loader/debugger firmware.
The Firmware version can be detected by user applications at address 0FFFAh,
finding at 0FFFA: 'KICK',VERSION,REVISION.
minor revisions, indicated with a letter are not noticed. This means v1.0 and v1.0b
can be considered the same.

Version 1.0
---
- A commandline interface is implemented to interact with the user. real-time executed, single byte instructions are implemented. Functionalities:
- automatic baudrate detection at most courant baudrates up to 56700 baud and for most of the ASCII chars (with loss of that character)
- echoing of characters to interact with user
- errors in datastreams refuse further processing until end of stream
- commands can be held/continued using spacebar
- IntelHEX loader
- ASCII dump monitor
- full 80C152 disassembler
- debug execution for subroutines at chosen address
- memoryclear is automatically performed if no boot routine is found at address 0FFF0h, indicating a power-on status
- manual memoryclear is possible.
- standard library was shadowed to address 0F000h to be accessible for user-applications. These can be overwritten however.

Version 1.0b
---
- Firmware identification is held until a readable, non IntelHEX charcter was printed to the MCB152 after baudrate detection.
- command line interface is rewritten to be more natural in response. Entering commands feels now like DOS
- Some library functions where rewritten or renamed, Delay() bug is fixed

Version 1.0c
---
- Library is relocated, compatibility with older versions only after recompiling sourcecode. Library contains standard header.
- CR/LF solution in front of strings is now replace by a standard CR after the string.
- Library is extended with several new routines.
- CODE memory is no longer erased when an error occures.
- New and much better auto-baudrate detection.
- Some major and minor bug fixes.
- code is optimized, gained nearly 1 kB of space.
- hackershield is removed, source is spread freely.
- commandprompt shows PC-counter
