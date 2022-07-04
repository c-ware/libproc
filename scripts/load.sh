#!/bin/sh
# Load documentation and Makefiles. Requires docgen and makegen
# as dependencies. Although, this realistically should not be
# ran by end users, and should instead be ran by developers.

docgen project ./src/libproc.h --section cware              \
                               --format manpage             \
                               --title 'C-Ware Manuals'     \
                               --date "`date +'%B %d, %Y'`" \
                               --include 'libproc.h'

#makegen library unix --name libcstring \
#                     --cflags '\-fpic' > Makefile
