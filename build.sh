#!/bin/bash
set -e

export PS4SDK=../

pushd libPS4 >/dev/null
make
popd >/dev/null

pushd kpayload >/dev/null
make
popd >/dev/null

pushd installer >/dev/null
make
popd >/dev/null

rm -f ps4hen_lite_*.bin
mv installer/installer.bin ps4hen_lite_5.05-12.02.bin
