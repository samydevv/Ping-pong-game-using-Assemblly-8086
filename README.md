# Ping pong game using Assemblly 8086
this Project is a ping pong game using serial communication made in 8086 language

## Requirement to run the game
### 1)

You will need the latest version of [DOSBOX](https://www.dosbox.com/download.php?main=1) and a [virtual serial ports](https://freevirtualserialports.com/)

### 2)

After the installing the DOSBOX and virtual serial ports open the virtual serial ports and it should look like this

![image](https://user-images.githubusercontent.com/44317150/84606033-763f0d00-aea2-11ea-9134-4f49d5c6860f.png)

click on creat local Bridge and this window should appear 

![image](https://user-images.githubusercontent.com/44317150/84606054-a7b7d880-aea2-11ea-8dc7-11d26a9a47be.png)

click creat and it should be created successfully 

![image](https://user-images.githubusercontent.com/44317150/84606076-dfbf1b80-aea2-11ea-9db4-a3aeb22e8df9.png)

### 3)
Now open DOSBOX option and write under the [autoexec] the directory that you will put this files in. In my case it look like this

```
mount D: D:\CUFE\6th_Semester\Team3\Team3
D:\
```
### 4)
Now open DOSBOX twice and write in the first one this code
```
serial1= directserial realport:COM1
```
and for the second one write 
```
serial1= directserial realport:COM2
```
and it should look like this 

![image](https://user-images.githubusercontent.com/44317150/84606179-e0a47d00-aea3-11ea-8a88-af73f82a18fe.png)

### 5) 
Now write Main in both windows and the game should start. Note that if the first user in the first screen write his name the game will not start
unitl the other player in the second screen enter his name.

![image](https://user-images.githubusercontent.com/44317150/84606213-3bd66f80-aea4-11ea-975c-0625bb14951b.png)

waiting for the other player

![image](https://user-images.githubusercontent.com/44317150/84606225-57417a80-aea4-11ea-8666-a5227cf21e64.png)

### 6)
Now you will see the main menu and as it show F1 for chat, F2 for playing the game and esc for closing the game.

![image](https://user-images.githubusercontent.com/44317150/84606236-76d8a300-aea4-11ea-9dbc-2a445fa45e53.png)

## Enter the chat mode
If any of the players click on F1 to enter the chat.The corresponding diamond will change from read to green and will wait for the other 
player to press F1 to enter the chat. As shown here Ziad Press F1 and the dimond color changed to green and he is waiting for me to enter 
the chat.

![image](https://user-images.githubusercontent.com/44317150/84606310-67a62500-aea5-11ea-8a5f-bb5d4b8fc746.png)

After the second player press on F1 the will go automatically to the chat as shown here.

![image](https://user-images.githubusercontent.com/44317150/84606365-e307d680-aea5-11ea-8d80-e58e265c11aa.png)

In the chat room if the player is typing the word will show automatically to the other player on his screen.as shown here.

![image](https://user-images.githubusercontent.com/44317150/84606398-282c0880-aea6-11ea-9baa-3da747e83218.png)

if any of the player press ESC to exit the chat the other player will automatically go to the main menu and close the chat.

## Run the game

Press F2 to play the game and the person who requset to play he will determind the paddle size and speed of the ball.

![image](https://user-images.githubusercontent.com/44317150/84606509-16973080-aea7-11ea-8e34-1eb848a4866e.png)

![image](https://user-images.githubusercontent.com/44317150/84606510-1f880200-aea7-11ea-87ed-a6d271e0f999.png)

Now the player who requsted to play will have the first move.

![image](https://user-images.githubusercontent.com/44317150/84606531-41818480-aea7-11ea-828b-70e7c13b838c.png)

If you want to pause the game press ESC and this main menu should appear.

![image](https://user-images.githubusercontent.com/44317150/84606558-75f54080-aea7-11ea-9dd3-345b1ed141a7.png)

You can return to the game by pressing SPACE or exit the game and go to the main menu by pressing ESC

## Exit the game 

Now if you want to exit the game just press on EsC while you are in the main menu and this screen should appear to you. In my case
i exit the game at the same time for both player.

![image](https://user-images.githubusercontent.com/44317150/84606635-ff0c7780-aea7-11ea-859a-57606a5ebcc5.png)









