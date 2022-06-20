#!/bin/sh
#
# NEURON IIoT System for Industry 4.0
# Copyright (C) 2020-2022 EMQ Technologies Co., Ltd All rights reserved.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 3 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

set -e -u

SCRIPTNAME=$(basename "$0")

usage() {
  echo "Convert deb package into rpm package for neuron"
  echo "Usage: $SCRIPTNAME file"
}

if [ $# -eq 0 ]
then
  usage
  exit 1
fi

debfile=$1
rpmfile=${debfile%.deb}.rpm
version=$(dpkg-deb -f $debfile version)
release=$(echo $version | cut -d . -f1)
builddir=neuron-${version}
specfile=neuron-${version}-${release}.spec

# generate package directory, that is $builddir
alien -v -g -c -r $debfile

# tweak rpm spec
cd $builddir
# filter out dependencies
sed -i '/\%description/i \
%global privlibs libneuron-base\
%global privlibs %{privlibs}|libzlog\
%global __requires_exclude ^(%{privlibs})\\.so\
' $specfile
# set built rpm file name
sed -i "/\%define _rpmfilename.*/c %define _rpmfilename ${rpmfile}" $specfile

# build rpm package
rpmbuild --buildroot $(pwd) -bb $specfile
