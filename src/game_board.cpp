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

GAME_BOARD::GAME_BOARD(const GAME_BOARD& obj)
{
    // Copy constructor
    m_player_moves[GAME_PLAYER::PLAYER_1] = obj.m_player_moves.at(GAME_PLAYER::PLAYER_1);
    m_player_moves[GAME_PLAYER::PLAYER_2] = obj.m_player_moves.at(GAME_PLAYER::PLAYER_2);
}

GAME_BOARD::~GAME_BOARD()
{
}

void GAME_BOARD::make_move(const GAME_MOVE& move, const GAME_PLAYER& player)
{
    PLOG_DEBUG << "Making move for " << GAME_BOARD_UTILS::get_player_cstr(player) << ": " << move.get_move_x() << ", "
               << move.get_move_y();
    int move_bit_index = game_x_y_to_bitset_index(move.get_move_x(), move.get_move_y());
    CMN_ASSERT(m_player_moves[player].test(move_bit_index) == false);

    m_player_moves[player].set(move_bit_index);
}

GAME_MOVE GAME_BOARD::get_best_move(const GAME_PLAYER& player, int depth)
{
    std::vector<GAME_MOVE> all_moves;

    // Get all possible moves
    all_moves = get_all_moves(player);
    CMN_ASSERT(all_moves.size() > 0);
    PLOG_DEBUG << "Generated " << all_moves.size() << " moves at depth " << depth;

    // Evaluate all possible moves. Each interation updates
    // the score of the move
    // Only look for moves that win
    bool found_winning_move = false;
    for (auto& cur_move : all_moves)
    {
        found_winning_move |= evaluate_move(&cur_move, player, depth, true);
    }

    if (!found_winning_move)
    {
        // If no winning move is found, evaluate all moves
        for (auto& cur_move : all_moves)
        {
            evaluate_move(&cur_move, player, depth);
        }
    }

    // Sort the moves based on score
    // Return the best move
    std::sort(all_moves.begin(), all_moves.end());
    PLOG_DEBUG << "Best move for " << GAME_BOARD_UTILS::get_player_cstr(player) << " at depth " << depth << " : "
               << all_moves.front().get_move_x() << ", " << all_moves.front().get_move_y()
               << " with score: " << all_moves.front().get_score();
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

bool GAME_BOARD::evaluate_move(GAME_MOVE* move, const GAME_PLAYER& player, int depth, bool no_recurse)
{
    if (move->is_move_evaluated())
    {
        // If the move is already evaluated, return
        return move->get_score() == 1;
    }
    else {
        // Create a copy of the current game board
        GAME_BOARD cur_move_board = *this;

        // Initialize the move score to -1
        move->set_score(-1);
        move->set_move_evaluated(false);

        // Make the move on the copy
        cur_move_board.make_move(*move, player);
        if (cur_move_board.game_over(player))
        {
            // If the game is over, set the score
            if (cur_move_board.player_won(player))
            {
                move->set_score(1);
                move->set_move_evaluated(true);
            }
            else
            {
                move->set_score(0);
                move->set_move_evaluated(true);
            }
        }
        else if (!no_recurse)
        {
            // If the game is not over, get the next player and evaluate the move
            GAME_PLAYER next_player = get_next_player(player);
            move->set_score(-1 * cur_move_board.get_best_move(next_player, depth + 1).get_score());
            move->set_move_evaluated(true);
        }
    }

    return move->get_score() == 1;
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
                row.push_back(" ");
            }
        }
        table.add_row(row);
    }

    std::cout << table << std::endl;
}

GAME_MOVE GAME_BOARD_UTILS::get_human_move(const GAME_PLAYER& player)
{
    std::string user_input;
    GAME_MOVE user_move;

    // Get the move from the user
    std::cout << "Enter your move (x y): ";
    std::cin >> user_input;

    // Split the input on the comma
    std::stringstream ss(user_input);
    std::string x_str, y_str;
    if (!std::getline(ss, x_str, ',') || !std::getline(ss, y_str))
    {
        throw std::invalid_argument("Invalid input format. Expected x,y.");
    }

    // Convert the strings to integers
    int x = std::stoi(x_str);
    int y = std::stoi(y_str);

    user_move.set_move_x(x);
    user_move.set_move_y(y);

    return user_move;
}