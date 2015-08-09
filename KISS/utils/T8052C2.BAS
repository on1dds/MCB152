DECLARE SUB PutFrame ()
'communicatie programma voor  met de 8052 ah basic
'snelheid 19200b
'mogelijkheid tot overdracht van files in beide richtingen
'filtering in de UPLOAD van PC naar 8052 mode zodat er geen fouten
'door de BASIC gegenereerd worden


DECLARE SUB menu ()
'menu waar keuze UP of DOWN load
'
'
DECLARE FUNCTION check% (files$)
'controle of file bestaat of kan aangemaakt worden
'
DEFINT B-Z
DEFSTR A
COMMON SHARED a$
DIM a$(27)


ON ERROR GOTO errorhandeling

 'scherm opstelling

 SCREEN 0, 0: WIDTH 80
 CLS
 CLOSE

 'initializatie

 false = 0: true = NOT false
 menus = 5'VALUE OF MENU KEY (^E)
 frame = 6'test KISS frame (^F)
 stp = 24  'einde prog ctrl-x
 xoff$ = CHR$(19): xon$ = CHR$(17)
 '
 '**** COM2 op 4800b en met een buffer van 2048 char
 '
 comfil$ = "COM2:19200,n,8,1,RB2048"
 

 LOCATE 25, 1: PRINT " TERM-PROGRAM "; comfil$; "   CNTRL-E to up-or download files ";
 LOCATE 24, 1

 ' openzetten com poort en scherm

 OPEN comfil$ FOR RANDOM AS #1
 OPEN "SCRN:" FOR OUTPUT AS #3
 pause = false


