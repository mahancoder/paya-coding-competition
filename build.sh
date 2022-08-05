#!/bin/bash

cmake -S . -B build
cd build/
make

cp question-1 ../question-1/
cp question-1-simple ../question-1/
cp question-2 ../question-2/
cp question-5 ../question-5/
cp question-7 ../question-7/