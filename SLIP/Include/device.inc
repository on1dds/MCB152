    IFNDEF  DEVICE_SRC
DEVICE_SRC     EQU TRUE
;**
;**     $Filename: device.src
;**     $Release: 0
;**     $Revision: 1
;**     $Date: 14/11/2000
;**     $Coding: Joachim Elen
;**     
;**
;**     device driver includes
;**

;parameters for device IOCTL instruction

CMD_INVALID		EQU	000h	;invalid command
CMD_RESET		EQU 001h	;reset as if just initialised
CMD_READ		EQU	002h	;standard read
CMD_WRITE		EQU	003h	;standard write
CMD_UPDATE		EQU	004h	;write out all buffers
CMD_CLEAR		EQU	005h	;clear all buffers
CMD_STOP		EQU	006h	;hold current and queued
CMD_START		EQU	007h	;restart after stop
CMD_FLUSH		EQU	008h	;abort entire queue
CMD_STATUS		EQU	009h	;read device status

CMD_RECEIVE		EQU	080h	;switch	to receive mode
CMD_TRANSMIT	EQU	081h	;switch	to transmit	mode
CMD_RAWWRITE	EQU	082h	;directly write
CMD_RAWREAD		EQU	083h


    ENDIF
