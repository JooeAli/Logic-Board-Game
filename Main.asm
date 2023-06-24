
.MODEL SMALL
.STACK 64

.286
.386

.DATA

;\\\\\\\\\\\\\\\\\\\\\\\\\ LOGIC VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ 
MAP_INDEX LABEL BYTE
ROW_0          DB ?,9 DUP(10H)             ;Row_0 10 nodes

ROW_1          DB ?,9 DUP(10H)             ;Row_1 10 nodes

ROW_2          DB ?,9 DUP(10H)             ;Row_2 10 nodes

ROW_3          DB ?,9 DUP(10H)             ;Row_3 10 nodes

ROW_4          DB ?,9 DUP(10H)             ;Row_4 10 nodes

ROW_5          DB ?,9 DUP(10H)             ;Row_5 10 nodes

ROW_6          DB ?,9 DUP(10H)             ;Row_6 10 nodes

ROW_7          DB ?,9 DUP(10H)             ;Row_7 10 nodes

ROW_8          DB ?,9 DUP(10H)             ;Row_8 10 nodes

ROW_9          DB ?,9 DUP(10H)             ;Row_9 10 nodes        
                     

INPUT_COMMAND LABEL BYTE                     ;syntax of input from users

CommandSize       DB 8                       ;command takes 7 bytes (ex:A223344)
ActualSize        DB ?
GATE              DB ?                       ;gate name: A,O,D,R,X,N 


;INPUT 1
INPUT1_COL        DB ?                 
INPUT1_ROW        DB ?
 
;INPUT 2
INPUT2_COL        DB ?
INPUT2_ROW        DB ?

;OUTPUT 1
INPUT3_COL        DB ?
INPUT3_ROW        DB ?   


INPUT1_INDEX      DB 00h
INPUT2_INDEX      DB 00h
OUTPUT_INDEX      DB 00h


INPUT1_VALUE      DB 5                     ;VALUE OF PIN 1 (IF = 5 THEREFOR NO VALUE IS ADDED)
INPUT2_VALUE      DB 5                     ;VALUE OF PIN 1 (IF = 5 THEREFOR NO VALUE IS ADDED)

ERROR_FLAG        DB 00h                   ;IF = 1 THEREFOR ERROR HAS OCCURED


COMMAND_MAP LABEL BYTE
ROW_COMMAND_0                  DB 70 DUP(00h)
ROW_COMMAND_1                  DB 70 DUP(00h)
ROW_COMMAND_2                  DB 70 DUP(00h)
ROW_COMMAND_3                  DB 70 DUP(00h)
ROW_COMMAND_4                  DB 70 DUP(00h)
ROW_COMMAND_5                  DB 70 DUP(00h)
ROW_COMMAND_6                  DB 70 DUP(00h)
ROW_COMMAND_7                  DB 70 DUP(00h)
ROW_COMMAND_8                  DB 70 DUP(00h)
ROW_COMMAND_9                  DB 70 DUP(00h) 

; VARIABLES FOR REFRESH BOARD 

COMMAND_CHARS_COUNT DB ?        ;7
COMMAND_ROWS_COUNT  DB ?        ;10
COMMAND_COLS_COUNT  DB ?        ;10  
SAVE_DI_IN_LOGIC    DW ?          


GAME_LEVEL          DB ? 
WINNER              DB 00h
MENU_FLAG           DB 0


;VARIABLES FOR RNG
rngnode             db 200
two_rng             db 2

Xposition db ?
;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ END LOGIC VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\



;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ GRAPHING VARIABLES AND ARRAYS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
;Board Variables
vlines_count         db ?
SPACES_BETWEEN_COLS  db ?
count_input          db ?
count_output         db ?
count_node_color     db ?
count_node_color_col db ?
currout              dw ?
currin               dw ?

;draw nodes variables
cursornodes dw ?
countnodes  db ?
countcols   db ?

