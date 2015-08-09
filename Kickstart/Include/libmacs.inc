        IF (LIBMACS_INC)
        ELSE
LIBMACS_INC        SET     1
;**
;**     $Filename: libmacs.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 3/06/1998
;**
;**     
;**
;**     Coded by Joachim Elen
;**


_CopyMemXC MACRO dest,src,size
        mov     DPTR,#src
        movwabs WR0,dest
        movwabs WR1,size
        call    CopyMemXC
        ENDM


_RouteToAddress MACRO field,dest,src
        mov     DPTR,#field
        movwabs WR1,dest
        movwabs WR0,src
        call    RouteToAddress
        ENDM


        ENDIF    ; LIBMACS_INC













