#include "BotBase.cpp"
#include <iostream>
using namespace std;

int main() {
    GameTree* game = new GameTree(nullptr);
    cout << "Do you want to play as O or X? ";
    string piece; cin >> piece;
    if (piece[0] == 'O') game->SetPiece(1);
    else if (piece[0] == 'X') game->SetPiece(2);
    cout << "Do you want to play first (1) or second (2)? ";
    int turn; cin >> turn;
    vector<vector<stack<char>>> board;
    board.resize(3, vector<stack<char>>(3));
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j].push(0);
    while (true) {
        if (GameState(board) != -1) {
            if (GameState(board) == 0) cout << "It's a draw!\n";
            else if (turn % 2 == 0) cout << "You win!\n";
            else cout << "Bot wins!\n";
            break;
        }
        if (turn % 2 == 0) {
            cout << "Bot is thinking...\n";
            game->SetGameRoot(new BoardNode(board, true));
            game->EliminationTraversal(game->GetGameRoot(), 1);
            int bot_move = game->ChooseMove();
            cout << bot_move << '\n';
            if (piece[0] == 'O') board[bot_move / 3][bot_move % 3].push('2');
            else board[bot_move / 3][bot_move % 3].push('1');
            cout << "Current board:\n";
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    cout << board[i][j].size() << ' ';
            cout << '\n';
            DrawBoard(board);
            game->~GameTree();
        }
        else {
            cout << "Your turn!\n";
            string cell; cin >> cell;
            if (piece[0] == 'O') board[cell[0] - 'a'][cell[1] - '1'].push('1');
            else board[cell[0] - 'a'][cell[1] - '1'].push('2');
            cout << "Current board:\n";
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    cout << board[i][j].size() << ' ';
            cout << '\n';
            DrawBoard(board);
        }
        ++turn;
    }
    int rand;
    cin >> rand;
    return 0;
}