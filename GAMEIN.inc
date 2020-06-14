.code

gameinput proc
		
		
		MOV AH,86H
		MOV DX,80h			;0.5 SECONDS IN HEXA IS 4B40 SO PUT IT IN CX,BX
		MOV CX,0000H		;this fixes some stuttering issues
		INT 15H
		
		
		mov ah,1			;get key input
		int 16h				;this checks the keyboard buffer and clears zf if a key is pressed
		
		jz return			;if zf is set this means there is no input and buffer is empty
		
		cmp al,77H			;cmp with W key
		jz W 
		
		cmp al,73H			;cmp with S key
		jz S
		
		cmp ah,48H			;cmp with Up arrow
		jz Uparrow
		
		cmp ah,50H			;cmp with Dn arrow
		jz Downarrow
		
		cmp ah,01H			;cmp with esc
		jz escapegame
		
		cmp serving,0
		je notserving
		cmp ah,39H			;cmp with space when serving
		jz served
		notserving:
		
		cmp aL,35H			;cmp with 5 THIS IS FOR TESTING AND SHOULD BE REMOVED
		jz QUITT
		
		
		;if the user pressed a key other than esc,w,s clear the buffer
		call clearinputbuffer
		ret
		
		W:							;Up arrow is pressed
		call Upplayer1
		ret
		
		S:							;Down arrow is pressed
		call Downplayer1
		ret
		
		Uparrow:					;Up arrow is pressed
		call Upplayer2
		ret
		
		Downarrow:					;Down arrow is pressed
		call Downplayer2
		ret
		
		escapegame:
		call pausegame
		ret
		
		served:
		mov serving,0
		call randballdir
		call clearinputbuffer
		ret
		
		QUITT:
		mov ah,0				;change to text mode
		mov al,03h
		int 10h
		mov ax,4c00h
		int 21h
		
		return:
		call clearinputbuffer
		ret
gameinput endp
;================================================;
Upplayer1 proc
		
		
		
		call clearinputbuffer
		cmp player1pos,4
		je	retup1
		mov bl, player1pos
		sub bl,playerspeed
		cmp bl,4
		JAE SKIPUP1
		MOV bl,4
		SKIPUP1:
		call clearoldplayer1
		mov player1pos,bl
		call drawplayer1
		
		
		cmp serving,1
		jne p1notservingux
		call clearoldball	;this just draws a black square on old ball effectively hiding it
		
		mov ballpos,19		;setting ball x pos if p1 is serving
		
		
		mov ah,0						;setting ball y pos if p1 is serving
		mov al,playersize
		shr al,1						;divide playersize by 2 then add playerpos to get midpoint of the paddle
		add al,player1pos
		sub al,2						;to make center of the ball at center of paddle
		mov ballpos+2,ax
		
		
		call drawball
		p1notservingux:
		
		retup1:
		ret
Upplayer1 endp
;================================================;
Downplayer1 proc
		
		call clearinputbuffer
		MOV bl,157
		SUB bl,PLAYERSIZE
		cmp player1pos,bl				;check if already at max y pos if at max just clear buffer and return
		je retdn1
		call clearoldplayer1			;erase old player
		mov al, player1pos
		add al,PLAYERSPEED
		cmp AL,bl						;compare that if after adding speed pos surpasses boundaries
		JB	SKIPDOWN1
		MOV AL,bl						;if it surpasses then set pos to 180
		SKIPDOWN1:
		mov player1pos,al				;al is either the new position if doesn't surpass boudaries or 180 if it surpasses
		call drawplayer1 
		
		cmp serving,1
		jne p1notservingd
		call clearoldball				;this just draws a black square on old ball effectively hiding it
		
		mov ballpos,19					;setting ball x pos if p1 is serving
		
		
		mov ah,0						;setting ball y pos if p1 is serving
		mov al,playersize
		shr al,1						;divide playersize by 2 then add playerpos to get midpoint of the paddle
		add al,player1pos
		sub al,2						;to make center of the ball at center of paddle
		mov ballpos+2,ax
		
		call drawball
		p1notservingd:
		
		retdn1:
		ret
Downplayer1 endp
;================================================;
Upplayer2 proc

		call clearinputbuffer
		cmp player2pos,4
		je	retup2
		mov bl, player2pos
		sub bl,playerspeed
		cmp bl,4
		JAE SKIPUP2
		MOV bl,4
		SKIPUP2:
		call clearoldplayer2
		mov player2pos,bl
		call drawplayer2
		
		cmp serving,2
		jne p2notservingu
		call clearoldball			;this just draws a black square on old ball effectively hiding it
		
		mov ballpos,612				;setting ball x pos if p1 is serving
		
		mov ah,0					;setting ball y pos if p1 is serving
		mov al,playersize
		shr al,1					;divide playersize by 2 then add playerpos to get midpoint of the paddle
		add al,player2pos
		sub al,2					;to make center of the ball at center of paddle
		mov ballpos+2,ax
		
		call drawball
		p2notservingu:
		
		retup2:
		ret
