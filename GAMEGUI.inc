.code

UPDATEGAMEGUI	proc
		
		cmp serving,0		;when not serving this proc controls movement of the ball, player movement moves the ball when serving
		jne servingrn
		call DELAY
		call clearoldball	;this just draws a black square on old ball effectively hiding it
		call MOVEBALL
		cmp mode,3
		jne servingrn
		call drawball
		servingrn:
		RET
UPDATEGAMEGUI endp
;================================================;
initializegame proc			;this proc will only be called if one of the players is serving
		
		call clearoldplayer1
		call clearoldplayer2
		call clearoldball
		
		call resetplayers
		call resetball
		
		call drawball
		call drawplayer1
		call drawplayer2
		
		ret
initializegame	endp
;================================================;
drawoutline proc		;this proc draws the horizontal lines that divide the screen in game mode

		call writeplayernames
		
		mov bh,00
		mov AH,0CH			;draw pixel int condition
		mov al,0Fh          ;set the white colour
		
		mov dx,2         
		outl12:
			mov cx,04
			outl11:
				int 10h
				inc cx
				cmp cx,636
			jne outl11
			inc dx
			cmp dx,3
		jne outl12
		
		
		mov dx,158         
		outl22:
			mov cx,04          
			outl21:
				int 10h
				inc cx
				cmp cx,636
			jne outl21
			inc dx
			cmp dx,159
		jne outl22
		
		mov dx,168         
		outl32:
			mov cx,04          
			outl31:
				int 10h
				inc cx
				cmp cx,636
			jne outl31
			inc dx
			cmp dx,169
		jne outl32
		
		mov dx,190         
		outl42:
			mov cx,04         
			outl41:
				int 10h
				inc cx
				cmp cx,636
			jne outl41
			inc dx
			cmp dx,191
		jne outl42
		
		ret
drawoutline endp
;================================================;
writeplayernames proc

		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1401h             ;a5er el screen
		int 10h
		
		mov ah,09
		mov dx,offset PLAYER1NAME+2 
		int 21h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1401h             ;a5er el screen
		add dl,player1name+1	 ;add playername length
		int 10h
		
		mov ah,09
		mov dx,offset score		 ;write "'s score" after playername
		int 21h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1401h            	
		add dl,player1name+1
		add dl,9
		int 10h
		
		mov ah,2                 ;move cursor at desired destination
		mov bh,0
		mov dx,1401h             ;a5ar el screen
		add dl,player1name+1
		add dl,09h               ;add length of score to cursor
		int 10h
		
		mov ah,02
		mov dl, player1score	;then write the score after adding all that
		int 21h
		;repeat the same procedure for player 2
		mov dx,144Fh             
		sub dx,0Ah
		sub dl,player2name+1
		mov ah,2                 
		mov bh,0
		int 10h
		
		mov ah,09
		mov dx,offset PLAYER2NAME+2 
		int 21h
		
		mov ah,2                
		mov bh,0
		mov dx,144Fh             
		sub dx,0Ah
		int 10h
		
		mov ah,09
		mov dx,offset score
		int 21h
		
		mov ah,2                
		mov bh,0
		mov dx,144Eh             
		int 10h
		
		mov ah,02
		mov dl, player2score
		int 21h
		
		mov bh,0
		mov ah,2          		
		mov dx,181Bh      		
		int 10h           		
		
		mov ah,9	      		;Display 'To end the program press ESC'
		mov dx,offset ESCTOPAUSE                  
		int 21h
		
		ret
writeplayernames endp
;================================================;
resetplayers proc

		mov player1pos,80				;move players to midscreen ,then sub half the paddle size to make half at midscreen
		mov player2pos,80
		mov ah,playersize
		shr ah,1
		sub player1pos,ah
		sub player2pos,ah
		
		ret
resetplayers endp
;================================================;
resetball proc

		mov ballpos+2,78
		cmp serving,1
		jne p2serveing
		mov ballpos,19
		ret
		p2serveing:
		mov ballpos,612	
		ret
