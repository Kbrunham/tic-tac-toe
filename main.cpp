// main.cpp : Defines the entry point for the application.
//

#include <memory>
#include <chrono>

#include <cxxopts.hpp>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Log.h>

#include "game_board.h"
#include "game_env.h"
#include "game_move.h"
#include "main.h"

using namespace std;

int main(int argc, char** argv)
{
    // Enable color logger
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    // Enable non-color logger
    // static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::info, &consoleAppender);

    PLOG_INFO << "Tic-Tac-Tow Game";

    // Create the Arguments parser
    cxxopts::Options options("test", "A brief description");

    options.add_options()("d,debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))("h,help",
                                                                                                         "Print usage");
    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    if (result.count("debug")) {
        plog::get()->setMaxSeverity(plog::debug);
    }

    PLOG_INFO << "Starting Game";

    // Create the board environment
    GAME_ENV game_env;

    // Set the starting player
    game_env.set_player(GAME_PLAYER::PLAYER_1);

    // Shorthand variables
    GAME_BOARD* game_board = game_env.get_board();

    // Start the game loop.
    // Iterate until the game is over and switch player through every iteration
    for (int game_round = 0; !game_board->game_over(game_env.get_current_player());
         game_round++, game_env.switch_player())
    {
        PLOG_INFO << "Game Round: " << game_round;

        // Print game board
        game_board->print_board();

        if (game_env.is_current_player_human())
        {
            std::string user_input;
            GAME_MOVE user_move;

            // Get the move from the user
            std::cout << "Enter your move (x y): ";
            std::cin >> user_input;

            // Split the input on the comma
            std::stringstream ss(user_input);
            std::string x_str, y_str;
            if (!std::getline(ss, x_str, ',') || !std::getline(ss, y_str)) {
                throw std::invalid_argument("Invalid input format. Expected x,y.");
            }

            // Convert the strings to integers
            int x = std::stoi(x_str);
            int y = std::stoi(y_str);

            user_move.set_move_x(x);
            user_move.set_move_y(y);

            game_board->make_move(user_move, game_env.get_current_player());
        }
        else {
            // Get the current player's move
            auto start_time = std::chrono::high_resolution_clock::now();
            GAME_MOVE game_move = game_board->get_best_move(game_env.get_current_player(), 0);
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_time = end_time - start_time;
            PLOG_INFO << "Computing best move took: " << elapsed_time.count() << " seconds";

            // Make the move
            game_board->make_move(game_move, game_env.get_current_player());
        }
    }

    PLOG_INFO << "Game Over!";
    if (game_board->player_won(game_env.get_current_player()))
    {
        PLOG_INFO << "Player " << game_env.get_current_player_cstr() << " won!";
    }
    else
    {
        PLOG_INFO << "Game is a draw!";
    }

    return 0;
}
