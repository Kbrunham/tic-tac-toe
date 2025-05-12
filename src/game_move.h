#pragma once

class GAME_MOVE
{
  public:
    GAME_MOVE();
    virtual ~GAME_MOVE();

    bool operator<(const GAME_MOVE& other) const;

    // Accessors
    int get_score() const
    {
        return m_score;
    }
    int get_move_x() const
    {
        return m_move_x;
    }
    int get_move_y() const
    {
        return m_move_y;
    }
    void set_score(int score)
    {
        m_score = score;
    }
    void set_move_x(int x)
    {
        m_move_x = x;
    }
    void set_move_y(int y)
    {
        m_move_y = y;
    }
    bool is_move_evaluated() const
    {
        return m_move_evaluated;
    }
    void set_move_evaluated(bool evaluated)
    {
        m_move_evaluated = evaluated;
    }

  private:
    int m_score;
    int m_move_x;
    int m_move_y;
    bool m_move_evaluated;
};
