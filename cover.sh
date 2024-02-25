#!/bin/bash

rm -rf reports
mkdir -p reports
mv *.gcda *.gcno reports

cd reports
find src -name '*.c' -exec gcov {} \+;

lcov --capture --directory . --output-file main_coverage.info
genhtml main_coverage.info --output-directory pages
open pages/index.html

cd ../
