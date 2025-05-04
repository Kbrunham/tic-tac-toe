#pragma once

// Includes
#include <memory>

// Include project headers
#include "game.h"

// Foward declarations
class GAME_BOARD;

class GAME_ENV
{
  public:
    GAME_ENV();
    virtual ~GAME_ENV();
    void set_player(GAME_PLAYER player);
    GAME_PLAYER get_current_player() const;
    const char* get_current_player_cstr() const;
    void switch_player();
    GAME_BOARD* get_board();

  private:
    GAME_PLAYER m_current_player;
    std::unique_ptr<GAME_BOARD> m_board;
};
