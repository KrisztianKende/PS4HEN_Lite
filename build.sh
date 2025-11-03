#!/bin/sh

export PS4SDK=../

cd libPS4
make

cd ../kpayload
make

cd ../installer
make

cp installer.bin ../ps4hen_lite_5.05-13.00.bin
