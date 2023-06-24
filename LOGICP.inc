INCLUDE MACROS.INC
.CODE

;********************* FINAL PROCEDURES ISA ***************************************

TAKE_COMMAND               PROC
    
    PUSHA
    PUSHF

     
START_COMMAND:
        MOV Xposition,0                 

        ;MOVE CURSOR POSITION 0
        MOV AH,2
        MOV BH,0
        MOV DL,0
        MOV DH,0
        INT 10H

        ;BLACK BACKGROUND
        mov ah,9
        mov al,0
        mov bh,3
        mov cx,7
        mov bl,00000100B
        int 10h    

    MOV CX,7D 
    LEA SI,GATE

AGAIN:

    MOV AH,0H  
    INT 16H 

                pusha
                PUSHF
                        
                        ;MOVE CURSOR NEW POSITION
                        MOV AH,2
                        MOV BH,0
                        MOV DL,Xposition
                        MOV DH,0
                        INT 10H
                        
                        ;PRINT CHAR
                        mov ah,9
                        mov bh,3
                        mov cx,1
                        mov bl,00000100B  ;RED COLOR
                        inc Xposition
                        int 10h
                popf        
                popa

    CMP AL,8D
    JZ  START_COMMAND

    CMP AH,3EH          ;PRESS F4 TO RETURN TO MAIN MENU
    JZ CHECK_LEVEL
    JNZ CONTINUE_TAKE_COMMAND

    CHECK_LEVEL:
    CMP BYTE PTR GAME_LEVEL,1
    JZ RETURN_TO_MENU
    JNZ SCORE_SCREEN

    SCORE_SCREEN:
    CALL SCOREBOARD
    JMP RETURN_TO_MENU
    

    CONTINUE_TAKE_COMMAND:
    MOV BYTE PTR [SI],AL
              
    INC SI
    DEC CX
    JNZ AGAIN 
    

    JMP CONTINUE_SKIP
    RETURN_TO_MENU:
    MOV MENU_FLAG,1
    CONTINUE_SKIP:

    POPA
    POPF
    
    RET
     
TAKE_COMMAND               ENDP 

;////////////////////////////////// ASCII TO DECIMAL /////////////////////////////////////////////

ASCII_TO_DECIMAL           PROC
       
        PUSHA
        PUSHF
       
        LEA SI,INPUT1_COL 
        MOV CX,6 
        
CHECK_IF_NUMBERS: 

        ;loop to check input number between 0 & 9 for the 3 digits
CHECK1:
        CMP BYTE PTR [SI],30H
        JC  LOOP_ERROR_ASCII_DEC


        CMP BYTE PTR [SI],3AH
        JNC LOOP_ERROR_ASCII_DEC

        INC SI
        DEC CX
        JNZ CHECK1
        
        LEA SI,INPUT1_COL 
        MOV CX,6
        
LOOP_MANAGE:        
         
        SUB BYTE PTR [SI],30H 
        INC SI
        DEC CX
        JNZ LOOP_MANAGE 
        
        JMP END_ASCII_TO_DEC 
        
LOOP_ERROR_ASCII_DEC:

        MOV ERROR_FLAG,1D
        
END_ASCII_TO_DEC:
                   
        POPA 
        POPF
       
        RET

ASCII_TO_DECIMAL           ENDP               

;////////////////////////// MANAGE MAP ///////////////////////////////////////////////////////////

MANAGE_MAP                 PROC 
      
;DETERMINE INDEX OF EACH NODE
        LEA SI,GATE 
        
        MOV AX,0                  ;INTIALIZE AX
        MOV BX,0                  ;INTIALIZE BX
        MOV CX,0                  ;INTIALIZE CX
               
        MOV AL,[SI]+2             ;MOVE ROW OF INPUT1 TO AL
        MOV Ah,10                 ;MOVE 10 TO AH ( NUMBER OF COLUMNS IN MAP )
        MUL AH                    ;MULTIPLY ROW BY NUMBER OF COLUMNS 
        ADD AL,[SI]+1             ;ADD COLUMN NUMBER TO AL TO REACH REQUIRED INDEX
        MOV INPUT1_INDEX,AL       ;EQUATION TO DETERMINE THE INDEX OF INPUT 1 PIN IN MAP INDEX ( INDEX = ROW * 10 + COL )
        
        MOV AL,[SI]+4
        MOV AH,10
        MUL AH
        ADD AL,[SI]+3
        MOV INPUT2_INDEX,AL       ;SAME EQUATION TO DETERMINE THE INDEX OF INPUT 1 PIN IN MAP INDEX ( INDEX = ROW * 10 + COL )
       
        MOV AL,[SI]+6
        MOV AH,10
        MUL AH
        ADD AL,[SI]+5
        MOV OUTPUT_INDEX,AL       ;SAME EQUATION TO DETERMINE THE INDEX OF OUTPUT PIN IN MAP INDEX  ( INDEX = ROW * 10 + COL )
        
