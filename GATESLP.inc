.CODE

GATE_TYPE                     PROC  
                    
; ***********CHECK GATE TYPE*********
       
        LEA DI,GATE
        
        CMP BYTE PTR [DI],65D              ;COMPARE GATE WITH ASCII VALUE OF A
        JZ  LOOP_AND
    
        CMP BYTE PTR [DI],79D              ;COMPARE GATE WITH ASCII VALUE OF O
        JZ  LOOP_OR
    
        CMP BYTE PTR [DI],68D              ;COMPARE GATE WITH ASCII VALUE OF D
        JZ  LOOP_NAND    
    
        CMP BYTE PTR [DI],82D              ;COMPARE GATE WITH ASCII VALUE OF R
        JZ  LOOP_NOR
    
        CMP BYTE PTR [DI],88D              ;COMPARE GATE WITH ASCII VALUE OF X
        JZ  LOOP_XOR
    
        CMP BYTE PTR [DI],78D              ;COMPARE GATE WITH ASCII VALUE OF N
        JZ  LOOP_XNOR 
        
        CMP BYTE PTR [DI],87D              ;COMPARE GATE WITH ASCII VALUE OF W
        JZ  LOOP_WIRE  
        
        CMP BYTE PTR [DI],73D              ;COMPARE GATE WITH ASCII VALUE OF I
        JZ  LOOP_NOT               
        
        
        JMP END_PROC_GATE
;************ CALL INPUT GATE **************

LOOP_AND:
    CALL AND_GATE
    JMP  END_PROC_GATE
    
LOOP_OR: 
    CALL OR_GATE
    JMP  END_PROC_GATE

LOOP_NAND:    
    CALL NAND_GATE
    JMP  END_PROC_GATE
    
LOOP_NOR:    
    CALL NOR_GATE
    JMP  END_PROC_GATE

LOOP_XOR:    
    CALL XOR_GATE
    JMP  END_PROC_GATE

LOOP_XNOR:    
    CALL XNOR_GATE
    JMP  END_PROC_GATE
    
LOOP_WIRE:    
    CALL WIRE_GATE
    JMP  END_PROC_GATE

LOOP_NOT:    
    CALL NOT_GATE
    JMP  END_PROC_GATE      
     
END_PROC_GATE:  
      
      RET
    
GATE_TYPE                     ENDP  


;////////////////////////////////// ALL GATES LOGIC ///////////////////////////////////


;////////////////////////// AND GATE PROC //////////////////////

AND_GATE                     PROC
             
;CHECK IF INPUT IS GARBAGE
          
        CMP AL,10H
        JZ  UNKNOWN_OUTPUT_AND        ;CHECK IF INPUT 1 IS GARBAGE
        
        CMP AH,10H
        JZ  UNKNOWN_OUTPUT_AND        ;CHECK IF INPUT 2 IS GARBAGE
        
        
        CMP AL,20H
        JZ  UNKNOWN_OUTPUT_AND        ;CHECK IF INPUT 1 IS GARBAGE
        
        CMP AH,20H
        JZ  UNKNOWN_OUTPUT_AND        ;CHECK IF INPUT 2 IS GARBAGE

;DO OPERATION
        
        AND AL,AH                 ;MAP_INDEX[INPUT1_INDEX] AND MAP_INDEX[INPUT2_INDEX] and store value in AL
        MOV [SI],AL               ;MOVE AL TO MAP_INDEX[OUTPUT_INDEX] (output value to output pin)
        JMP END_PROC_AND

    
UNKNOWN_OUTPUT_AND:

    CALL UNKNOWN_OUTPUT
    JMP  END_PROC_AND
       
END_PROC_AND:
     
    RET
                                                                  
AND_GATE                     ENDP


;////////////////////////// OR GATE PROC //////////////////////

OR_GATE                     PROC
    
;CHECK IF INPUT IS GARBAGE
        
        CMP AL,10H
        JZ  UNKNOWN_OUTPUT_OR     ;CHECK IF INPUT 1 IS GARBAGE
        
        CMP AH,10H
        JZ  UNKNOWN_OUTPUT_OR     ;CHECK IF INPUT 1 IS GARBAGE
        
        
        CMP AL,20H
        JZ  UNKNOWN_OUTPUT_OR     ;CHECK IF INPUT 1 IS GARBAGE
        
        CMP AH,20H
        JZ  UNKNOWN_OUTPUT_OR     ;CHECK IF INPUT 1 IS GARBAGE

