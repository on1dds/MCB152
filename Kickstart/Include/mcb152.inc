        IF (MCB152_INC)
        ELSE
MCB152_INC      SET     1
;**
;**     $Filename: mcb152.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 02/05/1998
;**
;**     MCB152 system include
;**
;**     Coded by Joachim Elen
;**

KICKID          EQU     0FFFAh
VERSION         EQU     1
REVISION        EQU     0

MCBVER  MACRO
        pushw   DP
        mov     DPTR,#-2
        clr     A
        movc    A,@A+DPTR
        popw    DP
        mov
        ENDM

MCBREV  MACRO
        pushw   DP
        mov     DPTR,#-1
        clr     A
        movc    A,@A+DPTR
        popw    DP
        mov
        ENDM

;----------------------------------------------------------
;
;       Fixed MCB152 Bootvectors
;
;----------------------------------------------------------
        SETCODE ColdReboot,0FFF0h       ;Coldreboot
        SETCODE GoEPROM,0FFF5h          ;Coldreboot to address in EPROM


        ENDIF   ; MCB152_INC
