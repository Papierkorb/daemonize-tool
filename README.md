Korbs Daemonize Tool
====================

A little C tool to start GUI applications and open files.

### Why?

Starting GUI applications on Linux from your shell is annoying. First, you add
the ampersand to the line to daemonize it. Afterwards the program will continue
to clutter your screen with random log output. How nice. So you add
`2>&1 >/dev/null`. On zsh, you also want to type `disown` afterwards, else it
will deny to close because a job is still running. And so on.

Ugh. How hard can it be? And that's why I wrote this tool. It's designed to not
have any dependencies, and only requires a C89 compatible C compiler.

As little extra, if it detects that you want to open a path, file, or URL,
it'll act as wrapper to `xdg-open`.

## Installation

    $ make
    # make install # Or copy 'd' to some directory in your $PATH manually

That's it. If you're using zsh, copy `_d` into a directory in your `$fpath` for
auto-completion:

    # cp _d /usr/local/share/zsh/site-functions
    $ exec zsh   # Reload zsh afterwards

## Usage

1. `d <Application-in-PATH> <Arguments to that application ...>`
2. `d <File, path or URL>`

## Examples

* Start firefox (Or any other application): `$ d firefox`
* Start firefox with a URL: `$ d firefox https://github.com/`
* Open a path with the default application: `$ d fileOrPath`
* Open a URL with the default application: `$ d http://example.com/` or `$ d mailto:foo@bar.com`
* Open the current working directory in a graphical browser: `$ d .`

## Behaviour

When **d** is started ..

1. If no arguments are given, print usage and exit
2. If more than one argument are given, start the application with those arguments 
3. If one argument is given, search for it in `$PATH`, and if found, start that. Else, start `xdg-open` on that path/file

## License (3-clause BSD)

Copyright (c) 2015, Stefan 'Papierkorb' Merettig
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

## Contributing

Just follow the code style already in the file. Functions would be nice, apart
from that, the tool shall remain in a single source file. If your feature is too
complex for that, it's too complex for d :)