'input van keyboard
 
 DO

  WHILE LOC(1) > 0
   
      IF LOC(1) > 128 AND pause = false THEN pause = true: PRINT #1, xoff$;
      
      a$ = INPUT$(1, #1)
      'filteren van chr die naar scherm gaan
      IF a$ <> "" AND a$ <> CHR$(10) AND a$ <> xoff$ AND a$ <> xon$ THEN PRINT #3, a$;
         
  WEND
 
  a$ = INKEY$

    IF a$ <> "" AND a$ <> xon$ AND a$ <> xoff$ THEN
        IF ASC(a$) = menus THEN
            IF fileexist <> 6 THEN CALL menu
        ELSE
            ' einde programma door CTRL-X te drukken
            IF ASC(a$) = stp THEN
                END
            ELSE
                IF ASC(a$) = frame THEN
                    CALL PutFrame
                ELSE
                    PRINT #1, a$;
                END IF
            END IF
        END IF
    END IF

        IF LOC(1) < 10 AND pause = true THEN
            pause = false
            PRINT #1, xon$;
        END IF


        LOOP

END



errorhandeling:
SELECT CASE ERR
  CASE 53 'file not found
    l = CSRLIN
    p = POS(0)
    LOCATE 25, 10
    PRINT " file not found ";
    fileexist = 0
    LOCATE l, p
    RESUME NEXT
  CASE 58 'file exist
    l = CSRLIN
    p = POS(0)
    LOCATE 25, 10
    PRINT " file exist already ";
    fileexist = 1
    LOCATE l, p
    RESUME NEXT
  CASE 68 'wrong path
    l = CSRLIN
    p = POS(0)
    LOCATE 25, 10
    PRINT " wrong path ";
    fileexist = 2
    LOCATE l, p
    RESUME NEXT
  CASE 64 'name to long
    l = CSRLIN
    p = POS(0)
    LOCATE 25, 10
    PRINT " name to long ";
    fileexist = 3
    LOCATE l, p
    RESUME NEXT
  CASE 76 'non existing path
    l = CSRLIN
    p = POS(0)
    LOCATE 25, 10
    PRINT " non existing path ";
    fileexist = 4
    LOCATE l, p
    RESUME NEXT
  CASE 75, 71'kan path niet maken
    l = CSRLIN
    p = POS(0)
    LOCATE 25, 10
    PRINT " inpossible to create path ";
    fileexist = 5
    LOCATE l, p
    RESUME NEXT
  CASE 5, 57'device IO error
    fileexist = 6
    RESUME NEXT
  CASE 52  'bad file argument
    fileexist = 6
    RESUME NEXT
  CASE ELSE
     ON ERROR GOTO 0
END SELECT

DEFINT A
FUNCTION check (files$)

' functie die kontroleert of dit path en file mogelijk is

SHARED fileexist
fileexist = 10

OPEN files$ FOR INPUT AS #4
CLOSE #4
SELECT CASE fileexist
    CASE 0, 1
     check = 0
     EXIT FUNCTION
   
    CASE 3, 4, 5, 6
     check = 1
     EXIT FUNCTION

    CASE ELSE
     check = 0
     EXIT FUNCTION
END SELECT

END FUNCTION

SUB menu
SHARED fileexist, true, false, xon$, xoff$, comfil$


'indrukken CNTRL E menu keuze

 LOCATE 1, 1: PRINT STRING$(30, 32): LOCATE 1, 1
DO
'loop controle file bestaat voor upload
 DO

   LINE INPUT "FILE? "; dskfil$
   LOCATE 1, 1: PRINT STRING$(30, 32): LOCATE 1, 1
   LINE INPUT " (U)pload or (D)ownload "; TXRX$

 LOOP WHILE check(dskfil$) <> 0

 'keuze UPLOAD
 IF UCASE$(TXRX$) <> "D" THEN
   IF fileexist = 0 THEN
     PRINT " no existing file ", dskfil$
     EXIT DO
   END IF
   OPEN dskfil$ FOR INPUT AS #2
   GOSUB upload
   EXIT DO
 'keuze DOWNLOAD
 ELSE
   IF fileexist = 1 THEN
    PRINT " overwriting existing file "
   END IF
   GOSUB download
   EXIT DO
 END IF
LOOP
CLS
 LOCATE 25, 1: PRINT " TERM-PROGRAM "; comfil$; "  CNTRL-E to up- or download files ";
 LOCATE 24, 1

EXIT SUB
'***************************************************************

download:
'routine om een file vanuit de 8052 op schijf te plaatsen
 CLS
 LOCATE 25, 1: PRINT "          * DOWNLOAD STARTED  * press ESC to exit download mode             ";
                                                                                             
 b$ = ""
 OPEN dskfil$ FOR OUTPUT AS #2 LEN = 128
 PRINT #1, CHR$(13);

 WHILE NOT EOF(1) OR (b$ <> CHR$(27))
   b$ = INKEY$
   IF b$ <> "" THEN
     PRINT #1, b$;
   END IF
   IF (pause = true) AND (LOC(1) = 0) THEN pause = false: PRINT #1, xon$;
   WHILE LOC(1) > 0

     IF (LOC(1) > 128) AND (pause = false) THEN
        pause = true
        PRINT #1, xoff$;
     END IF
     a$ = INPUT$(LOC(1), #1)
     PRINT #3, a$;
     PRINT #2, a$;
    
   WEND
 WEND
 CLOSE #2
 l = CSRLIN
 p = POS(0)
 LOCATE 25, 1: PRINT "          * DOWNLOAD COMPLETE *                                             ";
 LOCATE l, p
 COM(2) OFF

 RETURN

  

'***************************************************************
upload:
'opladen file
 CLS
 LOCATE 25, 1: PRINT "          ** UPLOAD STARTED  **                                             "
 LOCATE 1, 1
 c$ = ""

 WHILE NOT EOF(2) AND c$ <> CHR$(27)

  c$ = INKEY$

  LINE INPUT #2, a$
  
  IF (MID$(a$, 1, 5) = "READY") OR (MID$(a$, 1, 1) = ">") THEN
   'niets
  ELSE
 
    PRINT #1, a$
              
    WHILE b$ <> CHR$(10) AND c$ <> CHR$(27)

      b$ = INPUT$(1, #1)
      PRINT b$;
    WEND
    WHILE b$ <> ">" AND c$ <> CHR$(27)
      b$ = INPUT$(1, #1)
      PRINT b$;
    WEND
  END IF
 WEND
 CLOSE #2
 l = CSRLIN
 p = POS(0)

 LOCATE 25, 1: PRINT "          ** UPLOAD COMPLETE **                                             ";
 LOCATE l, n
 fileexist = 0

 RETURN




END SUB

'
SUB PutFrame
    PRINT #1, CHR$(192); CHR$(0); CHR$(13); CHR$(192);
    FOR h = 1 TO 39
        PRINT #1, CHR$(192); CHR$(0);
        FOR i = 1 TO 253
            PRINT #1, CHR$(ASC("A") + h - 1);
        NEXT i
        PRINT #1, CHR$(192)
        'FOR s = 1 TO 3
        'FOR k = 0 TO 30000: NEXT k
        'nEXT s
    NEXT h

END SUB