;DO OPERATION 
        
        OR AL,AH                  ;MAP_INDEX[INPUT1_INDEX] OR MAP_INDEX[INPUT2_INDEX] and store value in AL 
        MOV [SI],AL               ;MOVE AL TO MAP_INDEX[OUTPUT_INDEX] (output value to output pin)
        JMP END_PROC_OR

UNKNOWN_OUTPUT_OR:

    CALL UNKNOWN_OUTPUT
    JMP  END_PROC_OR
      
END_PROC_OR:    
    
    RET
                                    
                                                                  
OR_GATE                     ENDP


;////////////////////////// NAND GATE PROC //////////////////////

NAND_GATE                     PROC
        
;CHECK IF INPUT IS GARBAGE
        
        CMP AL,10H
        JZ  UNKNOWN_OUTPUT_NAND        ;CHECK IF INPUT 1 IS GARBAGE
        
        CMP AH,10H
        JZ  UNKNOWN_OUTPUT_NAND        ;CHECK IF INPUT 2 IS GARBAGE          
        
        CMP AL,20H
        JZ  UNKNOWN_OUTPUT_NAND        ;CHECK IF INPUT 1 IS GARBAGE
        
        CMP AH,20H
        JZ  UNKNOWN_OUTPUT_NAND        ;CHECK IF INPUT 2 IS GARBAGE

;DO OPERATION
         
        AND AL,AH                 ;MAP_INDEX[INPUT1_INDEX] AND MAP_INDEX[INPUT2_INDEX] and store value in AL
        NOT AL                    ;INVERSE OUTPUT TO BE NAND
        
        CMP AL,0FFH               ;COMPARE AL TO FFh IF = 0 -> THEREFOR ANSWER =1  ( FFh = NOT 0 )
        JZ  ANS_ONE_NAND
               
        CMP AL,0FEH               ;COMPARE AL TO FFh IF = 1 -> THEREFOR ANSWER =0  ( FEh = NOT 1 )
        JZ  ANS_ZERO_NAND
        
        JMP END_PROC_NAND

ANS_ZERO_NAND:
        
        MOV BYTE PTR [SI],0                ;MOVE ZERO TO OUTPUT PIN
        JMP END_PROC_NAND 
        
ANS_ONE_NAND:
        
        MOV BYTE PTR [SI],1                ;MOVE ONE TO OUTPUT PIN
        JMP END_PROC_NAND
    
UNKNOWN_OUTPUT_NAND:

    CALL UNKNOWN_OUTPUT
    JMP  END_PROC_NAND
       
END_PROC_NAND:     

    
    RET
                                                                  
NAND_GATE                     ENDP


;////////////////////////// NOR GATE PROC //////////////////////

NOR_GATE                     PROC
    
;CHECK IF INPUT IS GARBAGE
        
        CMP AL,10H
        JZ  UNKNOWN_OUTPUT_NOR        ;CHECK IF INPUT 1 IS GARBAGE
        
        CMP AH,10H
        JZ  UNKNOWN_OUTPUT_NOR        ;CHECK IF INPUT 2 IS GARBAGE          
        
        CMP AL,20H
        JZ  UNKNOWN_OUTPUT_NOR        ;CHECK IF INPUT 1 IS GARBAGE
        
        CMP AH,20H
        JZ  UNKNOWN_OUTPUT_NOR        ;CHECK IF INPUT 2 IS GARBAGE
;DO OPERATION
         
        OR  AL,AH                 ;MAP_INDEX[INPUT1_INDEX] AND MAP_INDEX[INPUT2_INDEX] and store value in AL
        NOT AL                    ;INVERSE OUTPUT TO BE NAND
        
        CMP AL,0FFH               ;COMPARE AL TO FFh IF = 0 -> THEREFOR ANSWER =1  ( FFh = NOT 0 )
        JZ  ANS_ONE_NOR
               
        CMP AL,0FEH               ;COMPARE AL TO FFh IF = 1 -> THEREFOR ANSWER =0  ( FEh = NOT 1 )
        JZ  ANS_ZERO_NOR
        
        JMP END_PROC_NOR

