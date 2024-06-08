#include "../include/game.h"

void game::load()
{
    // Load the data from the files
    game::users = database::users();
    game::trivias = database::trivias();
    game::leaderboards = database::leaderboards();

    // Get the categories from the trivias
    game::categories.clear();

    // Loop through the trivias and get the categories
    for (const auto &trivia : game::trivias)
    {
        if (std::find(game::categories.begin(), game::categories.end(), trivia.category) != game::categories.end())
            continue;

        game::categories.push_back(trivia.category);
    }
}

void game::save()
{
    // Save the data to the files
    database::save_users(game::users);
    database::save_trivias(game::trivias);
    database::save_leaderboards(game::leaderboards);
}

std::optional<model::User> game::login()
{
    utils::clear_screen();

    std::string username, password;

    stream::cout << "Enter your username: ";
    std::getline(stream::cin, username);

    auto user = game::search_user(username);

    if (!user.has_value())
    {
        // If the username is admin, ask for the password
        if (username == game::ADMIN_USERNAME)
        {
            stream::cout << "Enter your password: ";
            utils::get_password(password);

            if (password == game::ADMIN_PASSWORD)
            {
                stream::green << "Welcome back, " << game::ADMIN_USERNAME << "!" << stream::endl;
                return model::User{game::ADMIN_USERNAME, game::ADMIN_PASSWORD, 0};
            }

            stream::red << "Invalid password!" << stream::endl;
            utils::press_any_key();
        }

        stream::red << "User not found!" << stream::endl;
        utils::press_any_key();
        return std::nullopt;
    }

    auto current_user = user.value();

    stream::cout << "Enter your password: ";
    utils::get_password(password);

    if (current_user.password != password)
    {
        stream::red << "Invalid password!" << stream::endl;
        utils::press_any_key();
        return std::nullopt;
    }

    return current_user;
}

void game::register_user()
{
    utils::clear_screen();

    model::User user;
    stream::cout << "Enter your username: ";
    std::getline(stream::cin, user.username);

    if (user.username.empty())
    {
        stream::red << "Username cannot be empty!" << stream::endl;
        return;
    }

    if (game::search_user(user.username).has_value())
    {
        stream::red << "Username already exists!" << stream::endl;
        return;
    }

    stream::cout << "Enter your password: ";
    utils::get_password(user.password);

    if (user.password.empty())
    {
        stream::red << "Password cannot be empty!" << stream::endl;
        return;
    }

    stream::cout << "Confirm your password: ";
    std::string confirm_password;
    utils::get_password(confirm_password);

    if (user.password != confirm_password)
    {
        stream::red << "Passwords do not match!" << stream::endl;
        return;
    }

    user.score = 0;

    game::users.push_back(user);

    stream::green << "Success!" << stream::endl;
    utils::press_any_key();
}

std::optional<model::User> game::search_user(const std::string &username)
{
    for (const auto &user : game::users)
    {
        if (user.username == username)
            return user;
    }
    return std::nullopt;
}

void game::main_menu()
{
    utils::clear_screen();

    // TODO: Add a logo, maybe?
    stream::cout
        << "Knowlegr Knockout" << stream::endl
        << "[1] Login" << stream::endl
        << "[2] Register" << stream::endl
        << "[Q] Quit" << stream::endl
        << "Press a key to continue..." << stream::endl;

    switch (_getch())
    {
    case '1':
        /* code */
        game::logged_user = game::login();

        if (!game::logged_user.has_value())
            game::main_menu();

        if (game::logged_user.value().username == game::ADMIN_USERNAME)
            game::admin_menu();
        else
            game::user_menu();

        break;
    case '2':
        game::register_user();
        game::main_menu();
        break;

    case 'Q':
    case 'q':
        stream::green << "Goodbye!" << stream::endl;
        utils::play_sound("assets/sound/sfx_swooshing.wav", false);
        break;

    default:
        stream::red << "Invalid option!" << stream::endl;
        utils::press_any_key();
        game::main_menu();
    }
}

void game::user_menu()
{
    utils::clear_screen();

    stream::green << "Welcome, " << game::logged_user.value().username << "!" << stream::endl;

    stream::cout
        << "[1] Play" << stream::endl
        << "[2] Leaderboards" << stream::endl
        << "[3] Profile" << stream::endl
        << "[4] Change Password" << stream::endl
        << "[Q] Logout" << stream::endl
        << "Press a key to continue..." << stream::endl;

    switch (_getch())
    {
    case '1':
        game::play();
        game::user_menu();
        break;

    case '2':
        game::show_leaderboards();
        game::user_menu();
        break;

    case '3':
        game::profile();
        game::user_menu();
        break;
    case '4':
        game::change_password();
        game::user_menu();
        break;

    case 'Q':
    case 'q':
        game::logout();
        game::main_menu();
        break;

    default:
        stream::red << "Invalid option!" << stream::endl;
        utils::press_any_key();
        game::user_menu();
    }
}

