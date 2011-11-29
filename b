#!/bin/sh
qmake CONFIG+=debug -recursive
make -j 8 && ./run-tests $*
