#!/bin/bash

# compile
rm -rf build
mkdir build
cd build
cmake ..
make

# run
./bin/tu_touche_coule

# gen test coverage
mkdir reports
cd ..
gcovr -r . --html --html-details -o build/reports/index.html

# watch the result
firefox build/reports/index.html &
