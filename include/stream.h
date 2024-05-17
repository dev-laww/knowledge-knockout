#ifndef STREAM_H
#define STREAM_H

#include <iostream>
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
        Stream(fmt::color fg, TextStyle style = TextStyle::none, fmt::color bg = fmt::color::black)
            : foreground_color(fg), text_style(style), background_color(bg) {}

        Stream &operator<<(const std::string &str)
        {
            if (text_style == TextStyle::none)
            {
                fmt::print(fg(foreground_color) | bg(background_color), "{}", str);

                return *this;
            }

            fmt::print(fg(foreground_color) | bg(background_color) | fmt::emphasis(text_style), "{}", str);
            return *this;
        }

        Stream &operator<<(std::ostream &(*manip)(std::ostream &))
        {
            std::cout << manip;
            return *this;
        }

    private:
        fmt::color foreground_color;
        fmt::color background_color;
        TextStyle text_style;
    };

    Stream red(fmt::color::red);
    Stream green(fmt::color::green);
    Stream blue(fmt::color::blue);
    Stream yellow(fmt::color::yellow);
    Stream cyan(fmt::color::cyan);
    Stream magenta(fmt::color::magenta);
    Stream white(fmt::color::white);
    Stream black(fmt::color::black);
    Stream bold(fmt::color::white, TextStyle::bold);
    Stream italic(fmt::color::white, TextStyle::italic);
    Stream underline(fmt::color::white, TextStyle::underline);
    Stream strikethrough(fmt::color::white, TextStyle::strikethrough);
    Stream reverse(fmt::color::white, TextStyle::reverse);
    Stream faint(fmt::color::white, TextStyle::faint);
    Stream consceal(fmt::color::white, TextStyle::consceal);
    Stream blink(fmt::color::white, TextStyle::blink);
    using std::cout;
    using std::endl;
}

#endif // STREAM_H