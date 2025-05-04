#include "gtest/gtest.h"

#include "cmn.h"
#include "game_board.h"

using namespace GAME_BOARD_UTILS;

TEST(GameBoardUtilsTest, moveset_basic)
{
    // Ensure all bits are set to 0
    GAME_MOVES_BITSET player1_moves;
    GAME_MOVES_BITSET player2_moves;
    ASSERT_FALSE(player1_moves.any());
    ASSERT_FALSE(player2_moves.any());
}

TEST(GameBaordUtilsTest, allmoves_complete)
{
    GAME_MOVES_BITSET player1_moves;

    for (int x = 0; x < BOARD_SIZE_X; x++)
    {
        for (int y = 0; y < BOARD_SIZE_Y; y++)
        {
            player1_moves.set(game_x_y_to_bitset_index(x, y));
        }
    }
    ASSERT_TRUE(is_all_moves_made(player1_moves));
    ASSERT_TRUE(is_player_won(player1_moves));
}

TEST(GameBaordUtilsTest, allmoves_complete_2player)
{
    GAME_MOVES_BITSET player1_moves;
    GAME_MOVES_BITSET player2_moves;

    for (int x = 0; x < BOARD_SIZE_X; x++)
    {
        for (int y = 0; y < BOARD_SIZE_Y; y++)
        {
            if (x % 2 == 0)
            {
                player1_moves.set(game_x_y_to_bitset_index(x, y));
            }
            else
            {
                player2_moves.set(game_x_y_to_bitset_index(x, y));
            }
        }
    }
    ASSERT_TRUE(is_all_moves_made(get_combined_moves_bitset(player1_moves, player2_moves)));
}

TEST(GameBoardUtilsTest, column_win)
{
    GAME_MOVES_BITSET player1_moves;
    player1_moves.set(game_x_y_to_bitset_index(0, 0));
    player1_moves.set(game_x_y_to_bitset_index(0, 1));
    player1_moves.set(game_x_y_to_bitset_index(0, 2));

    ASSERT_TRUE(is_column_win(player1_moves));
    ASSERT_TRUE(is_player_won(player1_moves));
}

TEST(GameBoardUtilsTest, row_win)
{
    GAME_MOVES_BITSET player1_moves;
    player1_moves.set(game_x_y_to_bitset_index(0, 0));
    player1_moves.set(game_x_y_to_bitset_index(1, 0));
    player1_moves.set(game_x_y_to_bitset_index(2, 0));

    ASSERT_TRUE(is_row_win(player1_moves));
    ASSERT_TRUE(is_player_won(player1_moves));
}

TEST(GameBoardUtilsTest, left_to_right_diagional_win)
{
    GAME_MOVES_BITSET player1_moves;
    player1_moves.set(game_x_y_to_bitset_index(0, 0));
    player1_moves.set(game_x_y_to_bitset_index(1, 1));
    player1_moves.set(game_x_y_to_bitset_index(2, 2));

    ASSERT_TRUE(is_left_to_right_diagional_win(player1_moves));
    ASSERT_TRUE(is_player_won(player1_moves));
}

TEST(GameBoardUtilsTest, right_to_left_diagional_win)
{
    GAME_MOVES_BITSET player1_moves;
    player1_moves.set(game_x_y_to_bitset_index(2, 0));
    player1_moves.set(game_x_y_to_bitset_index(1, 1));
    player1_moves.set(game_x_y_to_bitset_index(0, 2));

    ASSERT_TRUE(is_right_to_left_diagional_win(player1_moves));
    ASSERT_TRUE(is_player_won(player1_moves));
}