;DETERMINE INPUTS AND THE OUTPUT LOCATION

        MOV BX,0                  ;INITIALIZE BX    
        LEA SI,MAP_INDEX          ;MOVE OFFSET MAP_INDEX TO SI  
        LEA DI,INPUT1_INDEX       ;MOVE OFFSET INPUT1_INDEX TO DI
        MOV BL,[DI]               ;MOVE INPUT1_INDEX TO AL
        ADD SI,BX                 ;MOVE SI TO OFSSET OF MAP_INDEX[INPUT1_INDEX]
        MOV AL,[SI]               ;MOVE MAP_INDEX[INPUT1_INDEX] TO AL (AL = MAP_INDEX[INPUT1_INDEX] )    (PIN 1)    
        MOV INPUT1_VALUE,AL 
        
        
        LEA SI,MAP_INDEX          ;MOVE OFFSET MAP_INDEX TO SI  
        LEA DI,INPUT2_INDEX       ;MOVE OFFSET INPUT2_INDEX TO DI
        MOV BL,[DI]               ;MOVE INPUT2_INDEX TO BL
        ADD SI,BX                 ;MOVE SI TO OFSSET OF MAP_INDEX[INPUT2_INDEX]
        MOV AH,[SI]               ;MOVE MAP_INDEX[INPUT2_INDEX] TO AH (AH = MAP_INDEX[INPUT2_INDEX] )    (PIN 2)
        MOV INPUT2_VALUE,AH
             
        LEA SI,MAP_INDEX          ;MOVE OFFSET MAP_INDEX TO SI
        LEA DI,OUTPUT_INDEX       ;MOVE OFFSET OUTPUT_INDEX TO DI
        MOV BL,[DI]               ;MOVE OUTPUT_INDEX TO BL
        ADD SI,BX                 ;MOVE SI TO OFSSET OF MAP_INDEX[OUTPUT_INDEX]    (OUTPUT PIN) 
       
    RET
    
MANAGE_MAP                 ENDP 

;////////////////////////// CHECK COMMANDS ///////////////////////////////////////////////////////

CHECK_COMMAND                 PROC
    
    PUSHA
    PUSHF 
    
;CHECK IF OUTPUT PIN IS USED 

        CALL MANAGE_MAP 

        LEA DI,GATE  
                     
        CMP BYTE PTR [DI],77D      ;CHECK IF INPUT COMMAND IS REMOVE (M)
        JZ  CHECK_DELETE_COMMAND   ;IF GATE = M THEREFORE SKIP OUTPUT CHECK
          
        CMP BYTE PTR [SI],20H
        JZ  LOOP_ERROR_CHECK       ;CHECK IF OUTPUT PIN IS ALREADY USED 

        CMP BYTE PTR [SI],1
        JZ  LOOP_ERROR_CHECK       ;CHECK IF OUTPUT PIN IS ALREADY USED

        CMP BYTE PTR [SI],0
        JZ  LOOP_ERROR_CHECK       ;CHECK IF OUTPUT PIN IS ALREADY USED
                    
; ***********CHECK GATE TYPE*********
       
        LEA DI,GATE
        
        CMP BYTE PTR [DI],65D              ;COMPARE GATE WITH ASCII VALUE OF A
        JZ  CHECK_2_INPUT_GATES
    
        CMP BYTE PTR [DI],79D              ;COMPARE GATE WITH ASCII VALUE OF O
        JZ  CHECK_2_INPUT_GATES
    
        CMP BYTE PTR [DI],68D              ;COMPARE GATE WITH ASCII VALUE OF D
        JZ  CHECK_2_INPUT_GATES   
    
        CMP BYTE PTR [DI],82D              ;COMPARE GATE WITH ASCII VALUE OF R
        JZ  CHECK_2_INPUT_GATES
    
        CMP BYTE PTR [DI],88D              ;COMPARE GATE WITH ASCII VALUE OF X
        JZ  CHECK_2_INPUT_GATES
    
        CMP BYTE PTR [DI],78D              ;COMPARE GATE WITH ASCII VALUE OF N
        JZ  CHECK_2_INPUT_GATES
        
        CMP BYTE PTR [DI],87D              ;COMPARE GATE WITH ASCII VALUE OF W
        JZ  CHECK_WIRE_GATE  
        
        CMP BYTE PTR [DI],73D              ;COMPARE GATE WITH ASCII VALUE OF I
        JZ  CHECK_NOT_GATE                           

;******** ERROR IF ANY CONSTRAIN IS NOT ACHIEVED ******************    
        
CHECK_GATES_ERROR:
    
        MOV ERROR_FLAG,1D
        JMP END_CHECK_COMMAND
    

CHECK_2_INPUT_GATES:

