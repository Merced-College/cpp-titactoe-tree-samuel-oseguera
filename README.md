[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=19440033)
# cpp_tictactoe_tree

Question responses:
1. What is the purpose of the minimax function?
The purpose of the minimax function is to evaluate all moves to determine the AIs best next move. This evaluation is based on simulations of future game states. It allows the standard "limitations" present in the original copy of code from the assignment.

2. How does the GameState class represent the tree?
The GameState class represents the tree as a single game state, and recursion builds the game tree by exploring possible moves. The exploring of possible moves is done by recursively applying the makeMove method. 

3. When does the recursion stop in the minimax algorithm?
The recursion will stop in the minimax algorithm when a winner is found or if the board becomes full.