ANS_ZERO_NOR:
        
        MOV BYTE PTR [SI],0                ;MOVE ZERO TO OUTPUT PIN
        JMP END_PROC_NOR 
        
ANS_ONE_NOR:
        
        MOV BYTE PTR [SI],1                ;MOVE ONE TO OUTPUT PIN
        JMP END_PROC_NOR
        
UNKNOWN_OUTPUT_NOR:

    CALL UNKNOWN_OUTPUT
    JMP  END_PROC_NOR
    
    
END_PROC_NOR:      
        
    RET
                                                                  
NOR_GATE                     ENDP   


;////////////////////////// XOR GATE PROC //////////////////////

XOR_GATE                     PROC

;CHECK IF INPUT IS GARBAGE
        
        CMP AL,10H
        JZ  UNKNOWN_OUTPUT_XOR     ;CHECK IF INPUT 1 IS GARBAGE
        
        CMP AH,10H
        JZ  UNKNOWN_OUTPUT_XOR     ;CHECK IF INPUT 1 IS GARBAGE
        
        
        CMP AL,20H
        JZ  UNKNOWN_OUTPUT_XOR     ;CHECK IF INPUT 1 IS GARBAGE
        
        CMP AH,20H
        JZ  UNKNOWN_OUTPUT_XOR     ;CHECK IF INPUT 1 IS GARBAGE

;DO OPERATION 
        
        XOR AL,AH                  ;MAP_INDEX[INPUT1_INDEX] OR MAP_INDEX[INPUT2_INDEX] and store value in AL 
        MOV [SI],AL               ;MOVE AL TO MAP_INDEX[OUTPUT_INDEX] (output value to output pin)                                                                                                  
        JMP END_PROC_XOR

UNKNOWN_OUTPUT_XOR:

    CALL UNKNOWN_OUTPUT
    JMP  END_PROC_XOR
    
    
END_PROC_XOR:    
    
    RET
                                                                  
XOR_GATE                     ENDP


;////////////////////////// XNOR GATE PROC //////////////////////

XNOR_GATE                     PROC
        
;CHECK IF INPUT IS GARBAGE
        
        CMP AL,10H
        JZ  UNKNOWN_OUTPUT_XNOR        ;CHECK IF INPUT 1 IS GARBAGE
        
        CMP AH,10H
        JZ  UNKNOWN_OUTPUT_XNOR        ;CHECK IF INPUT 2 IS GARBAGE          
        
        CMP AL,20H
        JZ  UNKNOWN_OUTPUT_XNOR        ;CHECK IF INPUT 1 IS GARBAGE
        
        CMP AH,20H
        JZ  UNKNOWN_OUTPUT_XNOR        ;CHECK IF INPUT 2 IS GARBAGE
;DO OPERATION
         
        XOR AL,AH                 ;MAP_INDEX[INPUT1_INDEX] AND MAP_INDEX[INPUT2_INDEX] and store value in AL
        NOT AL                    ;INVERSE OUTPUT TO BE NAND
        
        CMP AL,0FFH               ;COMPARE AL TO FFh IF = 0 -> THEREFOR ANSWER =1  ( FFh = NOT 0 )
        JZ  ANS_ONE_XNOR
               
        CMP AL,0FEH               ;COMPARE AL TO FFh IF = 1 -> THEREFOR ANSWER =0  ( FEh = NOT 1 )
        JZ  ANS_ZERO_XNOR
        
        JMP END_PROC_XNOR

ANS_ZERO_XNOR:
        
        MOV BYTE PTR [SI],0                ;MOVE ZERO TO OUTPUT PIN
        JMP END_PROC_XNOR 
        
ANS_ONE_XNOR:
        
        MOV BYTE PTR [SI],1                ;MOVE ONE TO OUTPUT PIN
        JMP END_PROC_XNOR
        