;CHECK IF COMMAND IS CORRECT AND ACHIEVABLE

        LEA DI,INPUT1_COL         ;MOVE OFFSET INPUT1_COL TO DI
        MOV BL,[DI]               ;MOVE INPUT1_COL TO BL
        MOV BH,[DI]+4             ;MOVE OUTPUT_COL TO BH
        SUB BH,BL                 ;SUBTRACT OUTPUT_COL AND INPUT1_COL 
        JC  LOOP_ERROR_CHECK      ;CHECK THAT THE OUTPUT_COL IS >> INPUT_COL
        
        CMP BH,1                  ;CHECK IF THE DIFFERENCE IS 1 
        JNZ LOOP_ERROR_CHECK      ;IF NOT 1 JMP TO ERROR MSG 
                      
        CMP BL,[DI]+2             ;CHECK IF INPUT 1 AND 2 ARE IN THE SAME COL
        JNZ LOOP_ERROR_CHECK      ;IF NOT JUMP TO ERROR MSG  
        
        MOV BH,[DI]+4             ;MOV OUTPUT_COL TO BH
        CMP BH,9D                 ;IF OUTPUT_COL IS 9 ( LAST COL ) 
        JZ  STORE_AFTER_CHECK     ;STORE COMMAND IF OTHER CONSTRAINTS ARE CORRECT
        
        MOV BL,[DI]+5             ;MOV BL OUTPUT_ROW
        
        CMP BL,0                  ;ELSE IF OUTPUT_COL != 9 THEREFORE CHECK IF OUTPUT_ROW = 0
        JZ  LOOP_ERROR_CHECK      ;IF OUTPUT_ROW = 0 THEREFOR WRONG COMMAND ELSE CONTINUE TO STORE  
        
        MOV BL,[DI]               ;MOVE BL INPUT1_COL
        CMP BL,0                  ;IF COL = 0 THEREFORE STORE WITHOUT CHECKING THE ROW
        JZ  STORE_AFTER_CHECK
        JMP CHECK_FIRST_INPUT_ROW
        
    CHECK_FIRST_INPUT_ROW:
        
        MOV BL,[DI]+1                  ;MOVE INPUT1_ROW
        CMP BL,0
        JZ  LOOP_ERROR_CHECK            
        JMP CHECK_SECOND_INPUT_ROW     ;IF ALL CONSTRAINTS ARE CORRECT END CHECK 
        
    CHECK_SECOND_INPUT_ROW:
    
        MOV BL,[DI]+3
        CMP BL,0
        JZ  LOOP_ERROR_CHECK
        JMP STORE_AFTER_CHECK        
   
CHECK_WIRE_GATE:

;CHECK IF COMMAND IS CORRECT AND ACHIEVABLE
        
        LEA DI,INPUT1_COL
        MOV BL,[DI]
        MOV BH,[DI]+1
        
        CMP BL,0
        JNZ LOOP_ERROR_CHECK      ;CHECK IF FIRST INPUT IN WIRE = 00
        CMP BH,0
        JNZ LOOP_ERROR_CHECK      ;CHECK IF FIRST INPUT IN WIRE = 00
        
        
        LEA DI,INPUT2_COL         ;MOVE OFFSET INPUT1_COL TO DI
        MOV BL,[DI]               ;MOVE INPUT2_COL TO BL
        MOV BH,[DI]+2             ;MOVE OUTPUT_COL TO BH
        SUB BH,BL                 ;SUBTRACT OUTPUT_COL = 1  AND INPUT2_COL =  3 
        
        JC  LOOP_ERROR_CHECK      ;CHECK THAT THE OUTPUT_COL IS >> INPUT_COL
        
        CMP BH,2                  ;IF DIFFERENCE = 2 
        JZ  INPUT_WIRE_CHECK      ;JUMP TO STORE COMMAND 
        
        CMP BH,1                  ;IF DIFFERENCE = 1 ( 1-3= -1-1 -> FEH )
        JZ  INPUT_WIRE_CHECK      ;JUMP TO STORE COMMAND   
                
        JMP  LOOP_ERROR_CHECK
        
        INPUT_WIRE_CHECK:
        
        LEA DI,INPUT2_COL        
        MOV BL,[DI]               ;MOVE INPUT2_COL TO BL 
        CMP BL,0                  ;IF INPUT2_COL = 0 JUMP TO CHECK OUTPUT ( FIRST COLUMN HAS 10 INPUT PINS )
        JZ  LAST_WIRE_CHECK
        
        MOV BL,[DI]+1             ;IF INPUT2_COL != 0 , MOVE INPUT2_ROW 
        CMP BL,0                  ;IF EQUAL 0 JUMP TO ERROR LOOP 
        JZ  LOOP_ERROR_CHECK 
        
        JMP LAST_WIRE_CHECK       ;IF NOT CONTINUE CHECKING 
        
        
        LAST_WIRE_CHECK:
        
        LEA DI,INPUT3_COL
        MOV BH,[DI]               ;MOV OUTPUT_COL TO BH
        CMP BH,9D                 ;IF OUTPUT_COL IS 9 ( LAST COL ) 
        JZ  STORE_AFTER_CHECK     ;STORE COMMAND IF OTHER CONSTRAINTS ARE CORRECT
        
        MOV BL,[DI]+1             ;MOV BL OUTPUT_ROW
        CMP BL,0                  ;ELSE IF OUTPUT_COL != 9 THEREFORE CHECK IF OUTPUT_ROW = 0
        JZ  LOOP_ERROR_CHECK      ;IF OUTPUT_ROW = 0 THEREFOR WRONG COMMAND ELSE CONTINUE TO STORE
                            
        JMP STORE_AFTER_CHECK     ;ELSE THE COMMAND IS NOT CORRECT --> DISPLAY ERROR MSG  
        
