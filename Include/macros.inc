        IFNDEF  MACROS_INC
MACROS_INC      EQU     1
;**
;**     $Filename: macros.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 10/01/1998
;**
;**     8052 Instruction extension
;**     adjusted for Macro Assembler
;**
;**     Coded by Joachim Elen
;**



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
prog    LABEL   address
        ENDM



;------ Structure management for on-chip memory

BITSTRUCT MACRO base
ACOUNT  SET     base
        ENDM

BITDEF  MACRO   label
label   BIT     ACOUNT
ACOUNT  SET     ACOUNT+1
        ENDM

BITSKIP MACRO
ACOUNT  SET     ACOUNT+1
        ENDM

STRUCTURE MACRO base
ACOUNT  SET     base
        ENDM

VOID    MACRO   label
label   EQU     ACOUNT
        ENDM

APTR    MACRO   addr
addr    SFR     ACOUNT
{"addr"}L  SFR  ACOUNT+0
{"addr"}H  SFR  ACOUNT+1
ACOUNT  SET     ACOUNT+2
        ENDM

UWORD   MACRO   wdat     
wdat    SFR     ACOUNT
{"wdat"}L  SFR  ACOUNT+0
{"wdat"}H  SFR  ACOUNT+1
ACOUNT  SET     ACOUNT+2
        ENDM

BYTE    MACRO   bdat
bdat    SFR     ACOUNT
ACOUNT  SET     ACOUNT+1
        ENDM

UBYTE   MACRO   bdat
bdat    SFR     ACOUNT
ACOUNT  SET     ACOUNT+1
        ENDM

BBYTE   MACRO   bdat
bdat    SFRB    ACOUNT
ACOUNT  SET     ACOUNT+1
        ENDM

BOOL    MACRO   bdat
bdat    SFR     ACOUNT
ACOUNT  SET     ACOUNT+1
        ENDM

;------ Structure Managemen for XDATA memory

XSTRUCTURE MACRO base
XACOUNT SET     base
        ENDM

XSTRUCT MACRO   struc,lbl,sizeof
{"lbl"} SET     sizeof
struc   LABEL   XACOUNT
XACOUNT SET     XACOUNT+sizeof
        ENDM


;----------------------------------------------------------
;
;       8-bit CPU Instruction extensions
;
;----------------------------------------------------------


;------ Data Transfer

pushm   MACRO   reg
            push    reg
        IF ARGCOUNT>1
            SHIFT
            pushm   ALLARGS
        ENDIF
        ENDM

popm    MACRO   reg
            pop     reg
        IF ARGCOUNT>1
            SHIFT
            popm    ALLARGS
        ENDIF
        ENDM

mova    MACRO   dest,source
        mov     A,source
        mov     dest,A
        ENDM

movs    MACRO   dest,source
        push    source
        pop     dest
        ENDM

exg     MACRO   ea1,ea2
        push    ea1
        push    ea2
        pop     ea1
        pop     ea2
        ENDM

pushstate MACRO
        pushm   PSW,DPH,DPL,ACC
        ENDM

popstate MACRO
        popm    ACC,DPL,DPH,PSW
        ENDM

pushregs MACRO
        pushm   AR0,AR1,AR2,AR3,AR4,AR5,AR6,AR7
        ENDM

popregs MACRO
        popm    AR7,AR6,AR5,AR4,AR3,AR2,AR1,AR0
        ENDM

;------ Arthemetic Operations

adda    MACRO   dest,source
        push    ACC
        mov     A,dest
        add     A,source
        mov     dest,A
        pop     ACC
        ENDM


subba   MACRO   dest,source
        push    ACC
        mov     A,dest
        subb    A,source
        mov     dest,A
        pop     ACC
        ENDM

;------ Program Branching

lcjne   MACRO   reg,num,label
        cjne    reg,num,$$jmp
        jmp     $$done
$$jmp:  jmp     label
$$done:
        ENDM


je      MACRO   label
        jnc     label
        ENDM


jne     MACRO   label
        jc      label
        ENDM


cje     MACRO   reg,num,label
        cjne    reg,num,$$done
        jmp     label
$$done:
        ENDM



;-----------------------------
; ABOVE                 >
; NOT BELOW OR EQUAL    NOT <=
;-----------------------------


cja     MACRO   reg,num,label           ;reg>num
        cjne    reg,num,$$ab
        sjmp    $$be
$$ab:   jnc     label
$$be:
        ENDM