void game::admin_menu()
{
    utils::clear_screen();

    stream::green << "Welcome, " << game::logged_user.value().username << "!" << stream::endl;

    stream::cout
        << "[1] Add category" << stream::endl
        << "[2] Add trivia" << stream::endl
        << "[3] Edit trivia" << stream::endl
        << "[4] Delete trivia" << stream::endl
        << "[5] Show trivias" << stream::endl
        << "[6] Show users" << stream::endl
        << "[Q] Logout" << stream::endl
        << "Press a key to continue..." << stream::endl;

    switch (_getch())
    {
    case '1':
        game::add_category();
        game::admin_menu();
        break;

    case '2':
        game::trivias.push_back(game::create_trivia());
        game::admin_menu();
        break;

    case '3':
        game::edit_trivia();
        game::admin_menu();
        break;

    case '4':
        game::delete_trivia();
        game::admin_menu();
        break;

    case '5':
        game::show_trivias();
        utils::press_any_key();
        game::admin_menu();
        break;

    case '6':
        game::show_users();
        game::admin_menu();
        break;

    case 'Q':
    case 'q':
        game::logout();
        game::main_menu();
        break;

    default:
        stream::red << "Invalid option!" << stream::endl;
        utils::press_any_key();
        game::admin_menu();
    }
}

void game::logout()
{
    game::logged_user.reset();
    stream::green << "Logged out successfully!" << stream::endl;
    utils::press_any_key();
}

void game::add_category()
{
    utils::clear_screen();

    stream::cout << "Enter the category: ";
    std::string category;
    std::getline(stream::cin, category);

    if (std::find(game::categories.begin(), game::categories.end(), category) != game::categories.end())
    {
        stream::red << "Category already exists!" << stream::endl;
        utils::press_any_key();
        return;
    }

    game::categories.push_back(category);

    stream::green << "Category added successfully!" << stream::endl;
    utils::press_any_key();
}

void game::show_users()
{
    utils::clear_screen();

    stream::cout << std::left << std::setw(20) << "Username"
                 << std::left << std::setw(20) << "Score" << stream::endl;

    for (const auto &user : game::users)
    {
        stream::cout << std::left << std::setw(20) << user.username
                     << std::left << std::setw(20) << user.score << stream::endl;
    }

    utils::press_any_key();
}

model::Trivia game::create_trivia()
{
    utils::clear_screen();

    model::Trivia trivia;

    stream::cout << "Enter the category: ";
    std::getline(stream::cin, trivia.category);

    if (std::find(game::categories.begin(), game::categories.end(), trivia.category) == game::categories.end())
    {
        stream::red << "Category does not exist!" << stream::endl;
        utils::press_any_key();
        return trivia;
    }

    stream::cout << "Enter the difficulty [easy, medium, hard]: ";
    std::string difficulty;
    std::getline(stream::cin, difficulty);

    if (difficulty != "easy" && difficulty != "medium" && difficulty != "hard")
    {
        stream::red << "Invalid difficulty!" << stream::endl;
        utils::press_any_key();
        return trivia;
    }

    if (difficulty == "easy")
        trivia.difficulty = model::Difficulty::easy;
    else if (difficulty == "medium")
        trivia.difficulty = model::Difficulty::medium;
    else
        trivia.difficulty = model::Difficulty::hard;

    stream::cout << "Enter the question: ";
    std::getline(stream::cin, trivia.question);

    stream::cout << "Enter the answer: ";
    std::getline(stream::cin, trivia.answer);

    stream::cout << "Enter the options: " << stream::endl;
    for (int i = 0; i < 4; i++)
    {
        stream::cout << "Option " << i + 1 << ": ";
        std::getline(stream::cin, trivia.options[i]);
    }

    return trivia;
}

void game::show_trivias()
{
    utils::clear_screen();

    stream::cout
        << std::left << "ID"
        << std::left << std::setw(20) << "Category"
        << std::left << std::setw(20) << "Difficulty"
        << std::left << std::setw(20) << "Question"
        << std::left << std::setw(20) << "Answer" << stream::endl;

    for (int i = 0; i < game::trivias.size(); i++)
    {
        stream::cout
            << std::left << std::setw(20) << i
            << std::left << std::setw(20) << game::trivias[i].category
            << std::left << std::setw(20) << (game::trivias[i].difficulty == model::Difficulty::easy ? "easy" : game::trivias[i].difficulty == model::Difficulty::medium ? "medium"
                                                                                                                                                                         : "hard")
            << std::left << std::setw(20) << game::trivias[i].question
            << std::left << std::setw(20) << game::trivias[i].answer << stream::endl;
    }
}