UNKNOWN_OUTPUT_XNOR:

    CALL UNKNOWN_OUTPUT
    JMP  END_PROC_XNOR
       
END_PROC_XNOR:    
       
    RET
                                                                  
XNOR_GATE                     ENDP 

;////////////////////////// WIRE GATE PROC //////////////////////

WIRE_GATE                     PROC
                    
;CHECK IF INPUT IS GARBAGE 
        
        CMP AH,10H
        JZ  UNKNOWN_OUTPUT_WIRE        ;CHECK IF INPUT 2 IS GARBAGE 
        
        CMP AH,20H
        JZ  UNKNOWN_OUTPUT_WIRE        ;CHECK IF INPUT 2 IS GARBAGE

;DO OPERATION
        
        MOV [SI],AH               ;PUT CONTENT OF INPUT PIN IN THE OUTPUT PIN 
        JMP END_PROC_WIRE    

UNKNOWN_OUTPUT_WIRE:

    CALL UNKNOWN_OUTPUT
    JMP  END_PROC_WIRE
    
    
END_PROC_WIRE:    
   
    
    RET
                                                                  
WIRE_GATE                     ENDP   


;////////////////////////// NOT GATE PROC //////////////////////

NOT_GATE                     PROC 
    
    
;CHECK IF INPUT IS GARBAGE
        
        CMP AH,10H
        JZ  UNKNOWN_OUTPUT_NOT        ;CHECK IF INPUT 2 IS GARBAGE 
        
        CMP AH,20H
        JZ  UNKNOWN_OUTPUT_NOT        ;CHECK IF INPUT 2 IS GARBAGE

;DO OPERATION 

        NOT AH                    ;INVERT CONTENT OF INPUT PIN (AL)
        
        CMP AH,0FFH               ;COMPARE AL TO FFh IF = 0 -> THEREFOR ANSWER =1  ( FFh = NOT 0 )
        JZ  ANS_ONE_NOT
               
        CMP AH,0FEH               ;COMPARE AL TO FFh IF = 0 -> THEREFOR ANSWER =0  ( FEh = NOT 1 )
        JZ  ANS_ZERO_NOT
        
       
ANS_ZERO_NOT:
        
        MOV BYTE PTR [SI],0                ;MOVE ZERO TO OUTPUT PIN
        JMP END_PROC_NOT 
        
ANS_ONE_NOT:
        
        MOV BYTE PTR [SI],1                ;MOVE ONE TO OUTPUT PIN
        JMP END_PROC_NOT    

UNKNOWN_OUTPUT_NOT:

    CALL UNKNOWN_OUTPUT
    JMP  END_PROC_NOT
    
       
END_PROC_NOT:

    RET
                                                                  
NOT_GATE                     ENDP 


;////////////////////////// UNKNOWN OUTPUT PROC //////////////////////

UNKNOWN_OUTPUT                     PROC
       
    MOV BYTE PTR [SI],20H              ;PUT GARBAGE IN OUTPUT PIN IF ANY INPUT PIN IS GARBAGE ( 20H )
    CALL STORE_COMMAND

    RET
                                                                  
UNKNOWN_OUTPUT                     ENDP


;///////////////////////////// CHECK WINNER ACCORDING TO GAME LEVEL ////////////////////////

CHECK_WINNER                       PROC
    
    MOV AX,0
    MOV BX,0
    MOV CX,0 
    MOV DX,0                               ;INITIALIZE REGISTERS
    
    MOV BL,GAME_LEVEL                      ;PUT GAME LEVEL IN BL
    CMP BL,1                               ;IF 1 THEN CHECK LEVEL 1 WINNER
    JZ  LEVEL_1_WINNER_CHECK
    
    CMP BL,2                               ;IF 2 CHECK LEVEL 2 WINNER
    JZ  LEVEL_2_WINNER_CHECK  
    
    JMP NO_WINNER                          ;ELSE END CHECK
    
