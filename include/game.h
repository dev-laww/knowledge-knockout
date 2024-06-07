#ifndef DATA_H
#define DATA_H

#include "data.h"
#include "stream.h"
#include "utils.h"

namespace game
{
    const std::string ADMIN_USERNAME = "admin";
    const std::string ADMIN_PASSWORD = "admin";

    std::optional<model::User> logged_user;
    std::vector<model::User> users;
    std::vector<model::Trivia> trivias;
    std::vector<model::Leaderboard> leaderboards;
    std::vector<std::string> categories;

    std::optional<model::User> login();
    void register_user();
    std::optional<model::User> search_user(const std::string &username);

    void main_menu();
    void profile();
    void edit_profile();
    void change_password();
    void load();
    void save();
    void logout();

    void admin_menu();
    void add_category();
    model::Trivia create_trivia();
    void edit_trivia();
    void delete_trivia();
    void show_trivias();
    void show_users();

    void user_menu();
    void show_leaderboards();
    void answer_trivia(model::Difficulty difficulty, const std::string &category);
    void play();
};

#include "../src/game.cpp"

#endif // DATA_H