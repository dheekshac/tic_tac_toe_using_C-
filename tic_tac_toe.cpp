#include <iostream>
#include <limits>
using namespace std;

char board[3][3];
char currentPlayer;

// Initialize board
void initializeBoard() {
    char num = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = num++;
        }
    }
}

// Display board
void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        if (i < 2) cout << "\n---|---|---\n";
    }
    cout << "\n\n";
}

// Switch player
void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Make move safely
bool makeMove(int choice) {
    if (choice < 1 || choice > 9)
        return false;

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] == 'X' || board[row][col] == 'O')
        return false;

    board[row][col] = currentPlayer;
    return true;
}

// Check winner
bool checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
            return true;

        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
            return true;
    }

    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
        return true;

    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
        return true;

    return false;
}

// Check draw
bool checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

int main() {
    int choice;
    char playAgain;

    do {
        initializeBoard();
        currentPlayer = 'X';

        while (true) {
            displayBoard();
            cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            cin >> choice;

            // Input validation
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter a number between 1 and 9.\n";
                continue;
            }

            if (!makeMove(choice)) {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            if (checkWinner()) {
                displayBoard();
                cout << "Player " << currentPlayer << " WINS!\n";
                break;
            }

            if (checkDraw()) {
                displayBoard();
                cout << "It's a DRAW!\n";
                break;
            }

            switchPlayer();
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing.\n";
    return 0;
}
