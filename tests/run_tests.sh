#!/bin/bash

find ../build -name "*Tests" -maxdepth 1 | while read test; do
    echo "Running test '$test'"
    $test
done