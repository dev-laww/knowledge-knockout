#include "../include/data.h"

std::vector<model::User> database::users()
{
    std::vector<model::User> users;
    std::ifstream ifs(USERS_FILE);
    if (!ifs)
        return {};

    std::string line;
    std::getline(ifs, line); // Skip header
    while (std::getline(ifs, line))
    {
        std::istringstream iss(line);
        std::string username, password, scoreStr;
        std::getline(iss, username, ',');
        std::getline(iss, password, ',');
        std::getline(iss, scoreStr, ',');
        users.push_back({username, password, std::stoi(scoreStr)});
    }
    return users;
}

void database::save_users(const std::vector<model::User> &users)
{
    std::ofstream ofs(USERS_FILE);
    ofs << "username,password,score\n";
    for (const auto &user : users)
    {
        ofs << user.username << "," << user.password << "," << user.score << "\n";
    }
    ofs.close();
}

std::vector<model::Leaderboard> database::leaderboards()
{
    std::vector<model::Leaderboard> leaderboards;
    std::ifstream ifs(LEADERBOARDS_FILE);
    if (!ifs)
        return {};

    std::string line;
    std::getline(ifs, line); // Skip header
    while (std::getline(ifs, line))
    {
        std::istringstream iss(line);
        std::string username, scoreStr;
        std::getline(iss, username, ',');
        std::getline(iss, scoreStr, ',');
        leaderboards.push_back({username, std::stoi(scoreStr)});
    }
    return leaderboards;
}

void database::save_leaderboards(const std::vector<model::Leaderboard> &leaderboards)
{
    std::ofstream ofs(LEADERBOARDS_FILE);
    ofs << "username,score\n";
    for (const auto &leaderboard : leaderboards)
    {
        ofs << leaderboard.username << "," << leaderboard.score << "\n";
    }
    ofs.close();
}

std::vector<model::Trivia> database::trivias()
{
    std::vector<model::Trivia> trivias;
    std::ifstream ifs(TRIVIA_FILE);
    if (!ifs)
        return {};

    std::string line;
    std::getline(ifs, line); // Skip header
    while (std::getline(ifs, line))
    {
        std::istringstream iss(line);
        std::string category, difficultyStr, question, answer;
        std::getline(iss, category, ',');
        std::getline(iss, difficultyStr, ',');
        std::getline(iss, question, ',');
        std::getline(iss, answer, ',');
        trivias.push_back({category, model::Difficulty(std::stoi(difficultyStr)), question, answer});
    }
    return trivias;
}

void database::save_trivias(const std::vector<model::Trivia> &trivias)
{
    std::ofstream ofs(TRIVIA_FILE);
    ofs << "category,difficulty,question,answer\n";
    for (const auto &trivia : trivias)
    {
        ofs << trivia.category << "," << static_cast<int>(trivia.difficulty) << "," << trivia.question << "," << trivia.answer << "\n";
    }
    ofs.close();
}