void game::edit_trivia()
{
    utils::clear_screen();

    game::show_trivias();

    stream::cout << "Enter the ID of the trivia you want to edit: ";
    int id;
    std::cin >> id;

    if (id < 0 || id >= game::trivias.size())
    {
        stream::red << "Invalid ID!" << stream::endl;
        utils::press_any_key();
        return;
    }

    stream::cout << "Editing trivia with ID " << id << stream::endl;

    model::Trivia &trivia = game::trivias[id];

    // cout trivia details
    stream::cout
        << "Category: " << trivia.category << stream::endl
        << "Difficulty: "
        << (trivia.difficulty == model::Difficulty::easy ? "easy" : trivia.difficulty == model::Difficulty::medium ? "medium"
                                                                                                                   : "hard")
        << stream::endl
        << "Question: " << trivia.question << stream::endl
        << "Answer: " << trivia.answer << stream::endl
        << "Options: " << stream::endl;

    for (int i = 0; i < 4; i++)
        stream::cout << "Option " << i + 1 << ": " << trivia.options[i] << stream::endl;

    stream::cout
        << "[1] Edit category" << stream::endl
        << "[2] Edit difficulty" << stream::endl
        << "[3] Edit question" << stream::endl
        << "[4] Edit answer" << stream::endl
        << "[5] Edit options" << stream::endl
        << "Press a key to continue..." << stream::endl;

    std::string category, difficulty, question, answer;
    
    switch (_getch())
    {
    case '1':
        stream::cout << "Enter the category [" << trivia.category << "]: ";
        std::getline(stream::cin, category);

        if (!category.empty())
            trivia.category = category;
        break;
    case '2':
        stream::cout << "Enter the difficulty [easy, medium, hard]: ";

        std::getline(stream::cin, difficulty);

        if (difficulty == "easy")
            trivia.difficulty = model::Difficulty::easy;
        else if (difficulty == "medium")
            trivia.difficulty = model::Difficulty::medium;
        else if (difficulty == "hard")
            trivia.difficulty = model::Difficulty::hard;
        break;
    case '3':
        stream::cout << "Enter the question [" << trivia.question << "]: ";

        std::getline(stream::cin, question);

        if (!question.empty())
            trivia.question = question;
        break;
    case '4':
        stream::cout << "Enter the answer [" << trivia.answer << "]: ";
        std::getline(stream::cin, answer);

        if (!answer.empty())
            trivia.answer = answer;

        break;
    case '5':
        stream::cout << "Enter the options: " << stream::endl;
        for (int i = 0; i < 4; i++)
        {
            stream::cout << "Option " << i + 1 << " [" << trivia.options[i] << "]: ";
            std::string option;
            std::getline(stream::cin, option);

            if (!option.empty())
                trivia.options[i] = option;
        }
        break;
    default:
        stream::red << "Invalid option!" << stream::endl;
        utils::press_any_key();
        return;
    }

    stream::green << "Trivia edited successfully!" << stream::endl;
    utils::press_any_key();
}

void game::delete_trivia()
{
    utils::clear_screen();

    game::show_trivias();

    stream::cout << "Enter the ID of the trivia you want to delete: ";
    int id;
    std::cin >> id;

    if (id < 0 || id >= game::trivias.size())
    {
        stream::red << "Invalid ID!" << stream::endl;
        utils::press_any_key();
        return;
    }

    game::trivias.erase(game::trivias.begin() + id);

    stream::green << "Trivia deleted successfully!" << stream::endl;
    utils::press_any_key();
}

void game::profile()
{
    utils::clear_screen();

    stream::green << "Profile" << stream::endl;

    stream::cout << "Username: " << game::logged_user.value().username << stream::endl;
    stream::cout << "Score: " << game::logged_user.value().score << stream::endl;

    utils::press_any_key();
}

void game::change_password()
{
    utils::clear_screen();

    stream::green << "Change Password" << stream::endl;

    stream::cout << "Enter your current password: ";
    std::string current_password;
    utils::get_password(current_password);

    if (current_password != game::logged_user.value().password)
    {
        stream::red << "Invalid password!" << stream::endl;
        utils::press_any_key();
        return;
    }

    stream::cout << "Enter your new password: ";
    std::string new_password;
    utils::get_password(new_password);

    if (new_password.empty())
    {
        stream::red << "Password cannot be empty!" << stream::endl;
        utils::press_any_key();
        return;
    }

    stream::cout << "Confirm your new password: ";
    std::string confirm_password;
    utils::get_password(confirm_password);

    if (new_password != confirm_password)
    {
        stream::red << "Passwords do not match!" << stream::endl;
        utils::press_any_key();
        return;
    }

    game::logged_user.value().password = new_password;

    for (auto &user : game::users)
    {
        if (user.username == game::logged_user.value().username)
        {
            user.password = new_password;
            break;
        }
    }

    stream::green << "Password changed successfully!" << stream::endl;
    utils::press_any_key();
}