CHECK_NOT_GATE:

;CHECK IF GAME LEVEL IS 2 OR NOT
        
        CMP GAME_LEVEL,2
        JNZ LOOP_ERROR_CHECK

;CHECK IF COMMAND IS CORRECT AND ACHIEVABLE
        
        LEA DI,INPUT1_COL
        MOV BL,[DI]                 ;PUT INPUT1_COL IN BL
        MOV BH,[DI]+1               ;PUT INPUT1_ROW IN BH
        
        CMP BL,0
        JNZ LOOP_ERROR_CHECK        ;CHECK IF INPUT1 COL IN NOT = 0
        CMP BH,0
        JNZ LOOP_ERROR_CHECK        ;CHECK IF INPUT1 ROW IN NOT = 0
        
        LEA DI,INPUT2_COL         ;MOVE OFFSET INPUT2_COL TO DI
        MOV BL,[DI]               ;MOVE INPUT2_COL TO BL
        MOV BH,[DI]+2             ;MOVE OUTPUT_COL TO BH
        SUB BH,BL                 ;SUBTRACT OUTPUT_COL AND INPUT2_COL 
        
        JC  LOOP_ERROR_CHECK      ;CHECK THAT THE OUTPUT_COL IS >> INPUT2_COL
        
        CMP BH,1                  ;CHECK IF THE DIFFERENCE IS 1 
        JNZ LOOP_ERROR_CHECK      ;IF NOT 1 JMP TO ERROR MSG 
        
        MOV BL,[DI]               ;MOVE INPUT2_COL TO BL
        CMP BL,0
        JZ  LAST_NOT_CHECK
        
        MOV BL,[DI]+1
        CMP BL,0
        JZ  LOOP_ERROR_CHECK
        
        JMP LAST_NOT_CHECK
        
        LAST_NOT_CHECK:
        
        MOV BH,[DI]+4             ;MOV OUTPUT_COL TO BH        
        
        CMP BH,9D                 ;IF OUTPUT_COL IS 9 ( LAST COL ) 
        JZ  STORE_AFTER_CHECK     ;STORE COMMAND IF OTHER CONSTRAINTS ARE CORRECT
        
        MOV BL,[DI]+5             ;MOV BL OUTPUT_ROW
        
        CMP BL,0                  ;ELSE IF OUTPUT_COL != 9 THEREFORE CHECK IF OUTPUT_ROW = 0
        JZ  LOOP_ERROR_CHECK      ;IF OUTPUT_ROW = 0 THEREFOR WRONG COMMAND ELSE CONTINUE TO STORE          
         
        JMP STORE_AFTER_CHECK     
        
CHECK_DELETE_COMMAND:   
                                                              
        CALL DELETE_STORED_COMMAND
          
        JMP END_CHECK_COMMAND
                                                              
LOOP_ERROR_CHECK:    
    
    MOV ERROR_FLAG,1D
    JMP END_CHECK_COMMAND 
    
STORE_AFTER_CHECK:

    CALL STORE_COMMAND
    JMP END_CHECK_COMMAND
    
END_CHECK_COMMAND:


    POPA 
    POPF
    
    RET



CHECK_COMMAND                 ENDP    

;////////////////////////// STORE INPUT COMMANDS /////////////////////////////////////////////////

STORE_COMMAND                 PROC
    
    PUSHA
    PUSHF
    
    LEA SI,GATE
    
    MOV AX,0
    MOV BX,0 
    MOV CX,0
    MOV DX,0
    
    MOV AL,[SI]+5          ;MOVE OUTPUT COLUMN TO BL
    MOV BL,[SI]+6          ;MOVE OUTPUT ROW TO AL

 ;******* EQUATION TO DETERMINE THE INDEX OF COMMAND ADDED TO STORE IT    
    
    MOV CL,7       
    MUL CL         ;MUL OUTPUT_COL BY 7
    
    ;CMP BL,0       ;CHECK IF OUTPUT ROW = 0 (NOT ACCEPTED)
    ;JZ  FAIL_PROC
  
    CMP AL,0       ;CHECK IF OUTPUT COL = 0 (NOT ACCEPTED)
    JZ  FAIL_PROC
    
    XCHG AX,BX     ;SWITCH BETWEEN AX AND BX ( AX=BX ,, BX=AX )
    
    MOV DL,70
    MUL DL         ;MULTIPLY INDEX BY 70 TO DETERMINE ROW 
    ADD AX,BX      ;ADD ROW TO COLUMN STORED IN BX  (AX = INDEX COMMAND )
    
    LEA DI,COMMAND_MAP   
    ADD DI,AX      ;NOW DI POINTS AT COMMAND_MAP[OUTPUT_INDEX]
    
    MOV CX,6
    MOV AL,[SI]
    MOV BYTE PTR [DI],AL
    
    
 ALL_CHARS_LOOP_1:    ;STORE EVERY CHAR IN COMMAND IN THE SELECTED INDEX IN COMMAND_MAP
    
    INC SI 
    INC DI
    MOV AL,[SI]  
    ADD AL,30H
    MOV BYTE PTR [DI],AL
    
    DEC CX
    JNZ ALL_CHARS_LOOP_1 
    JMP END_STORE_PROC
       

 FAIL_PROC:         ;IF COMMAND IS WRONG IT WON'T BE STORED   

    MOV ERROR_FLAG,1
    JMP END_STORE_PROC
    
 END_STORE_PROC:    
    
    POPA
    POPF
        
    RET
