#include "../include/utils.h"

void utils::timer(std::atomic<bool> &running, int duration)
{
    for (int i = duration; i > 0 && running.load(); --i)
    {
        // Sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int minutes = i / 60;
        int seconds = i % 60;

        std::cout << std::setw(2) << std::setfill('0') << minutes
                  << ":" << std::setw(2) << std::setfill('0') << seconds << '\r';
    }

    // Clear the timer if it's not running
    // This is to prevent the timer from being displayed when the user has already answered
    if (!running.load())
    {
        std::cout << std::setw(10) << std::setfill(' ') << '\r';
        return;
    }

    utils::play_sound("assets/sound/sfx_die.wav");
    stream::red << "Time's up!" << std::endl;
    utils::press_any_key();

    running.store(false);
}

char utils::wait_for_answer(int duration)
{
    // atomic variable to control the timer,
    // a variable whose value changes atomically,
    // which means there is a guarantee that no other processes/threads would see any intermediary state
    std::atomic<bool> running(true);
    char answer = '\0'; // Variable to store answer

    std::thread thread(timer, std::ref(running), duration);

    // Wait for an answer
    while (running.load())
    {
        if (!_kbhit())
            continue;

        answer = _getch();
        running.store(false);
    }

    // Wait for the timer thread to finish
    thread.join();

    return answer;
}

void utils::play_sound(const std::string &path, bool async)
{
    // Flags for PlaySound function
    auto flags = SND_FILENAME | SND_NODEFAULT;

    if (async)
        flags |= SND_ASYNC;

    PlaySoundA(path.c_str(), NULL, flags);
}

void utils::press_any_key()
{
    stream::consceal << "Press any key to continue..." << stream::endl;
    _getch();
}

void utils::clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void utils::get_password(std::string &password)
{
    // Clear the password
    password.clear();

    char ch = '\0';

    // Get the password
    while ((ch = _getch()) != '\r')
    {
        // If the user presses backspace
        if (ch == '\b')
        {
            if (!password.empty())
            {
                password.pop_back();
                std::cout << "\b \b";
            }
        }
        else
        {
            // Add the character to the password
            password.push_back(ch);

            // Print a '*' instead of the character
            std::cout << '*';
        }
    }

    std::cout << std::endl;
}

std::vector<std::string> utils::wrap_text(const std::string& text, size_t width) {
    std::istringstream words(text);
    std::string word;
    std::vector<std::string> lines;
    std::ostringstream wrapped;
    size_t current_width = 0;

    while (words >> word) {
        if (current_width + word.length() > width) {
            lines.push_back(wrapped.str());
            wrapped.str("");
            wrapped.clear();
            current_width = 0;
        }
        wrapped << word << " ";
        current_width += word.length() + 1;
    }
    lines.push_back(wrapped.str());

    return lines;
}