void game::show_leaderboards()
{
    utils::clear_screen();

    std::sort(
        game::leaderboards.begin(), game::leaderboards.end(),
        [](const model::Leaderboard &a, const model::Leaderboard &b)
        { return a.score > b.score; });

    stream::cout << std::left << std::setw(20) << "Username"
                 << std::left << std::setw(20) << "Score" << stream::endl;

    for (const auto &leaderboard : game::leaderboards)
    {
        stream::cout << std::left << std::setw(20) << leaderboard.username
                     << std::left << std::setw(20) << leaderboard.score << stream::endl;
    }

    utils::press_any_key();
}

void game::answer_trivia(model::Difficulty difficulty, const std::string &category)
{
    utils::clear_screen();

    std::vector<model::Trivia> filtered_trivias;

    for (const auto &trivia : game::trivias)
        if (trivia.difficulty == difficulty && trivia.category == category)
            filtered_trivias.push_back(trivia);

    if (filtered_trivias.empty())
    {
        stream::red << "No trivias found!" << stream::endl;
        utils::press_any_key();
        return;
    }

    std::shuffle(filtered_trivias.begin(), filtered_trivias.end(), std::mt19937(std::random_device()()));

    int score = 0;

    for (const auto &trivia : filtered_trivias)
    {
        utils::clear_screen();

        stream::cout << trivia.question << stream::endl;

        std::vector<std::string> options = trivia.options;
        options.push_back(trivia.answer);

        std::shuffle(options.begin(), options.end(), std::mt19937(std::random_device()()));

        for (int i = 0; i < options.size(); i++)
            stream::cout << "[" << i + 1 << "] " << options[i] << stream::endl;

        stream::cout << "Enter your answer: ";
        int answer = static_cast<int>(utils::wait_for_answer());

        if (options[answer - 1] == trivia.answer)
        {
            stream::green << "Correct!" << stream::endl;
            utils::play_sound("assets/sound/sfx_point.wav");
            switch (trivia.difficulty)
            {
            case model::Difficulty::easy:
                score += 10;
                break;
            case model::Difficulty::medium:
                score += 20;
                break;
            case model::Difficulty::hard:
                score += 30;
                break;
            }
        }
    }

    game::logged_user.value().score += score;

    for (auto &leaderboard : game::leaderboards)
    {
        if (leaderboard.username == game::logged_user.value().username)
        {
            leaderboard.score = game::logged_user.value().score;
            utils::press_any_key();
            return;
        }
    }

    game::leaderboards.push_back({game::logged_user.value().username, score});

    utils::press_any_key();
}

void game::play()
{
    utils::clear_screen();

    if (game::trivias.empty())
    {
        stream::red << "No trivias found! Ask admin to add one." << stream::endl;
        utils::press_any_key();
        return;
    }

    if (game::categories.empty())
    {
        stream::red << "No categories found! Ask admin to add one." << stream::endl;
        utils::press_any_key();
        return;
    }

    stream::cout << "Choose a category: " << stream::endl;

    for (int i = 0; i < game::categories.size(); i++)
        stream::cout << "[" << i + 1 << "] " << game::categories[i] << stream::endl;

    stream::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > game::categories.size())
    {
        stream::red << "Invalid choice!" << stream::endl;
        utils::press_any_key();
        return;
    }

    stream::cout << "Choose a difficulty: " << stream::endl;
    stream::cout << "[1] Easy" << stream::endl;
    stream::cout << "[2] Medium" << stream::endl;
    stream::cout << "[3] Hard" << stream::endl;
    stream::cout << "Enter your choice: ";
    int difficulty;
    std::cin >> difficulty;

    model::Difficulty diff;

    switch (difficulty)
    {
    case 1:
        diff = model::Difficulty::easy;
        break;
    case 2:
        diff = model::Difficulty::medium;
        break;
    case 3:
        diff = model::Difficulty::hard;
        break;
    default:
        stream::red << "Invalid choice!" << stream::endl;
        utils::press_any_key();
        game::play();
        return;
    }

    game::answer_trivia(diff, game::categories[choice - 1]);
}
