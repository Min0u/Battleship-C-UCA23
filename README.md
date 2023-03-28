# Battleship-C-UCA23

AUTHOR: Chloé KHAO (22106244)
DATE: 07-01-2023
GAME: Battleship - Project C

These programs are capable of reading commands from a given file.

Tests 1, 2, and 3 in each directory are to test for errors, and it should exit() if there are any.

The exits of bataille_navale_b1, bataille_navale_b2, and bataille_navale_blv are as follows:
0: Error while opening the file
1: Error while reading the board size
2: Error while placing the ship
3: Command error, unrecognized command
4: Error because the game has started, no more ships can be placed
5: Error because the player is trying to play twice in a row
6: Error because the game has not started, cannot fire
7: Error during firing

The Format_blv2.txt (located in the Failed Format folder) is the same as Format_blv.txt but with an AI playing for player 2. It does not work.

Basic format without comments Format_b1.txt: Successful
To execute, call the program with: ./bataille_navale_b1 (file.txt)

Basic format with comments Format_b2.txt: Successful
To execute, call the program with: ./bataille_navale_b2 (file.txt)

Format with boats of various lengths Format_blv.txt: Successful
To execute, call the program with: ./bataille_navale_blv (file.txt)

Format with movements: Not successful

Format with movements and collisions: Not successful

Format with boat names: Not successful

(expected.txt is just a draft for me to see if the result is correct or not)

CONCLUSION: My project works with the Basic Format (Format 1, 2, 3).
