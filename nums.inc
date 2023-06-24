.code

;------------------------------------------------------------------------------------------------
number0 proc
    pusha
    pushf
    cld

    mov si,0
    mov di,0  ;intilazing counter 1
    mov bx,0 ;intialzing counter 2
    mov cx,draw_location0[0] 
    mov dx,draw_location0[2]  
    
    still_drawing0:
    continue_draw0:
    mov al,draw_array0[si] ; put color array here
    mov ah,0ch 
    int 10h
	inc si
    inc di
    inc cx
    cmp di,draw_size[2] ; put width here
    jnz continue_draw0
    mov cx,draw_location0[0]
    mov di,0
    inc dx
    inc bx
    cmp bx,draw_size[0] ; put height here
    jnz still_drawing0

    popf
    popa
    ret
number0 ENDP
;------------------------------------------------------------------------------------------------
number1 proc
    pusha
    pushf
    cld

    mov si,0
    mov di,0  ;intilazing counter 1
    mov bx,0 ;intialzing counter 2
    mov cx,draw_location1[0] 
    mov dx,draw_location1[2]  
    
    still_drawing1:
    continue_draw1:
    mov al,draw_array1[si] ; put color array here
    mov ah,0ch 
    int 10h
	inc si
    inc di
    inc cx
    cmp di,draw_size[2] ; put width here
    jnz continue_draw1
    mov cx,draw_location1[0]
    mov di,0
    inc dx
    inc bx
    cmp bx,draw_size[0] ; put height here
    jnz still_drawing1
    
    popf
    popa
    ret
number1 ENDP
;------------------------------------------------------------------------------------------------
number2 proc
    pusha
    pushf
    cld

    mov si,0
    mov di,0  ;intilazing counter 1
    mov bx,0 ;intialzing counter 2
    mov cx,draw_location2[0] 
    mov dx,draw_location2[2]  
    
    still_drawing2:
    continue_draw2:
    mov al,draw_array2[si] ; put color array here
    mov ah,0ch 
    int 10h
	inc si
    inc di
    inc cx
    cmp di,draw_size[2] ; put width here
    jnz continue_draw2
    mov cx,draw_location2[0]
    mov di,0
    inc dx
    inc bx
    cmp bx,draw_size[0] ; put height here
    jnz still_drawing2
    
    popf
    popa
    ret
number2 ENDP

;------------------------------------------------------------------------------------------------
number3 proc
    pusha
    pushf
    cld

    mov si,0
    mov di,0  ;intilazing counter 1
    mov bx,0 ;intialzing counter 2
    mov cx,draw_location3[0] 
    mov dx,draw_location3[2]  
    
    still_drawing3:
    continue_draw3:
    mov al,draw_array3[si] ; put color array here
    mov ah,0ch 
    int 10h
	inc si
    inc di
    inc cx
    cmp di,draw_size[2] ; put width here
    jnz continue_draw3
    mov cx,draw_location3[0]
    mov di,0
    inc dx
    inc bx
    cmp bx,draw_size[0] ; put height here
    jnz still_drawing3

    popf
    popa
    ret
number3 ENDP
;------------------------------------------------------------------------------------------------
number4 proc
    pusha
    pushf
    cld

    mov si,0
    mov di,0  ;intilazing counter 1
    mov bx,0 ;intialzing counter 2
    mov cx,draw_location4[0] 
    mov dx,draw_location4[2]  
    
    still_drawing4:
    continue_draw4:
    mov al,draw_array4[si] ; put color array here
    mov ah,0ch 
    int 10h
	inc si
    inc di
    inc cx
    cmp di,draw_size[2] ; put width here
    jnz continue_draw4
    mov cx,draw_location4[0]
    mov di,0
    inc dx
    inc bx
    cmp bx,draw_size[0] ; put height here
    jnz still_drawing4

    popf
    popa
    ret
number4 ENDP
;------------------------------------------------------------------------------------------------
number5 proc
    pusha
    pushf
    cld

    mov si,0
    mov di,0  ;intilazing counter 1
    mov bx,0 ;intialzing counter 2
    mov cx,draw_location5[0] 
    mov dx,draw_location5[2]  
    
    still_drawing5:
    continue_draw5:
    mov al,draw_array5[si] ; put color array here
    mov ah,0ch 
    int 10h
	inc si
    inc di
    inc cx
    cmp di,draw_size[2] ; put width here
    jnz continue_draw5
    mov cx,draw_location5[0]
    mov di,0
    inc dx
    inc bx
    cmp bx,draw_size[0] ; put height here
    jnz still_drawing5
    

    popf
    popa
    ret
