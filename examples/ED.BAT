@ECHO OFF
CLS
EDIT -h %1.SRC %1.LST ..\include\library.inc
erase %1.lst >nul:
a51 %1.SRC >asm.msg
cnbel asm.msg nbel.msg
del asm.msg >nul:
type nbel.msg
del nbel.msg >nul:
hex2hex %1.hex >nul:
del %1.hex >nul:
copy %1.hx2 %1.hex >nul:
del %1.hx2 >nul:
