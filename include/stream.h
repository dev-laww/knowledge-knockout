#ifndef STREAM_H
#define STREAM_H

#include <iostream>
#include <optional>
#include <fmt/core.h>
#include <fmt/color.h>

namespace stream
{
    /*
     * @brief Enum class that represents the text style
     */
    enum class TextStyle
    {
        none,
        blink,
        bold,
        consceal,
        faint,
        italic,
        reverse,
        strikethrough,
        underline,
    };

    /*
     * @brief Stream class that allows to print colored text to the console
     * @param fg: foreground color
     * @param style: text style
     * @param bg: background color
     */
    class Stream
    {
    public:
        Stream(fmt::color fg, TextStyle style = TextStyle::none, std::optional<fmt::color> bg = std::nullopt)
            : foreground_color(fg), text_style(style), background_color(bg) {}

        Stream &operator<<(const std::string &str)
        {
            print(str);
            return *this;
        }

        Stream &operator<<(const char *str)
        {
            print(std::string(str));
            return *this;
        }

        Stream &operator<<(int value)
        {
            print(std::to_string(value));
            return *this;
        }

        Stream &operator<<(double value)
        {
            print(std::to_string(value));
            return *this;
        }

        Stream &operator<<(std::ostream &(*manip)(std::ostream &))
        {
            std::cout << manip;
            return *this;
        }

    private:
        void print(const std::string &str)
        {
            auto style = fmt::fg(foreground_color);

            if (background_color.has_value())
                style |= fmt::bg(background_color.value());

            if (text_style != TextStyle::none)
                style |= fmt::emphasis(text_style);

            fmt::print(style, "{}", str);
        }

        fmt::color foreground_color;
        std::optional<fmt::color> background_color;
        TextStyle text_style;
    };

    /*
     * @brief Stream to print RED colored text
     */
    Stream red(fmt::color::red);

    /*
     * @brief Stream to print GREEN colored text
     */
    Stream green(fmt::color::green);

    /*
     * @brief Stream to print BLUE colored text
     */
    Stream blue(fmt::color::blue);

    /*
     * @brief Stream to print YELLOW colored text
     */
    Stream yellow(fmt::color::yellow);

    /*
     * @brief Stream to print CYAN colored text
     */
    Stream cyan(fmt::color::cyan);

    /*
     * @brief Stream to print MAGENTA colored text
     */
    Stream magenta(fmt::color::magenta);

    /*
     * @brief Stream to print WHITE colored text
     */
    Stream white(fmt::color::white);

    /*
     * @brief Stream to print BLACK colored text
     */
    Stream black(fmt::color::black);

    /*
     * @brief Stream to print BOLD text
     */
    Stream bold(fmt::color::white, TextStyle::bold);

    /*
     * @brief Stream to print ITALIC text
     */
    Stream italic(fmt::color::white, TextStyle::italic);

    /*
     * @brief Stream to print UNDERLINED text
     */
    Stream underline(fmt::color::white, TextStyle::underline);

    /*
     * @brief Stream to print STRIKETHROUGH text
     */
    Stream strikethrough(fmt::color::white, TextStyle::strikethrough);

    /*
     * @brief Stream to print REVERSE text
     */
    Stream reverse(fmt::color::white, TextStyle::reverse);

    /*
     * @brief Stream to print FAINT text
     */
    Stream faint(fmt::color::white, TextStyle::faint);

    /*
     * @brief Stream to print CONSCEAL text
     */
    Stream consceal(fmt::color::white, TextStyle::consceal);

    /*
     * @brief Stream to print BLINK text
     */
    Stream blink(fmt::color::white, TextStyle::blink);

    // Aliases for std::cout, std::cin, std::flush, std::endl
    using std::cin;
    using std::cout;
    using std::endl;
    using std::flush;
}

#endif // STREAM_H