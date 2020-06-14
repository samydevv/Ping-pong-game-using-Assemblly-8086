.code

chatoutline proc
		
		MOV AH,0						;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,0EH						;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H	
		
		mov bh,00
		mov AH,0CH						;draw pixel int condition
		mov al,0Eh          			;set the purple colour
		mov dx,99    
		
		chat1:
			mov cx,04
			chat2:
				int 10h
				inc cx
				cmp cx,636
			jne chat2
			inc dx
			cmp dx,100
		jne chat1
		
		mov ah,2                		;move cursor at desired destination
		mov bh,0
		mov dx,0003h            
		int 10h
		
		mov ah,09
		mov dx,offset PLAYER1NAME+2 
		int 21h
		
		mov ah,2                		;move cursor at desired destination
		mov bh,0
		mov dx,0003h             
		add dl,player1name+1	 
		int 10h
		
		mov ah,02
		mov dl, 3AH					
		int 21h
		
		mov ah,2             		    ;move cursor at desired destination
		mov bh,0
		mov dx,0D03h         		    ;a5er el screen
		int 10h
		
		mov ah,09
		mov dx,offset PLAYER2NAME+2 
		int 21h
		
		mov ah,2               		    ;move cursor at desired destination
		mov bh,0
		mov dx,0D53h            		;a5er el screen
		add dl,PLAYER2NAME+1			;add playername length
		int 10h
		
		mov ah,02
		mov dl, 3AH				 		;write : after name
		int 21h
		
		mov ah,2             		    ;move cursor at desired destination
		mov bh,0
		mov dx,181Eh         		    ;a5er el screen
		int 10h
		
		mov ah,09
		mov dx,offset CHATEXIT
		int 21h
		
		mov bh,00
		mov AH,0CH						;draw pixel int condition
		mov al,0Eh          			;set the purple colour
		mov dx,190    
		
		chat3:
			mov cx,04
			chat4:
				int 10h
				inc cx
				cmp cx,636
			jne chat4
			inc dx
			cmp dx,191
		jne chat3
		
		mov ourcursor,0100H				;set the cursor of both players
		mov othercursor,0E00h	
		
		ret
chatoutline endp
;================================================;
Chat proc
		
		call chatoutline
		
		Chatting:
		call sending
		call receiving
		cmp mode,2h
		je chatting
		; jmp chatting
		call mainscreenui
		ret
chat endp
;================================================;
sending proc
		
		mov ah,1						;get key input
		int 16h
		jz midret					;if no keypress move to readingkeypresses
		; if keypress then send it and print it
		mov chatbyte,al
		call clearinputbuffer
		
		mov dx , 3FDH		; Line Status Register
		AGAINc:  	
		In al , dx 			;Read Line Status
  		AND al , 00100000b
  		JZ AGAINc
		
		mov dx , 3F8H		; Transmit data register
  		mov  al,chatbyte
  		out dx , al 
		
		mov ah,2                 ;move cursor at player1 pos
		mov bh,0
		mov dx,ourcursor             ;a5er el screen
		int 10h
		
		call displaychatbyte
		
		mov ah,3
		mov bh,0
		int 10h
		mov ourcursor,dx
		call checkscroll1
		
		; ret
		
		cmp chatbyte,0DH				;cmp with enter
		je enter1
		
		cmp chatbyte,8					;cmp with backspace
		je backspace1
		
		cmp chatbyte,27					;cmp with esc
		je chattomenu
		
		ret
		
		enter1:
		mov ah,2                 ;move cursor at player1 pos
		mov bh,0
		mov dx,ourcursor             ;a5er el screen
		inc dh
		mov dl,0h
		mov ourcursor,dx
		int 10h
		call checkscroll1
		midret:
		ret
		
		backspace1:
		mov dx,ourcursor
		cmp dl,0
		jne notatendx1
		;here at end x
		cmp dh,1
		jne notatendy1
		;here at end x and y
		ret
		
		notatendy1:
		;here at end x but not end y
		; call outro
		mov bx,ourcursor
		dec bh
		add bl,79
		mov ourcursor,bx
		mov ah,2                 ;move cursor at player1 pos
		mov bh,0
		mov dx,ourcursor             ;a5er el screen
		int 10h
		
		mov ah,2
		mov dl,0
		int 21h
		
		mov ah,3
		mov bh,0
		int 10h
		mov dl,79
		mov ourcursor,dx
		ret
		notatendx1:
		;here at not end x and not end y
		mov ah,2                 ;move cursor at player1 pos
		mov bh,0
		mov dx,ourcursor             ;a5er el screen
		int 10h
		
		mov ah,2
		mov dl,0
		int 21h
		
		mov ah,3
		mov bh,0
		int 10h
		mov ourcursor,dx
		dec ourcursor
		
		ret 
		cmp dl,0
		je keypressret
		ret
		
		chattomenu:
		mov mode,1h
		call resetindicators
		ret
		
		keypressret:
		ret