resetball endp
;================================================;
DELAY PROC						;WAITS 5 SECONDS AFTER THE SPLASHSCREEN AND IT WORKS!!!!!!

		MOV AH,86H
		MOV DX,DELAYSPEED			;0.5 SECONDS IN HEXA IS 4B40 SO PUT IT IN CX:BX
		MOV CX,0000H
		INT 15H
		
		RET
DELAY ENDP
;================================================;
RANDBALLDIR proc
		
		MOV AH,00H
		INT 1AH				;now cx:dx holds number of clock ticks since midnight
		
		MOV AL,DL
		MOV CL,3
		DIV CL				;now ah has the remainder of the division
		
		CMP AH,0
		JE	ANGLE45
		
		CMP AH,1
		JE	ANGLE0
		
		CMP AH,2
		JE	ANGLENEG45
		
		ANGLE45:
		CALL SETANGLE45
		RET
		
		ANGLE0:
		CALL SETANGLE0
		RET
		
		ANGLENEG45:
		CALL SETANGLENEG45
		RET
		
RANDBALLDIR endp
;================================================;
SETANGLE30	PROC
		
		MOV BALLSPEED,6
		MOV BALLSPEED+2,1
		mov SPEEDINCREMENTS+2,1111111111111111b			;WE CAN'T NEGATE BALLSPEED BECAUSE IT IS USED IN A LOOP
		
		RET
SETANGLE30	ENDP
;================================================;
SETANGLE45	PROC
		
		MOV BALLSPEED,6
		MOV BALLSPEED+2,2
		mov SPEEDINCREMENTS+2,1111111111111111b			;WE CAN'T NEGATE BALLSPEED BECAUSE IT IS USED IN A LOOP
		
		RET
SETANGLE45	ENDP
;================================================;
SETANGLE0	PROC
		
		MOV BALLSPEED,6
		MOV BALLSPEED+2,0
		
		RET
SETANGLE0	ENDP
;================================================;
SETANGLENEG45	PROC
		
		MOV BALLSPEED,6
		MOV BALLSPEED+2,2
		mov SPEEDINCREMENTS+2,01h			;WE CAN'T NEGATE BALLSPEED BECAUSE IT IS USED IN A LOOP
		
		RET
SETANGLENEG45	ENDP
;================================================;
SETANGLENEG30	PROC
		
		MOV BALLSPEED,6
		MOV BALLSPEED+2,1
		mov SPEEDINCREMENTS+2,01h			;WE CAN'T NEGATE BALLSPEED BECAUSE IT IS USED IN A LOOP
		
		RET
SETANGLENEG30	ENDP
;================================================;
MOVEBALL	PROC					;repeats adding or subtracting ones to ballpos for ballspeed number of times, this ensures ball passing each pixel
		
		mov cx,ballspeed
		cmp cx,0
		je zeroxspeed
		forx:
			call moveballx			;this function sets the ball pos if any player scored
			cmp serving,0			;so we check if any player scored and skip changing ballpos any further
			jne zeroyspeed
		loop forx
		zeroxspeed:
		mov cx,ballspeed+2			
		cmp cx,0
		je zeroyspeed
		fory:
			call movebally
		loop fory
		zeroyspeed:				
		ret
MOVEBALL ENDP
;================================================;
moveballx proc
		
		mov bx,speedincrements
		ADD BALLPOS,bx				;move ball
		
		CALL CHECKPLAYER1COLLISION	;then check for collision with paddles
		call CHECKPLAYER2COLLISION
		
		cmp BALLPOS,625				;then check for scoring points
		Je	p1scored				
		cmp BALLPOS,5		
		Je	p2scored				
		
		ret
		
		p1scored:
		call player1scored
		RET
		
		p2scored:
		call player2scored
		RET
moveballx endp
;================================================;
player1scored PROC					;handles scoring of player 1

		INC PLAYER1SCORE
		CMP PLAYER1SCORE,35H
		JE PLAYER1WIN
		MOV SERVING,2
		
		CALL INITIALIZEGAME
		call updatescores
		RET
		
		PLAYER1WIN:
		mov player1score,30H
		mov player2score,30H
		CALL PLAYER1WON
		RET
		
