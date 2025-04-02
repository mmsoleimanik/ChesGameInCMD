# chesGameCMD
This game created by C++ and you can run it in powershell or CMD. There are two teams such as real game, but with a little difference: the black team has the color of blue because of CMD is black and black can create many visual problem in black background.
<img src="documents/HowPlay.gif">

## How to play
There is a board that update evry time.The white side is in the top of board and black side is in bottom and the first turn is for white side.
All nuts define betwen [ and ]. All nuts have an unic character,number and color.The character at the beginning of the phrase refers to the role of the nut. The number in phrase refer to the number of same type nut and creates a difference betwen other nuts.

The list of nuts and their abbreviations:
  - "H" refer to "Horse"
  - "R" refer to "Rokh"
  - "S" refer to "Soldier"
  - "K" refer to "King"
  - "M" refer to "Minister"
  - "E" refer to "Elephent"

For playing you should to write an appropriate prompt in game: <br>
Prompt has two section.The first section determines what nut must to move.The first section consists of character and number.The second section determines the target.The first number refer to the row of target and second number refer to the column of target.
For examle the prompt of `H0=>30` means the nut of "H0" should goig to the cell with the row of 3 and the column of 0.
> [!IMPORTANT]
> **All the rules are just like the rules in reality.**
> **In this program, the rules for "check and checkmate" have not yet been develped.**

## Code overveiw
The structure of this game is divided into two main parts: 1. Definition of the nuts  2. Definition of the chessboard.<br>
All nuts definded as struct in C++. <br>
In general, each nuts includes a number, a position, a color, and a function for checking the movements of the nuts. <br> <br>
For example "horse":
```
struct horse {
   int color;
   int place[2];
   int number;

   bool cango(int newplace[2]) {...}
};
```
<br> <br> <br>
> [!TIP]
> The board wrote from top to bottom, so the white soldier should moves to bottom and black soldier should moves to top.The soldiers on both sides move in exactly opposite directions. Therefore, one moves in the positive direction and the other in the negative direction.Thus, we assign the number **+1** to the white group, which moves in the positive direction of the rows,and the number **-1** to the black group, which moves in the negative direction of the rows. Similarly, we assign the numbers **+2** and **-2** respectively to the two kings.