STORE_COMMAND                 ENDP







;////////////////////////// DELETE STORED COMMAND ////////////////////////////////////////////////

DELETE_STORED_COMMAND        PROC    
    
    PUSHA
    PUSHF 
    
    MOV AX,0
    MOV BX,0 
    MOV CX,0
    MOV DX,0
    
    LEA SI,GATE
    MOV AL,[SI]+5          ;MOVE OUTPUT COLUMN TO AL
    MOV BL,[SI]+6          ;MOVE OUTPUT ROW TO BL

             ;************* EQUATION TO DETERMINE THE INDEX OF COMMAND ADDED TO STORE IT ******************    
    
    MOV CL,7       
    MUL CL         ;MUL OUTPUT_COL BY 7
    
    ;CMP BL,0       ;CHECK IF OUTPUT COL = 0 (NOT ACCEPTED)
    ;JZ  FAIL_DELETE
  
    CMP AL,0       ;CHECK IF OUTPUT ROW = 0 (NOT ACCEPTED)
    JZ  FAIL_DELETE
    
    XCHG AX,BX     ;SWITCH BETWEEN AX AND BX ( AX=BX ,, BX=AX )
    
    MOV DL,70
    MUL DL         ;MULTIPLY INDEX BY 70 TO DETERMINE ROW 
    ADD AX,BX      ;ADD ROW TO COLUMN STORED IN BX  (AX = INDEX COMMAND )
    MOV DX,AX      ;STORE VALUE IN DX TO USE AGAIN IN CHECKING IF INPUT SWAPPED
    
    LEA SI,GATE
    LEA DI,COMMAND_MAP   
    ADD DI,AX      ;NOW DI POINTS AT COMMAND_MAP[OUTPUT_INDEX]
    INC DI         ;NOW DI POINTS ON GATE TYPE OF THE CURRENT INSTRUCTION 
    INC SI         ;POINT TO INPUT1_COL OF NEW COMMAND
    MOV CX,6
    
 COMMAND_CHECK:
    
    MOV AL,[DI]       ;MOVE AL CONTENT DI 
    SUB AL,30H
    CMP AL,[SI]       ;COMPARE STORED COMMAND WITH THE INPUT COMMAND 
    JNZ CHECKSWAPPED  ;IF NOT = 0 THERE FOR COMMAND IS WRONG AND SHOULDN'T BE DELETED
    INC DI
    INC SI
    DEC CX
    JNZ COMMAND_CHECK
    JZ  COMMAND_CORRECT
    
 ;CHECK IF INPUT IS SWAPPED
    CHECKSWAPPED:
    
    LEA SI,GATE
    LEA DI,COMMAND_MAP
    ADD DI,DX         ;NOW DI POINTS ON GATE TYPE OF THE CURRENT INSTRUCTION  
    
 ;COMPARE INPUT1_COL IN COMMAND_MAP WITH INPUT2_COL (NEW COMMAND)                              
    MOV AL,[DI]+1
    SUB AL,30H
    CMP AL,[SI]+3
    JNZ FAIL_DELETE

 ;COMPARE INPUT1_ROW IN COMMAND_MAP WITH INPUT2_ROW (NEW COMMAND)    
    MOV AL,[DI]+2
    SUB AL,30H
    CMP AL,[SI]+4
    JNZ FAIL_DELETE

 ;COMPARE INPUT2_COL IN COMMAND_MAP WITH INPUT1_COL (NEW COMMAND)
    MOV AL,[DI]+3
    SUB AL,30H
    CMP AL,[SI]+1
    JNZ FAIL_DELETE

 ;COMPARE INPUT2_ROW IN COMMAND_MAP WITH INPUT1_ROW (NEW COMMAND)   
    MOV AL,[DI]+4
    SUB AL,30H
    CMP AL,[SI]+2
    JNZ FAIL_DELETE

 ;COMPARE OUTPUT_COL IN COMMAND_MAP WITH OUTPUT_COL (NEW COMMAND)    
    MOV AL,[DI]+5
    SUB AL,30H
    CMP AL,[SI]+5
    JNZ FAIL_DELETE

 ;COMPARE OUTPUT_ROW IN COMMAND_MAP WITH OUTPUT_ROW (NEW COMMAND)    
    MOV AL,[DI]+6
    SUB AL,30H
    CMP AL,[SI]+6
    JNZ FAIL_DELETE
 
       
 ;************** IF COMMAND IS CORRECT PROCEED TO DELETE ************* 
    COMMAND_CORRECT:
       
    MOV CX,7
    LEA SI,GATE
    LEA DI,COMMAND_MAP
    ADD DI,DX                  ;NOW DI POINTS ON GATE TYPE OF THE CURRENT INSTRUCTION
    MOV AL,[DI]
    
 ALL_CHARS_LOOP_2:              ;STORE EVERY CHAR IN COMMAND IN THE SELECTED INDEX IN COMMAND_MAP
     
    MOV BYTE PTR [DI],0H       ;PUT ZEROS IN COMMAND INDEX TO DELETE IT 
    INC DI
    DEC CX
    JNZ ALL_CHARS_LOOP_2

    CMP AL,87D                  ;IF WIRE FILL SCREEN
    JE FILLSCREEN_WIRE
    JNZ CLEARSCREEN_GATES
    
    FILLSCREEN_WIRE:
    CALL FillScreen
    JMP END_DELETE_PROC

    CLEARSCREEN_GATES:
    CALL ClearScreen
    JMP END_DELETE_PROC


 FAIL_DELETE:

    MOV ERROR_FLAG,1
    JMP END_DELETE_PROC
    
 END_DELETE_PROC:    
    
    POPA
    POPF
        
    RET

