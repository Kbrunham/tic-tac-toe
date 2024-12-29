// Include standard library headers
#include <vector>
#include <memory>
#include <algorithm>

// Include project headers
#include <plog/Log.h>
#include "game_move.h"

// Include this class header
#include "game_board.h"

// Forward declaration for functions
std::vector<std::unique_ptr<GAME_MOVE>> get_all_moves(GAME_PLAYER player);
void evaluate_move(GAME_MOVE* move);


GAME_BOARD::GAME_BOARD()
{
}

GAME_BOARD::~GAME_BOARD()
{
}

void GAME_BOARD::make_move(GAME_MOVE* move)
{
}

GAME_MOVE* GAME_BOARD::get_best_move(GAME_PLAYER player)
{
    std::vector<std::unique_ptr<GAME_MOVE>> moves;

    // Get all possible moves
    moves = get_all_moves(player);
    PLOG_DEBUG << "Generated " << moves.size() << " moves";

    // Evaluate all possible moves
    for (auto& move : moves)
    {
        evaluate_move(move.get());
    }

    // Return the best move
    std::sort(moves.begin(), moves.end());

    return moves[0].release();
}

bool GAME_BOARD::game_over()
{
    static int count = 0;
    count++;

    return (count > 10);
}

std::vector<std::unique_ptr<GAME_MOVE>> get_all_moves(GAME_PLAYER player)
{
    std::vector<std::unique_ptr<GAME_MOVE>> moves;

    std::unique_ptr<GAME_MOVE> move(new GAME_MOVE());
    moves.push_back(std::move(move));

    return moves;
}

void evaluate_move(GAME_MOVE* move)
{

}
