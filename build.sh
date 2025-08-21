#!/bin/sh

export PS4SDK=../

cd libPS4
make

cd ../kpayload
make

cd ../installer
make

cp installer.bin ../ps4hen_lite_5.05-12.02.bin
