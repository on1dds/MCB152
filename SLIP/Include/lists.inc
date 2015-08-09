        IFNDEF LISTS_INC
LISTS_INC       EQU     1
;**
;**     $Filename: lists.inc
;**     $Release: 1
;**     $Revision: 0
;**     $Date: 24/09/2000
;**     $Coding: Joachim Elen 
;**     
;**     Node identifiers
;**

;-------------------------------------------------------------------------
;list structure.

;list header
LH      STRUCT
HEAD        db  ?
TAIL        db  ?
TYPE        db  ?
LH      ENDSTRUCT
;-------------------------------------------------------------------------
;node structure. each member in a list starts with a node

;list node -- no type checking possible

LN      STRUCT
            ds  LH_len
NEXT        db  ?           ;pointer to next (successor)
PREV        db  ?           ;pointer to previous (predecessor)
SIZE        db  ?           ;nodesize
TYPE        db  ?           ;type of node
PRI         db  ?           ;priority
LN      ENDSTRUCT
;-------------------------------------------------------------------------
;macro definitions



;get next node in list
node_next   MACRO   ;(DPTR = node)
            movx    A,@DPTR
            mov     DPH,A
node_next   ENDM

node_prev   MACRO
            inc     DPTR
            movx    A,@DPTR
            mov     DPH,A
            dec     DPL
node_prev   ENDM


;add node to tail of list
node_addtail MACRO  list
node_addtail ENDM

;add node to head of list
node_addhead MACRO  list
node_addhead ENDM

;remove first node in list
node_remhead MACRO  list
node_remhead ENDM

;remove last node in list
node_remtail MACRO  list
node_remtail ENDM


    ENDIF   ;LISTS_INC

