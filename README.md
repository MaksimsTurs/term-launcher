# Termlauncher
Simple terminal based application launcher for Linux, written in C.

## Table of Contents
+ [Todos](#todos)
+ [Documentation](#documentation)
    + [Installation](#installation)
    + [Configuration](#configuration)
    + [Usage](#usage)
    + [Keys](#keys)

## [Todos](#todos)
- [ ] Customization of input, value and list items styles.
- [ ] Customization of direcotries in which applications should be searched.
- [ ] More configuration options.
- [ ] Better configuration options handling.

## [Documentation](#documentation)
### [Installation](#installation)
Clone git repo
```
git clone --depth 1 https://github.com/MaksimsTurs/term-launcher.git .
```
Run make script
```
make
```
Make launcher runnable globaly ([how to make programm runnable globaly](https://unix.stackexchange.com/questions/3810/how-can-i-make-a-program-executable-from-everywhere)).

### [Use](#use)
Run `launcher` in your terminal this will open a small input in which you can write the name of the application that you want to run, to select the application, use the arrow up/down keys to move the cursor. If you want that terminal in which you run the application to be closed, run `launcher` with the `-c` flag.

![example](./readme/1.png)
> [!WARNING]
> Term launche support only ASCII characters, special characters like German "ü", "ö" or "ä" are not supported!

### [Configuration](#configuration)
To configure launcher styles you need to create a `conf.toml` file in you'r home `.config` directory, full directory should be `$HOME/.config/launcher/conf.toml`.
Currently launcher supports following properties:

**selected.format**:\
**unselected.format**:\
**input.format**: Set the custom print format, if you use custom format you need to reset the styles and adding the `\n` character manually, this would be correct value
```
[input]
    format = "Execute \x1b[0m(%s)\n"
                                  ^- must be added manually
[selected]
    format = "  » %s «  \x1b[0m\n"
                                ^- must be added manually
[unselected]
    format = "%s\x1b[0m\n"
                        ^- must be added manually
```
**selected.bg**:\
**unselected.bg**:\
**input.bg**: Set the background color, this would be correct value
```
[input]
          R    G   B
    bg = [255, 50, 150]
[selected]
          R   G    B
    bg = [50, 150, 255]
[unselected]
          R    G    B
    bg = [150, 255, 50]
```
**selected.fg**:\
**unselected.fg**:\
**input.fg**: Set the font color.
```
[input]
          R    G   B
    fg = [255, 50, 150]
[selected]
          R   G    B
    fg = [50, 150, 255]
[unselected]
          R    G    B
    fg = [150, 255, 50]
```

### [Keys](#keys)
| Key       | Description        |
| --------- | ------------------ |
| Esc       | Close the launcher |
| Arr. Up   | Move cursor up     |
| Arr. Down | Move cursor down   |
