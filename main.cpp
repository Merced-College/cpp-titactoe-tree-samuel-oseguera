// Samuel Oseguera
// Assignment: Coding: TicTacToe with Trees

#include <iostream>
#include <vector>
#include <limits>
#include <ctime>  // For randomness
#include <cstdlib> // For rand()
using namespace std;

const char EMPTY = ' ';

class GameState {
private:
    vector<char> board; // 9 cells for Tic-Tac-Toe

public:
    GameState() : board(9, EMPTY) {}

    GameState(const vector<char>& b) : board(b) {}
    
    // Prints current board state
    void printBoard() const {
        for (int i = 0; i < 9; ++i) {
            cout << (board[i] == EMPTY ? '-' : board[i]) << " ";
            if ((i + 1) % 3 == 0) cout << endl;
        }
    }

    // Checks if the board is full
    bool isFull() const {
        for (char c : board)
            if (c == EMPTY) return false;
        return true;
    }

    // Checks if the game has ended
    bool isGameOver() const {
        return checkWinner() != EMPTY || isFull();
    }
    
    // Returns the winner if player or AI achieves win
    char checkWinner() const {
        const int winPatterns[8][3] = {
            {0,1,2}, {3,4,5}, {6,7,8},
            {0,3,6}, {1,4,7}, {2,5,8},
            {0,4,8}, {2,4,6}
        };

        for (auto& pattern : winPatterns) {
            if (board[pattern[0]] != EMPTY &&
                board[pattern[0]] == board[pattern[1]] &&
                board[pattern[1]] == board[pattern[2]]) {
                return board[pattern[0]];
            }
        }
        return EMPTY;
    }

    // Returns a list of available moves
    vector<int> getAvailableMoves() const {
        vector<int> moves;
        for (int i = 0; i < 9; ++i)
            if (board[i] == EMPTY) moves.push_back(i);
        return moves;
    }

    // Applies the player's move and returns the new gameState
    GameState makeMove(int index, char player) const {
        vector<char> newBoard = board;
        newBoard[index] = player;
        return GameState(newBoard);
    }

    // Returns current board vector
    const vector<char>& getBoard() const {
        return board;
    }
};

class TicTacToeTree {
public:
    // Pass HUMAN and COMPUTER as parameters now
    int minimax(const GameState& state, bool isMaximizing, char HUMAN, char COMPUTER) { // minimax algorithm for the AI's moves
        char winner = state.checkWinner();
        if (winner == COMPUTER) return 1;
        if (winner == HUMAN) return -1;
        if (state.isFull()) return 0;

        if (isMaximizing) {
            int bestScore = numeric_limits<int>::min();
            for (int move : state.getAvailableMoves()) {
                GameState newState = state.makeMove(move, COMPUTER);
                int score = minimax(newState, false, HUMAN, COMPUTER);
                bestScore = max(bestScore, score);
            }
            return bestScore;
        } else {
            int bestScore = numeric_limits<int>::max();
            for (int move : state.getAvailableMoves()) {
                GameState newState = state.makeMove(move, HUMAN);
                int score = minimax(newState, true, HUMAN, COMPUTER);
                bestScore = min(bestScore, score);
            }
            return bestScore;
        }
    }

    // Pass HUMAN and COMPUTER as parameters now
    int findBestMove(const GameState& state, char HUMAN, char COMPUTER) {
        vector<int> bestMoves;
        int bestScore = numeric_limits<int>::min();

        // Collect moves with the best score
        for (int move : state.getAvailableMoves()) {
            GameState newState = state.makeMove(move, COMPUTER);
            int score = minimax(newState, false, HUMAN, COMPUTER);
            if (score > bestScore) {
                bestScore = score;
                bestMoves = { move };  // New best move found
            } else if (score == bestScore) {
                bestMoves.push_back(move);  // Add move if it has the same score
            }
        }

        // Randomly select one of the best moves
        srand(time(0));  // Seed for randomness
        int randomIndex = rand() % bestMoves.size();
        return bestMoves[randomIndex];
    }
};

void playGame() {
    GameState state;
    TicTacToeTree ai;
    char currentPlayer;
    char userChoice;

    char HUMAN, COMPUTER;  // Declare HUMAN and COMPUTER inside function

    // Allow user to choose their symbol
    cout << "Choose your symbol (X/O): ";
    cin >> userChoice;
    while (userChoice != 'X' && userChoice != 'O') {
        cout << "Invalid choice. Please choose X or O: ";
        cin >> userChoice;
    }

    // Set HUMAN and COMPUTER based on user choice
    if (userChoice == 'X') {
        HUMAN = 'X';
        COMPUTER = 'O';
        currentPlayer = HUMAN;
    } else {
        HUMAN = 'O';
        COMPUTER = 'X';
        currentPlayer = COMPUTER;
    }

    // Prints current board gameState
    while (!state.isGameOver()) {
        state.printBoard();
        if (currentPlayer == HUMAN) {
            int move;
            cout << "Enter your move (0-8): ";
            cin >> move;
            if (move >= 0 && move < 9 && state.getBoard()[move] == EMPTY) { // Player's move
                state = state.makeMove(move, HUMAN);
                currentPlayer = COMPUTER;
            } else {
                cout << "Invalid move. Try again.\n";
            }
        } else { // AI's play position
            int move = ai.findBestMove(state, HUMAN, COMPUTER);
            state = state.makeMove(move, COMPUTER);
            cout << "Computer plays at position " << move << endl;
            currentPlayer = HUMAN;
        }
    }

    // Final board's display output
    state.printBoard();
    char winner = state.checkWinner();
    if (winner == COMPUTER) cout << "Computer wins!\n";
    else if (winner == HUMAN) cout << "You win!\n";
    else cout << "It's a draw!\n";
}

int main() {
    playGame();
    return 0;
}

