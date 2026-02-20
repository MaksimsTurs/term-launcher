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
- [x] Customization of input, value and list items styles.
- [ ] Customization of direcotries in which applications should be searched.
- [x] More configuration options.
- [x] Better configuration options handling.

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
Run `launcher` in your terminal this will open a small input in which you can write the name of the application that you want to run, to select the application, use the arrow up/down keys to move the cursor.

![example](./readme/1.png)

> [!WARNING]
> Term launche support only ASCII characters, special characters like German "ü", "ö" or "ä" are not supported!

### [Configuration](#configuration)
To configure input, input value, selected and unselected item styles you need to create a `conf.toml` file in you'r home `.config` directory, full directory should be `$HOME/.config/launcher/conf.toml`.
Currently launcher supports following options:

**[element.format]**: Set the custom printf format, example
```
[input]
    format = "Run: " 
[value]
    format = "%s"
               ^- placeholder for value
[selected]
    format = "  » %s «"
                   ^- placeholder for item label
[unselected]
    format = "%s"
                 ^- placeholder for item label
```
**[element.bg]**(default none): Set the background color, example
```
[input]
    bg = "#ff00ff"
[value]
    bg = "#00ffff"
[selected]
    bg = "#00ff00"
[unselecte]
    bg = "#ffff00"
```
**[element.fg]**(default none): Set the font color, example
```
[input]
    bg = "#ff00ff"
[value]
    bg = "#00ffff"
[selected]
    bg = "#00ff00"
[unselecte]
    bg = "#ffff00"
```
**[element.bold]**(default false): Make font bold, example
```
[input]
    bold = false
[value]
    bold = true
[selected]
    bold = false
[unselecte]
    bold = true
```
**[element.underline]**(default false): Add underline, example
```
[input]
    underline = false
[value]
    underline = true
[selected]
    underline = false
[unselecte]
    underline = false
```

### [Keys](#keys)
| Key       | Description        |
| --------- | ------------------ |
| Esc       | Close the launcher |
| Arr. Up   | Move cursor up     |
| Arr. Down | Move cursor down   |
