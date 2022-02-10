# tinyscheme-embedded
Stripped and reorganized version of Tinyscheme for embedded enviroments.
In other words, this is a casual attempt to create a platform agnostic Scheme while being still useful.

In my opinion, Scheme is the best minimalist yet powerful language we can imagine.
For some time, I was trying get it run on common microcontrollers like ESP32, ESP8266 and STM32F103 (aka Blue Pill).
So I tried to remove platform dependent features from TinyScheme in order to make it usable on every enviroment with
enough memory.
Although it runs successfully on ESP32, it seems like there is not enough memory for ESP8266 *sigh*

This is an opinionated version of TinyScheme; symbols are case-sensitive, there is no loading mechanism for dynamic libraries,
interactive mode and most feature switches are removed or will be removed.
I plan to add a REPL loop as an example though.

It still passes nearly all cases of http://cvs.savannah.gnu.org/viewvc/*checkout*/scm/scm/r4rstest.scm except case-sensitivity ones.
(This is the test suite recommended by SLIB documentation).

In the future, I will add newlib style stubs to get rid of standard library dependency, too.