;Vars for Numbers Locations
draw_location0 dw ?,?
draw_location1 dw ?,?
draw_location2 dw ?,?
draw_location3 dw ?,?
draw_location4 dw ?,?
draw_location5 dw ?,?
draw_location6 dw ?,?
draw_location7 dw ?,?
draw_location8 dw ?,?
draw_location9 dw ?,?
draw_location_info dw ?,?

draw_size      dw  5d,3d             ; height , width 
draw_size_info dw 6d,129d       ; height , width  

;Arrays for Numbers
draw_array0 db  00h , 00h , 00h 
            db  00h , 0fh , 00h
            db  00h , 0fh , 00h 
            db  00h , 0fh , 00h 
            db  00h , 00h , 00h

draw_array1 db  0fh , 00h , 0fh 
            db  0fh , 00h , 0fh 
            db  0fh , 00h , 0fh 
            db  0fh , 00h , 0fh 
            db  0fh , 00h , 0fh 

draw_array2 db 00h , 00h , 00h 
            db 0fh , 0fh , 00h
            db 00h , 00h , 00h 
            db 00h , 0fh , 0fh
            db 00h , 00h , 00h

draw_array3 db  00h , 00h , 00h
            db  0fh , 0fh , 00h 
            db  00h , 00h , 00h 
            db  0fh , 0fh , 00h 
            db  00h , 00h , 00h


draw_array4  db 00h , 0fh , 00h
             db 00h , 0fh , 00h
             db 00h , 00h , 00h 
             db 0fh , 0fh , 00h
             db 0fh , 0fh , 00h

draw_array5  db 00h , 00h , 00h 
             db 00h , 0fh , 0fh
             db 00h , 00h , 00h 
             db 0fh , 0fh , 00h 
             db 00h , 00h , 00h

draw_array6 db 00h , 00h , 00h 
            db 00h , 0fh , 0fh
            db 00h , 00h , 00h 
            db 00h , 0fh , 00h 
            db 00h , 00h , 00h

draw_array7 db 00h , 00h , 00h 
            db 0fh , 0fh , 00h 
            db 0fh , 0fh , 00h
            db 0fh , 0fh , 00h
            db 0fh , 0fh , 00h

draw_array8 db 00h , 00h , 00h 
            db 00h , 0fh , 00h 
            db 00h , 00h , 00h 
            db 00h , 0fh , 00h 
            db 00h , 00h , 00h

draw_array9 db 00h , 00h , 00h 
            db 00h , 0fh , 00h 
            db 00h , 00h , 00h 
            db 0fh , 0fh , 00h 
            db 00h , 00h , 00h

draw_array_info db 0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0EH,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh
                db 0Eh,0Eh,00h,0Eh,0Eh,0Eh,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,00h,0Eh,0Eh,0EH,0Eh,00h,00h,0Eh,0Eh,0Eh,0Eh,0Eh,00h,00h,0Eh,0Eh,00h,00h,0Eh,0Eh,0Eh,00h,00h,0Eh,0Eh,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,00h,0Eh,0Eh,0Eh,00h,00h,0Eh,0Eh,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,00h,0Eh,0Eh,00h,00h,0Eh,0Eh,0Eh,00h,0Eh,00h,0Eh,0Eh,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,00h,0Eh,0Eh,00h,00h,0Eh,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,00h,0Eh,0Eh,00h,00h,0Eh,0Eh
                db 0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,0EH,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,00h,0Eh
                db 0Eh,00h,00h,00h,0Eh,0Eh,0Eh,00h,00h,00h,0Eh,00h,0Eh,00h,00h,0Eh,00h,0Eh,00h,0Eh,0EH,00h,0Eh,0Eh,00h,0Eh,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,00h,0Eh,0Eh,0Eh,00h,0Eh,00h,0Eh,0Eh,0Eh,00h,0Eh,00h,00h,0Eh,00h,00h,00h,0Eh,00h,0Eh,00h,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,00h,0Eh,0Eh,0Eh,0Eh,00h,0Eh,00h,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,00h,0Eh,0Eh,0Eh,0EH,00h,0Eh,0Eh,0Eh,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,00h,0Eh,0Eh,0Eh,00h,0Eh,00h,00h,0Eh,0Eh,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,00h,0Eh,0Eh
                db 0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,00h,0Eh,0Eh,0EH,0Eh,00h,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,00h,0Eh,0Eh,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,00h,0Eh,0Eh,00h,0Eh,0Eh,00h,00h,0Eh,0Eh,00h,0Eh,00h,0Eh
                db 0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0EH,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh,0Eh
                ;     ;      A    ;   ;  : ;  ;     A     ;   ;      N        ;   ;       D   ;        ;       O       ;   :    ;  ;       O      ;   ;     R     ;       ;     D     ;   ; :  ;  ;        N      ;   ;     A     ;   ;       N       ;   ;      D    ;       ;     R     ;     :     ;       N       ;   ;       O       ;   ;     R     ;       ;       X   ;   ; : ;   ;    X      ;   ;     O         ;   ;     R     ;       ;        N      ;   ; : ;   ;     X     ;   ;       N       ;   ;       O       ;   ;     R     ;
