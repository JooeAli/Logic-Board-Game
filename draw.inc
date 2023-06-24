.code

INITIALIZE_DRAW_ARRAY        PROC

    PUSHA
    PUSHF

    LEA DI,GATE
        
        CMP BYTE PTR [DI],65D              ;COMPARE GATE WITH ASCII VALUE OF A
        JZ  MOVE_AND_ARRAY
    
        CMP BYTE PTR [DI],79D              ;COMPARE GATE WITH ASCII VALUE OF O
        JZ  MOVE_OR_ARRAY
    
        CMP BYTE PTR [DI],68D              ;COMPARE GATE WITH ASCII VALUE OF D
        JZ  MOVE_NAND_ARRAY   
    
        CMP BYTE PTR [DI],82D              ;COMPARE GATE WITH ASCII VALUE OF R
        JZ  MOVE_NOR_ARRAY 
    
        CMP BYTE PTR [DI],88D              ;COMPARE GATE WITH ASCII VALUE OF X
        JZ  MOVE_XOR_ARRAY 
    
        CMP BYTE PTR [DI],78D              ;COMPARE GATE WITH ASCII VALUE OF N
        JZ  MOVE_XNOR_ARRAY    
        
        CMP BYTE PTR [DI],73D              ;COMPARE GATE WITH ASCII VALUE OF I
        JZ  MOVE_NOT_ARRAY

        ;CMP BYTE PTR [DI],87D              ;COMPARE GATE WITH ASCII VALUE OF W
        ;JZ  MOVE_WIRE_ARRAY

        JMP END_SWITCH_GATE   

    MOVE_AND_ARRAY:
        LEA SI,draw_array
        LEA DI,draw_array_and
        MOV CX,285
        AND_SWITCH:
        MOV AL,[DI]
        MOV BYTE PTR [SI],AL
        INC SI
        INC DI
        DEC CX
        JNZ AND_SWITCH
        JMP END_SWITCH_GATE

    MOVE_OR_ARRAY:
        LEA SI,draw_array
        LEA DI,draw_array_or
        MOV CX,285
        OR_SWITCH:
        MOV AL,[DI]
        MOV BYTE PTR [SI],AL
        INC SI
        INC DI
        DEC CX
        JNZ OR_SWITCH
        JMP END_SWITCH_GATE


    MOVE_NAND_ARRAY:

        LEA SI,draw_array
        LEA DI,draw_array_nand
        MOV CX,285
        NAND_SWITCH:
        MOV AL,[DI]
        MOV BYTE PTR [SI],AL
        INC SI
        INC DI
        DEC CX
        JNZ NAND_SWITCH
        JMP END_SWITCH_GATE

    MOVE_NOR_ARRAY:

        LEA SI,draw_array
        LEA DI,draw_array_nor
        MOV CX,285
        NOR_SWITCH:
        MOV AL,[DI]
        MOV BYTE PTR [SI],AL
        INC SI
        INC DI
        DEC CX
        JNZ NOR_SWITCH
        JMP END_SWITCH_GATE

    MOVE_XOR_ARRAY:

        LEA SI,draw_array
        LEA DI,draw_array_xor
        MOV CX,285
        XOR_SWITCH:
        MOV AL,[DI]
        MOV BYTE PTR [SI],AL
        INC SI
        INC DI
        DEC CX
        JNZ XOR_SWITCH
        JMP END_SWITCH_GATE

    MOVE_XNOR_ARRAY:

        LEA SI,draw_array
        LEA DI,draw_array_xnor
        MOV CX,285
        XNOR_SWITCH:
        MOV AL,[DI]
        MOV BYTE PTR [SI],AL
        INC SI
        INC DI
        DEC CX
        JNZ XNOR_SWITCH
        JMP END_SWITCH_GATE

    MOVE_NOT_ARRAY:   

        LEA SI,draw_array
        LEA DI,draw_array_not
        MOV CX,285
        NOT_SWITCH:
        MOV AL,[DI]
        MOV BYTE PTR [SI],AL
        INC SI
        INC DI
        DEC CX
        JNZ NOT_SWITCH
        JMP END_SWITCH_GATE 

    ;MOVE_WIRE_ARRAY:

        ;CALL drawwire_and_gate
        ;MOV WIRE_DRAWN_FLAG,1
        ;JMP END_SWITCH_GATE                         

    
END_SWITCH_GATE:

    POPA
    POPF
    RET

