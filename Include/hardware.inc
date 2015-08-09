        IFNDEF HARDWARE_INC
HARDWARE_INC      EQU   1

;**
;**     $Filename: hardware.inc
;**     $Release: 1
;**     $Revision: 1
;**     $Date: 09/08/1998
;**
;**     MCB152 Hardware Registeration
;**
;**     Coded by Joachim Elen
;**


;----------------------------------------------------------
;
;       Interrupt Vectors
;
;----------------------------------------------------------

RESET   LABEL   0000h           ;boot address
EXTI0   LABEL   0003h           ;external 0
TIMER0  LABEL   000Bh           ;timer 0
EXTI1   LABEL   0013h           ;external 1
TIMER1  LABEL   001Bh           ;timer 1
SINT    LABEL   0023h           ;serial interrupt

GSCRV   LABEL   002Bh           ;GSC receive valid
GSCRE   LABEL   0033h           ;GSC receive error
DMA0    LABEL   003Bh           ;DMA channel 0 done
GSCTV   LABEL   0043h           ;GSC transmit valid
GSCTE   LABEL   004Bh           ;GSC transmit error
DMA1    LABEL   0053h           ;DMA channel 1 done


;----------------------------------------------------------
;
;       16-bit Register Definition
;
;----------------------------------------------------------
HWREG   EQU     -4
SWREG   EQU     -3


WACC    EQU     SWREG
WACCL   EQU     ACC
WACCH   EQU     B
WR0     EQU     SWREG
WR0L    SFR     R0
WR0H    SFR     R1
WR1     EQU     SWREG
WR1L    SFR     R2
WR1H    SFR     R3
WR2     EQU     SWREG
WR2L    SFR     R4
WR2H    SFR     R5
WR3     EQU     SWREG
WR3L    SFR     R6
WR3H    SFR     R7

AWR0    EQU     HWREG
AWR0L   EQU     AR0
AWR0H   EQU     AR1
AWR1    EQU     HWREG
AWR1L   EQU     AR2
AWR1H   EQU     AR3
AWR2    EQU     HWREG
AWR2L   EQU     AR4
AWR2H   EQU     AR5
AWR3    EQU     HWREG
AWR3L   EQU     AR6
AWR3H   EQU     AR7

DP      EQU     HWREG

;----------------------------------------------------------
;
;       80c152 Register Extension
;
;----------------------------------------------------------
BITBASE EQU 20h
 
T0H           EQU TH0
T0L           EQU TL0
T1H           EQU TH1
T1L           EQU TL1

BCR0L         EQU BCRL0
BCR0H         EQU BCRH0
BCR1L         EQU BCRL1
BCR1H         EQU BCRH1
DAR0L         EQU DARL0
DAR0H         EQU DARH0
DAR1L         EQU DARL1
DAR1H         EQU DARH1
SAR0L         EQU SARL0
SAR0H         EQU SARH0
SAR1L         EQU SARL1
SAR1H         EQU SARH1

PR            EQU 1 <<  0
PR_SDLC       EQU PR
PR_CSMA       EQU 0
PR_CSMA_CD    EQU PR_CSMA

PL0           EQU 1 <<  1
PL1           EQU 1 <<  2
PL_0          EQU 0
PL_8          EQU PL0
PL_32         EQU PL1
PL_64         EQU PL1+PL0

CT            EQU 1 <<  3
CT_16         EQU 0
CT_32         EQU CT

AL            EQU 1 <<  4
AL_8          EQU 0
AL_16         EQU AL

M0            EQU 1 <<  5
M1            EQU 1 <<  6
M_NORMAL      EQU 0
M_RAWRX       EQU M0
M_RAWTX       EQU M1
M_ALTBACKOFF  EQU M0+M1

XTCLK         EQU 1 <<  7

TXC_ENABLE    EQU TXC
TXC_DISABLE   EQU 0

;------  Local Serial Channel baudrates

;standard baudrates - 11.0592 Mhz clock
LSC_AUTO	EQU 0
LSC_1200	EQU (-48 & 0FFh)
LSC_2400	EQU (-24 & 0FFh)
LSC_4800	EQU (-12 & 0FFh)
LSC_9600	EQU (- 6 & 0FFh)
LSC_14400	EQU (- 4 & 0FFh)
LSC_19200	EQU (- 3 & 0FFh)
LSC_28800	EQU (- 2 & 0FFh)
LSC_57600	EQU (- 1 & 0FFh)

LSC_921600	EQU	1		;not implemented
LSC_345600	EQU	2
LSC_172800	EQU	3

;extended baudrates - 14.7456 Mhz clock

LSC_X1200	EQU (-64 & 0FFh)
LSC_X2400	EQU (-32 & 0FFh)
LSC_X4800	EQU (-16 & 0FFh)
LSC_X9600	EQU (- 8 & 0FFh)
LSC_X19200	EQU (- 4 & 0FFh)
LSC_X38400	EQU (- 2 & 0FFh)
LSC_X76800	EQU (- 1 & 0FFh)

LSC_X921600	EQU	 1		;not implemented
LSC_X460800	EQU  2
LSC_X230400	EQU	 3



;------ Global Serial Channel baudrates

GSC_5400   EQU  255
GSC_9600   EQU  143
GSC_14400  EQU  95
GSC_19200  EQU  71
GSC_28800  EQU  47
GSC_38400  EQU  35
GSC_57600  EQU  23
GSC_76800  EQU  17
GSC_115200 EQU  11
GSC_125672 EQU  10
GSC_138240 EQU  9
GSC_153600 EQU  8
GSC_172800 EQU  7
GSC_197485 EQU  6
GSC_230400 EQU  5
GSC_460800 EQU  3
GSC_691200 EQU  1
GSC_XCLK   EQU  0               ;external clocking used

        ENDIF   ; HARDWARE_INC
