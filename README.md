# Rofi nerd font glyphs selector

## Description

The goal of this project is to select nerd font glyphs from rofi.

This project is a rofi plugin.

## How it is work

Program work with next simple algorithm:

- Scan '/usr/lib/nerd-fonts-complete' path. All files found contains nerd font glyphs description [^1]
- All found glyphs concatenate to list and pass to rofi.
- Selected glyphs pass to xdotool or xsel based on rofi complete action

[^1]: Included in this repo are the nerd font files with the glyphs descriptors, an attempt is made to keep them updated but you can find the latest version in the nerd font repository under 'bin/scripts/lib' if you dont have it already in your system

## How to build

Next buildtime dependencies must be installed:

- cmake
- gcc/clang - compiler with c++17 support
- rofi - required headers only, configuration searched with pkgconfig

Run next commands to build from source:

```bash
$ cmake .
$ make all
$ make install
```

Default install directory is '/usr/lib/rofi'

## Runtime dependepcies

Next runtime dependencies must be installed to plugin work:

- nerd-fonts-complete (~~must have database in '/usr/lib/nerd-fonts-complete' directory!~~ We're going to attempt to provide the nerd font database if it is not present already)
- rofi
- xdotool - used to paste selected values to active window
- xsel - used to copy selected values to clipboard

## References

- Nerd fonts: [https://nerdfonts.com/](https://nerdfonts.com/)
- Original gitlab repo: [https://gitlab.com/tekillaz/rofi-nerd-font-glyphs-plugin](https://gitlab.com/tekillaz/rofi-nerd-font-glyphs-plugin) Thanks to tekillaz
