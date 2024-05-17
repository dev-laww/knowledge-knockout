#ifndef DATABASE_H
#define DATABASE_H
#define LEADERBOARDS_FILE "leaderboards.txt"
#define USERS_FILE "users.txt"
#define TRIVIA_FILE "trivia.txt"

#include <fstream>
#include <vector>
#include <sstream>

namespace model
{
    struct User
    {
        std::string username;
        std::string password;
        int score;
    };

    struct Leaderboard
    {
        std::string username;
        int score;
    };

    enum class Difficulty
    {
        easy,
        medium,
        hard
    };

    struct Trivia
    {
        std::string category;
        Difficulty difficulty;
        std::string question;
        std::string answer;
    };
}

namespace database
{
    std::vector<model::User> users();
    std::vector<model::Leaderboard> leaderboards();
    std::vector<model::Trivia> trivias();

    void save_users(const std::vector<model::User> &users);
    void save_leaderboards(const std::vector<model::Leaderboard> &leaderboards);
    void save_trivias(const std::vector<model::Trivia> &trivias);
};

#include "../src/database.cpp"
#endif // DATABASE_H