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
        // Parse the line
        std::istringstream iss(line);
        std::string username, password, scoreStr;

        // Split the line by comma
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

    std::sort(
        leaderboards.begin(), leaderboards.end(),
        [](const model::Leaderboard &a, const model::Leaderboard &b)
        { return a.score > b.score; });

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

        for (int i = 0; i < 4; i++)
            std::getline(iss, trivias.back().options[i], (i == 3 ? '\n' : ','));
    }
    return trivias;
}

void database::save_trivias(const std::vector<model::Trivia> &trivias)
{
    std::ofstream ofs(TRIVIA_FILE);
    ofs << "category,difficulty,question,answer,option 1,option 2,option 3,option 4\n";

    for (const auto &trivia : trivias)
    {
        ofs << trivia.category << "," << static_cast<int>(trivia.difficulty) << "," << trivia.question << "," << trivia.answer << ",";

        for (int i = 0; i < 4; i++)
            ofs << trivia.options[i] << (i == 3 ? "\n" : ",");
    }

    ofs.close();
}
