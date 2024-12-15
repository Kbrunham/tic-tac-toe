#ifndef GAME_ENV_H
#define GAME_ENV_H

// Includes

// Foward declarations
class GAME_BOARD;

// Player Enum
enum class GAME_PLAYER
{
    PLAYER_1,
    PLAYER_2
};

class GAME_ENV
{
  public:
    GAME_ENV();
    virtual ~GAME_ENV();
    void set_player(GAME_PLAYER player);
    GAME_PLAYER get_current_player();
    void switch_player();
    GAME_BOARD* get_board()
    {
        return m_board;
    }

  private:
    GAME_PLAYER m_current_player;
    GAME_BOARD* m_board;
};

#endif // GAME_ENV_H