cjnbe   MACRO   reg,num,label
        cja     reg,num,label
        ENDM

;-----------------------------
; ABOVE OR EQUAL        >=
; NOT BELOW             NOT <
;-----------------------------


cjae    MACRO   reg,num,label           ;reg>=num
        cjne    reg,num,$$ab
$$eq    jmp     label
$$ab    jnc     label
        ENDM


cjnb    MACRO   reg,num,label
        cjae    reg,num,label
        ENDM

;-----------------------------
; BELOW                 <
; NOT ABOVE OR EQUAL    NOT >=
;-----------------------------


cjb     MACRO   reg,num,label           ;reg<num
        cjne    reg,num,$$ab
$$eq:   sjmp    $$done
$$ab:   jc      label
$$done:
        ENDM

cjnae   MACRO   reg,num,label
        cjb     reg,num,label
        ENDM

;-----------------------------
; BELOW OR EQUAL        <=
; NOT ABOVE             NOT >
;-----------------------------

cjbe    MACRO   reg,num,label           ;reg<=num
        cjne    reg,num,$$ab
        sjmp    label
$$ab    jc      label
$$done:
        ENDM



;-----------------------------
; NOT IN RANGE
; RANGE
;-----------------------------

cjnr    MACRO   reg,top,bot,label
        cja     reg,top,label
        cjb     reg,bot,label
        ENDM

cjr     MACRO   reg,top,bot,label
        cja     reg,bot,label
        cjb     reg,top,label
        ENDM


pushret MACRO   address
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

clrw    MACRO   dest
        mov     {"dest"}H,#0
        mov     {"dest"}L,#0
        ENDM

        
movw    MACRO   dest,src
        IF  (SUBSTR("src",0,1)="#") && (STRLEN("src")>1)

$$__OFFS    SET SUBSTR("src",1,0)
            mov     {"dest"}L,#LOW({$$__OFFS})
            mov     {"dest"}H,#HIGH({$$__OFFS})

        ELSEIF
            mov     {"dest"}H,{"src"}H
            mov     {"dest"}L,{"src"}L
        ENDIF
        ENDM

movwacc MACRO   dest
        mov     {"dest"}L,A
        mov     {"dest"}H,#0
        ENDM

movwb   MACRO   wdest,bsrc
        mov     {"wdest"}L,bsrc
        mov     {"wdest"}H,#0
        ENDM

movwc   MACRO   dest
        push    ACC
        clr     A
        movc    A,@A+DPTR
        push    ACC
        mov     A,#1
        movc    A,@A+DPTR
        mov     {"dest"}L,A
        pop     ACC
        mov     {"dest"}H,A
        pop     ACC
        ENDM


movwx   MACRO   dest,src
        IF  (SUBSTR("dest",0,5)="@DPTR")
            push    DPL                     ;keep DPTR intact!
            push    DPH
            IF STRLEN("dest")>5             ;add offset ?
$$__OFFS        SET substr("dest",6,0)      ;extract offset (no '+' check)
                mov     A,DPL               ;compute dest address 
                add     A,#low({$$__OFFS})
                mov     DPL,A
                mov     A,DPH
                addc    A,#high({$$__OFFS})
                mov     DPH,A
            ENDIF
            push    ACC                     ;do data transfer
            mov     A,{"src"}L
            movx    @DPTR,A
            inc     DPTR
            mov     A,{"src"}H
            movx    @DPTR,A
            pop     ACC
            pop     DPH                     ; restore DPTR when ofsetted
            pop     DPL
    
        ELSEIF  (SUBSTR("src",0,5)="@DPTR")
            push    DPL                     ;keep DPTR intact!
            push    DPH
            IF  STRLEN("src")>5        ; add offset ?
$$__OFFS        SET     substr("src",6,0)   ;extract offset (no '+' check)
                mov     A,DPL               ;compute dest address 
                add     A,#low({$$__OFFS})
                mov     DPL,A
                mov     A,DPH
                addc    A,#high({$$__OFFS})
                mov     DPH,A
            ENDIF
            push    ACC                     ;do data transfer
            movx    A,@DPTR
            mov     {"dest"}L,A
            inc     DPTR
            movx    A,@DPTR
            mov     {"dest"}H,A
            pop     ACC
            pop     DPH                    ; restore DPTR when done
            pop     DPL
    
        ELSEIF
            error   "??? movwx: unsupported addressingmode"
        ENDIF
        ENDM


