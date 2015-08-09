        IF (AX25_INC)
        ELSE
AX25_INC        SET     1
;**
;**     $Filename: ax25.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 30/03/1998
;**
;**     AX.25 Protocol Identifiers and Handlers
;**
;**     Coded by Joachim Elen
;**

;----------------------------------------------------------
;
;       AX.25 Specific MACRO definition
;
;----------------------------------------------------------

JMPFTYP MACRO iframe,sframe,uframe
        jnb     ACC.0,$+9       ;jump for Information frame
        jnb     ACC.1,$+9       ;jump for Supervisor frame
        ljmp    uframe          ;jump for Unnumbered frame
        ljmp    iframe
        ljmp    sframe
        ENDM

GTXSEQ  MACRO   reg,accu
        anl     accu,#FC_TXSEQ
        rr      accu
        ENDM

GRXSEQ  MACRO   reg,accu
        anl     accu,#FC_RXSEQ
        rr      accu
        rr      accu
        rr      accu
        rr      accu
        rr      accu
        ENDM

GSSID   MACRO   accu
        anl     accu,#FC_SSID
        rr      accu
        ENDM

;----------------------------------------------------------
;
;       AX.25 ROUTINE MESSAGES
;
;----------------------------------------------------------

AX25_DONE               EQU 0   ;result is correct
AX25_FIELDCLOSED        EQU 1   ;addressfield is terminated

AX25_NOTFIELDALIGNED    EQU -1  ;addressfield is terminated before end
AX25_ADDRESSTOOLONG     EQU -2  ;addresspath is too long for AX.25 frame
AX25_ILLEGALCHAR        EQU -3  ;addressfield contains illegal characters
AX25_UNKNOWN            EQU -4  ;unidentified system error
AX25_INCORRECTFTYPE     EQU -5  ;incorrect frame type
AX25_EMPTYADDRESSFIELD  EQU -6  ;empty addressfield
AX25_SSIDTOOBIG         EQU -7  ;SSID is out of range [0-15]

;----------------------------------------------------------
;
;       FRAME CONTROL FIELD
;
;----------------------------------------------------------

;------ General FCF

FC_POLL         EQU 00010000b   ;poll bit
FC_FINALE       EQU 00010000b   ;finale bit
FC_TXSEQ        EQU 00001110b   ;send sequence
FC_RXSEQ        EQU 11100000b   ;receive sequence
FC_SSID         EQU 00011110b   ;second station identifier

;------ Information-transfer FCF

IFC_INFORMATION EQU 0b


;------ Supervisory FCF

SFC_SUPERVISORY EQU 01b         ;supervisory frame
SFC_FILTER      EQU 1111b       ;supervisory frame filter

SFC_RR          EQU 0001b       ;receive ready
SFC_RNR         EQU 0101b       ;receive not ready
SFC_REJ         EQU 1001b       ;reject
SFC_SREJ        EQU 1101b       ;selective reject


;------ Unnumbered FCF

UFC_UNNUMBERED  EQU 11b         ;unnumbered frame
UFC_FILTER      EQU 11101111b   ;unnumbered frame filter

UFC_SABME       EQU 01101111b   ;connect request extended (modulo 128)
UFC_SABM        EQU 00101111b   ;connect request
UFC_DISC        EQU 01000011b   ;disconnect
UFC_DM          EQU 00001111b   ;disconnected mode
UFC_UA          EQU 01100011b   ;unnumbered acknowledge
UFC_FRMR        EQU 10000111b   ;frame reject
UFC_UI          EQU 00000011b   ;unnumbered information
UFC_XID         EQU 10101111b   ;exchange identification. negotiate features
UFC_TEST        EQU 11100011b   ;test


;----------------------------------------------------------
;
;       PROTOCOL IDENTIFIER (PID)
;
;----------------------------------------------------------
PID_COMPRESSED  EQU 00000110b   ;Compressed TCP/IP (Van Jacobson)
PID_UNCOMPRESSED EQU 00000111b  ;Uncompressed TCP/IP (Van Jacobson)
PID_SEGMENT     EQU 00001000b   ;Segmentation Fragment
PID_TEXNET      EQU 11000011b   ;TEXNET datagram protocol
PID_LQP         EQU 11000100b   ;Link Quality Protocol
PID_APPLETALK   EQU 11001010b   ;AppleTalk
PID_APPLETALK_ARP EQU 11001011b ;AppleTalk ARP
PID_IP          EQU 11001100b   ;TCP/IP Internet Protocol
PID_ARP         EQU 11001101b   ;TCP/IP Address Resolution Protocol
PID_FLEXNET     EQU 11001110b   ;FlexNet
PID_NETROM      EQU 11001111b   ;NET/ROM
PID_TEXT        EQU 11110000b   ;No Layer 3 implemented
PID_ESCAPE      EQU 11111111b   ;Escape character, next octet contains more

        ENDIF   ; AX25_INC

