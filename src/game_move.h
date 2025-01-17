#ifndef GAME_MOVE_H
#define GAME_MOVE_H

class GAME_MOVE
{
  public:
    GAME_MOVE();
    virtual ~GAME_MOVE();

    bool operator<(const GAME_MOVE& other) const;
};

#endif // GAME_MOVE_H