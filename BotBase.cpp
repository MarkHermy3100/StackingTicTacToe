#include "BotBase.hpp"
#include "Utils.cpp"

int totalNodes = 0;
int totalGames = 0;

void TreeDestructor(BoardNode* node) {
    if (node) {
        for (int i = 0; i < node->next_move.size(); ++i)
            TreeDestructor(node->next_move[i]);
        delete node;
    }
}

GameTree::~GameTree() {
    TreeDestructor(this->GameRoot);
    this->GameRoot = nullptr;
}

void GameTree::EliminationTraversal(BoardNode* cur_state, int depth) {
    if (depth > 5) return;
    ++totalNodes;

    if (cur_state->win_node || cur_state->loss_node || cur_state->draw_node) {
        ++totalGames;
        if (cur_state->loss_node && cur_state->getTurn())
            cur_state->prev_move->loss_node = true;
        else if (cur_state->win_node && !cur_state->getTurn())
            cur_state->prev_move->win_node = true;
        return;
    }
    std::vector<std::vector<std::stack<char>>> cur_board = cur_state->getBoard();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (cur_board[i][j].size() < 4) {
                std::vector<std::vector<std::stack<char>>> next_board = cur_board;
                if (cur_state->getTurn()) next_board[i][j].push(this->bot);
                else next_board[i][j].push(this->player);
                BoardNode* next_state = new BoardNode(next_board, !cur_state->getTurn());

                if (GameState(next_board) == 0)
                    next_state->draw_node = true;
                else if (GameState(next_board) == this->bot - '0')
                    next_state->win_node = true;
                else if (GameState(next_board) == this->player - '0')
                    next_state->loss_node = true;

                next_state->prev_move = cur_state;
                cur_state->next_move.push_back(next_state);
                EliminationTraversal(next_state, depth + 1);
            }
        }
    }
    
    if (cur_state->getTurn()) {
        bool loss_flag = true;
        for (int i = 0; i < cur_state->next_move.size(); ++i) {
            if (!cur_state->next_move[i]->loss_node) loss_flag = false;
            if (cur_state->next_move[i]->win_node) cur_state->win_node = true;
        }
        cur_state->loss_node = loss_flag;
    }
    else {
        bool win_flag = true;
        for (int i = 0; i < cur_state->next_move.size(); ++i) {
            if (!cur_state->next_move[i]->win_node) win_flag = false;
            if (cur_state->next_move[i]->loss_node) cur_state->loss_node = true;
        }
        cur_state->win_node = win_flag;
    }
}

int GameTree::ChooseMove() {
    // std::vector<int> win_moves;
    for (int i = 0; i < this->GameRoot->next_move.size(); ++i) {
        if (this->GameRoot->next_move[i]->win_node) {
            std::vector<std::vector<std::stack<char>>> b1 = this->GameRoot->getBoard();
            std::vector<std::vector<std::stack<char>>> b2 = this->GameRoot->next_move[i]->getBoard();
            return (AdjacentBoardDifference(b1, b2));
        }
    }
    // if (!win_moves.empty()) {
    //     return 0;
    // }
    for (int i = 0; i < this->GameRoot->next_move.size(); ++i) {
        std::cout << this->GameRoot->next_move[i]->loss_node << ' ';
        if (!this->GameRoot->next_move[i]->loss_node) {
            std::vector<std::vector<std::stack<char>>> b1 = this->GameRoot->getBoard();
            std::vector<std::vector<std::stack<char>>> b2 = this->GameRoot->next_move[i]->getBoard();
            return AdjacentBoardDifference(b1, b2);
        }
    }
    return 8;
}