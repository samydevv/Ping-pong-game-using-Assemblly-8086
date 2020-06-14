.code
menuinput proc
		
		GETMODE:
		
		call checkinvites
		cmp mode,2h
		je reteren
		cmp mode,3h
		je startthegame
		
		mov ah,1			;get key input
		int 16h
		jz GETMODE
		
		cmp ah,3bh			;cmp with f1
		jz f1
		
		cmp ah,3ch			;cmp with f2
		jz f2
		
		cmp ah,01h			;cmp with esc
		jz escape
		
		call clearinputbuffer
		jmp GETMODE
		
		f1:					;chat mode is chosen
		call clearinputbuffer
		call sendchatinv
		call checkchatinv
		;PUT CODE HERE TO CLEAR THE SCREEN AND CHOOSE SUITABLE VIDEO MODE FOR CHAT
		ret
		
		f2:					;game mode is chosen
		call clearinputbuffer
		call sendgameinv
		call checkgameinv
		cmp mode,3h
		je startthegame
		ret
		startthegame:
		MOV AH,0			
		MOV AL,0EH			;this is here just to clear the screen from the text of main menu
		INT 10H
		call clearinputbuffer
		; call GETPADDLESIZE		;ask user for paddle size
		; cmp mode,1h
		; je retr
		; CALL GETBALLSPEED		;ask user for ball speed
		; cmp mode,1h
		; je retr
		
		MOV AH,0			
		MOV AL,0EH				;this is here just to clear the screen from the text of main menu
		INT 10H		
		CALL drawoutline		;draw game outline
		call initializegame		;reset paddles and ball positions
		
		retr:
		call resetindicators
		ret
		
		escape:
		call outro
		
		reteren:
		ret
menuinput endp

checkinvites proc

		mov dx , 3FDH		; Line Status Register
		in al , dx 
  		AND al , 1			;check if there's something to recieve
  		JZ reeeeet			;if nothing then return
		
		mov dx , 03F8H
  		in al , dx 
		
		cmp al,3bh
		je chatinvrecieved
		
		cmp al,3ch
		je gameinvrecieved
		
		
		chatinvrecieved:
		mov recievedchatinv,1
		call drawnotification
		cmp readytochat,1
		jne dontstartchat
		mov mode,2h
		dontstartchat:
		ret
		
		
		gameinvrecieved:
		mov recievedgameinv,1
		call drawnotification
		cmp readytogame,1
		jne dontstartgame
		;I started the game here
		
		call GETPADDLESIZE		;ask user for paddle size
		cmp mode,1h
		je cancelgame
		call sendpaddlesize
		CALL GETBALLSPEED		;ask user for ball speed
		cmp mode,1h
		je cancelgame
		call sendballspeed
		
		mov mode,3h
		dontstartgame:
		ret
		
		cancelgame:			;send esc to other user
		; ;test
		; mov ah,2          		;Move Cursor, to middle of screen
		; mov dx,0d32h      		
		; int 10h           		
		
		; mov ah,9	      		;Display 'To end the program press ESC'
		; mov dx,offset mainscreen3                  
		; int 21h
		; ;test
		
		; mov ah,2          		;Move Cursor, to middle of screen
		; mov dx,0C1Fh      		
		; int 10h           		
		
		; mov ah, 9				;Display 'Player 1:'
		; mov dx, offset NAME1	
		; int 21h
		
		; call outro
		
		mov dx , 3FDH		; Line Status Register
		AGAIN1:
		In al , dx 			;Read Line Status
  		AND al , 00100000b
  		JZ AGAIN1
		
		mov dx , 3F8H		; Transmit data register
  		mov  ax,01h
  		out dx , ax 
		
		call resetindicators
		mov mode,1h
		call mainscreenui
		ret
		
		reeeeet:
		ret
checkinvites endp

sendpaddlesize proc
		
		mov dx , 3FDH		; Line Status Register
		AGAIN2:
		In al , dx 			;Read Line Status
  		AND al , 00100000b
  		JZ AGAIN2
		
		mov dx , 3F8H		; Transmit data register
  		mov  al,playersize
		mov ah,00
  		out dx , ax 
		
		ret
sendpaddlesize endp

sendballspeed proc
		
		mov dx , 3FDH		; Line Status Register
		AGAIN3:
		In al , dx 			;Read Line Status
  		AND al , 00100000b
  		JZ AGAIN3
		
		mov dx , 3F8H		; Transmit data register
  		mov  ax,ballspeed
  		out dx , ax
		
		
		mov dx , 3FDH		; Line Status Register
		AGAIN4:
		In al , dx 			;Read Line Status
  		AND al , 00100000b
  		JZ AGAIN4
		
		mov dx , 3F8H		; Transmit data register
  		mov  ax,ballspeed+1
  		out dx , ax
		
		ret
sendballspeed endp

checkchatinv proc
		
		cmp recievedchatinv,1			;check if recieved inv
		je startchat
		
		mov mode,1h						;if not recieved then remain in mainscreen
		ret
		
		startchat:						;if recieved then start chat
		mov mode,2h
		ret
checkchatinv endp

checkgameinv proc
		
		cmp recievedgameinv,1			;check if recieved inv
		je startgame
		
		mov mode,1h						;if not recieved then remain in mainscreen
		ret
		
		startgame:						;if recieved then start chat
		;he started the game here
		mov mode,3h
		call showwaitmessage
		call recievepaddlesize
		cmp mode,1h
		je retere
		; mov mode,3h
		call recieveballspeed
		cmp mode,1h
		je retere
		mov mode,3h
		retere:	
		call clearinputbuffer
		call resetindicators
		ret
checkgameinv endp

recievepaddlesize proc
		
		mov dx , 3FDH		; Line Status Register
		CHKmc:
		in al , dx 
  		AND al , 1
  		JZ CHKmc
		
		mov dx , 03F8H
  		in ax , dx 
  		
		cmp al,01h
		je gamecanceled
		
		mov playersize,al
		ret
		gamecanceled:
		
		mov mode,1h
		ret
recievepaddlesize endp

recieveballspeed proc
		
		
		mov dx , 3FDH		; Line Status Register
		CHK1:
		in al , dx 
  		AND al , 1
  		JZ CHK1
		
		mov dx , 03F8H
  		in ax , dx 
		
		cmp al,01h
		je gamecancelled
		
		mov ballspeed,ax
		
		mov dx , 3FDH		; Line Status Register
		CHK2:
		in al , dx 
  		AND al , 1
  		JZ CHK2
		
		mov dx , 03F8H
  		in ax , dx 
		mov ballspeed+1,ax
		mov mode,3
		ret
		
		gamecancelled:
		
		mov mode,1h
		ret
recieveballspeed endp

sendchatinv proc
		
		mov readytochat,1
		mov dx , 3FDH		; Line Status Register
AGAIN5:  	In al , dx 			;Read Line Status
  		AND al , 00100000b
  		JZ AGAIN5
		
		mov dx , 3F8H		; Transmit data register
  		mov  al,3bh
  		out dx , al 
		call drawnotification
		
		ret
sendchatinv endp

sendgameinv proc

		mov readytogame,1
		mov dx , 3FDH		; Line Status Register
AGAIN:  	In al , dx 			;Read Line Status
  		AND al , 00100000b
  		JZ AGAIN
		
		mov dx , 3F8H		; Transmit data register
  		mov  al,3ch
  		out dx , al 
		call drawnotification
		
		ret
sendgameinv endp