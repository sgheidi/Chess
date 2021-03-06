# ♚ PyChess

Full-featured Chess game written using Python.

## Screenshots

<img src="media/screenshots/3r.png" alt="Screenshot 1" width="250"/>&nbsp; &nbsp; &nbsp;
<img src="media/screenshots/2rr.png" alt="Screenshot 2" width="250"/>

## How to play

To set up: clone repo & run ```pip install -r requirements.txt```
To run: run ```py chess.py```.

## Features
- Chess AI which uses minimax & alpha-beta pruning to search the game tree and find the best move (current AI ELO is around ~1000 because of the weak eval function)
- Player vs. Player, Player vs. AI, even AI vs. AI!
- Pinning pieces
- Checking, checkmating
- En passant
- Castling
- Pawn promotion
- Movement animation
- Draw by:
  - Stalemate
  - Insufficient material
  - 3-fold repetition
  - 50-move rule

## Command-line switches
Default playing mode is Player vs. Player. To play a different mode (vs. AI), use the following switches:
- ```--black``` to play as Black.
- ```--white``` to play as White.
- ```--ai-vs-ai``` to watch 2 AI's battle it out!

## Bonus: AI vs. itself
(**AI evaluation functions in progress**) <br /><br />
<img src="media/old/out.gif" alt="AI vs. itself" width="320"/>
