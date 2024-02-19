#!/bin/bash

find ../cmake-build-debug -name "*Tests" -maxdepth 1 | while read test; do
    echo "Running test '$test'"
    $test
done