#include <iostream>
#include <climits>
using namespace std;


class TicTacToe
{
private:
    int board[3][3] = {0};

public:
    void printBoard()
    {
        cout << "-------------" << endl;
        for (int i = 0; i < 3; ++i)
        {
            cout << "| ";
            for (int j = 0; j < 3; ++j)
            {
                char symbol = (board[i][j] == 1) ? 'X' : ((board[i][j] == 2) ? 'O' : ' ');
                cout << symbol << " | ";
            }
            cout << endl
                      << "-------------" << endl;
        }
    }

    bool isBoardFull()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board[i][j] == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool checkWin(int player)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            {
                return true;
            }
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            {
                return true;
            }
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        {
            return true;
        }
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        {
            return true;
        }
        return false;
    }

    bool makeMove(int row, int col, int player)
    {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == 0)
        {
            board[row][col] = player;
            return true;
        }
        return false;
    }

    int minimax(int depth, bool isMax, int alpha, int beta)
    {
        int score = 0;

        if (checkWin(1))
        {
            return -1;
        }
        else if (checkWin(2))
        {
            return 1;
        }
        else if (isBoardFull())
        {
            return 0;
        }

        if (isMax)
        {
            int bestScore = INT_MIN;
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    if (board[i][j] == 0)
                    {
                        board[i][j] = 2;
                        int currentScore = minimax(depth + 1, false, alpha, beta);
                        board[i][j] = 0;
                        bestScore = max(bestScore, currentScore);
                        alpha = max(alpha, bestScore);

                        if (beta <= alpha)
                            break;
                    }
                }
            }
            score = bestScore;
        }
        else
        {
            int bestScore = INT_MAX;
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    if (board[i][j] == 0)
                    {
                        board[i][j] = 1;
                        int currentScore = minimax(depth + 1, true, alpha, beta);
                        board[i][j] = 0;
                        bestScore = min(bestScore, currentScore);
                        beta = min(beta, bestScore);

                        if (beta <= alpha)
                            break;
                    }
                }
            }
            score = bestScore;
        }

        return score;
    }

    void makeAIMove()
    {
        int bestScore = INT_MIN;
        int bestMoveRow = -1;
        int bestMoveCol = -1;

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board[i][j] == 0)
                {
                    board[i][j] = 2; // AI's move
                    int moveScore = minimax(0, false, INT_MIN, INT_MAX);
                    board[i][j] = 0;

                    if (moveScore > bestScore)
                    {
                        bestScore = moveScore;
                        bestMoveRow = i;
                        bestMoveCol = j;
                    }
                }
            }
        }

        if (bestMoveRow != -1 && bestMoveCol != -1)
        {
            makeMove(bestMoveRow, bestMoveCol, 2);
        }
    }
};

int main(){
    TicTacToe game;
    int currentPlayer = 1;
    cout<<"Enter your name: "<<endl;
    string name;
    cin>>name;
    while (true)
    {
        game.printBoard();

        if (currentPlayer == 1)
        {
            cout << "enter your move (row and column): ";
            int row, col;
            cin >> row >> col;

            if (game.makeMove(row - 1, col - 1, currentPlayer))
            {
                if (game.checkWin(currentPlayer))
                {
                    game.printBoard();
                    cout << "Player "<<name<<" wins!" << endl;
                    break;
                }
                else if (game.isBoardFull())
                {
                    game.printBoard();
                    cout << "TIE!!!" << endl;
                    break;
                }
            }
            else
            {
                cout << "Invalid move" << endl;
                continue;
            }
        }
        else
        {
            game.makeAIMove();

            if (game.checkWin(2))
            {
                game.printBoard();
                cout << "AI wins!" << endl;
                break;
            }
            else if (game.isBoardFull())
            {
                game.printBoard();
                cout << "It's a tie!" << endl;
                break;
            }
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    return 0;
}
