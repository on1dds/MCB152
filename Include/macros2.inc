        IF (MACROS_INC)
        ELSE
MACROS_INC      SET     1
;**
;**     $Filename: macros.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 10/01/1998
;**
;**     8052 Instruction extension
;**
;**     Coded by Joachim Elen
;**

;----------------------------------------------------------
;
;       Internal Macro Counters
;
;----------------------------------------------------------
RSET    MACRO   label,val
label   SET     label+val
        ENDM

mccnt   SET     0

;----------------------------------------------------------
;
;       Assembler Directive Extension
;
;----------------------------------------------------------

SETINT  MACRO   vector,address
        ORG     vector
        jmp     address
        ENDM

VOIDINT MACRO   vector
        ORG     vector
        reti
        ENDM

SETCODE MACRO   prog,address
prog    CODE    address
        ENDM



;------ Structure management for on-chip memory

BITSTRUCT MACRO base
ACOUNT  SET     base
        ENDM

BITDEF  MACRO   label
label   BIT     ACOUNT
        RSET    ACOUNT,1
        ENDM

BITSKIP MACRO
        RSET    ACOUNT,1
        ENDM

STRUCTURE MACRO base
ACOUNT  SET     base
        ENDM

VOID    MACRO   label
label   EQU     ACOUNT
        ENDM

APTR    MACRO   addr
addr    DATA    ACOUNT
addr&L  DATA    ACOUNT+0
addr&H  DATA    ACOUNT+1
        RSET    ACOUNT,2
        ENDM

UWORD   MACRO   wdat     
wdat    DATA    ACOUNT
wdat&L  DATA    ACOUNT+0
wdat&H  DATA    ACOUNT+1
        RSET    ACOUNT,2
        ENDM

BYTE    MACRO   bdat
bdat    DATA    ACOUNT
        RSET    ACOUNT,1
        ENDM

UBYTE   MACRO   bdat
bdat    DATA    ACOUNT
        RSET    ACOUNT,1
        ENDM

BOOL    MACRO   bdat
bdat    DATA    ACOUNT
        RSET    ACOUNT,1
        ENDM

STRUCT  MACRO   sdat,sizeof
sdat    DATA    ACOUNT
        RSET    ACOUNT,sizeof
        ENDM

;------ Structure Managemen for XDATA memory

XSTRUCTURE MACRO base
XACOUNT SET     base
        ENDM

XSTRUCT MACRO   struc,label,sizeof
label   SET     sizeof
struc   XDATA   XACOUNT
        RSET    XACOUNT,sizeof
        ENDM


;----------------------------------------------------------
;
;       8-bit CPU Instruction extensions
;
;----------------------------------------------------------

;------ Data Transfer

MOVA    MACRO   dest,source
        mov     A,source
        mov     dest,A
        ENDM

MOVS    MACRO   dest,source
        push    source
        pop     dest
        ENDM

EXG     MACRO   ea1,ea2
        push    ea1
        push    ea2
        pop     ea1
        pop     ea2
        ENDM

PUSHSTATE MACRO 
        push    PSW
        pushw   DP
        push    ACC
        ENDM

POPSTATE MACRO 
        pop     ACC
        popw    DP
        pop     PSW
        ENDM

PUSHREGS MACRO 
        push    AR0
        push    AR1
        push    AR2
        push    AR3
        push    AR4
        push    AR5
        push    AR6
        push    AR7
        ENDM

POPREGS MACRO 
        pop     AR7
        pop     AR6
        pop     AR5
        pop     AR4
        pop     AR3
        pop     AR2
        pop     AR1
        pop     AR0
        ENDM

;------ Arthemetic Operations

ADDA    MACRO   dest,source
        push    ACC
        mov     A,dest
        add     A,source
        mov     dest,A
        pop     ACC
        ENDM

SUBBA   MACRO   dest,source
        push    ACC
        mov     A,dest
        subb    A,source
        mov     dest,A
        pop     ACC
        ENDM

;------ Program Branching

LCJNE   MACRO   reg,num,label
        cjne    reg,num,$+5
        sjmp    $+5
        ljmp    label
        ENDM


JE      MACRO   label
        jnc     label
        ENDM

JNE     MACRO   label
        jc      label
        ENDM

LCJE    MACRO   reg,num,label
        cjne    reg,num,$+6
        ljmp    label
        ENDM

CJE     MACRO   reg,num,label           ;reg=num
        cjne    reg,num,$+5
        sjmp    label
        ENDM

CJA     MACRO   reg,num,label           ;reg>num
        cjne    reg,num,$+5
        sjmp    $+4
        jnc     label
        ENDM

CJNA    MACRO   reg,num,label           ;reg!>num
        cjne    reg,num,$+5
        sjmp    label
        jc      label
        ENDM

