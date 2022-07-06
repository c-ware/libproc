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
 * Implementations of the libproc_sleep(cware) function. This file contains
 * two macros that are used to tell the sleep function which kind of behavior
 * to take.
 *
 * LIBPROC_USE_SELECT       use select for microsecond sleeping
 * LIBPROC_USE_USLEEP       use sleep and usleep for microsecond sleeping
*/


/* ULTRIX uses time.h to store select for some reason */
#if defined(ultrix) 
#define LIBPROC_USE_SELECT
#include <time.h>
#endif

/* OpenVMS has no support for select(2), and only has poll(2), but
 * it has sleep(3) and usleep(3). */
#if defined(VMS)
#include <unistd.h>
#define LIBPROC_USE_USLEEP
#endif

/* These operating systems are normal and store select in
 * sys/select.h. */
#if defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__) || \
    defined(__OpenBSD__) || defined(__sun)
#define LIBPROC_USE_SELECT
#include <sys/select.h>
#endif

#include "libproc.h"

#define ONE_SEC_IN_USEC 1000000

void libproc_sleep(int microseconds) {
    struct timeval timer = {0, 0};

    liberror_is_negative(libproc_sleep, microseconds);

    timer.tv_usec = microseconds % ONE_SEC_IN_USEC;
    timer.tv_sec = (microseconds - timer.tv_usec) / ONE_SEC_IN_USEC;

#if defined(LIBPROC_USE_SELECT)
    select(0, NULL, NULL, NULL, &timer);
#endif

#if defined(LIBPROC_USE_USLEEP)
    sleep(timer.tv_sec);
    usleep(timer.tv_usec);
#endif
}
