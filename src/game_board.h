#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <memory>

// Forward references
enum class GAME_PLAYER;
class GAME_MOVE;

class GAME_BOARD
{
  public:
    GAME_BOARD();
    ~GAME_BOARD();
    void make_move(GAME_MOVE* move);
    std::unique_ptr<GAME_MOVE> get_best_move(GAME_PLAYER player);
    bool game_over();
};

#endif // GAME_BOARD_H