# Metafetch

A simple tool to extract and edit metadata and hex.

## Installation

### Dependencies:
#### Exiftool:
- Ubuntu: `sudo apt install exiftool`
- Arch: [Follow this tutorial](https://www.geeksforgeeks.org/installing-and-using-exiftool-on-linux/)

### CMake
- Ubuntu: `sudo apt install cmake`
- Arch: `sudo pacman -S cmake`

## Install
```bash
git clone https://github.com/LucasVChaves/metafetch.git
cd metafetch
cmake .
make
sudo make install
```

## Current Features
- [X] Hexdump
- [X] Metadata extraction
- [ ] Hex manipulation
- [ ] Metadata edition
- [ ] UI (Maybe)

## CLI Usage

|  Argument  | Function      |
|------------|---------------|
| -F / --file           |    Path to the file to open.     | 
| -d / --hexdump        |    Flag for Hexdump     | 
| -m / --edit-hex       |    Flag for opening Hex Editor     | 
| -f / --fetch-metadata |    Flag for fetching file's metadata     | 
| -e / --edit-metadata  |    Flag for opening Metadata Editor    | 
| -o / --output         | Output path (if not provided will print on terminal) |
| -v / --version        | Show the version of the tool |
| -h / --help           | Show this help message | 

## Editor Usage
VIM inspired keybindings and functions.

| Navigation | Key      | Function |
|------------|----------|----------|
| Left       |    h     | Move cursor 1 char left  |
| Down       |    j     | Move cursor 1 char down  |
| Up         |    k     | Move cursor 1 char up    |
| Right      |    l     | Move cursor 1 char right |
| Toggle Mode|    i     | Toggle normal / edit mode|
| Top of File| ctrl + t | Move cursor to top of file|
| Bot of File| ctrl + b | Move cursor to bottom of file|
| Undo       | ctrl + z | Undo last action |
| Redo       | ctrl + y | Redo last undid action |


| Shortcuts  | Key      | Function |
|------------|----------|----------|
| Open File  | ctrl + o | Select file path to open |
| Save File  | ctrl + s | Saves current file changes |
| Find Expr  | ctrl + f | Find expression in open file |
| Line Jump  | ctrl + l | Jump to line number |
|    Help    | ctrl + ? | Show help screen |
|*Toggle Edit|   TAB    | Toggle edit between Hex and ASCII |

***: Only works in hex editor.**

## Examples

Hexdumping a file and outputting to a file:  
```bash
./metafetch -F /bin/somebinarie.o -d -o /tmp/hexdump.txt
```

Fetching metadata from an image and not using the output flag:  
```bash
./metafetch --file /img/funnycat.png --fetch-metadata
```
