.code
;====================CLEARSCREEN=============================================================
ClearscreenM macro
    mov ah,0
    mov al,3
    int 10h
endm ClearscreenM
;============================================================================================

;====================scrollup=============================================================
scrollup MACRO from,to
    mov ax,0601h
    mov bh,00
    mov cx,from
    mov dx,to
    int 10h
ENDM scrollup
;============================================================================================
;====================scrolldown=============================================================
scrolldown MACRO from,to
    mov ax,0701h
    mov bh,07
    mov cx,from
    mov dx,to
    int 10h
ENDM scrolldown
;============================================================================================


;=====================GetKeyPressed==========================================================
GetKeyPress MACRO
    MOV AH,01H                     ;DOESN'T WAIT FOR KEY PRESSED, JUST CHECKS THE KEYBOARD BUFFER FOR ONE
    INT 16H
ENDM GetKeyPress
;============================================================================================



;===============================ENTERTEXTMODE===============================================
TEXTMODE MACRO 
    MOV AH,0
    MOV AL,3
	INT 10H
ENDM TEXTMODE
;===========================================================================================

;===============================GRAPHICSMODE================================================
GraphicsMode MACRO 
    MOV AH,0
    MOV AL,13h
	INT 10H
ENDM GraphicsMode
;===========================================================================================

;================================MOVECURSORPOSITION=========================================
MOVECURSOR MACRO   X,Y
    MOV AH,2
	MOV BH,0
	MOV DL,X
	MOV DH,Y
	INT 10H
ENDM MOVECURSOR
;============================================================================================

;================================getCURSORPOSITION=========================================
GETCURSORPOSINCHAT MACRO
    MOV AH,3
	MOV BH,2
	INT 10H
ENDM GETCURSORPOSINCHAT

GETCURSOR MACRO 
    mov ah,3h 
    mov bh,0h 
    int 10h    
ENDM
;============================================================================================



;=======================================DisplayString========================================

DisplayString macro str    ;this macro displays a string when given its memory variable name
	mov dx, offset str
	mov ah, 9h
	int 21h
endm DisplayString
;============================================================================================

;=======================================ReadString===========================================
ReadString macro buffer
    ;this macro reads a string from the keyboard and stores it in the buffer
	mov ah, 0ah
	mov dx, offset buffer
	int 21h
endm ReadString
;============================================================================================

;=====================DisplayASingleCharacter================================================
DisplayChar MACRO MyChar
    MOV AH, 2
    MOV DL, MyChar
    INT 21H
ENDM PrintChar
;============================================================================================
