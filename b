#!/bin/sh
qmake
make -j 8 && ./run-tests $*
