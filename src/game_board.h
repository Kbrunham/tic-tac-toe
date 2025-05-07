#pragma once

#include <bitset>
#include <memory>
#include <unordered_map>
#include <vector>

#include "game.h"

// Forward references
class GAME_MOVE;

// Type definitions
using GAME_MOVES_BITSET = std::bitset<(BOARD_SIZE_X + BOARD_ROW_PADDING) * BOARD_SIZE_Y>;

// Class GAME_BOARD

/**
 * @class GAME_BOARD
 * @brief Represents the game board and its operations.
 *
 * This class encapsulates the state and behavior of the game board.
 * It provides methods to make moves, get the best move for a player,
 * and check if the game is over.
 */
class GAME_BOARD
{
  public:
    /**
     * @brief Constructs a new GAME_BOARD object.
     */
    GAME_BOARD();

    GAME_BOARD(const GAME_BOARD&); // Copy constructor

    /**
     * @brief Destroys the GAME_BOARD object.
     */
    ~GAME_BOARD();

    /**
     * @brief Makes a move on the game board.
     *
     * @param move The move to be made.
     * @param player The player making the move.
     */
    void make_move(const GAME_MOVE& move, const GAME_PLAYER& player);

    /**
     * @brief Gets the best move for a player.
     *
     * @param player The player for whom the best move is to be determined.
     * @param depth The depth for the minimax algorithm.
     * @return The best move for the player.
     */
    GAME_MOVE get_best_move(const GAME_PLAYER& player, int depth);

    /**
     * @brief Checks if the game is over.
     *
     * @return true if the game is over, false otherwise.
     */
    bool game_over(const GAME_PLAYER& active_player) const;

    /**
     * @brief Checks if the player has won the game.
     */
    bool player_won(const GAME_PLAYER& active_player) const;

    /**
     * @brief Prints the game board.
     */
    void print_board() const;

  private:
    std::unordered_map<GAME_PLAYER, GAME_MOVES_BITSET> m_player_moves;

    GAME_MOVES_BITSET get_combined_moves() const;
    std::vector<GAME_MOVE> get_all_moves(const GAME_PLAYER& player) const;
    void evaluate_move(GAME_MOVE* move, const GAME_PLAYER& player, int depth = 0);
};

namespace GAME_BOARD_UTILS
{

GAME_PLAYER get_next_player(const GAME_PLAYER& active_player);

const char* get_player_cstr(const GAME_PLAYER& player);

int game_x_y_to_bitset_index(int x, int y);

GAME_MOVES_BITSET get_combined_moves_bitset(const GAME_MOVES_BITSET& player1_moves,
                                            const GAME_MOVES_BITSET& player2_moves);

bool is_all_moves_made(const GAME_MOVES_BITSET& combined_moves);

bool is_column_win(const GAME_MOVES_BITSET& player_moves);

bool is_row_win(const GAME_MOVES_BITSET& player_moves);

bool is_left_to_right_diagional_win(const GAME_MOVES_BITSET& player_moves);

bool is_right_to_left_diagional_win(const GAME_MOVES_BITSET& player_moves);

bool is_game_over(const GAME_MOVES_BITSET& active_player_moves, const GAME_MOVES_BITSET& combined_moves);

bool is_player_won(const GAME_MOVES_BITSET& active_player_moves);

} // namespace GAME_BOARD_UTILS
