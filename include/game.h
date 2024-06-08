#ifndef DATA_H
#define DATA_H

#include "data.h"
#include "stream.h"
#include "utils.h"
#include <random>

namespace game
{
    // Constants for admin user
    const std::string ADMIN_USERNAME = "admin";
    const std::string ADMIN_PASSWORD = "admin";

    // Game variables
    std::optional<model::User> logged_user;
    std::vector<model::User> users;
    std::vector<model::Trivia> trivias;
    std::vector<model::Leaderboard> leaderboards;
    std::vector<std::string> categories;

    /*
    * @brief Function to login 
    * @return std::optional<model::User>: the user that logged in
    * @details This function asks the user for the username and password and tries to find the user in the users vector
    */
    std::optional<model::User> login();

    /*
    * @brief Function to register a new user
    * @details This function asks the user for the username and password and creates a new user
    */
    void register_user();

    /*
    * @brief Function to search a user by username
    * @param username: the username to search
    * @return std::optional<model::User>: the user found
    * @details This function searches for a user in the users vector by username
    */
    std::optional<model::User> search_user(const std::string &username);

    /*
    * @brief Function to show the main menu
    * @details This function shows the main menu options, and serves as the main entry point for the game
    */
    void main_menu();

    /*
    * @brief Function to show the profile of the logged user
    * @details This function shows the profile of the logged user
    */
    void profile();

    /*
    * @brief Function to change the password of the logged user
    * @details This function asks the user for the new password and changes the password of the logged user
    */
    void change_password();

    /*
    * @brief Function to load the data from the files
    * @details This function loads the users, trivias, and leaderboards from the files
    */
    void load();

    /*
    * @brief Function to save the data to the files
    * @details This function saves the users, trivias, and leaderboards to the files
    */
    void save();

    /*
    * @brief Function to logout
    * @details This function logs out the user
    */
    void logout();

    /*
    * @brief Function to show the admin menu
    * @details This function shows the admin menu options
    */
    void admin_menu();

    /*
    * @brief Function to add a new category
    * @details This function asks the user for the category name and adds it to the categories vector
    */
    void add_category();

    /*
    * @brief Function to create a new trivia
    * @return model::Trivia: the trivia created
    * @details This function asks the user for the question, answer, category, and difficulty of the trivia
    */
    model::Trivia create_trivia();

    /*
    * @brief Function to edit a trivia
    * @details This function asks the user for the trivia id and edits the question, answer, category, and difficulty of the trivia
    */
    void edit_trivia();

    /*
    * @brief Function to delete a trivia
    * @details This function asks the user for the trivia id and deletes the trivia
    */
    void delete_trivia();

    /*  
    * @brief Function to show the trivias
    * @details This function shows the trivias
    */
    void show_trivias();

    /*
    * @brief Function to show the users
    * @details This function shows the users
    */
    void show_users();

    /*
    * @brief Function to show the user menu
    * @details This function shows the user menu options
    */
    void user_menu();

    /*
    * @brief Function to show the leaderboard
    * @param category: the category of the leaderboard
    * @details This function shows the leaderboard of the given category
    */
    void show_leaderboards();

    /*
    * @brief Function to play the trivia game
    * @param difficulty: the difficulty of the trivia game
    * @param category: the category of the trivia game
    * @details This function plays the trivia game with the given difficulty and category
    */
    void answer_trivia(model::Difficulty difficulty, const std::string &category);

    /*
    * @brief Function to play the trivia game
    * @details This function asks the user for the difficulty and category of the trivia game
    */
    void play();
};

#include "../src/game.cpp"

#endif // DATA_H
