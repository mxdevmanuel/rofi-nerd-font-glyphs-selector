
Rofi nerd font glyphs selector
==============================

Description
-----------

The goal of this project is to select nerd font glyphs from rofi.

This project is a rofi plugin.

How it is work
--------------

Program work with next simple algorithm:
* Scan '/usr/lib/nerd-fonts-complete' path. All files found contains nerd font glyphs description
* All found glyphs concatenate to list and pass to rofi.
* Selected glyphs pass to xdotool or xsel based on rofi complete action

Hot to build
------------

Next buildtime dependencies must be installed:
* cmake
* gcc/clang - compiler with c++17 support
* rofi - required headers only, configuration searched with pkgconfig

Run next commands to build from source:

```bash
$ cmake .
$ make all 
$ make install
```

Default install directory is '/usr/lib/rofi'

Runtime dependepcies
--------------------

Next runtime dependencies must be installed to plugin work:
* nerd-fonts-complete (must have database in '/usr/lib/nerd-fonts-complete' directory!)
* rofi
* xdotool - used to paste selected values to active window
* xsel - used to copy selected values to clipboard

References
----------

Nerd fonts: [https://nerdfonts.com/](https://nerdfonts.com/)
Rofi nerd font glyphs selector, python prototype: [https://gitlab.com/tekillaz/rofi-nerd-font-glyphs-python](https://gitlab.com/tekillaz/rofi-nerd-font-glyphs-python)

