;====================================================================
; rtl.asm file generated by New Project wizard
;
; Created:   �ܶ� ���� 15 2016
; Processor: USB8086
; Compiler:  Digital Mars C
;====================================================================

.MODEL	SMALL

.8086
.stack
.code
extern _main:near
.startup
        cli		       ; interrupt disable
	call  near ptr _main
endless:
	jmp   endless
.data
public	__acrtused		; trick to force in startup

__acrtused = 9876h	; funny value not easily matched ; ; in SYMDEB

END