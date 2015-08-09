        IFNDEF IKICK_INC
IKICK_INC        EQU     1
;**
;**     $Filename: kick.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 09/08/1998
;**
;**     Kickstart library definitions include
;**
;**     Coded by Joachim Elen
;**

        INCLUDE "macros.inc"
        INCLUDE "library.inc"

;------ Kickstart Constants

KICK_VERSION    EQU     1       ;kickstart version
KICK_REVISION   EQU     0       ;kickstart revision

;------ Fixed Kickstart Bootvectors

        SETCODE ColdReboot,0FFF0h       ;Coldreboot
        SETCODE GoKickROM,0FFF5h        ;jump to address in ROM

;----------------------------------------------------------
;
;       Kickstart library routines
;
;----------------------------------------------------------
        LIBDEF  Kickbase,0F000h
        LIBNAME Kickbase,!K,!I,!C,!K

;------------------
;System routines
;------------------
        FUNCDEF WarmReboot      ;warmreboot application
        FUNCDEF Reserved00      ;coldreboot application
        FUNCDEF Hold            ;holds the processor, including interrupts
        FUNCDEF FlashLED        ;Reserved00
        FUNCDEF Delay           ;delay in units of 10ms

        FUNCDEF ClearXRam       ;clear DATA memory
        FUNCDEF ClearChip       ;clear CHIP memory

        FUNCDEF ReadCRAM        ;read a byte from CRAM
        FUNCDEF WriteCRAM       ;write a byte to CRAM
        FUNCDEF ReadKick        ;read a byte from EPROM

        FUNCDEF CopyMemXC       ;copy memory from CODE to DATA memory
        FUNCDEF Reserved01      ;Reserved01 - CompareMemXC
        FUNCDEF CopyMemXX       ;copy memory from DATA to DATA memory
        FUNCDEF CompareMemXX    ;compare two area's in DATA memory
        FUNCDEF GSCClearRFIFO   ;clear Rx-FIFO of GSC

;------------------
;LSC I/O routines
;------------------
        FUNCDEF OpenLSC         ;open LSC with Autobaud function
        FUNCDEF OldOpenLSC      ;open LSC (obsolete)
        FUNCDEF PutChar         ;write character
        FUNCDEF GetChar         ;read character
        FUNCDEF NewLine         ;write <CR>
        FUNCDEF PutBin          ;write 8-bits as binary
        FUNCDEF PutDec4         ;write 4-bits as decimal (0-16)
        FUNCDEF PutDec8         ;write 8-bits as decimal (0-255)
        FUNCDEF PutDec16        ;write 16-bits as decimal (0-65535)
        FUNCDEF PutHex4         ;write 4-bits as hexadecimal (0-F)
        FUNCDEF PutHex8         ;write 8-bits as hexadecimal (0-FF)
        FUNCDEF PutHex16        ;write 16-bits as hexadecimal (0-FFFF)
        FUNCDEF PutAddress      ;write address in DPTR as 16-bits (0-FFFF)
        FUNCDEF PutMessage      ;write string from CODE memory
        FUNCDEF PutString       ;write string from DATA memory

        FUNCDEF GetDec4         ;read 4-bits as decimal (0-9)
        FUNCDEF Reserved02      ;Reserved01
        FUNCDEF GetDec16        ;read 16-bits as decimal (0-65535)
        FUNCDEF GetHex4         ;read 4-bits as hexadecimal (0-F)
        FUNCDEF GetHex8         ;read 8-bits as hexadecimal (0-FF)
        FUNCDEF GetHex16        ;read 16-bits as hexadecimal (0-FFFF)
        FUNCDEF GetString       ;read string to DATA memory
        FUNCDEF WaitSilence     ;wait until charstream stops at LSC

;------------------
;String operations
;------------------
        FUNCDEF StrNull         ;erase chars from string
        FUNCDEF StrLength       ;count non-null chars in string
        FUNCDEF StrUpper        ;convert chars in string to uppercase
        FUNCDEF StrLower        ;convert chars in string to lowercase
        FUNCDEF StrCopy         ;copy sourcestring to destinationstring
        FUNCDEF StrMoveLeft     ;shift string 'index' chars to left
        FUNCDEF StrMoveRight    ;shift string 'index' chars to right
        FUNCDEF StrCompare      ;compare 2 strings
        FUNCDEF StrCompareSub   ;compare substring into mainstring
        FUNCDEF StrPos          ;find substring into mainstring
        FUNCDEF StrDelete       ;delete 'count' chars from 'index' in string
        FUNCDEF StrConcat       ;append string to another
        FUNCDEF Reserved03      ;insert substring into main string

;------------------
;Usefull Tools
;------------------
        FUNCDEF CharToUpper     ;convert char to uppercase
        FUNCDEF CharToLower     ;convert char to lowercase
        FUNCDEF Hex2ASCII       ;convert hexcipher to ASCII
        FUNCDEF ASCII2Dec       ;convert ASCII to decimal cipher
        FUNCDEF ASCII2Hex       ;convert ASCII to hexadecimal cipher
        FUNCDEF AddDecDigit     ;shift base, include decimal cipher
        FUNCDEF AddHexDigit     ;shift base, include hexadecimal cipher
        FUNCDEF CRCInit         ;init temporary CRC-checksum
        FUNCDEF CRCPass         ;include data to temporary CRC
        FUNCDEF CRCFinish       ;recalculate temporary CRC to final CRC


        ENDIF   ; MCB152_INC