DELETE_STORED_COMMAND         ENDP

;////////////////////////// DO ALL STORED COMMANDS ///////////////////////////////////////////////

REFRESH                    PROC
    
    PUSHA
    PUSHF
    ;call Entergraphics
    ;call FillScreen
    call drawlineThick
    call DrawLinethinBottom
    call DrawLinethinTop
    call DrawVerticalLines
    call DrawInputs
    call draw_num_cols_odd
    call draw_num_cols_even
    call info

    
    LEA DI,COMMAND_MAP 
    
    MOV COMMAND_CHARS_COUNT,7D
    MOV COMMAND_ROWS_COUNT,10D
    MOV COMMAND_COLS_COUNT,10D 

 NEXT_COL_OF_COMMANDS:
       
    MOV COMMAND_ROWS_COUNT,10D
    
 NEXT_ROW_OF_COMMANDS:

    LEA SI,GATE  
    MOV COMMAND_CHARS_COUNT,7D
       
 TRASNFER_COMMAND:
    
    MOV AL,[DI]                           ;MOV COMMAND FROM COMMAND_MAP TO AL ( BYTE BY BYTE )
    MOV [SI],AL                           ;MOV COMMAND FROM AL TO INPUT_COMMAND ( BYTE BY BYTE )
    INC SI                                ;MOVE TO NEXT BYTE IN INPUT COMMAND
    INC DI                                ;MOVE TO NEXT BYTE IN COMMAND STORED IN COMMAND_MAP
    
    DEC COMMAND_CHARS_COUNT
    JNZ TRASNFER_COMMAND 
    
    SUB DI,7                              ;MOVE DI TO GATE BYTE OF STORED COMMAND IN COMMAND_MAP
    CMP BYTE PTR [DI],0                            
    JZ  SKIP_CALL                         ;IF GATE = 0 THEREFOR NO COMMAND IS STORED CONTINUE TO NEXT ONE 
    
    MOV BX,DI
    MOV SAVE_DI_IN_LOGIC,BX
    
    CALL DO_LOGIC                         ;IF THERE IS A COMMAND THEN DO IT AND CONTINUE TO NEXT ONE
    CALL INPUT_COMMAND_TO_DRAW_ARRAY
    CALL get_all2_coordinates
    CALL INITIALIZE_DRAW_ARRAY
    ;CMP  WIRE_DRAWN_FLAG,1
    ;JZ   AFTER_WIRE
    CALL drawwire_and_gate
        
    call DrawNodes
    call DrawOutputs 
    call draw_input_cols 
    call draw_bottom_nums

    ;AFTER_WIRE:
    ;MOV WIRE_DRAWN_FLAG,0

    MOV BX,SAVE_DI_IN_LOGIC
    MOV DI,BX
    MOV ERROR_FLAG,0 
    

SKIP_CALL:     
    
    ADD DI,70D                             ;MOVE DI TO NEXT ROW OF THE SAME COL IN COMMAND_MAP
                
    DEC COMMAND_ROWS_COUNT
    JNZ NEXT_ROW_OF_COMMANDS
    
    SUB DI,700D                           ;MOVE DI TO THE BEGINNING OF NEXT COL IN COMMAND_MAP
    ADD DI,7D
    DEC COMMAND_COLS_COUNT
    JNZ NEXT_COL_OF_COMMANDS       
    
    call DrawNodes
    call DrawOutputs 
    call draw_input_cols 
    call draw_bottom_nums

    POPA 
    POPF                                    

    RET

