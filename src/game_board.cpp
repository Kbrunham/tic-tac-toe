// Include standard library headers
#include <algorithm>
#include <memory>
#include <vector>

// Include library headers
#include <plog/Log.h>
#include <tabulate/table.hpp>

// Include project headers
#include "cmn.h"
#include "game_move.h"

// Include this class header
#include "game_board.h"

using namespace GAME_BOARD_UTILS;

// Forward declaration for functions
std::vector<GAME_MOVE> get_all_moves(const GAME_PLAYER& player);
void evaluate_move(GAME_MOVE* move);

// Method defintions

GAME_BOARD::GAME_BOARD()
{
    // Initialize the game board to a 0
    m_player_moves[GAME_PLAYER::PLAYER_1].reset();
    m_player_moves[GAME_PLAYER::PLAYER_2].reset();
}

GAME_BOARD::~GAME_BOARD()
{
}

void GAME_BOARD::make_move(const GAME_MOVE& move, const GAME_PLAYER& player)
{
    int move_bit_index = game_x_y_to_bitset_index(move.get_move_x(), move.get_move_y());
    CMN_ASSERT(m_player_moves[player].test(move_bit_index) == false);

    m_player_moves[player].set(move_bit_index);
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

GAME_MOVES_BITSET GAME_BOARD::get_combined_moves() const
{
    return get_combined_moves_bitset(m_player_moves.at(GAME_PLAYER::PLAYER_1),
                                     m_player_moves.at(GAME_PLAYER::PLAYER_2));
}

bool GAME_BOARD::game_over(const GAME_PLAYER& active_player) const
{
    const GAME_MOVES_BITSET combined_moves = get_combined_moves();
    const GAME_MOVES_BITSET active_player_moves = m_player_moves.at(active_player);

    return is_game_over(active_player_moves, combined_moves);
}

bool GAME_BOARD::player_won(const GAME_PLAYER& active_player) const
{
    return is_player_won(m_player_moves.at(active_player));
}

std::vector<GAME_MOVE> GAME_BOARD::get_all_moves(const GAME_PLAYER& player) const
{
    std::vector<GAME_MOVE> all_available_moves;
    GAME_MOVES_BITSET combined_moves = get_combined_moves();

    for (int x = 0; x < BOARD_SIZE_X; x++)
    {
        for (int y = 0; y < BOARD_SIZE_Y; y++)
        {
            int bit_index = game_x_y_to_bitset_index(x, y);
            if (combined_moves.test(bit_index) == false)
            {
                GAME_MOVE cur_move;
                cur_move.set_move_x(x);
                cur_move.set_move_y(y);
                all_available_moves.push_back(cur_move);
            }
        }
    }

    PLOG_DEBUG << "Generated " << all_available_moves.size() << " moves";
    CMN_ASSERT(all_available_moves.size() > 0);

    return all_available_moves;
}

void GAME_BOARD::evaluate_move(GAME_MOVE* move)
{
}

void GAME_BOARD::print_board() const
{
    tabulate::Table table;

    for (int y = BOARD_SIZE_Y - 1; y >= 0; y--)
    {
        tabulate::Table::Row_t row;
        for (int x = 0; x < BOARD_SIZE_X; x++)
        {
            int bit_index = game_x_y_to_bitset_index(x, y);
            if (m_player_moves.at(GAME_PLAYER::PLAYER_1).test(bit_index))
            {
                row.push_back("X");
            }
            else if (m_player_moves.at(GAME_PLAYER::PLAYER_2).test(bit_index))
            {
                row.push_back("O");
            }
            else
            {
                row.push_back("");
            }
        }
        table.add_row(row);
    }

    std::cout << table << std::endl;
}