INITIALIZE_DRAW_ARRAY        ENDP

 draw_just_wire proc

    pusha
    pushf
    cld
    xor si,si ;Safr el register
      
    mov bx,start_wire[2] ;put y of start
    mov ax,finish_wire[2] ;put y of end
    
    cmp bx,ax ;compare between y of start &end , if start > end , go up else go down
    ja go_up_2 ;jum
    jmp go_down_2
    
    go_up_2:          
    mov bx,start_wire[0]
    mov ax,finish_wire[0]
    mov temp_array_finish,ax
    cmp bx,ax
    ja go_up_left_2
    jmp go_up_right_2
    
    go_down_2:
    mov bx,start_wire[0]
    mov ax,finish_wire[0]
    mov temp_array_finish,ax
    cmp bx,ax
    ja go_down_left_2
    jmp go_down_right_2
    
    
    go_up_left_2:
    add temp_array_finish,5
    mov cx,start_wire[0]
    mov dx,start_wire[2]
    drawing_UL_2:
    mov al,color_wire
    mov ah,0ch
    int 10h
    inc si
    mov ax,si
    div two[0]
    cmp ah,1
    jz dec_cx_UL_2
    jmp dec_dx_UL_2
    
    dec_cx_UL_2:
    cmp cx,temp_array_finish
    jb no_dec_cx_UL_2
    dec cx
    jmp drawing_UL_2
    no_dec_cx_UL_2:
    
    dec_dx_UL_2:
    cmp dx,finish_wire[2]
    jz no_dec_dx_UL_2
    dec dx
    jmp drawing_UL_2
    no_dec_dx_UL_2:
    cmp cx,temp_array_finish
    ja dec_cx_UL_2
    
    dec cx
    cmp cx,finish_wire[0]
    jnz drawing_UL_2
    
    
    jmp done_direction_2 
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;    
    
    go_up_right_2:
    sub temp_array_finish,5
    mov cx,start_wire[0]
    mov dx,start_wire[2]
    drawing_UR_2:
    mov al,color_wire
    mov ah,0ch
    int 10h
    inc si
    mov ax,si
    div two[0]
    cmp ah,1
    jz inc_cx_UR_2
    jmp dec_dx_UR_2
    
    inc_cx_UR_2:
    cmp cx,temp_array_finish
    ja no_inc_cx_UR_2
    inc cx
    jmp drawing_UR_2
    no_inc_cx_UR_2:
    
    dec_dx_UR_2:
    cmp dx,finish_wire[2]
    jz no_dec_dx_UR_2
    dec dx
    jmp drawing_UR_2
    no_dec_dx_UR_2:
    cmp cx,temp_array_finish
    jb inc_cx_UR_2
    
    inc cx
    cmp cx,finish_wire[0]
    jnz drawing_UR_2
    
    jmp done_direction_2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    go_down_left_2:
    add temp_array_finish,5
    mov cx,start_wire[0]
    mov dx,start_wire[2]
    drawing_DL_2:
    mov al,color_wire
    mov ah,0ch
    int 10h
    inc si
    mov ax,si
    div two[0]
    cmp ah,1
    jz dec_cx_DL_2
    jmp inc_dx_DL_2
    
    dec_cx_DL_2:
    cmp cx,temp_array_finish
    jb no_dec_cx_DL_2
    dec cx
    jmp drawing_DL_2
    no_dec_cx_DL_2:
    
    inc_dx_DL_2:
    cmp dx,finish_wire[2]
    jz no_inc_dx_DL_2
    inc dx
    jmp drawing_DL_2
    no_inc_dx_DL_2: 
    cmp cx,temp_array_finish
    ja dec_cx_DL_2
    
    dec cx
    cmp cx,finish_wire[0]
    jnz drawing_DL_2
    
    jmp done_direction_2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    go_down_right_2:
    sub temp_array_finish,5
    mov cx,start_wire[0]
    mov dx,start_wire[2]
    drawing_DR_2:
    mov al,color_wire
    mov ah,0ch
    int 10h
    inc si
    mov ax,si
    div two[0]
    cmp ah,1
    jz inc_cx_DR_2
    jmp inc_dx_DR_2
    
    inc_cx_DR_2:
    cmp cx,temp_array_finish
    ja no_inc_cx_DR_2
    inc cx
    jmp drawing_DR_2
    no_inc_cx_DR_2:
    
    inc_dx_DR_2:
    cmp dx,finish_wire[2]
    jz no_inc_dx_DR_2
    inc dx
    jmp drawing_DR_2
    no_inc_dx_DR_2:
    cmp cx,temp_array_finish
    jb inc_cx_DR_2
    
    inc cx
    cmp cx,finish_wire[0]
    jnz drawing_DR_2
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	done_direction_2:
    popf
    popa
    ret 

 draw_just_wire endp

