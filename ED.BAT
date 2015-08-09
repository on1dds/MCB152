@ECHO OFF
CLS
EDIT -h %1.SRC HEXLOAD.SRC DISASM.SRC ASCIIDMP.SRC ..\LIBS\IO.SRC KICK.INC %1.LST
erase %1.lst >nul:
a51 %1.SRC >asm.msg
cnbel asm.msg nbel.msg
erase asm.msg >nul:
type nbel.msg
erase nbel.msg >nul:
hex2hex %1.hex >nul:
erase %1.hex >nul:
copy %1.hx2 %1.hex >nul:
erase %1.hx2 >nul:
copy %1.hex "C:\temp\%1.txt"