REFRESH                    ENDP   

;//////////////////////////////////// DO LOGIC OF ONE COMMAND ////////////////////////////////////

DO_LOGIC                   PROC
    
    PUSHA
    PUSHF
    
    CALL ASCII_TO_DECIMAL_LOGIC  
    
    CMP  ERROR_FLAG,1
    JZ   END_DO_LOGIC
    
    CALL MANAGE_MAP
    
    CALL GATE_TYPE
    
    CMP  ERROR_FLAG,1
    JZ   END_DO_LOGIC
    
    
END_DO_LOGIC:    
    
    POPA
    POPF
    
    RET
    
    
DO_LOGIC                   ENDP 

;////////////////////////////////// ASCII TO DECIMAL /////////////////////////////////////////////

ASCII_TO_DECIMAL_LOGIC           PROC
       
        LEA SI,INPUT1_COL 
        MOV CX,6 
        
CHECK2:
        CMP BYTE PTR [SI],30H
        JC  LOOP_ERROR_ASCII_DEC_2


        CMP BYTE PTR [SI],3AH
        JNC LOOP_ERROR_ASCII_DEC_2

        INC SI
        DEC CX
        JNZ CHECK2
        
        LEA SI,INPUT1_COL 
        MOV CX,6
                
LOOP_MANAGE_2:        
         
        SUB BYTE PTR [SI],30H 
        INC SI
        DEC CX
        JNZ LOOP_MANAGE_2 
        
        JMP END_ASCII_TO_DEC_IN_LOGIC
        
LOOP_ERROR_ASCII_DEC_2:

        MOV ERROR_FLAG,1
         
END_ASCII_TO_DEC_IN_LOGIC:
        
       
        RET

ASCII_TO_DECIMAL_LOGIC           ENDP

;///////////////////////////////////// INITIALIZE MAP INDEX /////////////////////////////////////

INITIALIZE_MAP_INDEX       PROC
    
    PUSHA 
    PUSHF
    
    LEA SI,MAP_INDEX
    INC SI
    MOV CH,10  
    
INITIALIZE_NEXT_ROW:
    
    MOV CL,9   
     
INITIALIZE_ROWS:
    
    MOV BYTE PTR [SI],10H
    INC SI
    DEC CL
    JNZ INITIALIZE_ROWS
    
    INC SI
    DEC CH 
    JNZ INITIALIZE_NEXT_ROW
    
    
    POPA
    POPF
    
    RET
 
INITIALIZE_MAP_INDEX       ENDP

;//////////////////////////////////////////////////////////////////////////////////////////////// 

;////////////////////////////////////// INITIALIZE_COMMAND_MAP////////////////////////////////
INITIALIZE_COMMAND_MAP       PROC
        
        PUSHA 
        PUSHF
        
                LEA SI,COMMAND_MAP
                MOV CX,700D

                CONTINUE_INITIALIZE:
                MOV BYTE PTR [SI],0
                INC SI
                DEC CX
                JNZ CONTINUE_INITIALIZE

        POPA
        POPF
        RET

INITIALIZE_COMMAND_MAP       ENDP
;////////////////////////////////////////////////////////////////////////////////////////////////

;////////////////////////////////////// TAKE LEVEL     //////////////////////////////////////////



TAKE_LEVEL                  PROC
        PUSHA
        PUSHF
                LEA SI,GAME_LEVEL

                WAIT_FOR_1_OR_2:
                MOV AH,0
                INT 16h

                CMP AL,31h
                JZ LEVEL_1

                CMP AL,32h
                JZ LEVEL_2
                
                JNZ WAIT_FOR_1_OR_2

                LEVEL_1:
                MOV BYTE PTR [SI],1d
                JMP END_LEVEL_PROC

                LEVEL_2:
                MOV BYTE PTR [SI],2d
                JMP END_LEVEL_PROC

                END_LEVEL_PROC:
        POPA
        POPF
        RET    
TAKE_LEVEL                  ENDP


;///////////////////////////////////////////// RNG  ///////////////////////////////////////////////
RNG                             PROC
                   
        mov si,0 ;safrna el si
    rng_repeating:
    mov ah,0                    ;sytem time
    int 1ah                     ;int code
    mov al,dl                   ;put seconds in dl & al
    xor dl,rngnode           ;el rgnode el fou2 
    mov dh,0                    ;safrt dh
    shl dx,1                    ;shift left (*2)
    xor dh,dl                   ;(chaiotic)
    shl dx,1                    ;shift tany (*2)
    mov ah,34                   ;ay rakm
    xor ax,dx                   ; chaiotic
    and ah,1                    ;ne2sm 3la 2 to get 0,1
    mov rngnode,dh           ;random no.(bykhtlf kol loop)
    mov map_index[si],ah        ; reaminder el division y 0 y 1
    add si,10                   ;counter 
    cmp si,90                   ;compare with 10
    jnz rng_repeating           ;h3ed el function 10 marat
          
