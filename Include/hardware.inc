        IF (HARDWARE_INC)
        ELSE
HARDWARE_INC      SET     1
;**
;**     $Filename: hardware.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 10/01/1998
;**
;**     MCB152 Hardware Registering
;**
;**     Coded by Joachim Elen
;**

;----------------------------------------------------------
;
;       Interrupt Vectors
;
;----------------------------------------------------------

        SETCODE RESET, 0000h            ;Power-up Reset
        SETCODE EXTI0, 0003h            ;External Interrupt 0
        SETCODE TIMER0,000Bh            ;Timer 0
        SETCODE EXTI1, 0013h            ;External Interrupt 1
        SETCODE TIMER1,001Bh            ;Timer 1
        SETCODE SINT,  0023h            ;Serial Interrupt

        SETCODE GSCRV,0002Bh            ;GSC Receive Valid
        SETCODE GSCRE,00033h            ;GSC Receive Error
        SETCODE DMA0, 0003Bh            ;DMA Channel 0 Done
        SETCODE GSCTV,00043h            ;GSC Transmit Valid
        SETCODE GSCTE,0004Bh            ;GSC Transmit Error
        SETCODE DMA1, 00053h            ;DMA Channel 1 Done

;----------------------------------------------------------
;
;       80c152 Register Extension
;
;----------------------------------------------------------

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

PR            EQU 1 SHL  0
PR_SDLC       EQU PR
PR_CSMA       EQU 0
PR_CSMA_CD    EQU PR_CSMA

PL0           EQU 1 SHL  1
PL1           EQU 1 SHL  2
PL_0          EQU 0
PL_8          EQU PL0
PL_32         EQU PL1
PL_64         EQU PL1+PL0

CT            EQU 1 SHL  3
CT_16         EQU 0
CT_32         EQU CT

AL            EQU 1 SHL  4
AL_8          EQU 0
AL_16         EQU AL

M0            EQU 1 SHL  5
M1            EQU 1 SHL  6
M_NORMAL      EQU 0
M_RAWRX       EQU M0
M_RAWTX       EQU M1
M_ALTBACKOFF  EQU M0+M1

XTCLK         EQU 1 SHL  7

TXC_ENABLE    EQU TXC
TXC_DISABLE   EQU 0

;------  Local Serial Channel baudrates

LSC_1200   EQU  LOW -48
LSC_2400   EQU  LOW -24
LSC_4800   EQU  LOW -12
LSC_9600   EQU  LOW -6
LSC_14400  EQU  LOW -4
LSC_19200  EQU  LOW -3
LSC_28800  EQU  LOW -2
LSC_57600  EQU  LOW -1
LSC_READ   EQU  0

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
GSC_172800 EQU  7
GSC_230400 EQU  5
GSC_460800 EQU  3
GSC_691200 EQU  1
GSC_XCLK   EQU  0               ;external clocking used

        ENDIF   ; HARDWARE_INC
