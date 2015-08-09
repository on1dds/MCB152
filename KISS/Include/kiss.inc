        IF (KISS_INC)
        ELSE
KISS_INC        SET     1
;**
;**     $Filename: kiss.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 12/01/1998
;**
;**     
;**
;**     Coded by Joachim Elen
;**

;----------------------------------------------------------
;
;       KISS Specific MACRO definition
;
;----------------------------------------------------------

JPB     MACRO   pbit,label
        jnb     pbit,label
        ENDM

JNPB    MACRO   pbit,label
        jb      pbit,label
        ENDM

PBSET   MACRO   pbit
        clr     pbit
        ENDM

PBCLR   MACRO   pbit
        setb    pbit
        ENDM

PBCPL   MACRO   pbit
        cpl     pbit
        ENDM


PBMOV   MACRO   dpbit,spbit
        mov     C,spbit
        mov     dpbit,C
        ENDM

;----------------------------------------------------------
;
;       KISS constants
;
;----------------------------------------------------------

;------ Commands

KC_RETURN       EQU -1          ;back to downloader
KC_RETURN2      EQU -2          ;warmreboot

KC_DATAFRAME    EQU 0           ;dataframe
KC_TXDELAY      EQU 1           ;tx-delay
KC_PERSIST      EQU 2           ;persistance
KC_SLOTTIME     EQU 3           ;slottime
KC_TXTAIL       EQU 4           ;tx-tail
KC_HARDWARE     EQU 6           ;hardware

;------ Custom hardware commands

KCH_INFO        EQU 0           ;show info firmware
KCH_KISSINFO    EQU 1           ;show param info

KCH_GMOD        EQU 084h        ;hardware register settings
KCH_BAUD        EQU 095h  
KCH_SLOT        EQU 0B4h
KCH_PCON        EQU 087h

;------ Frame Escape sequences

FEND            EQU 0C0h        ;Frame END
FESC            EQU 0DBh        ;Frame ESCape
TFEND           EQU 0DCh        ;Transpose Frame END
TFESC           EQU 0DDh        ;Transpose Frame ESCape


;----------------------------------------------------------
;
;       External DATA memory partitioning
;
;----------------------------------------------------------
        xstructure 0000h
        xstruct RXBuf,RXBUFSIZE,10*1024 ;RX buffer
        xstruct TXBuf,TXBUFSIZE,20*1024 ;TX buffer

;----------------------------------------------------------
;
;       On-Chip Bit definitions
;
;----------------------------------------------------------

;------ KISS flags

KF_GETTYP       BIT  0          ;reading frametype
KF_CFRAME       BIT  1          ;frametype 'command'
KF_DFRAME       BIT  2          ;frametype 'data'
KF_FESC         BIT  3          ;frame-escape is active
KF_CFPARAM      BIT  4          ;reading 'command' parameter
KF_SETSFR       BIT  5          ;set special function register
KF_COLDREBOOT   BIT  6          ;restore MCB152
KF_WARMREBOOT   BIT  7          ;restore KISS-TNC
KF_INFO         BIT  8          ;show firmware information
KF_KISSINFO     BIT  9          ;show parameter settings


;------ TNC status flags

TX_BUSY         BIT  16          ;TX/GSC busy
TX_TAIL         BIT  17          ;TXTail active


;------ TNC status LEDs

LED_PUTGSC      BIT P4.0
LED_GETLSC      BIT P4.1
LED_GETGSC      BIT P4.2
LED_PUTLSC      BIT P4.3
LED_RXFULL      BIT P4.4
LED_TXFULL      BIT P4.5

BUTTON1         BIT P4.4
BUTTON2         BIT P4.5


;------ Baycom modem status

DCD             BIT P4.6
PTT             BIT P4.7

;----------------------------------------------------------
;
;       On-Chip Variable definitions
;
;----------------------------------------------------------

        STRUCTURE 030h          ;new data structure

;------ RX Variables

        APTR    rx_writeframe   ;GetGSC framepointer
        APTR    rx_writedata    ;GetGSC datapointer
        APTR    rx_readframe    ;PutLSC framepointer
        APTR    rx_readdata     ;PutLSC datapointer
        UWORD   rx_framelen     ;actual RX framelength
        UWORD   rx_allocated    ;RXBuffer allocated memory
        UBYTE   rx_framecount   ;framecounter

;------ TX Variables

        APTR    tx_writeframe   ;GetLSC framepointer
        APTR    tx_writedata    ;GetLSC datapointer
        APTR    tx_readframe    ;PutGSC framepointer
        APTR    tx_readdata     ;PutGSC datapointer
        UWORD   tx_framelen     ;actual TX framelength
        UWORD   tx_allocated    ;TXBuffer allocated memory
        UBYTE   tx_framecount   ;framecounter
        UWORD   tx_dmaframelen  ;actual TX framelength for DMA

;------ KISS Protocol variables

        UBYTE   kiss_command    ;command in execution
        UBYTE   kiss_hardcmd    ;hardware command
        UBYTE   kiss_randomize  ;persistance randomizer

        UBYTE   kiss_hardware
        UBYTE   kiss_txdelay
        UBYTE   kiss_persist
        UBYTE   kiss_slottime
        UBYTE   kiss_txtail
        UBYTE   kiss_fullduplex

        ENDIF   ; KISS_INC

