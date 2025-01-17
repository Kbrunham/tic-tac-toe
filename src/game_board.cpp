// Include standard library headers
#include <algorithm>
#include <memory>
#include <vector>

// Include project headers
#include "game_move.h"
#include <plog/Log.h>

// Include this class header
#include "game_board.h"

// Forward declaration for functions
std::vector<GAME_MOVE> get_all_moves(const GAME_PLAYER& player);
void evaluate_move(GAME_MOVE* move);

GAME_BOARD::GAME_BOARD()
{
}

GAME_BOARD::~GAME_BOARD()
{
}

void GAME_BOARD::make_move(const GAME_MOVE& move)
{
}

GAME_MOVE GAME_BOARD::get_best_move(const GAME_PLAYER& player)
{
    std::vector<GAME_MOVE> all_moves;

    // Get all possible moves
    all_moves = get_all_moves(player);
    PLOG_DEBUG << "Generated " << all_moves.size() << " moves";

    // Evaluate all possible moves. Each interation updates
    // the score of the move
    for (auto& cur_move : all_moves)
    {
        evaluate_move(&cur_move);
    }

    // Return the best move
    std::sort(all_moves.begin(), all_moves.end());
    return all_moves.front();
}

bool GAME_BOARD::game_over() const
{
    static int count = 0;
    count++;

    return (count > 10);
}

std::vector<GAME_MOVE> get_all_moves(const GAME_PLAYER& player)
{
    std::vector<GAME_MOVE> all_moves;

    // Create all moves
    // Fake for now
    GAME_MOVE cur_move;
    all_moves.push_back(cur_move);
    //

    return all_moves;
}

void evaluate_move(GAME_MOVE* move)
{
}