number5 ENDP
;------------------------------------------------------------------------------------------------
number6 proc
    pusha
    pushf
      cld

    mov si,0
    mov di,0  ;intilazing counter 1
    mov bx,0 ;intialzing counter 2
    mov cx,draw_location6[0] 
    mov dx,draw_location6[2]  
    
    still_drawing6:
    continue_draw6:
    mov al,draw_array6[si] ; put color array here
    mov ah,0ch 
    int 10h
	inc si
    inc di
    inc cx
    cmp di,draw_size[2] ; put width here
    jnz continue_draw6
    mov cx,draw_location6[0]
    mov di,0
    inc dx
    inc bx
    cmp bx,draw_size[0] ; put height here
    jnz still_drawing6
    

    popf
    popa
    ret
number6 ENDP
;------------------------------------------------------------------------------------------------
    number7 proc
    pusha
    pushf
      cld

    mov si,0
    mov di,0  ;intilazing counter 1
    mov bx,0 ;intialzing counter 2
    mov cx,draw_location7[0] 
    mov dx,draw_location7[2]  
    
    still_drawing7:
    continue_draw7:
    mov al,draw_array7[si] ; put color array here
    mov ah,0ch 
    int 10h
	inc si
    inc di
    inc cx
    cmp di,draw_size[2] ; put width here
    jnz continue_draw7
    mov cx,draw_location7[0]
    mov di,0
    inc dx
    inc bx
    cmp bx,draw_size[0] ; put height here
    jnz still_drawing7


    popf
    popa
    ret
number7 ENDP
;------------------------------------------------------------------------------------------------
  number8 proc
    pusha
    pushf
      cld

    mov si,0
    mov di,0  ;intilazing counter 1
    mov bx,0 ;intialzing counter 2
    mov cx,draw_location8[0] 
    mov dx,draw_location8[2]  
    
    still_drawing8:
    continue_draw8:
    mov al,draw_array8[si] ; put color array here
    mov ah,0ch 
    int 10h
	inc si
    inc di
    inc cx
    cmp di,draw_size[2] ; put width here
    jnz continue_draw8
    mov cx,draw_location8[0]
    mov di,0
    inc dx
    inc bx
    cmp bx,draw_size[0] ; put height here
    jnz still_drawing8

    popf
    popa
    ret
number8 ENDP
;------------------------------------------------------------------------------------------------
number9 proc
    pusha
    pushf
      cld
    
    mov si,0
    mov di,0  ;intilazing counter 1
    mov bx,0 ;intialzing counter 2
    mov cx,draw_location9[0] 
    mov dx,draw_location9[2]  
    
    still_drawing9:
    continue_draw9:
    mov al,draw_array9[si] ; put color array here
    mov ah,0ch 
    int 10h
	inc si
    inc di
    inc cx
    cmp di,draw_size[2] ; put width here
    jnz continue_draw9
    mov cx,draw_location9[0]
    mov di,0
    inc dx
    inc bx
    cmp bx,draw_size[0] ; put height here
    jnz still_drawing9

popf
popa
ret
number9 ENDP
;------------------------------------------------------------------------------------------------

info proc
    pusha
    pushf
      cld
    
    mov draw_location_info[0],97      ;x-pos
    mov draw_location_info[2],3      ;y-pos

    mov si,0
    mov di,0  ;intilazing counter 1
    mov bx,0 ;intialzing counter 2
    mov cx,draw_location_info[0] 
    mov dx,draw_location_info[2]  
    
    still_drawing_info:
    continue_drawing_info:
    mov al,draw_array_info[si] ; put color array here
    mov ah,0ch 
    int 10h
	inc si
    inc di
    inc cx
    cmp di,draw_size_info[2] ; put width here
    jnz continue_drawing_info
    mov cx,draw_location_info[0]
    mov di,0
    inc dx
    inc bx
    cmp bx,draw_size_info[0] ; put height here
    jnz still_drawing_info