player1scored ENDP
;================================================;
updatescores proc					;updates scores of both players

		mov ah,2                
		mov bh,0
		mov dx,1401h            
		add dl,player1name+1
		add dl,09h             
		int 10h
		
		;player 1
		mov dl, player1score
		int 21h
		
		mov bh,0
		mov dx,144Eh             
		int 10h
		;player2
		mov dl, player2score
		int 21h
		
		
		ret
updatescores endp
;================================================;
player2scored PROC					;handles scoring of player 1

		INC PLAYER2SCORE
		CMP PLAYER2SCORE,35H
		JE PLAYER2WIN
		MOV SERVING,1
		
		CALL INITIALIZEGAME
		call updatescores
		RET
		
		PLAYER2WIN:
		mov player1score,30H
		mov player2score,30H
		CALL PLAYER2WON
		RET
		
player2scored ENDP
;================================================;
movebally proc
		
		MOV AX,speedincrements+2
		ADD BALLPOS+2,AX
		
		cmp BALLPOS+2,153
		JG	NEGATE_Y
		cmp BALLPOS+2,4
		JL	NEGATE_Y
		RET
		
		NEGATE_Y:
		NEG speedincrements+2
		RET
movebally endp
;================================================;
CHECKPLAYER1COLLISION PROC

		
		CMP	BALLPOS,18				;moving ballpos+2 to bx then comparing bl and bh is alot faster you should do it to not lag
		JNE RETUR	
		mov di,ballpos+2
		mov bh,0
		mov bl,player1pos
		sub bl,4
		cmp di,bx
		jb retur
		add bl,4
		mov ah,0
		mov al,playersize
		add bl,al
		cmp di,bx					;this means the ball is bellow the paddle
		ja retur
		NEG speedincrements
		call checkangle			;a proc that makes dl 1 if angle -45, 2 if -30 or 30,3 if 0,4 if 45
		mov cl,3
		div cl
		;now al has the third of the player size,
		sub bl,al
		sub bl,2
		cmp di,bx
		ja atlastthird
		sub bl,al
		cmp di,bx
		jb atfirstthird
		ret
		
		atfirstthird:
		cmp dl,3
		jne atlastthird			;we just want to jump to other angles logic, i could've made another label but it would be same position as atlastthird
		call setangleneg45
		ret
		
		atlastthird:
		cmp dl,1
		jne notneg45
		call setangle30
		ret
		notneg45:
		cmp dl,2
		jne notneg30or30
		call setangle0
		ret
		notneg30or30:
		cmp dl,3
		jne not0
		call setangle45
		ret
		not0:
		call setangleneg30			;this is the case for angle 45=>-30
		ret
		
		RETUR:
		RET
CHECKPLAYER1COLLISION ENDP
;================================================;
checkangle proc

		cmp ballspeed+2,0h				;if angle is zero y velocity is 0
		je zero
		cmp ballspeed+2,1				;if angle is 30 y velocity is 1
		je thirty
		cmp speedincrements+2,1			;if it is not 30 or 0 then it is 45
		je fortyfive					;but how to differentiate b/w 45 & -45
		mov dl,1						;by y increments
		ret
		zero:
		mov dl,3
		ret
		thirty:
		mov dl,2
		ret
		fortyfive:
		mov dl,4
		ret