movwxabs MACRO   dest,source
        pushw   DP
        movw    DP,dest
        mov     A,#HIGH({"source"}L)
        movx    @DPTR,A
        inc     DPTR
        mov     A,#HIGH({"source"}H)
        movx    @DPTR,A
        popw    DP
        ENDM

clrwx   MACRO   dest
        IF upstring("dest")="@DPTR"
            push    ACC
            pushw   DP
            clr     A
            movx    @DPTR,A
            inc     DPTR
            movx    @DPTR,A
            popw    DP
            pop     ACC
        ENDIF
        ENDM

pushw   MACRO   word
        push    {"word"}L
        push    {"word"}H
        ENDM

popw    MACRO   word
        pop     {"word"}H
        pop     {"word"}L
        ENDM

xchw    MACRO   word1,word2
        pushw   {"word1"}
        pushw   {"word2"}
        popw    {"word1"}
        popw    {"word2"}
        ENDM


;------ Program Branching

cwjz    MACRO   word,label
        mov     A,{"word"}H
        orl     A,{"word"}L
        jz      label
        ENDM

cwjnz   MACRO   word,label
        mov     A,{"word"}H
        orl     A,{"word"}L
        jnz     label
        ENDM

cwjne   MACRO   word1,word2,label
        mov     A,{"word1"}H
        cjne    A,{"word2"}H,label
        mov     A,{"word1"}L
        cjne    A,{"word2"}L,label
        ENDM

cwje    MACRO   word1,word2,label
        mov     A,{"word1"}H
        cjne    A,{"word2"}H,$+10
        mov     A,{"word1"}L
        cjne    A,{"word2"}L,$+5
        sjmp    label
        ENDM

cwjeabs MACRO   word1,val,label
        mov     A,{"word1"}H
        cjne    A,#HIGH(val),$+10
        mov     A,{"word1"}L
        cjne    A,#LOW(val),$+5
        sjmp    label
        ENDM


cwjaeabs MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,#HIGH(val),$+10
        mov     A,{"word"}L
        cjne    A,#LOW(val),$+5
        sjmp    label
        jnc     label
        ENDM

cwjbeabs MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,#HIGH(val),$+10
        mov     A,{"word"}L
        cjne    A,#LOW(val),$+5
        sjmp    label
        jc      label
        ENDM

cwjbabs MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,#HIGH(val),$+12
        sjmp    $+11
        mov     A,{"word"}L
        cjne    A,#LOW(val),$+5
        sjmp    $+4
        jc      label                   ;jump if lower
        ENDM

cwjaabs MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,#HIGH(val),$+12
        sjmp    $+11
        mov     A,{"word"}L
        cjne    A,#LOW(val),$+5
        sjmp    $+4
        jnc     label                   ;jump if lower
        ENDM

cwjnbabs MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,#HIGH(val),$+10
        mov     A,{"word"}L
        cjne    A,#LOW(val),$+5
        sjmp    label
        jnc     label
        ENDM

cwjnaabs MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,#HIGH(val),$+10
        mov     A,{"word"}L
        cjne    A,#LOW(val),$+5
        sjmp    label
        jc      label
        ENDM

cwjnaeabs MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,#HIGH(val),$+12
        sjmp    $+11
        mov     A,{"word"}L
        cjne    A,#LOW(val),$+5
        sjmp    $+4
        jc      label                   ;jump if lower
        ENDM

cwjnbeabs MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,#HIGH(val),$+12
        sjmp    $+11
        mov     A,{"word"}L
        cjne    A,#LOW(val),$+5
        sjmp    $+4
        jnc     label                   ;jump if lower
        ENDM

cwjae   MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,{"val"}H,$+10
        mov     A,{"word"}L
        cjne    A,{"val"}L,$+5
        sjmp    label
        jnc     label
        ENDM

cwjbe   MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,{"val"}H,$+10
        mov     A,{"word"}L
        cjne    A,{"val"}L,$+5
        sjmp    label
        jc      label
        ENDM

cwjb    MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,{"val"}H,$$bigr

        mov     A,{"word"}L
        cjne    A,{"val"}L,$$bigr
        sjmp    $$done

$$bigr: jc      label                   ;jump if lower
$$done:
        ENDM

cwja    MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,{"val"}H,$+12
        sjmp    $+11
        mov     A,{"word"}L
        cjne    A,{"val"}L,$+5
        sjmp    $+4
        jnc     label                   ;jump if lower
        ENDM

