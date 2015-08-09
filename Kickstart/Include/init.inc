        IF (INIT_INC)
        ELSE
INIT_INC      SET     1
;**
;**     $Filename: init.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 12/01/1998
;**
;**     Software initialization
;**
;**     Coded by Joachim Elen
;**

FALSE   EQU 00h
TRUE    EQU NOT FALSE

;----------------------------------------------------------
;
;       16-bit Register Definition
;
;----------------------------------------------------------
ACCL    EQU     ACC
ACCH    EQU     B

WR0L    EQU     R0
WR0H    EQU     R1
WR1L    EQU     R2
WR1H    EQU     R3
WR2L    EQU     R4
WR2H    EQU     R5
WR3L    EQU     R6
WR3H    EQU     R7

AWR0L   EQU     AR0
AWR0H   EQU     AR1
AWR1L   EQU     AR2
AWR1H   EQU     AR3
AWR2L   EQU     AR4
AWR2H   EQU     AR5
AWR3L   EQU     AR6
AWR3H   EQU     AR7

        ENDIF   ;INIT_INC