checkangle endp
;================================================;
CHECKPLAYER2COLLISION PROC

		CMP	BALLPOS,613				;moving ballpos+2 to bx then comparing bl and bh is alot faster you should do it to not lag
		JNE RETUR2	
		mov di,ballpos+2
		mov bh,0
		mov bl,player2pos
		sub bl,4
		cmp di,bx
		jb retur2
		add bl,4
		mov ah,0
		mov al,playersize
		add bl,al
		cmp di,bx					;this means the ball is bellow the paddle
		ja retur2
		NEG speedincrements
		call checkangle				;a proc that makes dl 1 if angle -45, 2 if -30 or 30,3 if 0,4 if 45
		mov cl,3
		div cl
		;now al has the third of the player size,
		sub bl,al
		sub bl,2
		cmp di,bx
		ja atlastthird2
		sub bl,al
		cmp di,bx
		jb atfirstthird2
		ret
		
		atfirstthird2:
		cmp dl,3
		jne atlastthird2			;we just want to jump to other angles logic, i could've made another label but it would be same position as atlastthird
		call setangleneg45
		ret
		
		atlastthird2:
		cmp dl,1
		jne not2neg45
		call setangle30
		ret
		not2neg45:
		cmp dl,2
		jne not2neg30or30
		call setangle0
		ret
		not2neg30or30:
		cmp dl,3
		jne not20
		call setangle45
		ret
		not20:
		call setangleneg30		;this is the case for angle 45=>-30
		ret
		
		RETUR2:
		RET
CHECKPLAYER2COLLISION ENDP
;================================================;
clearoldball PROC		;same as drawball but draws in black color
		
		MOV AL,0
		MOV AH,0CH
		mov bH,0
		
		MOV SI,BALLPOS
		mov bp,si
		MOV DI,BALLPOS+2
		MOV DX,DI
		ADD SI,8
		ADD DI,4
		W_OLD:
			mov cX,bp
			
			L_OLD:
				INT 10H
				INC CX
				CMP CX,SI
			JNZ L_OLD
			INC DX
			CMP DX,DI
		JNZ W_OLD
		
		RET
clearoldball ENDP
;================================================;
drawball PROC
		
		MOV AL,0Eh
		MOV AH,0CH
		mov bH,0
		
		MOV SI,BALLPOS
		mov bp,si
		MOV DI,BALLPOS+2
		MOV DX,DI
		ADD SI,8		;x distance of ball
		ADD DI,4		;y distance of ball, they aren't the same due to 640x200 resolution
		Wball:
			mov cX,bp
			
			Lball:
				INT 10H
				INC CX
				CMP CX,SI
			JNZ Lball
			INC DX
			CMP DX,DI
		JNZ Wball

		RET
DRAWBALL ENDP
;================================================;
clearoldplayer1 proc			;draws player in black

		MOV AL,0			
		MOV AH,0CH			
		
		MOV BH,player1pos
		ADD BH,PLAYERSIZE			;this is the height which the player starts from player1pos and adds playersize
		
		MOV DH,0
		MOV DL,player1pos
		Widtold:
			MOV CX,0009H
			
			Linold:
				push bx
				mov bh,0
				INT 10H
				pop bx
				INC CX
				CMP CL,18			;width of player is 18-9	
			JNZ Linold
			INC DX
			CMP DL,BH				;bh contains the y position where the player ends at
		JNZ Widtold
		;all draw player funciton work in the same way
		ret
clearoldplayer1 endp
;================================================;
drawplayer1 proc	
		
		MOV AL,9				;color of player 1 is light blue
		MOV AH,0CH				;interrupt condition
		
		MOV BH,player1pos
		ADD BH,PLAYERSIZE			;this is the height which the player starts from player1pos and adds playersize
		
		MOV DH,0
		MOV DL,player1pos
		Widt:
			MOV CX,0009
			
			Lin:
				push bx
				mov bh,0
				INT 10H
				pop bx
				INC CX
				CMP CL,18		;width of the player is 0EH - 0009H
			JNZ Lin
			INC DX
			CMP DL,BH
		JNZ Widt
		
		RET
drawplayer1	endp
;================================================;
clearoldplayer2 proc		;draws player in black

		MOV AL,0			
		MOV AH,0CH			
		
		MOV BH,player2pos
		ADD BH,PLAYERSIZE			;this is the height of the player starts from player1pos and adds 20
		
		MOV DH,0
		MOV DL,player2pos
		Widtold2:
			MOV CX,621
			
			Linold2:
				push bx
				mov bh,0
				INT 10H
				pop bx
				INC CX
				CMP CX,630 		
			JNZ Linold2
			INC DX
			CMP DL,BH
		JNZ Widtold2
		
		ret
