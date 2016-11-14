/* shellnoise.c -- VERSION 0.0.1
 *
 *                   _          _ _             _          
 *  BSD /        ___| |__   ___| | |_ __   ___ (_)___  ___ 
 *     / C99    / __| '_ \ / _ \ | | '_ \ / _ \| / __|/ _ \
 *              \__ \ | | |  __/ | | | | | (_) | \__ \  __/
 *              |___/_| |_|\___|_|_|_| |_|\___/|_|___/\___|               
 *                                          
 *
 *                 A BSD Licensed Guerrilla Shell Library 
 *     Against the idea that a shell lib needs 20,000K lines of C code.
 *
 * You can find the latest source code at:
 *
 *                 http://github.com/sonophoto/shellnoise
 *
 * Makes a number of crazy assumptions that happen to be true in 99.9942%
 * of the 2010 - 2016 unix/POSIX/GNU/*Linux/*BSD computers around.
 */
 
/* ------------------------------------------------------------------------
 * B S D  T W O  C L A U S E  L I C E N S E  A N D  C O P Y R I G H T S
 * ------------------------------------------------------------------------
 * Original Linenoise Functions:
 * Copyright (c) 2010-2014, Salvatore Sanfilippo <antirez at gmail dot com>
 * Copyright (c) 2010-2013, Pieter Noordhuis <pcnoordhuis at gmail dot com>
 *
 * UTF-8 Utility Functions:
 * Copyright (c)      2015, Yhirose [github.com/yhirose]
 *
 * Additional Shell Functions:
 *  Copyright (c) 2015-2016, Brig Young [github.com/sonophoto]
 *
 * Names have been changed to protect namespaces.
 *
 *                ----- All rights reserved. -----
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/* ------------------------------------------------------------------------
 * F E A T U R E S   S P E C   A N D   T O D O   L I S T
 * ------------------------------------------------------------------------
 * Todo list (from linenoise):
 * - Filter bogus Ctrl+<char> combinations.
 * - To the devil with Win32/Windows and any other non-POSIX systems
 *
 * Todo Shellnoise 
 *       (a simple shell building system in the tradition of linenoise)
 *       (Static linked single file include, simple, plain, self documented)
 *
 * - Create a very basic type of shell for creating library interfaces:
 *   - Greatly improved tab completion with command and filesystem awareness
 *   - simple variable system (shvar "a" = "b"; shvar "a" returns b) (string = string)
 *   - simple alias system (alias "a" "b"; "a" returns "b") (name = command)
 *   - simple job system (&& || Ctrl-z bj fj lj background, foreground, list)
 *   - simple pipeline system (> >> < | tee STIN STOUT STERR)
 *   - built-in commands such as cd, pushd, popd, shvar, tee, bj, fj, lj, etc 
 *   - Under 5000K lines of C code in the style of redis and linenoise
 */
 
/* ------------------------------------------------------------------------
 * T E R M I N A L   C O N T R O L   T H E O R Y   A N D   M E T H O D 
 * ------------------------------------------------------------------------
 * List of escape sequences used by this program, we do everything just
 * with three sequences. In order to be so cheap we may have some
 * flickering effect with some slow terminal, but the lesser sequences
 * the more compatible.
 *
 * References:
 * - http://invisible-island.net/xterm/ctlseqs/ctlseqs.html
 * - http://www.3waylabs.com/nw/WWW/products/wizcon/vt220.html
 *
 * EL (Erase Line)
 *    Sequence: ESC [ n K
 *    Effect: if n is 0 or missing, clear from cursor to end of line
 *    Effect: if n is 1, clear from beginning of line to cursor
 *    Effect: if n is 2, clear entire line
 *
 * CUF (CUrsor Forward)
 *    Sequence: ESC [ n C
 *    Effect: moves cursor forward n chars
 *
 * CUB (CUrsor Backward)
 *    Sequence: ESC [ n D
 *    Effect: moves cursor backward n chars
 *
 * The following is used to get the terminal width if getting
 * the width with the TIOCGWINSZ ioctl fails
 *
 * DSR (Device Status Report)
 *    Sequence: ESC [ 6 n
 *    Effect: reports the current cusor position as ESC [ n ; m R
 *            where n is the row and m is the column
 *
 * When multi line mode is enabled, we also use an additional escape
 * sequence. However multi line editing is disabled by default.
 *
 * CUU (CUrsor Up)
 *    Sequence: ESC [ n A
 *    Effect: moves cursor up of n chars.
 *
 * CUD (CUrsor Down)
 *    Sequence: ESC [ n B
 *    Effect: moves cursor down of n chars.
 *
 * When linenoiseClearScreen() is called, two additional escape sequences
 * are used in order to clear the screen and position the cursor at home
 * position.
 *
 * CUP (CUrsor Position)
 *    Sequence: ESC [ H
 *    Effect: moves the cursor to upper left corner
 *
 * ED (Erase Display)
 *    Sequence: ESC [ 2 J
 *    Effect: clear the whole screen
 */

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "linenoise.c"
