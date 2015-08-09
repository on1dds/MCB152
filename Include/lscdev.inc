        IF (LSCDEV_INC)
        ELSE
LSCDEV_INC SET     1
;**
;**     $Filename: lsc.inc
;**     $Release: 1
;**     $Revision: 1
;**     $Date: 10/11/1998
;**
;**     Local Serial Channel device
;**
;**     Coded by Joachim Elen
;**

        $INCLUDE(X:hardware.inc)

;----------------------------
;   Constants
;----------------------------
LSC_VERSION     EQU 1
LSC_REVISION    EQU 0

;----------------------------
;   LSC device library
;----------------------------
        LIBDEF  LSCDevice,0E800h
        FUNCDEF LSC_reset
        FUNCDEF LSC_read
        FUNCDEF LSC_write
        FUNCDEF LSC_clear
        FUNCDEF LSC_stop
        FUNCDEF LSC_start
        FUNCDEF LSC_update
        FUNCDEF LSC_flush

;----------------------------
;buffer allocation
;----------------------------
    xstructure 8000h
        xstruct LRbuffer,LRB_SIZEOF,00800h      ;lsc receive buffer
        xstruct LTbuffer,LTB_SIZEOF,01800h      ;lsc transmit buffer
        xstruct GRbuffer,GRB_SIZEOF,02000h      ;lsc receive buffer
        xstruct GTbuffer,GTB_SIZEOF,04000h      ;lsc transmit buffer

;----------------------------
;flag assignments
;----------------------------
        bitstruct 0000h
        bitdef  lt_done

;----------------------------
;variable definitions
;----------------------------

        structure 0030h
                    
;local io device
;---------------
        aptr    ltw_data        ;tx lsc datawrite pointer
        aptr    ltr_data        ;tx lsc dataread pointer
        uword   lt_alloc        ;tx lsc allocated bytes

        aptr    lrw_data        ;rx lsc datawrite pointer
        aptr    lrr_data        ;rx lsc dataread pointer
        uword   lr_alloc        ;rx lsc allocated bytes

;global io device
;----------------
        aptr    gtw_data        ;tx gsc datawrite pointer
        aptr    gtr_data        ;tx gsc dataread pointer
        uword   gt_alloc        ;tx gsc allocated bytes

        aptr    grw_data        ;rx gsc datawrite pointer
        aptr    grr_data        ;rx gsc dataread pointer
        uword   gr_alloc        ;rx gsc allocated bytes

        ENDIF   ; LSCDEV_INC





















