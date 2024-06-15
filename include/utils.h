#ifndef UTILS_H
#define UTILS_H

#include <thread>
#include <atomic>
#include <chrono>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <sstream>
#include <vector>
#include "stream.h"

#pragma comment(lib, "winmm.lib")

namespace utils
{
    /*
     * @brief Function that plays a sound
     * @param path: path to the sound file
     */
    void play_sound(const std::string &path, bool async = true);

    /*
     * @brief Function that prints a message with a delay
     * @param running: atomic boolean that indicates if the timer is running
     * @param duration: duration of the delay
     */
    void timer(std::atomic<bool> &running, int duration);

    /*
     * @brief Function that waits for an answer
     * @param duration: duration of the wait
     * @return char
     */
    char wait_for_answer(int duraion = 10);

    /*
     * @brief Function that waits for a key press
     */
    void press_any_key();

    /*
     * @brief Function that clears the screen
     */
    void clear_screen();

    /*
     * @brief Function that gets a password from the user
     * @param password: string to store the password
     */
    void get_password(std::string &password);

    std::vector<std::string> wrap_text(const std::string &text, size_t width = 30);
};

#include "../src/utils.cpp"

#endif
