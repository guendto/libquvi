#!/bin/sh
#
# gen-news.sh for libquvi
# Copyright (C) 2012  Toni Gundogdu
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
IFS=$'
'
a=`grep < ~/.gitconfig name | cut -f2 -d= | sed 's/^\s*//'`
v=`./gen-ver.sh`
d=`date +%F`
b="$v ($d) / $a

"
t=`git tag | tail -n1`
for a in `git log --format='%an' "$t"..HEAD | sort | uniq`; do
  c=`git log --format="  - %s [%h]" --author="$a" "$t"..HEAD | sort -h`
  b="$b$a:
$c
"
done
b="$b
`git diff --stat-width=72 "$t"..HEAD`

"
n=`cat NEWS`
F=NEWS
echo "$b"  >"$F" ; echo "$n" >>"$F"
