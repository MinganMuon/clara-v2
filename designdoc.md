# Designing Clara

UIs:
----
Game UI: allows the user to play against a selected group of AI's
AI testing UI: allows the user to pit AIs against each other and analyze the results
AI statistics/info UI: allows the user to get info about the AIs and statistics from previous AI-AI matches
AI training UI: allows the user to train trainable AI types

Game logic:
-----------
Game state class: Holds a game state:
		  - board
		  - who's turn it is
		  - a list of previous moves
		  - possibly other things like how many moves since the last capture and similar stuff
		  Also contains functions to determine:
		  - if the board represents a winning situation
		  - other things like that
Board class: Holds a board state; see the board representation section for details
             Also contains functions to do things like count the pieces on the board and similar stuff
Move generation subsystem: Generates the possible moves/jumps that a particular piece can take on a particular board

Roadmap:
--------

- Get the game UI, all the game logic, and a simple AI that moves randomly set up and tested
- Plan out all the AI stuff