RET
RNG                             ENDP




;///////////////////////////////////////////// SCOREBOARD  ///////////////////////////////////////////////

SCOREBOARD                              PROC
        PUSHA
        PUSHF

                TEXTMODE
                ClearscreenM

                CAll CALC_SCORE

                ;USER 1
                MOVECURSOR 0,0
                DisplayString MESS_USER_1_SCORE

                MOVECURSOR 0,2
                DisplayString MESS_USER_No0
                DisplayChar COUNTER_USER1_0
                
                MOVECURSOR 0,3
                DisplayString MESS_USER_No1
                DISPLAYCHAR COUNTER_USER1_1     


                ;USERC2
                MOVECURSOR 0,15
                DisplayString MESS_USER_2_SCORE

                MOVECURSOR 0,17
                DisplayString MESS_USER_No0
                DisplayChar COUNTER_USER2_0
                
                MOVECURSOR 0,18
                DisplayString MESS_USER_No1
                DISPLAYCHAR COUNTER_USER2_1 




                ;DELAY FOR 5 SECONDS
                MOV BX,5                                ;loop for 5 seconds
                MOV     CX, 0FH                         ;CX:DX number of microseconds to elapse
                MOV     DX, 4240H                       ; 1 second delay =1000 000 microseconds 

                LOOP_DELAY:                             ;INT FOR DELAY
                MOV AH,86h
                INT 15H

                DEC BX
                JNZ LOOP_DELAY

        POPF
        POPA
        RET

    SCOREBOARD                          ENDP

;///////////////////////////////////////////// CALC SCORE  ///////////////////////////////////////////////

CALC_SCORE                              PROC
        PUSHA
        PUSHF   

                ;USER 1 NODES

                MOV CX,5                                ;COUNTER FOR 5 OUTPUT NODES
                LEA SI,MAP_INDEX                        
                ADD SI,9                                ;SI POINTS ON USER1 FIRST OUTPUT NODE
                MOV COUNTER_USER1_0,0                   ;INITIALIZE USER 1 COUNTERS
                MOV COUNTER_USER1_1,0

                USER1_OUTPUT_NODES:
               
                MOV AL,[SI]                     
                ADD SI,10                               ;MOV SI TO NEXT OUTPUT NODE

                CMP AL,1                                ;CMP NODE WITH 1 OR 0 TO INC COUNTERS ACCORDINGLY
                JZ INCREMENT_USER1_ONES
                JNZ CHECK_USER1_ZEROS

                INCREMENT_USER1_ONES:
                INC COUNTER_USER1_1
                JMP END_USER1_CHECK_NODE
                
                CHECK_USER1_ZEROS:
                CMP AL,0
                JZ INCREMENT_USER1_ZEROS
                JNZ END_USER1_CHECK_NODE

                INCREMENT_USER1_ZEROS:
                INC COUNTER_USER1_0
                JMP END_USER1_CHECK_NODE

                END_USER1_CHECK_NODE:
                DEC CX
                JNZ USER1_OUTPUT_NODES

                ADD COUNTER_USER1_0,30H                 ;CHANGE USER 1 COUNTER FOR ASCII TO PRINT
                ADD COUNTER_USER1_1,30H





                ;USER 2 NODES
                
                MOV CX,5                                        ;COUNTER FOR 5 OUTPUT NODES
                LEA SI,MAP_INDEX                                ;SI POINTS ON USER2 FIRST OUTPUT NODE
                ADD SI,59
                MOV COUNTER_USER2_0,0                           ;INITIALIZE USER 2 COUNTERS
                MOV COUNTER_USER2_1,0

                USER2_OUTPUT_NODES:
                
                MOV AL,[SI]
                ADD SI,10                                       ;MOV SI TO NEXT OUTPUT NODE

                CMP AL,1                                        ;CMP NODE WITH 1 OR 0 TO INC COUNTERS ACCORDINGLY
                JZ INCREMENT_USER2_ONES
                JNZ CHECK_USER2_ZEROS

                INCREMENT_USER2_ONES:
                INC COUNTER_USER2_1
                JMP END_USER2_CHECK_NODE
                
                CHECK_USER2_ZEROS:
                CMP AL,0
                JZ INCREMENT_USER2_ZEROS
                JNZ END_USER2_CHECK_NODE

                INCREMENT_USER2_ZEROS:
                INC COUNTER_USER2_0
                JMP END_USER2_CHECK_NODE

                END_USER2_CHECK_NODE:
                DEC CX
                JNZ USER2_OUTPUT_NODES

                ADD COUNTER_USER2_0,30H                                 ;CHANGE USER 2 COUNTER FOR ASCII TO PRINT
                ADD COUNTER_USER2_1,30H

        POPA
        POPF
        RET

CALC_SCORE                              ENDP