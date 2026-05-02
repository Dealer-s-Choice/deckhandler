[![Linux](https://github.com/Dealer-s-Choice/deckhandler/actions/workflows/linux.yml/badge.svg)](https://github.com/Dealer-s-Choice/deckhandler/actions/workflows/linux.yml)
[![Windows](https://github.com/Dealer-s-Choice/deckhandler/actions/workflows/windows.yml/badge.svg)](https://github.com/Dealer-s-Choice/deckhandler/actions/workflows/windows.yml)
[![MacOS](https://github.com/Dealer-s-Choice/deckhandler/actions/workflows/macos.yml/badge.svg)](https://github.com/Dealer-s-Choice/deckhandler/actions/workflows/macos.yml)

The code for this library has been moved into [Dealer's
Choice](https://github.com/Dealer-s-Choice/dealers-choice), and this project
will be archived.

# deckhandler
Library that will create a deck of cards and shuffle it.

Detailed example usage can be seen in
[test/test_01.c](https://github.com/Dealer-s-Choice/deckhandler/blob/master/test/test_01.c).

Commented types and functions in
[deckhandler.h](https://github.com/Dealer-s-Choice/deckhandler/blob/master/deckhandler.h)

## Dependencies

* [meson](http://mesonbuild.com/Quick-guide.html) (for the build system)

## Building

    meson setup builddir
    cd builddir
    ninja

## Tests

    ninja test

## Installation

To specify the installation directory (defaults to /usr/local) and
install the program:

    From *builddir*: `meson configure --prefix=
    ninja install

To uninstall:

    ninja uninstall

## Projects that use deckhandler

* [Dealer's Choice](https://github.com/Dealer-s-Choice/dealers-choice)

## Using the library with other languages

See [SWIG_INTERFACE.md](https://github.com/Dealer-s-Choice/deckhandler/blob/master/SWIG_INTERFACE.md)
