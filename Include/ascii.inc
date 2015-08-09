        IFNDEF  ASCII_INC
ASCII_INC       EQU     1

;**
;**     $Filename: ascii.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 10/01/1998
;**
;**     Definition of ASCII-names
;**
;**     Coded by Joachim Elen
;**

;------ ASCII-name definition

NUL       EQU 00h ;null
NULL      EQU 00h ;null
SOH       EQU 01h ;start of heading
STX       EQU 02h ;start of text
ETX       EQU 03h ;end of text
EOT       EQU 04h ;end of transmission
ENQ       EQU 05h ;enquire
ACK       EQU 06h ;acknoledge
BEL       EQU 07h ;bell
BS        EQU 08h ;backspace
HT        EQU 09h ;horizontal tab
LF        EQU 0Ah ;line feed
VT        EQU 0Bh ;vertical tab
FF        EQU 0Ch ;form feed
CR        EQU 0Dh ;carriage return
SO        EQU 0Eh ;shift out
SI        EQU 0Fh ;shift in
DLE       EQU 10h ;data link escape
DC1       EQU 11h ;device control 1
DC2       EQU 12h ;device control 2
DC3       EQU 13h ;device control 3
DC4       EQU 14h ;device control 4
NAK       EQU 15h ;negative acknowledge
SYN       EQU 16h ;syncronous idle
ETB       EQU 17h ;end of transmission block
CAN       EQU 18h ;cancel
EM        EQU 19h ;end of medium
SUB       EQU 1Ah ;substitute
ESC       EQU 1Bh ;escape, prefix
FS        EQU 1Ch ;file separator
GS        EQU 1Dh ;group separator
RS        EQU 1Eh ;record separator
US        EQU 1Fh ;unit separator
SPACE     EQU ' ' ;space
SEMICOLON EQU 3Bh ;semicolon
COMMA     EQU 2Ch ;comma
CEDILLA   EQU 2Ch ;comma
        ENDIF     ; ASCII_INC