clearoldplayer2 endp
;================================================;
drawplayer2 proc	
		
		MOV AL,4				;color of player 2 is red
		MOV AH,0CH				;interrupt condition
		
		MOV DH,0
		MOV DL,player2pos
		
		MOV BH,DL
		ADD BH,PLAYERSIZE			
		
		Widt2:
			MOV CX,621
			
			Lin2:
				push bx
				mov bh,0
				INT 10H
				pop bx
				INC CX
				CMP CX,630		
			JNZ Lin2
			INC DX
			CMP DL,BH
		JNZ Widt2
		
		RET
drawplayer2	endp
;================================================;
drawgamepausedtext proc
		
		mov bh,0
		mov ah,2          		;Move Cursor to upper middle of screen
		mov dx,0A21h      		
		int 10h           		
		
		mov ah, 9				;Display PAUSEDSTRING
		mov dx, offset PAUSEDSTRING	
		int 21h 
		
		mov bh,0
		mov ah,2          		;Move Cursor to lower middle of screen
		mov dx,0B1Ah      		
		int 10h           		

		mov ah, 9				;Display PAUSEDSPACE
		mov dx, offset PAUSEDSPACE	
		int 21h 
		
		mov bh,0
		mov ah,2          		;Move Cursor, to middle of screen
		mov dx,0C1Ah      		
		int 10h           		
		
		mov ah,9	      		;Display PAUSEDESCAPE
		mov dx,offset PAUSEDESCAPE                  
		int 21h
		
		ret
drawgamepausedtext endp
;================================================;
cleargamepausedtext proc
		
		MOV AL,0			;draw black rectangle over text
		MOV AH,0CH			;interrupt condition
		MOV BH,0
		MOV DX,50H
		CLEARWtext:
			MOV CX,0D0H
			
			CLEARtextl:
				INT 10H
				INC CX
				CMP CX,1C0H	
			JNZ CLEARtextl
			INC DX
			CMP Dx,6CH
		JNZ CLEARWtext
		
		ret
cleargamepausedtext endp
;================================================;
drawgamepausedsign proc
		
		MOV AL,0DH			;draw magenta rectangle
		MOV AH,0CH			;interrupt condition
		MOV BH,0
		MOV DX,34
		firstw:
			MOV CX,280
			
			firstl:
				INT 10H
				INC CX
				CMP CX,360	
			JNZ firstl
			INC DX
			CMP Dx,35
		JNZ firstw
		
		MOV DX,74
		secondw:
			MOV CX,280
			
			secondl:
				INT 10H
				INC CX
				CMP CX,360	
			JNZ secondl
			INC DX
			CMP Dx,75
		JNZ secondw	
		
		MOV DX,35
		thirdw:
			MOV CX,280
			
			thirdl:
				INT 10H
				INC CX
				CMP CX,281	
			JNZ thirdl
			INC DX
			CMP Dx,75
		JNZ thirdw	
		
		MOV DX,35
		fourthw:
			MOV CX,359
			
			fourthl:
				INT 10H
				INC CX
				CMP CX,360	
			JNZ fourthl
			INC DX
			CMP Dx,75
		JNZ fourthw
		
		
		MOV AL,0FH			;draw white rectangle
		MOV DX,40
		wpause:
			MOV CX,295
			
			lpause:
				INT 10H
				INC CX
				CMP CX,315		
			JNZ lpause
			INC DX
			CMP Dx,70
		JNZ wpause		
		
		MOV DX,40
		w2pause:
			MOV CX,325
			
			l2pause:
				INT 10H
				INC CX
				CMP CX,345		
			JNZ l2pause
			INC DX
			CMP Dx,70
		JNZ w2pause
		
		ret
