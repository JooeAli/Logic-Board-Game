.code

INPUT_COMMAND_TO_DRAW_ARRAY    PROC
    PUSHA
    PUSHF

    LEA SI,INPUT1_COL
    LEA DI,input_array
    MOV CX,6

    NEXT_DIGIT:
        MOV AL,[SI]
        MOV BYTE PTR [DI],AL
        INC SI
        INC DI
        DEC CX
        JNZ NEXT_DIGIT

    POPA
    POPF
    RET

INPUT_COMMAND_TO_DRAW_ARRAY    ENDP


get_coordinates proc
    pusha
    pushf
    cld
    ;;;;;;;;;;;;X CALCULATIONS;;;;;;;;;;;;
    mov al,calculating_array[0];coulumn of inout 1
    cmp al,0 ; b-compare ano msh coulmn 0 3ashan lie differen procedure
    jz col_6 ; thicknes el node heya el madrod 7 bs zbtet keda aktr
    cmp al,9 ;b-compare ano msh coulmn 9 3ashan lie differen procedure
    jz col_312 ;msh 314 thickness 3ashan mybwzsh shakl el rakm msh aktr
     ;3ashan el eqaution tezbot (if (coulumn == 0) {
    ;mov array_pixel[0], 6
    ;else if (coulumn == 9)
    ;{
   ; mov array_pixel[0], 6
    ;
   ; else
   ;{nekhos 3la el equation }
    ;}
    ;####EQUATION######
    dec al
    mul twenty_eight
    add ax,44
    mov calculating_array_pixels[0],ax 
    mov ax,0
    jmp done_x
    ;#####################################
    col_6:
    mov calculating_array_pixels[0],6
    jmp done_x
    col_312:
    mov calculating_array_pixels[0],318
    done_x:
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;;;;;;;;;Y CALCULATIONS;;;;;;;;;;;;
    mov al,calculating_array[0] ;7atet el coulumn msh el row 3ashan asln el coulumn hwa el by7dedly even wala odd
    cmp al,0 ;zero sprcial coulumn
    jz special_column_6
    cmp al,9 ;zero sprcial coulumn
    jz special_column_312
    div two ;to check even wala odd
    cmp ah,0 ; b-acheck el remainder 
    jz odd_col ;el mafrod even ana lkhbt wana bsmy
    jmp even_col ;el mafrod odd ana lkhbt wana bsmy
    
    odd_col: 
    mov ax,0 ;bsfr ax 3ashan a7ot fieh el row
    mov al,calculating_array[1] ; b7ot el row fir ax
    dec al
    mul fifteen ;bdrb fie 17 bs mghhyrthash 3ashan mtbwzsh el fun
    add ax,29 ;offset el even rows
    jmp done_y ;7sbt el y lie awl input khlas 
    
    even_col:
    mov ax,0;bsfr ax 3ashan a7ot fieh el row
    mov al,calculating_array[1] ;b7ot el row fie ax
    dec al
    mul fifteen ;bdrb fie 17 bs mghhyrthash 3ashan mtbwzsh el fun
    add ax,21 ;offset el even rows
    
    done_y:
    jmp not_special_column 
    
    special_column_6:
    mov ax,0
    mov al,calculating_array[1]
    dec fifteen ;thicnkess el node b 1
    mul fifteen
    add ax,14 ;offset hena 14
    inc fifteen ;3ashan mnsash azwdha
    jmp not_special_column

    special_column_312:
    mov ax,0
    mov al,calculating_array[1]
    cmp al,0
    jz no_mul 
    dec fifteen ;thicnkess el node b 1
    mul fifteen  
    inc fifteen ;3ashan mnsash azwdha
    no_mul:
    add ax,14 ;offset hena 15

    
    
    not_special_column:
    mov calculating_array_pixels[2],ax
    popf
    popa
    ret
    get_coordinates endp

get_all_coordinates proc 
    
    mov ax,0
    mov al,input_array[0]
    mov calculating_array[0],al
    mov al,input_array[1]
    mov calculating_array[1],al
    
    call get_coordinates
    
    mov ax,calculating_array_pixels[0]
    mov input_array_pixels[0],ax
    mov ax,calculating_array_pixels[2]
    mov input_array_pixels[2],ax
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    mov ax,0
    mov al,input_array[2]
    mov calculating_array[0],al
    mov al,input_array[3]
    mov calculating_array[1],al
    
    call get_coordinates
    
    mov ax,calculating_array_pixels[0]
    mov input_array_pixels[4],ax
    mov ax,calculating_array_pixels[2]
    mov input_array_pixels[6],ax
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    mov ax,0
    mov al,input_array[4]
    mov calculating_array[0],al
    mov al,input_array[5]
    mov calculating_array[1],al
    
    call get_coordinates
    
    mov ax,calculating_array_pixels[0]
    mov input_array_pixels[8],ax
    mov ax,calculating_array_pixels[2]
    mov input_array_pixels[10],ax
    ret
    get_all_coordinates endp

    
get_all2_coordinates proc 
    pusha
    pushf
    
    mov ax,0
    mov al,input_array[0]
    mov calculating_array[0],al
    mov al,input_array[1]
    mov calculating_array[1],al
    
    call get_coordinates
    
    mov ax,calculating_array_pixels[0]
    mov input_array_pixels[0],ax
    mov ax,calculating_array_pixels[2]
    mov input_array_pixels[2],ax
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    mov ax,0
    mov al,input_array[2]
    mov calculating_array[0],al
    mov al,input_array[3]
    mov calculating_array[1],al
    
    call get_coordinates
    
    mov ax,calculating_array_pixels[0]
    mov input_array_pixels[4],ax
    mov ax,calculating_array_pixels[2]
    mov input_array_pixels[6],ax
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    mov ax,0
    mov al,input_array[4]
    mov calculating_array[0],al
    mov al,input_array[5]
    mov calculating_array[1],al
    
    call get_coordinates
    
    mov ax,calculating_array_pixels[0]
    mov input_array_pixels[8],ax
    mov ax,calculating_array_pixels[2]
    mov input_array_pixels[10],ax

    popa
    popf
    ret
    get_all2_coordinates endp