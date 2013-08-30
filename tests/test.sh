#!/bin/bash

COMPILE="clang++ -O2 -std=c++11 -pedantic -Wall -Wextra -lboost_unit_test_framework"
COMPILE_ADDRESS="$COMPILE -fsanitize=address -fno-omit-frame-pointer -g"
COMPILE_MEMORY="$COMPILE -fsanitize=memory -fno-omit-frame-pointer -g"

for file in *.cpp; do
    file_name=${file%.*}
    echo "[${file_name}]: BUILDING..."
    $COMPILE_ADDRESS $file -o "${file_name}a"
    $COMPILE_MEMORY $file -o "${file_name}m"
    echo "[${file_name}]: RUNNING adress..."
    ./${file_name}a
    echo "[${file_name}]: RUNNING memory..."
    ./${file_name}m
    echo "[${file_name}]: DONE!"
    mv "${file_name}a" "tmp/${file_name}a"
    mv "${file_name}m" "tmp/${file_name}m"
done