cwjnb   MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,{"val"}H,$+10
        mov     A,{"word"}L
        cjne    A,{"val"}L,$+5
        sjmp    label
        jnc     label
        ENDM

cwjna   MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,{"val"}H,$+10
        mov     A,{"word"}L
        cjne    A,{"val"}L,$+5
        sjmp    label
        jc      label
        ENDM

cwjnae  MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,{"val"}H,$+12
        sjmp    $+11
        mov     A,{"word"}L
        cjne    A,{"val"}L,$+5
        sjmp    $+4
        jc      label                   ;jump if lower
        ENDM

cwjnbe  MACRO   word,val,label
        mov     A,{"word"}H
        cjne    A,{"val"}H,$+12
        sjmp    $+11
        mov     A,{"word"}L
        cjne    A,{"val"}L,$+5
        sjmp    $+4
        jnc     label                   ;jump if lower
        ENDM

dwjnz   MACRO   word,label
        decw    word
        cwjnz   word,label
        ENDM

dwjne   MACRO   word,val,label
        decw    word
        mov     A,{"word"}H
        cjne    A,#HIGH val,label
        mov     A,{"word"}L
        cjne    A,#LOW val,label
        ENDM


;------ Arthemetic Operations

subwabs MACRO   dest,source
        mov     A,{"dest"}L
        clr     C
        subb    A,#LOW(source)
        mov     {"dest"}L,A
        mov     A,{"dest"}H
        subb    A,#HIGH(source)
        mov     {"dest"}H,A
        ENDM

subw    MACRO   dest,source
        mov     A,{"dest"}L
        clr     C
        subb    A,{"source"}L
        mov     {"dest"}L,A
        mov     A,{"dest"}H
        subb    A,{"source"}H
        mov     {"dest"}H,A
        ENDM

subbw   MACRO   dest,source
        mov     A,{"dest"}L
        subb    A,{"source"}L
        mov     {"dest"}L,A
        mov     A,{"dest"}H
        subb    A,{"source"}H
        mov     {"dest"}H,A
        ENDM

addwabs MACRO   dest,source
        IF  source<>0
            mov     A,{"dest"}L
            add     A,#LOW(source)
            mov     {"dest"}L,A
            mov     A,{"dest"}H
            addc    A,#HIGH(source)
            mov     {"dest"}H,A
        ENDIF
        ENDM

addw    MACRO   dest,source
        mov     A,{"dest"}L
        add     A,{"source"}L
        mov     {"dest"}L,A
        mov     A,{"dest"}H
        addc    A,{"source"}H
        mov     {"dest"}H,A
        ENDM

addcw   MACRO   dest,source
        mov     A,{"dest"}L
        addc    A,{"source"}L
        mov     {"dest"}L,A
        mov     A,{"dest"}H
        addc    A,{"source"}H
        mov     {"dest"}H,A
        ENDM


decw    MACRO   dest
        push    ACC
        mov     A,{"dest"}L
        jnz     $$low
        dec     {"dest"}H
$$low   dec     {"dest"}L
        pop     ACC
        ENDM


negw    MACRO   dest

        push    ACC
        decw    dest
        mov     A,{"dest"}H
        cpl     A
        mov     {"dest"}H,A
        mov     A,{"dest"}L
        cpl     A
        mov     {"dest"}L,A
        pop     ACC

        ENDM

incw    MACRO   dest
        push    ACC
        mov     A,{"dest"}L
        jnz     $$a
        dec     {"dest"}H
$$a     dec     {"dest"}L
        pop     ACC
        ENDM

addwb   MACRO   dest,reg
        mov     A,{"dest"}L
        add     A,reg
        mov     {"dest"}L,A
        mov     A,{"dest"}H
        addc    A,#0
        mov     {"dest"}H,A
        ENDM

addwacc MACRO   dest
        add     A,{"dest"}L
        mov     {"dest"}L,A
        mov     A,{"dest"}H
        addc    A,#0
        mov     {"dest"}H,A
        ENDM

;----------------------------------------------------------
;
;       Internal Debug Tools
;
;----------------------------------------------------------

getxdata MACRO
        movx    A,@DPTR
        inc     DPTR
        ENDM

putxdata MACRO
        movx    @DPTR,A
        inc     DPTR
        ENDM

addsum  MACRO chksum,reg
        if(reg = "A")
            push    ACC
            add     A,chksum
            mov     chksum,A
            pop     ACC
        else
            mov     ACC,ACC
        endif
        ENDM

        ENDIF   ; MACROS_INC
        