;--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ END GRAPHING VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\USERSCREEN VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


Buffersize  db 16d                                     ;size rserved for username 

Actualsize2 db ?                                       ;actual size of username 

USERNAME    db 16d DUP(?)                              ;RESERVE 15 PLACES FOR USERNAME  



MESUSERNAME     db 'Please enter your name:',10,13,'$'                                                       ;MESSAGE TO ENTER USERNAME   

MESUSERNAME2    db 'Please enter your name without special char or number in the first letter:',10,13,'$'    ;MESSAGE TO ENTER USERNAME AGAIN  


MESMAIN         db 'Press Enter key to continue',10,13,'$'                                                   ;MESSAGE TO CONTINUE TO MAIN

;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ END USERSCREEN VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ MAIN MENU VARIABLES\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

MESCHATTING         db         'To start chatting press F1',10,13,'$'         ;MESSAGE TO START CHATTING  

MESGAME             db         'To start the game press F2',10,13,'$'         ;MESSAGE TO START GAME 
        
MESEND              db         'To end the program press ESC',10,13,'$'       ;MESSAGE TO END PROGRAM

MESS_END_PROGRAM    db         'Program Ended','$'

;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ END MAIN MENU VARIABLES\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ Notifications Messages \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

LINE                db      80 dup('-'),'$' 

SEND_CHAT           db      '  - You sent a chat invitation to opponent',10,13,'$'                   ;MESSAGE TO SEND CHAT INVITIATION 
RECIEVE_CHAT        db      '  - You recieved chat invitiation Press F1 to accept',10,13,'$'         ;MESSAGE TO RECIEVE CHAT INVITATION

SEND_GAME           db      '  - You sent a game invitation to opponent',10,13,'$'                   ;MESSAGE TO SEND GAME INVITIATION 
RECIEVE_GAME        db      '  - You recieved game invitiation Press F2 to accept',10,13,'$'         ;MESSAGE TO RECIEVE GAME INVITATION 

;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\END Notifications Messages \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ CHOOSE LEVEL VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
MESS_CHOOSE_LEVEL1  db      '# Press 1 to choose level 1','$'
MESS_CHOOSE_LEVEL2  db      '# Press 2 to choose level 2 ','$'

MESS_LEVEL_1        db      'Level 1:- All Gates are allowed except NOT gate','$'
MESS_LEVEL_1_win_1  db      '        - To win put logic one to any of your terminal nodes ','$'
MESS_LEVEL_1_win_2  db      '        - Put logic zero to any of the opponent nodes.','$'