drawWire proc
    pusha
    pushf
    cld
    xor si,si ;safr register SI
      
    mov bx,start_wire[2] ;put y of start
    mov cx,finish_wire[2] ;put y of end
    
    cmp bx,cx ;compare between y of start & end , if start > end , go up else go down
    ja go_up ;jump above
    jmp go_down ;jump other
    
    go_up:          
    mov bx,start_wire[0] ;X start
    mov cx,finish_wire[0] ; X end
    cmp bx,cx ;compare between X  of start & end , if start > end , go left else go right
    ja go_up_left
    jmp go_up_right
    
    go_down:
    mov bx,start_wire[0] ;X start
    mov cx,finish_wire[0] ; X end
    cmp bx,cx ;compare between X  of start & end , if start > end , go left else go right
    ja go_down_left
    jmp go_down_right
    
    
    go_up_left:
    mov cx,start_wire[0] ;put x coordinate ( 3ashan 3amla DB f mynf3sh a7otha fel cx 3latol)
    mov dx,start_wire[2] ;put y coordinate ( 3ashan 3amla DB f mynf3sh a7otha fel dx 3latol)
    drawing_UL:
    mov al,color_wire ;color of pixel
    mov ah,0ch ;drawing int
    int 10h ;drawing int
    inc si ;counter
    mov ax,si ;mov counter value of counter to ax for division
    div two[0] ;the defined array (mktbtsh 2 3ashan lazm yeb2a array/register)
    cmp ah,1 ; compare remainder , 1=odd , 0=even
    jz dec_cx_UL
    jmp dec_dx_UL 
    
    dec_cx_UL:
    cmp cx,finish_wire[0] ;did I reach end point ?
    jz no_dec_cx_UL ;wesl , e3ml skip lie decrment 
    dec cx ; lw mwlsesh hn3ml dec
    jmp drawing_UL ;Jmp lel drawing 
    no_dec_cx_UL:
    
    dec_dx_UL:
    cmp dx,finish_wire[2] ;compare m3 y
    jz no_dec_dx_UL ;wesl , e3ml skip lie decrment
    dec dx; lw mwlsesh hn3ml de
    jmp drawing_UL ;Jmp lel drawing 
    no_dec_dx_UL:
    cmp cx,finish_wire[0] ;lw m7tethmsh lw wslt lel y hytl3 mn awl hena 
    jnz dec_cx_UL ;decrment x 
    
    jmp done_direction ;end the procedure

    ;kol el functions nfs el haga b ekhtalf el increment wel decrement 
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;    
    
    go_up_right:
    
    mov cx,start_wire[0]
    mov dx,start_wire[2]
    drawing_UR:
    mov al,color_wire
    mov ah,0ch
    int 10h
    inc si
    mov ax,si
    div two[0]
    cmp ah,1
    jz inc_cx_UR
    jmp dec_dx_UR
    
    inc_cx_UR:
    cmp cx,finish_wire[0]
    jz no_inc_cx_UR
    inc cx
    jmp drawing_UR
    no_inc_cx_UR:
    
    dec_dx_UR:
    cmp dx,finish_wire[2]
    jz no_dec_dx_UR
    dec dx
    jmp drawing_UR
    no_dec_dx_UR:
    cmp cx,finish_wire[0]
    jnz inc_cx_UR
    
    jmp done_direction

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    go_down_left:
    
    mov cx,0
    mov dx,0
    mov cx,start_wire[0]
    mov dx,start_wire[2]
    drawing_DL:
    mov al,color_wire
    mov ah,0ch
    int 10h
    inc si
    mov ax,si
    div two[0]
    cmp ah,1
    jz dec_cx_DL
    jmp inc_dx_DL
    
    dec_cx_DL:
    cmp cx,finish_wire[0]
    jz no_dec_cx_DL
    dec cx
    jmp drawing_DL
    no_dec_cx_DL:
    
    inc_dx_DL:
    cmp dx,finish_wire[2]
    jz no_inc_dx_DL
    inc dx
    jmp drawing_DL
    no_inc_dx_DL: 
    cmp cx,finish_wire[0]
    jnz dec_cx_DL
    
    jmp done_direction

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    go_down_right:
    
    mov cx,0
    mov dx,0
    mov cx,start_wire[0]
    mov dx,start_wire[2]
    drawing_DR:
    mov al,color_wire
    mov ah,0ch
    int 10h
    inc si
    mov ax,si
    div two[0]
    cmp ah,1
    jz inc_cx_DR
    jmp inc_dx_DR
    
    inc_cx_DR:
    cmp cx,finish_wire[0]
    jz no_inc_cx_DR
    inc cx
    jmp drawing_DR
    no_inc_cx_DR:
    
    inc_dx_DR:
    cmp dx,finish_wire[2]
    jz no_inc_dx_DR
    inc dx
    jmp drawing_DR
    no_inc_dx_DR:
    cmp cx,finish_wire[0]
    jnz inc_cx_DR
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
done_direction:
popf
popa
ret 
drawwire endp

