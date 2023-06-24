.code


Entergraphics proc
    PUSHA
    PUSHF
        mov ax,13h
        int 10h
    POPA
    POPF
    ret
Entergraphics endp

;------------------------------------------------------------------------------------------------

FillScreen proc
    PUSHA
    PUSHF
        MOV AL,0fh ; AL gets the color value
        MOV BX,0A000H ;
        MOV ES,BX ; ES set to start of VGA
        MOV CX,64000 ; CX set to number of pixels
        MOV DI,0 ; DI set to pixel offset 0
        REP STOSB ; While CX <> 0 Do
        ; Memory[ES:DI] := AL
        ; DI := DI + 1
        ; CX := CX - 1

    POPA
    POPF
    ret
FillScreen endp

;------------------------------------------------------------------------------------------------

ClearScreen PROC
    PUSHA
    PUSHF
        mov SPACES_BETWEEN_COLS,7
        mov     ax,0A000h
        mov     es,ax  
        cld
        MOV DI,3566                 ;320x11+9+34+3
        backSCreen2:
        mov dx,163                  ;HEIGHT OF WHITE BOX
        mov al,0FH                  ;white

        backScreen:
            mov cx,25               ;WIDTH OF WHITEBOX
            rep stosb
            add di,320-25
            dec DX
        jnz backScreen

        mov bx,52126 ;              ;eg (3566+320*163) - 3566+34  --> 55726-3600     difference between bottom left point and top left in next square
        sub di,bx
        dec SPACES_BETWEEN_COLS
        jnz backSCreen2



        mov     ax,0A000h
        mov     es,ax  
        cld
        MOV DI,3527                ;320x11+9
        mov dx,163                  ;HEIGHT OF WHITE BOX
        mov al,0FH                  ;white

        backScreen4:
            mov cx,30              ;WIDTH OF WHITEBOX
            rep stosb
            add di,320-30
            dec DX
        jnz backScreen4

        
        mov     ax,0A000h
        mov     es,ax  
        cld
        MOV DI,2524                 ;320x11+9
        mov dx,167                  ;HEIGHT OF WHITE BOX
        mov al,0FH                  ;white

        backScreen5:
            mov cx,27              ;WIDTH OF WHITEBOX
            rep stosb
            add di,320-27
            dec DX
        jnz backScreen5

       
        


    POPA
    POPF
    RET
ClearScreen ENDP    

;------------------------------------------------------------------------------------------------

drawlineThick proc
    PUSHA
    PUSHF
        mov     ax,0A000h
        mov     es,ax
        cld ; clear direction flag
        
        ;bottom line
        MOV DI,58560        ; 320*183{line)
        mov al,0h           ; black
        back:
            mov cx,320      ;width of line
            rep stosb
            cmp cx,0
        jnz back

        ;top line
        MOV DI,58240        ;320*182(line)
        mov al,0h           ; black
        back1:
            mov cx,320      ;width of line
            rep stosb
            cmp cx,0
        jnz back1
    POPF
    POPA
    ret
drawlineThick ENDP

;------------------------------------------------------------------------------------------------

DrawLineThinBottom proc
    PUSHA
    PUSHF
        mov     ax,0A000h
        mov     es,ax
        cld ; clear direction flag
        
        MOV DI,55680            ; 320*174
        mov al,1000b            ; dark grey
        back2:
            mov cx,320          ;width of line
            rep stosb
            cmp cx,0
        jnz back2
    POPA
    POPF
    ret
DrawLinethinBottom endp

;------------------------------------------------------------------------------------------------

DrawLineThinTop proc
    PUSHA
    PUSHF
        mov     ax,0A000h
        mov     es,ax
        cld ; clear direction flag
        
        MOV DI,3230             ; 10*320+7   (line 10 start from col 7)
        mov al,1000b            ; dark grey
        back3:
            mov cx,260          ;width of line
            rep stosb
            cmp cx,0
        jnz back3
    POPA
    POPF
    ret
DrawLinethinTop endp

;------------------------------------------------------------------------------------------------

DrawVerticalLines proc
    pusha
    PUSHF
        mov vlines_count,8
        mov     ax,0A000h
        mov     es,ax  
        cld
        MOV DI,3241                 ;320x10+7+34
        back6:
        mov dx,164                  ;length of vl line
        mov al,1000b                ;dark grey color

        back5:
            mov cx,1
            rep stosb
            add di,320-1
            dec DX
        jnz back5

        mov bx,52446 ;              ;diffrence between last point of vl line and first point of next vl line
        sub di,bx
        dec vlines_count
        jnz back6
        
        POPF
        POPa
        ret
DrawVerticalLines endp

;------------------------------------------------------------------------------------------------

