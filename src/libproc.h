/*
 * C-Ware License
 * 
 * Copyright (c) 2022, C-Ware
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Redistributions of modified source code must append a copyright notice in
 *    the form of 'Copyright <YEAR> <NAME>' to each modified source file's
 *    copyright notice, and the standalone license file if one exists.
 * 
 * A "redistribution" can be constituted as any version of the source code
 * that is intended to comprise some other derivative work of this code. A
 * fork created for the purpose of contributing to any version of the source
 * does not constitute a truly "derivative work" and does not require listing.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * @docgen: project
 * @brief: handle processes in a portable way
 * @name: libproc
 *
 * @embed constant: LIBPROC_ABORTED
 * @embed constant: LIBPROC_SLEEP_MILLI
 * @embed constant: LIBPROC_SLEEP_SECOND
 * @embed function: libproc_sleep
 *
 * @description
 * @libproc is a library that aims to allow cross platform handling of
 * @processes, and providing utility functions that can make dealing with
 * @processes easier.
 * @
 * @table
 * @sep: ;
 * @Manual;Description
 * @libproc_sleep(cware);microsecond sleeping
 * @table
 * @description
 *
 * @reference: cware(cware)
*/

#ifndef CWARE_LIBPROC_H
#define CWARE_LIBPROC_H

#include "liberror/liberror.h"

/*
 * Represents the exit code returned by the operating system's native
 * libc when the abort(3) function is called. Operating systems such
 * as VAX ULTRIX, seem to intentionally have the function use an
 * illegal instruction, but even though this might not be a program
 * abortion in the typical sense, it is still the exit code from abort(3).
*/

/*
 * @docgen: constant
 * @name: LIBPROC_ABORTED
 * @brief: the exit code from the abort(3) function
 * @value: 134
*/
#if defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__) || \
    defined(__OpenBSD__) || defined(__sun)
#define LIBPROC_ABORTED 134
#endif

#if defined(__ultrix__)
#define LIBPROC_ABORTED 132
#endif

/*
 * Some useful constants for dealing with sleeping in pre-determined
 * intervals based off microseconds.
*/

/*
 * @docgen: constant
 * @name: LIBPROC_SLEEP_MILLI
 * @brief: one millisecond in microseconds
 * @value: 1000
*/
#define LIBPROC_SLEEP_MILLI     (1000)

/*
 * @docgen: constant
 * @name: LIBPROC_SLEEP_SECOND
 * @brief: one second in microseconds
 * @value: 1000000
*/
#define LIBPROC_SLEEP_SECOND    (LIBPROC_SLEEP_MILLI * 1000)

/*
 * @docgen: function
 * @brief: put the thread to sleep for a n microseconds
 * @name: libproc_sleep
 *
 * #include: libproc.h
 *
 * @description
 * @This function will allow the programmer to put the running thread or
 * @process to sleep for a given number of microseconds.
 * @description
 *
 * @example
 * @#include <stdio.h>
 * @#include "libproc.h"
 * @
 * @int main(void) {
 * @    // Sleep for one second
 * @    libproc_sleep(LIBPROC_SLEEP_SECOND);
 * @
 * @    return 0;
 * @}
 * @example
 *
 * @error: microseconds is NULL
 *
 * @param microseconds: the number of microseconds to sleep
 * @type: int
*/
void libproc_sleep(int microseconds);











#endif