MESS_LEVEL_2        db      'Level 2:- All Gates are allowed ','$'
MESS_LEVEL_2_win_1  db      '        - To win put logic one to all of your terminal nodes','$'
MESS_LEVEL_2_win_2  db      '        - Put logic zero to all of the opponent nodes.','$'
;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ END CHOOSE LEVEL VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ SCORE SCREEN VARIABLES   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
COUNTER_USER1_1     db  ?
COUNTER_USER1_0     db  ?

COUNTER_USER2_1     db  ?
COUNTER_USER2_0     db  ?

MESS_USER_1_SCORE   db 'USER 1 Score','$'
MESS_USER_No1       db 'Number of logic ones : ','$'
MESS_USER_No0       db 'Number of logic Zeros: ','$'

MESS_USER_2_SCORE   db 'USER 2 Score','$'

;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ END SCORE SCREEN VARIABLES   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\



;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ WINNER SCREEN VARIABLES   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

MESS_USER_1_WINS   db       3,' USER 1 WINS ',3,'$'                   ;MESSAGE USER 1 WINS 
MESS_USER_2_WINS   db       3,' USER 2 WINS ',3,'$'                   ;MESSAGE USER 2 WINS 
XPOSITION_WINNER   db       ?                                         ;X POSITION OF WINNER MESSAGE

;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ END WINNER SCREEN VRAIBLES    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ GATES VARIABLES\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
start_wire  dw 00h,00h                   ;x,y ;start of the wire
finish_wire dw 00h,00h                  ;x,y ;finish of the wire

;Draw Gates Variables
draw_location  dw  20d,20d
draw_size_yara dw  15d,19d                  ; height , width
input_array    db   ?,?,?,?,?,?             ; column input1, row input1
                                            ; column input2, row input2
                                            ; column output, row output
input_array_pixels       dW 6 dup(?)        ;Change input for location on map 
calculating_array        db ?,?             ;used inside the function
calculating_array_pixels dw ?,?             ;used inside the function
just_wire_counter db 0

;Numbers for multiplication
two          db 2
fifteen      db 17
twenty_eight db 34

;Draw wires variables
wire_input_up       dw ?,?
wire_input_down     dw ?,?
color_wire          db 09h
WIRE_DRAWN_FLAG     db 00h
temp_array_finish dw ?


;28*col + 44 -> x location
;15*row + 19 -> y location if col odd
;15*row + 26 -> y location if col even                     
;####################################  

draw_array      db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,-1   ,-1    , -1, -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22  
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , -1, -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22  
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22   
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , 00h  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,00h  ,00h  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,00h  ,00h  ,00h  ,00h  ,00h  ,00h   ;22
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,00h  ,00h  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  00h , 00h , 00h , 00h  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22 
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , -1, -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22          
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,-1   ,-1    , -1, -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22



draw_array_nand db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,-1   ,-1    , -1, -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22  
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , -1, -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22  
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22   
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , 00h  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,00h  ,00h  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,00h  ,00h  ,00h  ,00h  ,00h  ,00h   ;22
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,00h  ,00h  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  00h , 00h , 00h , 00h  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22 
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , -1, -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22          
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,-1   ,-1    , -1, -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22


draw_array_and  db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,-1   ,-1    , -1, -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22  
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , -1, -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22  
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22   
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , 00h  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,-1  ,-1  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,00h  ,00h  ,00h  ,00h  ,00h  ,00h   ;22
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,-1  ,-1  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  00h , 00h , 00h , 00h  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , 00h, 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22 
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,00h    , -1, -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22          
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,-1   ,-1    , -1, -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22

draw_array_or   db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,  -1  , -1  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22  
                db  -1 , -1 , -1 , -1  ,  -1  , 00h   ,00h   ,  00h  , 00h  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22  
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22   
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , 00h  ,  00h  , 00h   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,-1  ,-1  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,00h  ,00h  ,00h  ,00h  ,00h   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,-1  ,-1  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  00h , 00h , 00h , 00h  ,  00h  , 00h   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22 
                db  -1 , -1 , -1 , -1  ,  -1  , 00h   ,00h   ,  00h  , 00h  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22          
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,  -1  , -1  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22



draw_array_nor  db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,  -1  , -1  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22  
                db  -1 , -1 , -1 , -1  ,  -1  , 00h   ,00h   ,  00h  , 00h  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22  
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22   
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , 00h  ,  00h  , 00h   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,00h  ,00h  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,00h  ,00h  ,00h  ,00h  ,00h   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,00h  ,00h  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  00h , 00h , 00h , 00h  ,  00h  , 00h   ,00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  00h  , 00h  , 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22 
                db  -1 , -1 , -1 , -1  ,  -1  , 00h   ,00h   ,  00h  , 00h  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22          
                db  -1 , -1 , -1 , -1  ,  00h  , 00h   ,00h   ,  -1  , -1  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22


draw_array_xnor db  -1 , -1 , -1 , -1  ,  00h  , -1   ,00h   ,  00h  , -1  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22  
                db  -1 , -1 , -1 , -1  ,  -1  , 00h   ,-1   ,  00h  , 00h  , 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22  
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22   
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , 00h  ,  00h  , 00h   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,00h  ,00h  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,00h  ,00h  ,00h  ,00h  ,00h   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,00h  ,00h  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  00h , 00h , 00h , 00h  ,  00h  , 00h   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22 
                db  -1 , -1 , -1 , -1  ,  -1  , 00h   ,-1   ,  00h  , 00h  , 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22          
                db  -1 , -1 , -1 , -1  ,  00h  , -1   ,00h   ,  00h  , -1  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22
                
               
draw_array_xor  db  -1 , -1 , -1 , -1  ,  00h  , -1   ,00h   ,  00h  , -1  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22  
                db  -1 , -1 , -1 , -1  ,  -1  , 00h   ,-1   ,  00h  , 00h  , 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22  
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22   
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , 00h  ,  00h  , 00h   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,-1  ,-1  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,00h  ,00h  ,00h  ,00h  ,00h   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,-1  ,-1  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  00h , 00h , 00h , 00h  ,  00h  , 00h   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , 00h  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1   ,00h   ,  -1  , 00h  , 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22 
                db  -1 , -1 , -1 , -1  ,  -1  , 00h   ,-1   ,  00h  , 00h  , 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22          
                db  -1 , -1 , -1 , -1  ,  00h  , -1   ,00h   ,  00h  , -1  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22
                

draw_array_not  db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  -1  , -1  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22  
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  00h  , -1  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22  
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  00h  , 00h  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22   
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  00h  , 00h  , 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  00h  , 00h  , 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,-1  ,00h  ,00h  ,-1  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,00h  ,00h  ,00h  ,00h  ,00h  ,00h   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , 00h  ,-1  ,00h  ,00h  ,-1  ,-1  ,-1   ;22
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  00h  , 00h  , 00h ,  00h  , 00h  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;y22
                db  00h , 00h , 00h , 00h  ,  00h  , 00h  ,  00h   ,  00h  , 00h  , 00h ,  00h  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;n22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  00h  , 00h  , 00h ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;v22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  00h  , 00h  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;j22 
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  00h  , -1  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;l22          
                db  -1 , -1 , -1 , -1  ,  -1  , -1  ,  00h   ,  -1  , -1  , -1 ,  -1  , -1  , -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ;p22




;INCLUDES
INCLUDE LOGICP.INC
INCLUDE DRAW.INC
INCLUDE TRANS.INC
INCLUDE BOARD.INC
INCLUDE NUMS.INC
INCLUDE GATESLP.INC
INCLUDE MACROS.INC

.CODE

MAIN PROC FAR  
     MOV AX,@DATA
     MOV DS,AX

      ENTER_USERSCREEN2:
      TEXTMODE  
            clearscreenM                                    ;clear screen before starting       

            DisplayString MESUSERNAME                       ;Message for entering username 

                  jmp Continue2
                  
                  CHECKCHAR:
                  ClearscreenM
                  MOVECURSOR 0,0                            ;move cursor to appropriate spacing
                  DisplayString MESUSERNAME2                ;Message for entering username again withou special chars

                  Continue2: 
            
            ReadString buffersize                           ;Takes username from user max 15 characters

            
            ;CHECK IF FIRST LETTER IS A NUM/SPECIAL CHAR
            MOV BX, OFFSET USERNAME
            MOV AH,[BX]
            CMP AH,40H
            JLE CHECKCHAR 
            CMP AH,7BH                       ;REJECT SPECIAL CHAR LESS THAN OR EQUAL 40H AND GREATER THAN OR EQUAL 7B
            JGE CHECKCHAR

            CMP AH,5BH
            JZ  CHECKCHAR                    ;REJECT ASCII SPECIAL CHARACTERS BETWEEN 5BH---60AH
            CMP AH,5CH
            JZ  CHECKCHAR    
            CMP AH,5DH 
            JZ  CHECKCHAR    
            CMP AH,5EH
            JZ  CHECKCHAR    
            CMP AH,5FH
            JZ  CHECKCHAR    
            CMP AH,60H

            MOVECURSOR 0,4                             ;move cursor for appropriate spacing
            DisplayString  MESMAIN                     ;Message to continue to main screen   
            MOVECURSOR 0,8                             ;move cursor for appropriate spacing
          
            ;wait for enter to be pressed 
            cont:
            mov ah,0  
            int 16h
            cmp al,0Dh  
            je GO_TO_MAIN 
            jmp cont
 
            GO_TO_MAIN:
            jmp ENTER_MAIN_SCREEN

    ENTER_MAIN_SCREEN:
                CALL INITIALIZE_MAP_INDEX
                CALL INITIALIZE_COMMAND_MAP
                CALL RNG
    
                TEXTMODE
                clearscreenM
                
                MOVECURSOR 25,09           
                DisplayString MESCHATTING                       ;MESSAGE TO START CHATTING 

                MOVECURSOR 25,13
                DisplayString MESGAME                           ;MESSAGE TO START GAME

                MOVECURSOR 25,17
                DisplayString MESEND                            ;MESSAGE TO END PROGRAM

                MOVECURSOR 0,22
                DisplayString LINE

                ;END PROGRAM IF ESC PRESSED 
                cont2:
                mov ah,0 
                int 16h
                
                cmp al,27d                              ;PRESS ESC 
                je END_PROGRAM
                
                cmp aH,3CH                              ;PRESS F2 to send game invitation
                je WAIT_OPPONENT_GAME

                CMP AH,3BH
                je WAIT_OPPONENT_CHAT                   ;PRESS F1 to send chat invtitaion

                jmp cont2

;------------------------------- GAME INVITATION NOTFICATION
                WAIT_OPPONENT_GAME:
                
                MOVECURSOR 0,23
                DisplayString SEND_GAME
                
                ;WAIT FOR F2 TO BE PRESSED FROM OPPONENT
                WAIT_FOR_F2:
                mov ah,0 
                int 16h

                CMP AH,3BH                              ;if user pressed F1 to send chat
                JE WAIT_OPPONENT_CHAT 

                CMP AH,3CH
                JE startgame
                JNE WAIT_FOR_F2

;------------------------------ CHAT INVITATION NOTIFICATION
                WAIT_OPPONENT_CHAT:

                MOVECURSOR 0,23
                DisplayString SEND_CHAT

                ;WAIT FOR F1 TO BE PRESSED FROM OPPONENT
                WAIT_FOR_F1:
                mov ah,0 
                int 16h

                CMP AH,3CH                              ;if user pressed f2 to send game
                JE WAIT_OPPONENT_GAME

                CMP AH,3BH
                ;JE startchat
                JNE WAIT_FOR_F1