drawgamepausedsign endp
;================================================;
cleargamepausedsign proc
		
		MOV AL,0			;draw black rectangle over sign
		MOV AH,0CH			;interrupt condition
		MOV BH,0
		MOV DX,34
		Widtext:
			MOV CX,280
			
			textl:
				INT 10H
				INC CX
				CMP CX,360	
			JNZ textl
			INC DX
			CMP Dx,75
		JNZ Widtext

		RET		
cleargamepausedsign endp
;================================================;
GETPADDLESIZE proc
		MOV AH,0			;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,0EH			;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H	
		
		call clearinputbuffer
		mov bh,0
		mov ah,2          		;Move Cursor to lower middle of screen
		mov dx,0B1Ch      		
		int 10h           		

		mov ah, 9				
		mov dx, offset CHOOSEPADDLESIZE	
		int 21h 
		
		mov bh,0
		mov ah,2          		;Move Cursor, to middle of screen
		mov dx,0D17h      		
		int 10h           		
		
		mov ah,9	      		
		mov dx,offset PADDLECHOICES                  
		int 21h
		
		mov bh,0
		mov ah,2          		;Move Cursor, to middle of screen
		mov dx,181Ah      		
		int 10h           		
		
		mov ah,9	      		;Display 'To end the program press ESC'
		mov dx,offset PAUSEDESCAPE                  
		int 21h
		
		GETPADDLE:
		
		MOV AH,0			;GET KEY INPUT
		INT 16H
		
		CMP AL,31H			;CMP WITH 1
		JZ SIZESMALL
		
		CMP AL,32H			;CMP WITH 2
		JZ SIZEMEDIUM
		
		CMP AL,33H			;CMP WITH 3
		JZ SIZELARGE
		
		CMP AH,01H			;CMP WITH esc
		JZ TOMAINMENU
		
		JMP GETPADDLE
		
		SIZESMALL:					
		MOV PLAYERSIZE,25
		mov mode,3h
		RET
		
		SIZEMEDIUM:					
		MOV PLAYERSIZE,35
		mov mode,3h
		RET
		
		SIZELARGE:					
		MOV PLAYERSIZE,45
		mov mode,3h
		RET
		
		TOMAINMENU:					
		MOV MODE,1H
		RET
		
GETPADDLESIZE endp
;================================================;
GETBALLSPEED proc
		MOV AH,0			;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,0EH			;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H	
		
		call clearinputbuffer
		mov bh,0
		mov ah,2          		;Move Cursor to lower middle of screen
		mov dx,0B1Ch      		
		int 10h           		

		mov ah, 9				
		mov dx, offset CHOOSEBALLSPEED	
		int 21h 
		
		mov bh,0
		mov ah,2          		;Move Cursor, to middle of screen
		mov dx,0D13h      		
		int 10h           		
		
		mov ah,9	      		
		mov dx,offset BALLCHOICES                  
		int 21h
		
		mov bh,0
		mov ah,2          		;Move Cursor, to middle of screen
		mov dx,181Ah      		
		int 10h           		
		
		mov ah,9	      		;Display 'To end the program press ESC'
		mov dx,offset PAUSEDESCAPE                  
		int 21h
		
		GETSPEED:
		
		MOV AH,0			;GET KEY INPUT
		INT 16H
		
		CMP AL,31H			;CMP WITH 1
		JZ SLOW
		
		CMP AL,32H			;CMP WITH 2
		JZ MEDUIM
		
		CMP AL,33H			;CMP WITH 3
		JZ FAST
		
		CMP AL,34H			;CMP WITH 3
		JZ INSANE
		
		CMP AH,01H			;CMP WITH 3
		JZ TOMENU
		
		JMP GETSPEED
		
		SLOW:					
		MOV DELAYSPEED,511BH
		mov mode,3h
		RET
		
		MEDUIM:					
		MOV DELAYSPEED,411BH
		mov mode,3h
		RET
		
		FAST:					
		MOV DELAYSPEED,311BH
		mov mode,3h
		RET
		
		INSANE:					
		MOV DELAYSPEED,211BH
		mov mode,3h
		RET
		
		TOMENU:					
		MOV MODE,1H
		RET
		
		
GETBALLSPEED endp
;================================================;
