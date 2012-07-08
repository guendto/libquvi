#!/bin/sh
#
# libquvi
# Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.
#
set -e

C='\n' # delimiter
O= # output buffer
T= # tests

dump_tests()
{
  O=; for t in $T; do
    O="$O$t$C"
  done
  echo "$O" | sed 's/,$//'
}

find_tests()
{
  dir=`dirname $0`
  T=`find $dir -maxdepth 1 -name '*.c' -type f -exec sh -c '
    for f; do
      sed -n <"$f" "s/^static void \(test_.*\)()/\1/p"
    done' _ {} +`
  return 0
}

help()
{
  echo "Usage: $0 [OPTIONS]
-h  Show this help and exit
-c  Use comma to separate test names"
  exit 0
}

while [ $# -gt 0 ]
do
  case "$1" in
    -h) help;;
    -c) C=,;;
    *) break;;
  esac
  shift
done

find_tests
dump_tests

# vim: set ts=2 sw=2 tw=72 expandtab:
