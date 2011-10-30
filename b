#!/bin/sh
qmake
make -j && ./run-tests $*
