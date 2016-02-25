/* shellnoise.h -- VERSION 0.1
 *
 *         Guerrilla shell library against the idea
 *   that a shell lib needs to be 20,000+ lines of C code.
 *
 * You can find the latest source code at:
 *
 *   http://github.com/sonophoto/shellnoise
 *
 * Makes a number of crazy assumptions that happen to be true in 99.9942%
 * of the 2010 - 2016 unix/POSIX/GNU/*Linux/*BSD computers around.
 *
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2010-2014, Salvatore Sanfilippo <antirez at gmail dot com>
 * Copyright (c) 2010-2013, Pieter Noordhuis <pcnoordhuis at gmail dot com>
 *
 * UTF-8 Utility Functions:
 * Copyright (c)      2015, Yhirose [github.com/yhirose]
 *
 * Additional Shell Functions:
 * Copyright (c) 2015-2016, Brig Young [github.com/sonophoto]
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

#ifndef SHELLNOISE_SP_H
#define SHELLNOISE_SP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct linenoiseCompletions {
  size_t len;
  char **cvec;
} linenoiseCompletions;

typedef void(linenoiseCompletionCallback)(const char *, linenoiseCompletions *);
void linenoiseSetCompletionCallback(linenoiseCompletionCallback *);
void linenoiseAddCompletion(linenoiseCompletions *, const char *);

char *linenoise(const char *prompt);
int linenoiseHistoryAdd(const char *line);
int linenoiseHistorySetMaxLen(int len);
int linenoiseHistorySave(const char *filename);
int linenoiseHistoryLoad(const char *filename);
void linenoiseClearScreen(void);
void linenoiseSetMultiLine(int ml);
void linenoisePrintKeyCodes(void);

typedef size_t (linenoisePrevCharLen)(const char *buf, size_t buf_len, size_t pos, size_t *col_len);
typedef size_t (linenoiseNextCharLen)(const char *buf, size_t buf_len, size_t pos, size_t *col_len);
typedef size_t (linenoiseReadCode)(int fd, char *buf, size_t buf_len, int* c);

void linenoiseSetEncodingFunctions(
    linenoisePrevCharLen *prevCharLenFunc,
    linenoiseNextCharLen *nextCharLenFunc,
    linenoiseReadCode *readCodeFunc);

/* UTF-8 functions from yhirose */
size_t linenoiseUtf8PrevCharLen(const char* buf, size_t buf_len, size_t pos, size_t *col_len);
size_t linenoiseUtf8NextCharLen(const char* buf, size_t buf_len, size_t pos, size_t *col_len);
size_t linenoiseUtf8ReadCode(int fd, char* buf, size_t buf_len, int* cp);

/* Shell functions from sonophoto */

#ifdef __cplusplus
}
#endif

#endif /* SHELLNOISE_SP_H */
