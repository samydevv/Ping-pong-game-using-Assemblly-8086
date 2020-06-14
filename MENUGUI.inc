.code

mainscreenui proc
		
		; mov recievedchatinv,0
		; mov recievedgameinv,0
		call writetext
		call drawnotification
		ret
mainscreenui endp

writetext proc

		mov serving,1			;each time the user goes to the main menu, serving should be set to player 1
		
		MOV AH,0				;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,0EH				;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H	
		
		mov bh,0
		mov ah,2          		;Move Cursor to upper middle of screen
		mov dx,0A1Ah      		
		int 10h           		
		
		mov ah, 9				;Display 'To start chatting press f1'
		mov dx, offset mainscreen1	
		int 21h 
		
		mov ah,2          		;Move Cursor to lower middle of screen
		mov dx,0C1Ah      		
		int 10h           		

		mov ah, 9				;Display 'To start Pong game press F2'
		mov dx, offset mainscreen2	
		int 21h 
		
		mov ah,2          		;Move Cursor, to middle of screen
		mov dx,0E1Ah      		
		int 10h           		
		
		mov ah,9	      		;Display 'To end the program press ESC'
		mov dx,offset mainscreen3                  
		int 21h
		
		ret
writetext endp

showwaitmessage proc
		
		MOV AH,0				;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,0EH				;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H	
		
		mov ah,2          		;Move Cursor to lower middle of screen
		mov dx,0C0Ch      		
		int 10h           		

		mov ah, 9				;Display 'To start Pong game press F2'
		mov dx, offset MAINSCREEN7	
		int 21h 
		
		ret
showwaitmessage endp

drawnotification proc
		
		mov bh,00
		mov AH,0CH			;draw pixel int condition
		mov al,09h          ;set the purple colour
		mov dx,166    
		
		menu1:
			mov cx,04
			menu2:
				int 10h
				inc cx
				cmp cx,636
			jne menu2
			inc dx
			cmp dx,167
		jne menu1
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1615h             ;a5er el screen
		int 10h
		
		mov ah,09
		mov dx,offset PLAYER1NAME+2 
		int 21h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1615h             ;a5er el screen
		add dl,player1name+1	 ;add playername length
		int 10h
		
		mov ah,02
		mov dl, 3AH	;then write the score after adding all that
		int 21h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1815h             ;a5er el screen
		int 10h
		
		mov ah,09
		mov dx,offset PLAYER2NAME+2 
		int 21h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1815h             ;a5er el screen
		add dl,player2name+1	 ;add playername length
		int 10h
		
		mov ah,02
		mov dl, 3AH	;then write the score after adding all that
		int 21h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1815h             ;a5er el screen
		add dl,player2name+1	 ;add playername length
		int 10h
		
		mov ah,02
		mov dl, 3AH	;then write the score after adding all that
		int 21h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1815h             ;a5er el screen
		add dl,player2name+1	 ;add playername length
		int 10h
		
		mov ah,02
		mov dl, 3AH	;then write the score after adding all that
		int 21h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1815h             ;a5er el screen
		add dl,player2name+1	 ;add playername length
		int 10h
		
		mov ah,02
		mov dl, 3AH	;then write the score after adding all that
		int 21h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1815h             ;a5er el screen
		add dl,player2name+1	 ;add playername length
		int 10h
		
		mov ah,02
		mov dl, 3AH	;then write the score after adding all that
		int 21h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1526h             ;a5er el screen
		int 10h
		
		mov ah,09
		mov dx,offset MAINSCREEN4
		int 21h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1535h             ;a5er el screen
		int 10h
		
		mov ah,09
		mov dx,offset MAINSCREEN5
		int 21h
		
		call drawindicators
		
		ret
drawnotification endp

drawindicators proc
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1628h             ;a5er el screen
		int 10h
		
		cmp readytogame,0
		je notrgame
		mov bl,02h
		jmp d1
		notrgame:
		mov bl,004h				;red on black background
		d1:
		mov ah,9				;int condition			
		mov bh,0				;page number
		mov al,04H				;arrow sign  			
		mov cx,1H				;1 time
		int 10h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1837h             ;a5er el screen
		int 10h
		
		cmp recievedchatinv,0
		je notrecchat
		mov bl,02h
		jmp d2
		notrecchat:
		mov bl,004h				;red on black background
		d2:
		mov ah,9				;int condition			
		mov bh,0				;page number
		mov al,04H				;arrow sign  			
		mov cx,1H				;1 time
		int 10h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1828h             ;a5er el screen
		int 10h
		
		cmp recievedgameinv,0
		je notrecgame
		mov bl,02h
		jmp d3
		notrecgame:
		mov bl,004h				;red on black background
		d3:
		mov ah,9				;int condition			
		mov bh,0				;page number
		mov al,04H				;arrow sign  			
		mov cx,1H				;1 time
		int 10h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1637h             ;a5er el screen
		int 10h
		
		cmp readytochat,0
		je notrchat
		mov bl,02h
		jmp d4
		notrchat:
		mov bl,004h				;red on black background
		d4:
		mov al,04H				;arrow sign  			
		mov ah,9				;int condition			
		mov bh,0				;page number
		mov cx,1H				;1 time
		int 10h 
		
		
		ret
drawindicators endp

resetindicators proc
		
		mov recievedchatinv,0	
		mov recievedgameinv,0	
		mov readytochat,0	
		mov readytogame,0
		
		ret
resetindicators endp