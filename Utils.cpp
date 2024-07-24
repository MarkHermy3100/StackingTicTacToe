#include <iostream>
#include <vector>
#include <stack>

const std::string pad(7, ' ');
const std::string horizontal(7, '_');

const std::vector<std::vector<std::string>> oh = {{pad, pad,
                                                   "  /\\   ",
                                                  "  \\/   ",
                                                  pad, pad, pad},
                                                {pad,
                                                 "  /\\   ",
                                                 " /  \\  ",
                                                " \\  /  ",
                                                "  \\/   ",
                                                pad, pad},
                                                {"  /\\   ",
                                                 " /  \\  ",
                                                 "/    \\ ",
                                                "\\    / ",
                                                " \\  /  ",
                                                "  \\/   ",
                                                pad}};

const std::vector<std::vector<std::string>> ex = {{pad, pad,
                                                   "  \\/   ",
                                                    "  /\\   ",
                                                    pad, pad, pad},
                                                  {pad,
                                                   " \\  /  ",
                                                   "  \\/   ",
                                                    "  /\\   ",
                                                    " /  \\  ",
                                                    pad, pad},
                                                  {"\\    / ",
                                                   " \\  /  ",
                                                   "  \\/   ",
                                                    "  /\\   ",
                                                    " /  \\  ",
                                                    "/    \\ ",
                                                    pad}};

void DrawBoard(std::vector<std::vector<std::stack<char>>>& board) {
    for (int i = 0; i < 21; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (j % 2 == 1) std::cout << '|';
            else {
                if (i % 7 == 6 && i < 20) std::cout << horizontal;
                else if (board[i / 7][j / 2].top() == '1')
                    std::cout << oh[board[i / 7][j / 2].size() - 2][i % 7];
                else if (board[i / 7][j / 2].top() == '2')
                    std::cout << ex[board[i / 7][j / 2].size() - 2][i % 7];
                else std::cout << pad;
            }
        }
        std::cout << '\n';
    }
}

int GameState(std::vector<std::vector<std::stack<char>>>& board) {
    int count = 0;
    if (board[0][0].top() && board[0][0].top() == board[1][1].top()
                        && board[0][0].top() == board[2][2].top())
        return board[0][0].top() - '0';
    if (board[0][2].top() && board[0][2].top() == board[1][1].top()
                        && board[0][2].top() == board[2][0].top())
        return board[0][2].top() - '0';
    for (int i = 0; i < 3; ++i) {
        if (board[i][0].top() && board[i][0].top() == board[i][1].top()
                            && board[i][0].top() == board[i][2].top())
            return board[i][0].top() - '0';
        if (board[0][i].top() && board[0][i].top() == board[1][i].top()
                            && board[0][i].top() == board[2][i].top())
            return board[0][i].top() - '0';
        for (int j = 0; j < 3; ++j)
            count += board[i][j].size();
    }
    return (count == 36) ? 0 : -1;
}

int AdjacentBoardDifference(std::vector<std::vector<std::stack<char>>>& b1, std::vector<std::vector<std::stack<char>>>& b2) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (b1[i][j].size() != b2[i][j].size())
                return i * 3 + j;
}