LEVEL_1_WINNER_CHECK:
    
    LEA SI,MAP_INDEX
    ADD SI,9                               ;MOVE SI TO COL 9 ROW 0 
    
    LEA DI,MAP_INDEX                       ;MOVE DI TO COL 9 ROW 5
    ADD DI,59D
    
    MOV CL,5
    MOV CH,5                               ;LOOPS COUNTERS 
    
    CHECK_USER_1_WINNER:
    
        CHECK_USER_1_PINS_1:
    
        MOV AL,[SI]                         ;MOVE USER 1 PINS TO AL       
        CMP AL,1                            ;COMPARE WITH 1 
        JZ  CHECK_USER_2_PINS_1             ;IF USER1 HAVE 1 IN HIS PINS JMP TO CHECK USER2 PINS
        ADD SI,10D                          ;MOVE SI TO NEXT ROW 
        DEC CL
        JNZ CHECK_USER_1_PINS_1 
        
        
        JMP CHECK_USER_2_WINNER
     
        CHECK_USER_2_PINS_1:
       
        MOV AH,[DI]                         ;MOVE USER 2 PINS TO AH         
        CMP AH,0                            ;COMPARE WITH 0
        JZ  USER_1_WINS                     ;IF USER1 HAVE 1 IN HIS PINS AND USER2 HAVE 0 --> JMP USER1 WINS
        ADD DI,10                           ;MOVE DI TO NEXT ROW
        DEC CH
        JNZ CHECK_USER_2_PINS_1
        
        
        JMP CHECK_USER_2_WINNER


    CHECK_USER_2_WINNER:

    LEA SI,MAP_INDEX
    ADD SI,9                               ;MOVE SI TO COL 9 ROW 0 
    
    LEA DI,MAP_INDEX                       ;MOVE DI TO COL 9 ROW 5
    ADD DI,59D
    
    MOV CL,5
    MOV CH,5                               ;LOOPS COUNTERS 
    
    
        CHECK_USER_2_PINS_2:
    
        MOV AL,[DI]                         ;MOVE USER 2 PINS TO AL      
        CMP AL,1                            ;COMPARE WITH 1
        JZ  CHECK_USER_1_PINS_2             ;IF USER2 HAVE 1 IN HIS PINS JMP TO CHECK USER1 PINS
        ADD DI,10D                          ;MOVE DI TO NEXT ROW 
        DEC CL
        JNZ CHECK_USER_2_PINS_2 
        
        
        JMP NO_WINNER
     
        CHECK_USER_1_PINS_2:
       
        MOV AH,[SI]                         ;MOVE USER 1 PINS TO AH
        CMP AH,0                            ;COMPARE WITH 0
        JZ  USER_2_WINS                     ;IF USER2 HAVE 1 IN HIS PINS AND USER1 HAVE 0 --> JMP TO USER2 WINS
        ADD SI,10                           ;MOVE SI TO NEXT ROW
        DEC CH
        JNZ CHECK_USER_2_PINS_2     
        
        JMP NO_WINNER          
        
