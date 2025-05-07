// Include standard library headers
#include <algorithm>
#include <memory>
#include <vector>

// Include library headers
#include <plog/Log.h>

// Include project headers
#include "cmn.h"
#include "game_board.h"

// Include this class header
// #include "game_board.h"

bool GAME_BOARD_UTILS::is_all_moves_made(const GAME_MOVES_BITSET& combined_moves)
{
    GAME_MOVES_BITSET all_moves_made = combined_moves & combined_moves >> (BOARD_SIZE_X + BOARD_ROW_PADDING) * 1 &
                                       combined_moves >> (BOARD_SIZE_X + BOARD_ROW_PADDING) * 2;
    all_moves_made &= all_moves_made >> 1;
    all_moves_made &= all_moves_made >> 1;
    return all_moves_made[0];
}

bool GAME_BOARD_UTILS::is_column_win(const GAME_MOVES_BITSET& player_moves)
{
    GAME_MOVES_BITSET column_win_moves = player_moves & player_moves >> (BOARD_SIZE_X + BOARD_ROW_PADDING) * 1 &
                                         player_moves >> (BOARD_SIZE_X + BOARD_ROW_PADDING) * 2;
    column_win_moves |= column_win_moves >> 1;
    column_win_moves |= column_win_moves >> 1;
    return column_win_moves[0];
}

bool GAME_BOARD_UTILS::is_row_win(const GAME_MOVES_BITSET& player_moves)
{
    GAME_MOVES_BITSET row_win_moves = player_moves & player_moves >> 1 & player_moves >> 2;
    row_win_moves |= row_win_moves >> (BOARD_SIZE_X + BOARD_ROW_PADDING);
    row_win_moves |= row_win_moves >> (BOARD_SIZE_X + BOARD_ROW_PADDING) * 2;
    return row_win_moves[0];
}

bool GAME_BOARD_UTILS::is_left_to_right_diagional_win(const GAME_MOVES_BITSET& player_moves)
{
    GAME_MOVES_BITSET diagional_win_moves = player_moves &
                                            player_moves >> ((BOARD_SIZE_X + BOARD_ROW_PADDING) * 1 + 1) &
                                            player_moves >> ((BOARD_SIZE_X + BOARD_ROW_PADDING) * 2 + 2);
    diagional_win_moves |= diagional_win_moves >> 1;
    diagional_win_moves |= diagional_win_moves >> 1;
    return diagional_win_moves[0];
}

bool GAME_BOARD_UTILS::is_right_to_left_diagional_win(const GAME_MOVES_BITSET& player_moves)
{
    GAME_MOVES_BITSET diagional_win_moves = player_moves &
                                            player_moves >> ((BOARD_SIZE_X + BOARD_ROW_PADDING) * 1 - 1) &
                                            player_moves >> ((BOARD_SIZE_X + BOARD_ROW_PADDING) * 2 - 2);
    diagional_win_moves |= diagional_win_moves >> 1;
    diagional_win_moves |= diagional_win_moves >> 1;
    return diagional_win_moves[0];
}

GAME_MOVES_BITSET GAME_BOARD_UTILS::get_combined_moves_bitset(const GAME_MOVES_BITSET& player1_moves,
                                                              const GAME_MOVES_BITSET& player2_moves)
{
    GAME_MOVES_BITSET combined_moves = player1_moves;
    combined_moves |= player2_moves;
    return combined_moves;
}

int GAME_BOARD_UTILS::game_x_y_to_bitset_index(int x, int y)
{
    // Game board has a space on the right of either row
    return (y * (BOARD_SIZE_X + BOARD_ROW_PADDING)) + x;
}

bool GAME_BOARD_UTILS::is_game_over(const GAME_MOVES_BITSET& active_player_moves,
                                    const GAME_MOVES_BITSET& combined_moves)
{
    if (is_all_moves_made(combined_moves) || is_player_won(active_player_moves))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GAME_BOARD_UTILS::is_player_won(const GAME_MOVES_BITSET& active_player_moves)
{
    if (is_column_win(active_player_moves) || is_row_win(active_player_moves) ||
        is_left_to_right_diagional_win(active_player_moves) || is_right_to_left_diagional_win(active_player_moves))
    {
        return true;
    }
    else
    {
        return false;
    }
}

GAME_PLAYER GAME_BOARD_UTILS::get_next_player(const GAME_PLAYER& active_player)
{
    if (active_player == GAME_PLAYER::PLAYER_1)
    {
        return GAME_PLAYER::PLAYER_2;
    }
    else
    {
        return GAME_PLAYER::PLAYER_1;
    }
}

const char* GAME_BOARD_UTILS::get_player_cstr(const GAME_PLAYER& player)
{
    if (player == GAME_PLAYER::PLAYER_1)
    {
        return "Player 1";
    }
    else
    {
        return "Player 2";
    }
}
