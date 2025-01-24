#pragma once

// Player Enum
enum class GAME_PLAYER
{
    PLAYER_1 = 0,
    PLAYER_2 = 1,

    MAX_PLAYERS = 2
};

const int NUM_PLAYERS = static_cast<int>(GAME_PLAYER::MAX_PLAYERS);

const int BOARD_SIZE_X = 3;
const int BOARD_SIZE_Y = 3;
const int BOARD_ROW_PADDING = 3;