CJAE    MACRO   reg,num,label           ;reg>=num
        cjne    reg,num,$+3
        jnc     label
        ENDM

CJNAE   MACRO   reg,num,label           ;reg!>=num
        cjne    reg,num,$+3
        jc      label
        ENDM

CJB     MACRO   reg,num,label           ;reg<num
        cjne    reg,num,$+3
        jc      label
        ENDM

CJNB    MACRO   reg,num,label           ;reg!<num
        cjne    reg,num,$+3
        jnc     label
        ENDM

CJBE    MACRO   reg,num,label           ;reg<=num
        cjne    reg,num,$+5
        sjmp    label
        jc      label
        ENDM

CJNBE   MACRO   reg,num,label           ;reg!<=num
        cjne    reg,num,$+5
        sjmp    $+4
        jnc     label
        ENDM


CJNR    MACRO   reg,top,bot,label
        cja     reg,top,label
        cjb     reg,bot,label
        ENDM

CJR     MACRO   reg,top,bot,label
        cja     reg,bot,label
        cjb     reg,top,label
        ENDM


PUSHRET MACRO   address
        mov     A,#LOW(address)
        push    ACC
        mov     A,#HIGH(address)
        push    ACC
        ENDM


;----------------------------------------------------------
;
;       16-bit CPU Instruction extensions
;
;----------------------------------------------------------


;------ Data Transfer

MOVWABS MACRO   dest,value
        mov     dest&L,#LOW(value)
        mov     dest&H,#HIGH(value)
        ENDM

MOVW    MACRO   dest,source
        mov     dest&H,source&H
        mov     dest&L,source&L
        ENDM

MOVWACC MACRO   dest
        mov     dest&L,A
        mov     dest&H,#0
        ENDM

MOVWB   MACRO   wdest,bsrc
        mov     wdest&L,bsrc
        mov     wdest&H,#0
        ENDM

MOVWC   MACRO   dest
        push    ACC
        clr     A
        movc    A,@A+DPTR
        push    ACC
        mov     A,#1
        movc    A,@A+DPTR
        mov     dest&L,A
        pop     ACC
        mov     dest&H,A
        pop     ACC
        ENDM

MOVWCX  MACRO   dest,source
        pushw   DP
        movw    DP,source
        movx    A,@DPTR
        mov     dest&L,A
        inc     DPTR
        movx    A,@DPTR
        mov     dest&H,A
        popw    DP
        ENDM

MOVWXC  MACRO   dest,source
        pushw   DP
        movw    DP,dest
        mov     A,source&L
        movx    @DPTR,A
        inc     DPTR
        mov     A,source&H
        movx    @DPTR,A
        popw    DP
        ENDM

MOVWXABS MACRO   dest,source
        pushw   DP
        movw    DP,dest
        mov     A,#HIGH(source&L)
        movx    @DPTR,A
        inc     DPTR
        mov     A,#HIGH(source&H)
        movx    @DPTR,A
        popw    DP
        ENDM

CLRWX   MACRO   dest
        pushw   DP
        movw    DP,dest
        clr     A
        movx    @DPTR,A
        inc     DPTR
        movx    @DPTR,A
        popw    DP
        ENDM

PUSHW   MACRO   word
        push    word&L
        push    word&H
        ENDM

POPW    MACRO   word
        pop     word&H
        pop     word&L
        ENDM

XCHW    MACRO   word1,word2
        pushw   word1
        pushw   word2
        popw    word1
        popw    word2
        ENDM


;------ Program Branching

CWJZ    MACRO   word,label
        mov     A,word&H
        orl     A,word&L
        jz      label
        ENDM

CWJNZ   MACRO   word,label
        mov     A,word&H
        orl     A,word&L
        jnz     label
        ENDM

CWJNE   MACRO   word1,word2,label
        mov     A,word1&H
        cjne    A,word2&H,label
        mov     A,word1&L
        cjne    A,word2&L,label
        ENDM

CWJE    MACRO   word1,word2,label
        mov     A,word1&H
        cjne    A,word2&H,$+10
        mov     A,word1&L
        cjne    A,word2&L,$+5
        sjmp    label
        ENDM

CWJAE   MACRO   word,val,label
        mov     A,word&H
        cjne    A,val&H,$+8
        mov     A,word&L
        cjne    A,val&L,$+3
        jnc     label
        ENDM

CWJNAE  MACRO   word,val,label
        mov     A,word&H
        cjne    A,val&H,$+8
        mov     A,word&L
        cjne    A,val&L,$+3
        jc      label                   ;jump if lower
        ENDM

CWJB    MACRO   word,val,label
        mov     A,word&H
        cjne    A,val&H,$+8
        mov     A,word&L
        cjne    A,val&L,$+3
        jc      label                   ;jump if lower
        ENDM

