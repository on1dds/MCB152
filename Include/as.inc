    IFNDEF  AS_INC
AS_INC  EQU 1
;**
;**     $Filename: as.src
;**     $Release: 0
;**     $Revision: 1
;**     $Date: 15/11/2000
;**     $Coding: Joachim Elen
;**     
;**
;**     assembler extensions
;**		pseudo instructions
;**

H       EQU         0
L       EQU         1

HIGH    function    num,((num>>8)&0FFh)
high    function    num,((num>>8)&0FFh)
HI      function    num,((num>>8)&0FFh)
hi      function    num,((num>>8)&0FFh)
LOW     function    num,(num&0FFh)
low     function    num,(num&0FFh)
LO      function    num,(num&0FFh)
lo      function    num,(num&0FFh)

PROC    MACRO   name
        SECTION name
        PUBLIC  name:PARENT
name    LABEL   $
        ENDM


ENDP    MACRO   name
        ENDSECTION  name
        ENDM


    ENDIF   ;AS_INC
