#include "../include/utils.h"

void utils::timer(std::atomic<bool> &running, int duration)
{
    for (int i = duration; i > 0 && running.load(); --i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int minutes = i / 60;
        int seconds = i % 60;

        std::cout << std::setw(2) << std::setfill('0') << minutes
                  << ":" << std::setw(2) << std::setfill('0') << seconds << '\r';
    }

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

    thread.join();

    return answer;
}

void utils::play_sound(const std::string &path, bool async)
{
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
    password.clear();

    char ch = '\0';
    while ((ch = _getch()) != '\r')
    {
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
            password.push_back(ch);
            std::cout << '*';
        }
    }

    std::cout << std::endl;
}
