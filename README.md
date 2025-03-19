```
 __                            ___          _ _             
/ _\ ___ _ __ ___  ___ _ __   / _ \__ _  __| (_) __ _ _ __  
\ \ / __| '__/ _ \/ _ \ '_ \ / /_)/ _` |/ _` | |/ _` | '_ \ 
_\ \ (__| | |  __/  __/ | | / ___/ (_| | (_| | | (_| | | | |
\__/\___|_|  \___|\___|_| |_\/    \__,_|\__,_|_|\__,_|_| |_|
                                                            
```

## About
ScreenPadian is a Linux command-line tool for controlling brightness and power for the ASUS ScreenPad. It works similarly to the well-known [Monitorian](https://github.com/emoacht/Monitorian) application but is designed specifically for Linux and ASUS ScreenPad.

## What is ScreenPad?
ScreenPad is a secondary touchscreen built into ASUS dual-screen laptops. It functions as an additional display and a touchpad, but ASUS does not provide official brightness control tools for Linux.

<p align="center">
  <img src="resources/images/ScreenPad.jpg" alt="ScreenPad" width="500">
</p>

## Motivation
I wanted to manage my ScreenPad’s brightness and power directly from Linux, but no existing software allowed it. I created ScreenPadian as a simple and efficient solution that works the way I need it.

## Features
- Get current brightness
- Set brightness 
- Increase or decrease brightness 
- Turn the ScreenPad on and off

## Usage
To see available options, run `screenpadian --help`:
```
ScreenPadian 1.0.0
Usage: ./screenpadian [option] <brightness>
Options:
  <val>             Set brightness directly (equal to --set <val>)
  -g, --get         Get current brightness
  -s, --set <val>   Set brightness to <val>% (0-100%)
  -i, --inc <val>   Increase brightness by <val>%
  -d, --dec <val>   Decrease brightness by <val>%
      --off         Turn off the screen
      --on          Turn on the screen
  -t, --toggle      Toggle between on and off
  -h, --help        Show help
  -v, --version     Show version
```

### Usage Examples:
```
screenpadian --get        # get current brightness
screenpadian --set 50     # set brightness to 50%
screenpadian --toggle     # toggle ScreenPad on/off
```

### Automatization Examples

#### Automatically Reduce Brightness at Night
You can set up a cron job to lower brightness at 10 PM:
```sh
crontab -e
```
Add this line:
```
0 22 * * * screenpadian --set 30
```
Now brightness will automatically reduce to 30% at 10 PM!

#### Map Brightness Control to Keyboard Keys
You can assign `screenpadian` commands to hotkeys using `xbindkeys`.

1. Install `xbindkeys`:
   ```sh
   sudo apt install xbindkeys
   ```
2. Open the configuration file:
   ```sh
   xbindkeys --defaults > ~/.xbindkeysrc
   nano ~/.xbindkeysrc
   ```
3. Add these lines:
   ```
   "screenpadian --inc 10"
       XF86MonBrightnessUp

   "screenpadian --dec 10"
       XF86MonBrightnessDown
   ```
4. Run:
   ```sh
   xbindkeys
   ```

Now brightness keys will control the ScreenPad!

## Contributing
If you have suggestions or improvements, feel free to open an issue or submit a pull request!