DrawNodes proc
    pusha
    pushf
        mov cursornodes,6437        ;320*20+34+7-3      6438 WIDTH 7       6437 WIDTH 9
        mov countnodes,2
        mov countcols,4
        mov bx,11                   ;start of output col
        next2cols:                  ;loop to repeat the drawing of the first 2 columns again (3 more times)
        nextcol:                    ;loop to draw next col nodes

            mov     ax,0A000h
            mov     es,ax
        
            mov count_node_color,9 ;each col counter
            mov count_node_color_col,9
            
            

            nodelabel2:
            mov di,cursornodes
            mov dx,2
            mov al,map_index[bx]            ;store map_index to compare with 0 & 1 to color nodes accordingly (0=red,1=green)
            
            cmp al,0                        ;if map_index[0,10,20,30,40,etc]=0,color red else if not color green else unknown
                jz  draw_nodes_red
                jnz check_green2

            draw_nodes_red:
                mov AL,0100b

            jmp loop_counter_nodes         ;if red is chosen exit loop and draw next node
            
            check_green2:
            cmp al,1
                jz draw_nodes_green
                jnz draw_black

            draw_nodes_green:              
            mov AL,0010b

            jmp loop_counter_nodes          ;if green is chosen exit loop and draw next node

            draw_black:                     ;color for case of unknown output
            mov al,0000b
            
            loop_counter_nodes: 
            add bx,10
            
            dec count_node_color_col        ;check if all nodes in same col are drawn if so jump to next col
            jz next_col
            jmp nodelabel1
            next_col:
            sub bx,89
        


            NODELABEL1:
                mov cx,9           ;node width
                rep stosb           ;draw st. line
                add di,320-9       ;di to next line at the start of node
                dec dx          
                jnz NODELABEL1

            ;mov cursornode to next node in same col
            add cursornodes,5440 ;17*320
            dec count_node_color
            jnz nodelabel2

            ;mov cursornode to next node in the next col to move from col 1 to col 2
            sub cursornodes,46366         ;subtract from DI to jump to next node in next col
            dec countnodes
            jnz nextcol

            ;intiliaze countnodes, move cursornodes to next col after drawing two cols
            mov countnodes,2
            sub cursornodes,5120 ;               525522+5440-46366=11626    ->11626-6506=5120
            dec countcols
            jnz next2cols


    popa
    popf

    ret

DrawNodes endp

;------------------------------------------------------------------------------------------------

DrawOutputs proc
    pusha
    pushf

        mov currout,4791
        mov     ax,0A000h
        mov     es,ax
    
        mov count_output,10    ;each col counter
        mov bx,09              ;start of output col

        nodelabelout2:
        mov di,currout
        mov dx,1

        mov al,map_index[bx]        ;store map_index to compare with 0 & 1 to color outputs accordingly (0=red,1=green)
        cmp al,0                    ;if map_index[09,19,29,39,49,etc]=0,color red else if not color green else unknown
            jz  draw_output_red
            jnz check_green

        draw_output_red:
        mov AL,0100b

        jmp loop_counter_out        ;if red is chosen exit loop and draw next node       
        
        check_green:
        cmp al,1
            jz draw_out_green
            jnz draw_unknown_color

        draw_out_green:
            mov AL,0010b
            
            jmp loop_counter_out        ;if green is chosen exit loop and draw next node

            draw_unknown_color:         ;color for case of unknown output
            cmp  count_output,6         ;color first 5 nodes Light Magenta
                jc draw_yellow          ;color first 5 nodes yellow
            mov al,1101b
            jmp loop_counter_out        ;if light magenta is chosen exit loop and draw next node
            
            draw_yellow:
            mov al,1110b

            loop_counter_out:
            add bx,10


        NODELABELout1:
            mov cx,9                ;node width
            rep stosb
            add di,320-9
            dec dx
            jnz NODELABELout1

    
        add currout,5120 ;16*320
        dec count_output 
        jnz nodelabelout2



    popa
    popf

    ret

DrawOutputs endp

;------------------------------------------------------------------------------------------------

DrawInputs proc
    pusha
    pushf
        mov currin,4480
        mov     ax,0A000h
        mov     es,ax
    
        mov count_input,10 ;each col counter
        mov bx,0

        nodelabelin2:
        mov di,currin
        mov dx,1
        mov al,map_index[bx]            ;store map_index to compare with 0 & 1 to color inputs accordingly (0=red,1=green)
        cmp al,0                        ;if map_index[0,10,20,30,40,etc]=0,color red else if not color green
            jz  draw_input_red
            jnz draw_input_green

        draw_input_red:
        mov AL,0100b

        jmp loop_counter                ;if red is chosen exit loop and draw next node

        draw_input_green:
        mov AL,0010b

        loop_counter:
        add bx,10


        NODELABELin1:
            mov cx,9     ;node width
            rep stosb
            add di,320-9
            dec dx
            jnz NODELABELin1

        add currin,5120 ;16*320
        dec count_input
        jnz nodelabelin2

    popa
    popf

    ret

DrawInputs endp

;------------------------------------------------------------------------------------------------

DRAW_BOARD              PROC
    PUSHA
    PUSHF

        call Entergraphics
        call FillScreen
        call drawlineThick
        call DrawLinethinBottom
        call DrawLinethinTop
        call DrawVerticalLines
        call DrawNodes
        call DrawOutputs
        call DrawInputs
        call draw_num_cols_odd
        call draw_num_cols_even 
        call draw_input_cols 
        call draw_bottom_nums
        call info


    POPA
    POPF
    RET

DRAW_BOARD              ENDP
