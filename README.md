Windows Console Pong
===
A simple Pong game for Windows terminals.
---
This game is windows-only as it depends upon the C++ Win32 API. It was completed on 2020/07/07.

![The game has variable difficulty!](img/difficulty-screen.png)

![Screenshot of the gameplay.](img/game-screen.png)

### Install on Windows
* [Install Git Bash](https://git-scm.com/download/win); make sure to choose "Run Git from the Windows Command Prompt" during installation. This should result in a MINGW64 Bash installation that can access your Windows PATH while having access to Linux commands (ie. the `find` command).
* [Clone this repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository#cloning-a-repository) to a directory on your computer. That directory will be referred to as `root`.
* Install [Make for Windows](https://gnuwin32.sourceforge.net/packages/make.htm); the location of `make.exe` should be `C:\Program Files (x86)\GnuWin32\bin\make.exe`.
* Add `C:\Program Files (x86)\GnuWin32\bin\` to the Windows Environment Variable [PATH](https://www.computerhope.com/issues/ch000549.htm).

From here, everything should be installed to compile & run this software.

### Compile & Run Scripts
To run a script, open a Bash (or equivalent) terminal within `root` and type the command.

| command | description |
|:----------- |:----------- |
| `make` | compile & link the program |
| `make clean` | remove all compiled files |

### Contribute
Unfortunately, this project doesn't support community contributions right now. Feel free to fork, but be sure to read the license.
