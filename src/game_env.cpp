#include "game_env.h"
#include "game_board.h"

GAME_ENV::GAME_ENV() : m_current_player(GAME_PLAYER::PLAYER_1)
{
    m_board = std::make_unique<GAME_BOARD>();
}

GAME_ENV::~GAME_ENV()
{
}

void GAME_ENV::set_player(GAME_PLAYER player)
{
    m_current_player = player;
}

GAME_PLAYER GAME_ENV::get_current_player()
{
    return m_current_player;
}

void GAME_ENV::switch_player()
{
    m_current_player = (m_current_player == GAME_PLAYER::PLAYER_1) ? GAME_PLAYER::PLAYER_2 : GAME_PLAYER::PLAYER_1;
}

GAME_BOARD* GAME_ENV::get_board()
{
    return m_board.get();
}