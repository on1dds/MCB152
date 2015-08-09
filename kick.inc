        IF (KICK_INC)
        ELSE
KICK_INC        SET 1
;**
;**     $Filename: kick.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 15/01/1998
;**
;**     MCB152 Kickstart firmware internal
;**
;**     Coded by Joachim Elen
;**

;----------------------------------------------------------
;
;       Kickstart specific MACRO definitions
;
;----------------------------------------------------------

CPLMEM  MACRO
        cpl     P1.7
        nop
        nop
        ENDM

;----------------------------------------------------------
;
;       Error messages
;
;----------------------------------------------------------

ERR_ILLEGALCHAR EQU 1   ;illegal character in commandline
ERR_RECTYPE     EQU 2   ;unsupported recordtype
ERR_VERIFY      EQU 3   ;RAM write did not verify correct
ERR_CHECKSUM    EQU 4   ;checksum error
ERR_COMMAND     EQU 5   ;unknown command
ERR_PARAMETER   EQU 6   ;illegal parameter
ERR_NOBOOTVECT  EQU 7   ;bootvector was overwritten, could not execute
ERR_NOBOOTCODE  EQU 8   ;no code found at bootaddress
ERR_WRONGKICK   EQU 9   ;kickstart version has been manipulated
ERR_REGNAME     EQU 10  ;registername is not supported

ERR_NOTAVAIL    EQU -2  ;
ERR_IHEXFAIL    EQU -1  ;IHexload failed

;----------------------------------------------------------
;
;       IntelHEX recordtype definition
;
;----------------------------------------------------------

IH_DATA        EQU 0    ;data record
IH_EOF         EQU 1    ;end of file record
IH_XSEG        EQU 2    ;extended segment address record
IH_STARTSEG    EQU 3    ;start segment address record
IH_XADDR       EQU 4    ;extended linear address record
IH_STARTADDR   EQU 5    ;start linear address record

;----------------------------------------------------------
;
;       Onchip structures
;
;----------------------------------------------------------

        STRUCTURE 020h

        ;IntelHex loader
          BOOL  ihl_status      ;ihex status
          BOOL  ihl_errors      ;ihex errors

        ;Bootstrap menu
          BOOL  cli_status      ;bootstrap status
          UBYTE cli_lastcmd     ;last command
          UWORD cli_param1      ;
          UWORD cli_param2      ;

        ;Debug registers
          VOID  dbg_registers
          UBYTE dbg_acc
          UBYTE dbg_b
          UBYTE dbg_psw
          UBYTE dbg_dph
          UBYTE dbg_dpl
          UBYTE dbg_ar0
          UBYTE dbg_ar1
          UBYTE dbg_ar2
          UBYTE dbg_ar3
          UBYTE dbg_ar4
          UBYTE dbg_ar5
          UBYTE dbg_ar6
          UBYTE dbg_ar7

;----------------------------------------------------------
;
;       Bit Definitions
;
;----------------------------------------------------------

;------ IntelHEX errors

IHLERR_ILLEGAL  BIT ihl_errors.0        ;invalid ASCII-character
IHLERR_CHECKSUM BIT ihl_errors.1        ;checksum error
IHLERR_RECTYPE  BIT ihl_errors.2        ;unsupported recordtype
IHLERR_VERIFY   BIT ihl_errors.3        ;RAM-verify error

;------ IntelHEX status

IHLSTAT_EOF     BIT ihl_status.0        ;end of file record

CLI_GOTEND      BIT cli_status.0        ;end address is known
CLI_HELD        BIT cli_status.1        ;command was held
CLI_NOPROMPT    BIT cli_status.2        ;disable command line prompt



        ENDIF