popf
popa
ret
info ENDP
;------------------------------------------------------------------------------------------------
draw_num_cols_odd proc
    pusha
    pushf
      cld

    mov draw_location1[0],37
    mov draw_location2[0],37
    mov draw_location3[0],37
    mov draw_location4[0],37
    mov draw_location5[0],37
    mov draw_location6[0],37
    mov draw_location7[0],37
    mov draw_location8[0],37
    mov draw_location9[0],37


    mov draw_location1[2],23
    mov draw_location2[2],40
    mov draw_location3[2],57
    mov draw_location4[2],74
    mov draw_location5[2],91
    mov draw_location6[2],108
    mov draw_location7[2],125
    mov draw_location8[2],142
    mov draw_location9[2],159

mov cx,4
 num_loop_col_odd:
   call number1
   call number2
   call number3
   call number4
   call number5
   call number6
   call number7
   call number8
   call number9

add draw_location1,68
add draw_location2,68
add draw_location3,68
add draw_location4,68
add draw_location5,68
add draw_location6,68
add draw_location7,68
add draw_location8,68
add draw_location9,68

dec cx
jnz  num_loop_col_odd ;repeats odd cols
 popa
    popf
    ret
draw_num_cols_odd ENDP



;------------------------------------------------------------------------------------------------
draw_num_cols_even proc
    pusha
    pushf
    cld
      

mov cx,4

mov draw_location1[0],71
mov draw_location2[0],71
mov draw_location3[0],71
mov draw_location4[0],71
mov draw_location5[0],71
mov draw_location6[0],71
mov draw_location7[0],71
mov draw_location8[0],71
mov draw_location9[0],71


mov draw_location1[2],31
mov draw_location2[2],48
mov draw_location3[2],65
mov draw_location4[2],82
mov draw_location5[2],99
mov draw_location6[2],116
mov draw_location7[2],133
mov draw_location8[2],150
mov draw_location9[2],167


 num_loop_col_even:
   call number1
   call number2
   call number3
   call number4
   call number5
   call number6
   call number7
   call number8
   call number9

add draw_location1[0],68
add draw_location2[0],68
add draw_location3[0],68
add draw_location4[0],68
add draw_location5[0],68
add draw_location6[0],68
add draw_location7[0],68
add draw_location8[0],68
add draw_location9[0],68

dec cx
jnz  num_loop_col_even ;repeats odd even



popf
popa
ret
draw_num_cols_even ENDP
;------------------------------------------------------------------------------------------------
draw_input_cols proc
    pusha
    pushf
    cld
      

mov cx,2

mov draw_location0[0],2
mov draw_location1[0],2
mov draw_location2[0],2
mov draw_location3[0],2
mov draw_location4[0],2
mov draw_location5[0],2
mov draw_location6[0],2
mov draw_location7[0],2
mov draw_location8[0],2
mov draw_location9[0],2

mov draw_location0[2],17
mov draw_location1[2],33
mov draw_location2[2],49
mov draw_location3[2],65
mov draw_location4[2],81
mov draw_location5[2],97
mov draw_location6[2],113
mov draw_location7[2],129
mov draw_location8[2],145
mov draw_location9[2],161


 num_loop_col_input:
   call number0
   call number1
   call number2
   call number3
   call number4
   call number5
   call number6
   call number7
   call number8
   call number9

add draw_location0[0],313
add draw_location1[0],313
add draw_location2[0],313
add draw_location3[0],313
add draw_location4[0],313
add draw_location5[0],313
add draw_location6[0],313
add draw_location7[0],313
add draw_location8[0],313
add draw_location9[0],313

dec cx
jnz  num_loop_col_input ;repeats input col



popf
popa
ret
draw_input_cols  ENDP


;------------------------------------------------------------------------------------------------
draw_bottom_nums proc
    pusha
    pushf
    cld
      
mov draw_location0[0],7
mov draw_location1[0],40
mov draw_location2[0],74
mov draw_location3[0],108
mov draw_location4[0],142
mov draw_location5[0],176
mov draw_location6[0],210
mov draw_location7[0],244
mov draw_location8[0],278
mov draw_location9[0],311

mov draw_location0[2],176
mov draw_location1[2],176
mov draw_location2[2],176
mov draw_location3[2],176
mov draw_location4[2],176
mov draw_location5[2],176
mov draw_location6[2],176
mov draw_location7[2],176
mov draw_location8[2],176
mov draw_location9[2],176


   call number0
   call number1
   call number2
   call number3
   call number4
   call number5
   call number6
   call number7
   call number8
   call number9


popf
popa
ret
draw_bottom_nums ENDP