drawwire_and_gate proc
    pusha
    pushf
    cld

   

   cmp gate,57h
   jnz no_need_for_jump_far
   jmp  just_wire
   no_need_for_jump_far:
    mov si,0
    mov di,0  ;intilazing counter 1
    mov bx,0 ;intialzing counter 2
    mov ax ,input_array_pixels[8] ;3ashn with respect lel output node
    mov draw_location[0],ax ;7atet fel draw location el x w y beta3t akhr wahda
    mov ax ,input_array_pixels[10] ;
    mov draw_location[2],ax
    sub draw_location[0],26 ;offset
    sub draw_location[2],7 ;10 ;offset
    mov cx,draw_location[0] ;x
    mov dx,draw_location[2] ;y
    mov ax, draw_location[0] ;counter
    mov wire_input_up[0] , ax ;el x sabt fel input wel output 
    add wire_input_up[0] , 2
    mov wire_input_down[0] , ax ;same because all have same x
    mov ax, draw_location[2] ;b7ot el y w hzwd 3leha el offset
    mov wire_input_up[2] , ax 
    add  wire_input_up[2] ,5
    mov wire_input_down[2] , ax
    add wire_input_down[2],10 ;b7ot el y w hzwd 3leha el offset

    mov cx,draw_location[0]
    mov dx,draw_location[2]
    mov si,0                         
    still_deciphering:
    deciphering:
    cmp draw_array[si],-1
    jnz dont_get_color_background
    mov bh,0
    mov ah,0dh
    int 10h
    mov draw_array[si],al
    dont_get_color_background:
	inc si
    inc di
    inc cx
    cmp di,draw_size_yara[2] ; put width here
    jnz deciphering
    mov cx,draw_location[0]
    mov di,0
    inc dx
    cmp si,285 ;width x height cuz bh is being used and we dont have any more registers :(
    jnz still_deciphering
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov cx,draw_location[0] ;x
    mov dx,draw_location[2] ;y
    mov si,0
    mov di,0
    mov bx,0
    still_drawing:
    continue_draw:
    mov al,draw_array[si] ; put color array here
    mov ah,0ch 
    int 10h
	inc si
    inc di
    inc cx
    cmp di,draw_size_yara[2] ; put width here
    jnz continue_draw
    mov cx,draw_location[0]
    mov di,0
    inc dx
    inc bx
    cmp bx,draw_size_yara[0] ; put height here
    jnz still_drawing
;######################################################
    cmp gate,49h
    jz no_second_wire
    mov ax,input_array_pixels[0]
    mov start_wire [0] ,ax
    add start_wire[0],1
    mov ax,input_array_pixels[2]
    mov start_wire[2],ax
    sub start_wire[2],1

    mov ax,wire_input_up[0]
    mov finish_wire[0],ax
   ; sub finish_wire[0],1
    mov ax,wire_input_up[2]
    mov finish_wire[2],ax
    sub finish_wire[2],1
    
    call drawWire
    no_second_wire:
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    
    mov ax,input_array_pixels[4]
    mov start_wire [0],ax ;x start
    add start_wire [0] ,1
    mov ax,input_array_pixels[6]
    mov start_wire[2],ax ;y start
    ;sub start_wire[2],1

    mov ax,wire_input_down[0]
    mov finish_wire[0],ax
    mov ax,wire_input_down[2]
    mov finish_wire[2],ax
    ;sub finish_wire[2],1
    
    call drawwire
    jmp a5eeran_5lst_rsm
    
    just_wire:
    mov ax,input_array_pixels[8]
    mov start_wire [0],ax ;x el start point (3la el yemen)
    sub start_wire [0],7
    mov ax,input_array_pixels[10]
    mov start_wire[2],ax ;y el end point (3la el yemen)
    ;sub start_wire[2],10

   

    mov ax,input_array_pixels[4]
    mov finish_wire[0],ax ;x of finish
    add finish_wire [0],1
    mov ax,input_array_pixels[6]
    mov finish_wire[2],ax ; y of finish

    
    call draw_just_wire
    
    a5eeran_5lst_rsm: 
    popf
    popa
ret
drawwire_and_gate endp

