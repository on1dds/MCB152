        IFNDEF LIBRARY_INC
LIBRARY_INC      EQU     1

;**
;**     $Filename: library.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 09/08/1998
;**
;**     MCB152 Function Library
;**
;**     Coded by Joachim Elen
;**

        INCLUDE "macros.inc"

;------ library constants

LIB_VECTSIZE    EQU     3
LIB_HEADSIZE    EQU     8


;----------------------------------------------------------
;
;       library definition macros (for creating libraries)
;
;----------------------------------------------------------

LIBDEF  MACRO   libname,libbase
libname EQU     libbase
LIBCNT  SET     libbase+LIB_HEADSIZE
        ENDM

FUNCDEF MACRO   fncname
fncname EQU     LIBCNT
LIBCNT  SET     LIBCNT+LIB_VECTSIZE
        ENDM

LIBNAME MACRO   lb,c1,c2,c3,c4
{"lb"}_id1 EQU     "c1"
{"lb"}_id2 EQU     "c2"
{"lb"}_id3 EQU     "c3"
{"lb"}_id4 EQU     "c4"
        ENDM


;----------------------------------------------------------
;
;       library presence check macros
;
;----------------------------------------------------------

LIBEXISTS MACRO libbase
        pushw   DP
        mov     DPTR,#libbase+0
        clr     A
        movc    A,@A+DPTR
        cjne    A,#libbase&_id1,$+24
        inc     DPTR
        clr     A
        movc    A,@A+DPTR
        cjne    A,#libbase&_id2,$+18
        inc     DPTR
        clr     A
        movc    A,@A+DPTR
        cjne    A,#libbase&_id3,$+12
        inc     DPTR
        clr     A
        movc    A,@A+DPTR
        cjne    A,#libbase&_id4,$+6
        clr     C
        sjmp    $+3
        setb    C
        popw    DP
        ENDM

LIBVER  MACRO   libbase
        pushw   DP
        mov     DPTR,#libbase+4
        clr     A
        movc    A,@A+DPTR
        popw    DP
        ENDM

LIBREV  MACRO   libbase
        pushw   DP
        mov     DPTR,#libbase+5
        clr     A
        movc    A,@A+DPTR
        popw    DP
        ENDM


        ENDIF   ; LIBRARY_INC
