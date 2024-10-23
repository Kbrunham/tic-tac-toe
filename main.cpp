// main.cpp : Defines the entry point for the application.
//

#include <cxxopts.hpp>

#include "main.h"

using namespace std;

int main(int argc, char **argv)
{
    cxxopts::Options options("test", "A brief description");

    options.add_options()("d,debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))("h,help",
                                                                                                         "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    cout << "Hello CMake." << endl;
    return 0;
}