LEVEL_2_WINNER_CHECK:

        MOV AX,0
        MOV BX,0
        MOV CX,0
        MOV DX,0

        LEA SI,MAP_INDEX
        ADD SI,9                               ;MOVE SI TO COL 9 ROW 0 
        
        LEA DI,MAP_INDEX                       ;MOVE DI TO COL 9 ROW 5
        ADD DI,59D
        
        MOV CL,5
        MOV CH,5                               ;LOOPS COUNTERS 

    CHECK_USER_1_ALL_PINS_WINNER:

        CHECK_USER_1_ALL_PINS_1:
    
        MOV AL,[SI]                         ;MOVE USER 1 PINS TO AL       
        CMP AL,1                            ;COMPARE WITH 1 
        JZ  INCREASE_COUNTER_USER1          ;IF USER1 HAVE 1 IN HIS PINS JMP TO CHECK USER2 PINS
        ADD SI,10D                          ;MOVE SI TO NEXT ROW 
        DEC CL
        JNZ CHECK_USER_1_ALL_PINS_1 
        JMP CONTINUE_USER1 

        INCREASE_COUNTER_USER1:
        INC DL
        ADD SI,10
        DEC CL
        JNZ CHECK_USER_1_ALL_PINS_1
        
        CONTINUE_USER1:
        SUB SI,50                           ;MOVE SI TO COL 9 ROW 0 AGAIN
        MOV CL,5                            ;INITIALIZE COUNTER AGAIN
        CMP DL,5
        JZ  CHECK_USER_2_ALL_PINS_1
        JNZ CHECK_USER_2_ALL_PINS_WINNER
        
        CHECK_USER_2_ALL_PINS_1:

        MOV AH,[DI]                         ;MOVE USER 2 PINS TO AH         
        CMP AH,0                            ;COMPARE WITH 0
        JZ  INCREASE_COUNTER_USER2                    ;IF USER1 HAVE 1 IN HIS PINS AND USER2 HAVE 0 --> JMP USER1 WINS
        ADD DI,10                           ;MOVE DI TO NEXT ROW
        DEC CH
        JNZ CHECK_USER_2_ALL_PINS_1
        SUB DI,50                           ;MOVE DI TO COL 9 ROW 5 AGAIN
        MOV CH,5                            ;INITIALIZE COUNTER AGAIN
        JMP CONTINUE_USER2

        INCREASE_COUNTER_USER2:
        INC DH
        ADD DI,10
        DEC CH
        JNZ CHECK_USER_2_ALL_PINS_1

        CONTINUE_USER2:
        SUB DI,50                           ;MOVE SI TO COL 9 ROW 0 AGAIN
        MOV CH,5                            ;INITIALIZE COUNTER AGAIN
        CMP DH,5
        JZ  USER_1_WINS
        JNZ CHECK_USER_2_ALL_PINS_WINNER

    CHECK_USER_2_ALL_PINS_WINNER:  
        MOV AX,0
        MOV BX,0
        MOV CX,0
        MOV DX,0

        LEA SI,MAP_INDEX
        ADD SI,9                               ;MOVE SI TO COL 9 ROW 0 
        
        LEA DI,MAP_INDEX                       ;MOVE DI TO COL 9 ROW 5
        ADD DI,59D
        
        MOV CL,5
        MOV CH,5                               ;LOOPS COUNTERS 

        CHECK_USER_2_ALL_PINS_2:
    
        MOV AL,[DI]                         ;MOVE USER 1 PINS TO AL       
        CMP AL,1                            ;COMPARE WITH 1 
        JZ  INCREASE_COUNTER_USER1_1         ;IF USER1 HAVE 1 IN HIS PINS JMP TO CHECK USER2 PINS
        ADD DI,10D                          ;MOVE SI TO NEXT ROW 
        DEC CL
        JNZ CHECK_USER_2_ALL_PINS_2 
        JMP CONTINUE_USER2_2 

        INCREASE_COUNTER_USER1_1:
        INC DL
        ADD DI,10
        DEC CL
        JNZ CHECK_USER_2_ALL_PINS_2
        
        CONTINUE_USER2_2:
        CMP DL,5
        JZ  CHECK_USER_1_ALL_PINS_2
        JNZ NO_WINNER
        
        CHECK_USER_1_ALL_PINS_2:

        MOV AH,[SI]                         ;MOVE USER 2 PINS TO AH         
        CMP AH,0                            ;COMPARE WITH 0
        JZ  INCREASE_COUNTER_USER1_2                    ;IF USER1 HAVE 1 IN HIS PINS AND USER2 HAVE 0 --> JMP USER1 WINS
        ADD SI,10                           ;MOVE DI TO NEXT ROW
        DEC CH
        JNZ CHECK_USER_1_ALL_PINS_2
        SUB DI,50                           ;MOVE DI TO COL 9 ROW 5 AGAIN
        MOV CH,5                            ;INITIALIZE COUNTER AGAIN
        JMP CONTINUE_USER1_2

        INCREASE_COUNTER_USER1_2:
        INC DH
        ADD SI,10
        DEC CH
        JNZ CHECK_USER_1_ALL_PINS_2

        CONTINUE_USER1_2:
        CMP DH,5
        JZ  USER_2_WINS
        JNZ NO_WINNER
     
USER_1_WINS:
    
    MOV WINNER,1
    JMP NO_WINNER

USER_2_WINS: 
    
    MOV WINNER,2
    JMP NO_WINNER   

NO_WINNER:
    
    RET

CHECK_WINNER                       ENDP