#include "game_move.h"

GAME_MOVE::GAME_MOVE() : m_move_x(0), m_move_y(0)
{
}

GAME_MOVE::~GAME_MOVE()
{
}

bool GAME_MOVE::operator<(const GAME_MOVE& other) const
{
    return other.m_score < m_score;
}
