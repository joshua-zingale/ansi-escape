# Interactive Ansi Escape

[ANSI escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code) are
supported by most terminals and allow for the creation of Terminal User
Interfaces (TUIs). Escape codes look like `\x1b[1;31m`, `\n`, or `\e[H`, for
example, and specify visual actions in the terminal.

To learn more about these escape codes, I created this interactive TUI for
typing in escape codes and seeing the immediate visual feedback.

## Compilation

The compilation process may itself be compiled by CMake. So to compile the code,
in the root of this repository, do

```bash
cmake . && cmake --build .
```

## Running

After compiling the binary, you may run it with

```bash
./interactive-ansi-escape $LINE $COLUMN
```

on a UNIX-like operating system. `$LINE` and `$COLUMN` are the height and width
respectively, in characters, of the terminal emulator. If you are on Windows or
for some other reason do not have those environment variables defined, you may
instead manually pass in the height and width with

```bash
./interactive-ansi-escape 42 136
```

## Usage

In the bottom, you may type in an arbitrary sequence of characters, including
ANSI escapes. After pressing enter, the sequence (with the newline you entered
with ENTER being removed), is drawn to the canvas above. The session will stay
open until you type CTRL+C.
