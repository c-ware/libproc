#!/bin/sh
# Load documentation and Makefiles. Requires docgen and makegen
# as dependencies. Although, this realistically should not be
# ran by end users, and should instead be ran by developers.

docgen project ./src/libproc.h --section cware              \
                               --format manpage             \
                               --title 'C-Ware Manuals'     \
                               --date "`date +'%B %d, %Y'`" \
                               --include 'libproc.h'

docgen functions ./src/libproc.h --section cware              \
                                 --format manpage             \
                                 --title 'C-Ware Manuals'     \
                                 --date "`date +'%B %d, %Y'`"

makegen library unix --name libproc \
                     --cflags '\-fpic' > Makefile

makegen library unix --name libproc \
                     --cflags '\-fpic \-Wall -Wextra -Wpedantic -Wshadow -ansi -g -Wno-unused-parameter -Wno-type-limits -Wno-sign-compare' > Makefile.dev