CWJNB   MACRO   word,val,label
        mov     A,word&H
        cjne    A,val&H,$+8
        mov     A,word&L
        cjne    A,val&L,$+3
        jnc     label
        ENDM


CWJNBABS MACRO  word,val,label
        mov     A,word&H
        cjne    A,#HIGH(val),$+3
        jc      $+12
        mov     A,word&L
        cjne    A,#LOW(val),$+3
        jc      $+5
        ljmp    label
        ENDM



CWJBABS MACRO   word,val,label
        mov     A,word&H
        cjne    A,#HIGH(val),$+3
        jnc     label    
        mov     A,word&L
        cjne    A,#LOW(val),$+3
        jc      label
        ENDM

CWJAEABS MACRO  word,val,label
        mov     A,word&H
        cjne    A,#HIGH(val),$+3
        jc      $+12
        mov     A,word&L
        cjne    A,#LOW(val),$+3
        jc      $+5
        ljmp    label
        ENDM

CWJNAEABS MACRO   word,val,label
        mov     A,word&H
        cjne    A,#HIGH(val),$+3
        jnc     $+9
        mov     A,word&L
        cjne    A,#LOW(val),$+3
        jnc     $+5
        ljmp    label
        ENDM

CWJNEABS MACRO  word1,absval,label
        mov     A,word1&H
        cjne    A,#HIGH(absval),label
        mov     A,word1&L
        cjne    A,#LOW(absval),label
        ENDM

CWJEABS MACRO   word1,absval,label
        mov     A,word1&H
        cjne    A,#HIGH(absval),$+11
        mov     A,word1&L
        cjne    A,#LOW(absval),$+6
        ljmp    label
        ENDM


DWJNZ   MACRO   word,label
        decw    word
        mov     A,word&H
        jnz     label
        mov     A,word&L
        jnz     label
        ENDM

DWJNE   MACRO   word,val,label
        decw    word
        mov     A,word&H
        cjne    A,#HIGH val,label
        mov     A,word&L
        cjne    A,#LOW val,label
        ENDM


;------ Arthemetic Operations

SUBWABS MACRO   dest,source
        mov     A,dest&L
        clr     C
        subb    A,#LOW(source)
        mov     dest&L,A
        mov     A,dest&H
        subb    A,#HIGH(source)
        mov     dest&H,A
        ENDM

SUBW    MACRO   dest,source
        mov     A,dest&L
        clr     C
        subb    A,source&L
        mov     dest&L,A
        mov     A,dest&H
        subb    A,source&H
        mov     dest&H,A
        ENDM

SUBBW   MACRO   dest,source
        mov     A,dest&L
        subb    A,source&L
        mov     dest&L,A
        mov     A,dest&H
        subb    A,source&H
        mov     dest&H,A
        ENDM

ADDWABS MACRO   dest,source
        mov     A,dest&L
        add     A,#LOW(source)
        mov     dest&L,A
        mov     A,dest&H
        addc    A,#HIGH(source)
        mov     dest&H,A
        ENDM

ADDW    MACRO   dest,source
        mov     A,dest&L
        add     A,source&L
        mov     dest&L,A
        mov     A,dest&H
        addc    A,source&H
        mov     dest&H,A
        ENDM

ADDCW   MACRO   dest,source
        mov     A,dest&L
        addc    A,source&L
        mov     dest&L,A
        mov     A,dest&H
        addc    A,source&H
        mov     dest&H,A
        ENDM


DECW    MACRO   dest
        push    ACC
        mov     A,dest&L
        if (dest=reg)
            jnz     $+3
        else
            jnz     $+4
        endif
        dec     dest&H
        dec     dest&L
        pop     ACC
        ENDM

INCW    MACRO   dest
        push    ACC
        inc     dest&L
        mov     A,dest&L
        if (dest=reg)
            jnz     $+3
        else
            jnz     $+4
        endif
        inc     dest&H
        pop     ACC
        ENDM

ADDWB   MACRO   dest,reg
        mov     A,dest&L
        add     A,reg
        mov     dest&L,A
        mov     A,dest&H
        addc    A,#0
        mov     dest&H,A
        ENDM

ADDWACC MACRO   dest
        add     A,dest&L
        mov     dest&L,A
        mov     A,dest&H
        addc    A,#0
        mov     dest&H,A
        ENDM

;----------------------------------------------------------
;
;       Internal Debug Tools
;
;----------------------------------------------------------

GETXDATA MACRO
        movx    A,@DPTR
        inc     DPTR
        ENDM

PUTXDATA MACRO
        movx    @DPTR,A
        inc     DPTR
        ENDM

ADDSUM  MACRO chksum,reg
        if('reg' = 'A')
            push    ACC
            add     A,chksum
            mov     chksum,A
            pop     ACC
        else
            mov     ACC,ACC
        endif
        ENDM

        ENDIF   ; MACROS_INC
        
