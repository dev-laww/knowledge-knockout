#ifndef DATABASE_H
#define DATABASE_H
#define LEADERBOARDS_FILE "data/leaderboards.txt"
#define USERS_FILE "data/users.txt"
#define TRIVIA_FILE "data/trivia.txt"

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
    /*
     * @brief Function that returns the users from the database
     * @return std::vector<model::User>
     */
    std::vector<model::User> users();
    /*
     * @brief Function that returns the leaderboards from the database
     * @return std::vector<model::Leaderboard>
     */
    std::vector<model::Leaderboard> leaderboards();
    /*
     * @brief Function that returns the trivias from the database
     * @return std::vector<model::Trivia>
     */
    std::vector<model::Trivia> trivias();

    /*
     * @brief Function that saves the users to the database
     * @param users: vector of users
     */
    void save_users(const std::vector<model::User> &users);
    /*
     * @brief Function that saves the leaderboards to the database
     * @param leaderboards: vector of leaderboards
     */
    void save_leaderboards(const std::vector<model::Leaderboard> &leaderboards);
    /*
     * @brief Function that saves the trivias to the database
     * @param trivias: vector of trivias
     */
    void save_trivias(const std::vector<model::Trivia> &trivias);
};

#include "../src/database.cpp"
#endif // DATABASE_H