#ifndef BOTBASE_H
#define BOTBASE_H

#include <vector>
#include <stack>

class BoardNode {
public:
    bool win_node = false;
    bool loss_node = false;
    bool draw_node = false;

    float win_rate = 0;
    float loss_rate = 0;
    float draw_rate = 0;

    class BoardNode* prev_move;
    std::vector<class BoardNode*> next_move;

    BoardNode(std::vector<std::vector<std::stack<char>>>& b, bool t): board(b), turn(t) {};
    std::vector<std::vector<std::stack<char>>> getBoard() const { return board; }
    bool getTurn() const { return turn; }

private:
    std::vector<std::vector<std::stack<char>>> board;
    bool turn;
};

class GameTree {
private:
    char player; char bot;
    BoardNode* GameRoot;
public:
    GameTree(BoardNode* root): GameRoot(root) {}
    ~GameTree();

    void SetPiece(int p) {
        this->player = (char)('0' + p);
        this->bot = (char)('0' + 3 - p);
    }

    BoardNode* GetGameRoot() { return this->GameRoot; }
    void SetGameRoot(BoardNode* root) { this->GameRoot = root; }

    void EliminationTraversal(BoardNode* cur_state, int depth);

    int ChooseMove();
};

#endif