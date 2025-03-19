#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <unistd.h>

#define PROGRAM_NAME        "ScreenPadian"
#define PROGRAM_VERSION     "1.0.0"

#define BRIGHTNESS_PATH         "/sys/class/backlight/asus_screenpad/brightness"
#define MAX_BRIGHTNESS_PATH     "/sys/class/backlight/asus_screenpad/max_brightness"
#define BL_POWER_PATH           "/sys/class/backlight/asus_screenpad/bl_power"

int get_power_state()
{
    std::ifstream file(BL_POWER_PATH);
    if (!file)
    {
        std::cerr << "error: cannot access " << BL_POWER_PATH << ", use sudo" << std::endl;
        return -1;
    }

    int state;
    file >> state;
    if (state != 0 && state != 1)
    {
        std::cerr << "error: invalid power state value in " << BL_POWER_PATH << std::endl;
        return -1;
    }
    return state;
}

int get_max_brightness()
{
    std::ifstream file(MAX_BRIGHTNESS_PATH);
    int max_brightness = 100;
    if (file)
        file >> max_brightness;
    return max_brightness;
}

int get_current_brightness()
{
    std::ifstream file(BRIGHTNESS_PATH);
    int brightness = -1;
    if (file)
        file >> brightness;
    return brightness;
}

void set_brightness(int percentage)
{
    int max_brightness = get_max_brightness();
    int new_brightness = std::round(percentage / 100.0 * max_brightness);

    std::ofstream brightness_file(BRIGHTNESS_PATH);
    if (!brightness_file)
    {
        std::cerr << "error: cannot access " << BRIGHTNESS_PATH << ", use sudo" << std::endl;
        return;
    }

    brightness_file << new_brightness;
    brightness_file.close();
    std::cout << "brightness set to " << percentage << "%" << std::endl;
}

void turn_off_screen()
{
    std::ofstream power_file(BL_POWER_PATH);
    if (!power_file)
    {
        std::cerr << "error: cannot access " << BL_POWER_PATH << ", use sudo" << std::endl;
        return;
    }

    power_file << "1";
    power_file.close();
    std::cout << "screenpad turned off" << std::endl;
}

void turn_on_screen()
{
    std::ofstream power_file(BL_POWER_PATH);
    if (!power_file)
    {
        std::cerr << "error: cannot access " << BL_POWER_PATH << ", use sudo" << std::endl;
        return;
    }

    power_file << "0";
    power_file.close();
    std::cout << "screenpad turned on" << std::endl;
}

void print_help(const char* prog_name)
{
    std::cout << "Usage: " << prog_name << " [option] <brightness>\n"
              << "Options:\n"
              << "  <val>             Set brightness directly (equal to --set <val>)\n"
              << "  -g, --get         Get current brightness\n"
              << "  -s, --set <val>   Set brightness to <val>% (0-100%)\n"
              << "  -i, --inc <val>   Increase brightness by <val>%\n"
              << "  -d, --dec <val>   Decrease brightness by <val>%\n"
              << "      --off         Turn off the screen\n"
              << "      --on          Turn on the screen\n"
              << "  -t, --toggle      Toggle between on and off\n"
              << "  -h, --help        Show help\n"
              << "  -v, --version     Show version"
              << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "error: no arguments provided, use --help" << std::endl;
        return 1;
    }

    std::string arg = argv[1];

    if (arg == "--help" || arg == "-h")
    {
        print_help(argv[0]);
        return 0;
    }
    if (arg == "--version" || arg == "-v")
    {
        std::cout << PROGRAM_NAME << " " << PROGRAM_VERSION << std::endl;
        return 0;
    }
    if (arg == "--get" || arg == "-g")
    {
        int max_brightness = get_max_brightness();
        int current = get_current_brightness();
        if (current == -1)
        {
            std::cerr << "error: cannot read brightness, use sudo" << std::endl;
            return 1;
        }
        std::cout << "current brightness " << std::round(current * 100.0 / max_brightness) << "%" << std::endl;
        return 0;
    }
    if (arg == "--off")
    {
        turn_off_screen();
        return 0;
    }
    if (arg == "--on")
    {
        turn_on_screen();
        return 0;
    }
    if (arg == "--toggle" || arg == "-t")
    {
        int power_state = get_power_state();
        if (power_state == -1)
            return 1;

        if (power_state == 1)
            turn_on_screen();
        else
            turn_off_screen();

        return 0;
    }
    if ((arg == "--set" || arg == "-s") && argc == 3)
    {
        try
        {
            int brightness = std::stoi(argv[2]);
            if (brightness < 0 || brightness > 100)
            {
                std::cerr << "error: invalid brightness value" << std::endl;
                return 1;
            }
            set_brightness(brightness);
        }
        catch (...)
        {
            std::cerr << "error: invalid brightness argument, use --help" << std::endl;
            return 1;
        }
        return 0;
    }
    if ((arg == "--inc" || arg == "-i" || arg == "--dec" || arg == "-d") && argc == 3)
    {
        try
        {
            int change = std::stoi(argv[2]);
            if (change < 0)
            {
                std::cerr << "error: invalid increment/decrement value" << std::endl;
                return 1;
            }

            int max_brightness = get_max_brightness();
            int current = get_current_brightness();
            if (current == -1)
            {
                std::cerr << "error: cannot read brightness, use sudo" << std::endl;
                return 1;
            }

            int current_percent = std::round(current * 100.0 / max_brightness);
            int new_percent = (arg == "--inc" || arg == "-i") ? current_percent + change
                                                              : current_percent - change;

            if (new_percent < 0) new_percent = 0;
            if (new_percent > 100) new_percent = 100;

            set_brightness(new_percent);
        }
        catch (...)
        {
            std::cerr << "error: invalid increment/decrement argument, use --help" << std::endl;
            return 1;
        }
        return 0;
    }

    try
    {
        int brightness = std::stoi(arg);
        if (brightness < 0 || brightness > 100)
        {
            std::cerr << "error: invalid brightness value" << std::endl;
            return 1;
        }
        set_brightness(brightness);
    }
    catch (...)
    {
        std::cerr << "error: invalid arguments, use --help" << std::endl;
        return 1;
    }
    return 0;
}