;------------------------------- GAME
                startgame:
                ClearscreenM
                MOVECURSOR 0,0
                DisplayString MESS_CHOOSE_LEVEL1

          

                MOVECURSOR 0,3
                DisplayString MESS_LEVEL_1
                
                MOVECURSOR 0,4
                DisplayString MESS_LEVEL_1_win_1

                MOVECURSOR 0,5
                DisplayString MESS_LEVEL_1_win_2


                MOVECURSOR 0,13
                DisplayString MESS_CHOOSE_LEVEL2

                MOVECURSOR 0,16
                DisplayString MESS_LEVEL_2

                MOVECURSOR 0,17 
                DisplayString MESS_LEVEL_2_win_1

                MOVECURSOR 0,18
                DisplayString MESS_LEVEL_2_win_2

                MOV GAME_LEVEL,0d
                CALL TAKE_LEVEL

                CALL Entergraphics
                CALL DRAW_BOARD

                
    
    START_AGAIN: 

        MOV ERROR_FLAG,00h
        MOV MENU_FLAG,0
        

        CALL TAKE_COMMAND

        CMP MENU_FLAG,1
        JZ  ENTER_MAIN_SCREEN
        
        CMP ERROR_FLAG,1
        JZ  START_AGAIN
        
        CALL ASCII_TO_DECIMAL
        
        CMP ERROR_FLAG,1
        JZ  START_AGAIN

        CALL CHECK_COMMAND
        
        CMP ERROR_FLAG,1
        JZ  START_AGAIN 

        CALL INITIALIZE_MAP_INDEX
        
        CALL REFRESH 
        
        CALL CHECK_WINNER
        
        ;CMP  WINNER,00h
        ;JNZ  END_ALL_GAME 
        

        CMP WINNER,1
        JZ  DISPLAY_WINNER
        CMP WINNER,2
        JZ  DISPLAY_WINNER

        JMP  START_AGAIN

        DISPLAY_WINNER:
        ;TEXTMODE
        ;clearscreenM
        call fillscreen
        CMP WINNER,1
        JZ  DISPLAY_WINNER_1

        CMP WINNER,2
        JZ DISPLAY_WINNER_2


        DISPLAY_WINNER_1:
            LEA SI,MESS_USER_1_WINS                         ;DISPLAY USER1 WINS
            MOV XPOSITION_WINNER,13                         ;COUNTER FOR X POSITION
            LOOP_WINNER1:
            MOVECURSOR XPOSITION_WINNER,12
            ;DisplayString MESS_USER_1_WINS
                        mov ah,9
                        MOV AL,[SI]
                        mov bh,3
                        mov cx,1
                        mov bl,00bh
                        int 10h                             ;INT TO PRINT CHAR
                        inc XPOSITION_WINNER
                        INC SI
                        MOV DL,[SI]
                        CMP DL,'$'
                        JNZ LOOP_WINNER1

                        
        JMP END_ALL_GAME

        DISPLAY_WINNER_2:                                   ;DISPLAY USER2 WINS

            LEA SI,MESS_USER_2_WINS
            MOV XPOSITION_WINNER,13
            LOOP_WINNER2:
            MOVECURSOR XPOSITION_WINNER,12
            ;DisplayString MESS_USER_1_WINS
                        mov ah,9
                        MOV AL,[SI]
                        mov bh,3
                        mov cx,1
                        mov bl,00bh
                        int 10h                             ;INT TO PRINT CHAR
                        inc XPOSITION_WINNER
                        INC SI
                        MOV DL,[SI]
                        CMP DL,'$'
                        JNZ LOOP_WINNER2  
        
        JMP END_ALL_GAME


    END_PROGRAM:
    clearscreenM
    MOVECURSOR 33,12
    DisplayString MESS_END_PROGRAM 

    END_ALL_GAME: 
    
    HLT   

    

MAIN ENDP
END MAIN