sending endp

receiving proc
		
		mov dx , 3FDH		; Line Status Register
		in al , dx 
  		AND al , 1
  		JZ mid2
		
		mov dx , 03F8H
  		in al , dx 
  		mov chatbyte , al
		
		
		
		mov ah,2                 ;move cursor at player1 pos
		mov bh,0
		mov dx,othercursor             ;a5er el screen
		int 10h
		
		call displaychatbyte
		
		mov ah,3
		mov bh,0
		int 10h
		mov othercursor,dx
		call checkscroll2
		
		
		cmp chatbyte,0DH				;cmp with enter
		je enter2
		
		cmp chatbyte,8					;cmp with backspace
		je backspace2
		
		cmp chatbyte,27					;cmp with esc
		je chattomenu2
		mid2:
		ret
		
		enter2:
		mov ah,2                 ;move cursor at player1 pos
		mov bh,0
		mov dx,othercursor             ;a5er el screen
		inc dh
		mov dl,0h
		mov othercursor,dx
		int 10h
		call checkscroll2
		ret
		
		backspace2:
		mov dx,othercursor
		cmp dl,3
		jae notatendx2
		cmp dh,14
		jae notatendy2
		ret
		
		notatendy2:
		dec dh
		mov dl,79
		
		notatendx2:
		mov ah,2                 ;move cursor at player1 pos
		mov bh,0
		mov dx,othercursor             ;a5er el screen
		int 10h
		
		mov ah,2
		mov dl,0
		int 21h
		
		mov ah,3
		mov bh,0
		int 10h
		mov othercursor,dx
		dec othercursor
		
		ret 
		
		chattomenu2:
		mov mode,1h
		call resetindicators
		ret
		
		receivingret:
		ret
receiving endp

checkscroll1 proc
		
		mov dx,ourcursor
		cmp dh,11
		jne dontscroll1
		
		mov ah,6       ; function 6
		mov al,1        ; scroll by 1 line    
		mov bh,0       ; normal video attribute         
		mov ch,1       ; upper left Y
		mov cl,0        ; upper left X
		mov dh,11     ; lower right Y
		mov dl,79      ; lower right X 
		int 10h 
		
		mov dx,ourcursor
		mov dh,10
		mov ourcursor,dx
		dontscroll1:
		ret
checkscroll1 endp

checkscroll2 proc
		
		mov dx,othercursor
		cmp dh,22
		jne dontscroll2
		
		mov ah,6       ; function 6
		mov al,1        ; scroll by 1 line    
		mov bh,0       ; normal video attribute         
		mov ch,14      ; upper left Y
		mov cl,0        ; upper left X
		mov dh,22     ; lower right Y
		mov dl,79      ; lower right X 
		int 10h 
		
		mov dx,othercursor
		mov dh,21
		mov othercursor,dx
		dontscroll2:
		ret
checkscroll2 endp

displaychatbyte proc
		
		mov ah,2
		mov dl,chatbyte
		int 21h
		
		ret
displaychatbyte endp