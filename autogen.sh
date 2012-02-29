#!/bin/sh
#
# autogen.sh for libquvi
# Copyright (C) 2011  Toni Gundogdu
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301  USA
#
set -e

source=.gitignore
cachedir=autom4te.cache

gen_manual()
{
  echo "Generate manual..."
  MAN=doc/man3/libquvi.3 ; POD=$MAN.pod ; VN=`./gen-ver.sh`
  pod2man -c "libquvi manual" -n libquvi -s 3 -r "$VN" "$POD" "$MAN"
  return $?
}

cleanup()
{
  echo "WARNING!
Removes _files_ listed in $source and $cachedir directory.
Last chance to bail out (^C) before we continue."
  read n1
  [ -f Makefile ] && make distclean
  for file in `cat $source`; do # Remove files only.
    [ -e "$file" ] && [ -f "$file" ] && rm -f "$file"
  done
  [ -e "$cachedir" ] && rm -rf "$cachedir"
  exit 0
}

help()
{
  echo "Usage: $0 [-c|-h]
-h  Show this help and exit
-c  Make the source tree 'maintainer clean'
Run without options to (re)generate the configuration files."
  exit 0
}

while [ $# -gt 0 ]
do
  case "$1" in
    -c) cleanup;;
    -h) help;;
    *) break;;
  esac
  shift
done

echo "Generate configuration files..."
autoreconf -if && gen_manual && echo "You can now run 'configure'"