Upplayer2 endp
;================================================;
Downplayer2 proc
		
		call clearinputbuffer
		MOV bl,157
		SUB bl,PLAYERSIZE
		cmp player2pos,bl				;check if already at max y pos if at max just clear buffer and return
		je retdn2
		call clearoldplayer2			;erase old player
		mov al, player2pos
		add al,PLAYERSPEED
		cmp AL,bl						;compare that if after adding speed pos surpasses boundaries
		JB	SKIPDOWN2
		MOV AL,bl						;if it surpasses then set pos to 180
		SKIPDOWN2:
		mov player2pos,al				;al is either the new position if doesn't surpass boudaries or 180 if it surpasses
		call drawplayer2 
		
		cmp serving,2
		jne p2notservingd
		call clearoldball			;this just draws a black square on old ball effectively hiding it
		
		mov ballpos,612				;setting ball x pos if p1 is serving
		
		mov ah,0					;setting ball y pos if p1 is serving
		mov al,playersize
		shr al,1					;divide playersize by 2 then add playerpos to get midpoint of the paddle
		add al,player2pos
		sub al,2					;to make center of the ball at center of paddle
		mov ballpos+2,ax
		
		call drawball
		p2notservingd:
		retdn2:
		ret
Downplayer2 endp
;================================================;
pausegame	proc
		
		call clearinputbuffer			;buffer will still have escape if not cleared
		call drawgamepausedsign
		call drawgamepausedtext
		paused:
		
		mov ah,0			;get key input
		int 16h
		
		cmp ah,39h			;cmp with space
		jz space
	
		cmp ah,01h			;cmp with esc
		jz quit
		
		jmp paused
		
		space:
		call cleargamepausedtext
		call cleargamepausedsign
		ret
		
		quit:
		MOV AH,0			;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,0EH			;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H
		mov mode,1h
		mov serving,1
		mov player1score,30H
		mov player2score,30H
		call resetindicators
		ret
		
pausegame endp
;================================================;
PLAYER1WON proc

		MOV AH,0					;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,0EH					;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H	
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dx,0A1Ah      		
		int 10h   
		
		mov ah, 9					;Display player1name
		mov dx, offset player1name+2	
		int 21h 
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dx,0A1Ah
		add dl,player1name+1
		int 10h 
		
		mov ah, 9					;Display 'WINS!!!!!'
		mov dx, offset PLAYERWONSTRING	
		int 21h 
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dx,0C1Ah      		
		int 10h           		
		
		mov ah, 9					;Display 'Press ESC to exit the game'
		mov dx, offset WONESC	
		int 21h 
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dx,0D1Ah      		
		int 10h           		
		
		mov ah, 9					;Display 'Press SPACE to go to main menu'
		mov dx, offset WONSPACE	
		int 21h 
		
		GAMEOVER1:
		
		mov ah,0			;get key input
		int 16h
		
		cmp ah,39h			;cmp with space
		jz WON1SPACE
	
		cmp ah,01h			;cmp with esc
		jz WON1QUIT
		
		jmp GAMEOVER1
		
		WON1SPACE:
		mov serving,1
		call mainscreenui
		MOV MODE,1H
		call resetindicators		
		ret
		
		WON1QUIT:
		CALL OUTRO
		RET
		
PLAYER1WON endp
;================================================;
PLAYER2WON proc

		MOV AH,0					;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,0EH					;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H	
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dx,0A1Ah      		
		int 10h           		
		
		mov ah, 9					;Display player2name
		mov dx, offset player2name+2	
		int 21h 
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dx,0A1Ah
		add dl,player2name+1
		int 10h 
		
		mov ah, 9					;Display 'WINS!!!!!'
		mov dx, offset PLAYERWONSTRING	
		int 21h 
		
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dx,0C1Ah      		
		int 10h           		
		
		mov ah, 9					;Display 'Press ESC to exit the game'
		mov dx, offset WONESC	
		int 21h 
		
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dx,0D1Ah      		
		int 10h           		
		
		mov ah, 9					;Display 'Press SPACE to go to main menu'
		mov dx, offset WONSPACE	
		int 21h 
		
		GAMEOVER2:
		
		mov ah,0			;get key input
		int 16h
		
		cmp ah,39h			;cmp with space
		jz WON2SPACE
	
		cmp ah,01h			;cmp with esc
		jz WON2QUIT
		
		jmp GAMEOVER2
		
		WON2SPACE:
		mov serving,1
		call mainscreenui
		MOV MODE,1H
		call resetindicators
		ret
		
		WON2QUIT:
		CALL OUTRO
		RET
		
PLAYER2WON endp
;================================================;