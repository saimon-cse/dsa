#include <iostream>
#include <vector>
using namespace std;

// Function to print the board
void printBoard(const vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

// Check if a queen can be placed on board[row][col]
bool isSafe(const vector<vector<int>>& board, int row, int col, int N) {
    // Check the same column
    for (int i = 0; i < row; i++)
        if (board[i][col]) return false;

    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j]) return false;

    return true;
}

// Recursive utility to solve the problem
bool solveNQueens(vector<vector<int>>& board, int row, int N) {
    if (row >= N) {
        printBoard(board, N);
        return true;  // change to false if you want all solutions
    }

    bool found = false;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1;
            found = solveNQueens(board, row + 1, N) || found;
            board[row][col] = 0;  // backtrack
        }
    }
    return found;
}

int main() {
    int N;
    cout << "Enter the number of queens (N): ";
    cin >> N;

    
    vector<vector<int>> board(N, vector<int>(N, 0));

    if (!solveNQueens(board, 0, N)) {
        cout << "No solution exists for " << N << " queens.\n";
    } else {
        cout << "One or more solutions found above.\n";
    }

    return 0;
}
