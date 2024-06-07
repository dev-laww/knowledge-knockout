#include "../include/game.h"

void game::load()
{
    game::users = database::users();
    game::trivias = database::trivias();
    game::leaderboards = database::leaderboards();
}

void game::save()
{
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

    if (game::search_user(user.username).has_value())
    {
        stream::red << "Username already exists!" << stream::endl;
        return;
    }

    stream::cout << "Enter your password: ";
    utils::get_password(user.password);

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
    stream::cout << "[1] Login" << stream::endl
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

    stream::cout << "[1] Play" << stream::endl
                 << "[2] Leaderboards" << stream::endl
                 << "[3] Profile" << stream::endl
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

    stream::cout << "[1] Add category" << stream::endl
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