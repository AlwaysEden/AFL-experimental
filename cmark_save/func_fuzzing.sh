#!/bin/sh
cd fuzz1

cp ../target.json ./

../../../afl-fuzz -i ../../good_input/ -o ./findings0 -R target.json ../.libs/pngfix @@ &
program_pid0=$!

mkdir ../fuzz2
cd ../fuzz2
cp ../target.json ./
../../../afl-fuzz -i ../../good_input/ -o ./findings0 -R target.json ../.libs/pngfix @@ &
program_pid1=$!

mkdir ../fuzz3
cd ../fuzz3
cp ../target.json ./

../../../afl-fuzz -i ../../good_input/ -o ./findings0 -R target.json ../.libs/pngfix @@ &
program_pid2=$!

mkdir ../fuzz4
cd ../fuzz4
cp ../target.json ./
../../../afl-fuzz -i ../../good_input/ -o ./findings0 -R target.json ../.libs/pngfix @@ &
program_pid3=$!

mkdir ../fuzz5
cd ../fuzz5
cp ../target.json ./
../../../afl-fuzz -i ../../good_input/ -o ./findings0 -R target.json ../.libs/pngfix @@ &
program_pid4=$!


sleep 3600

        kill -9 $program_pid0
        kill -9 $program_pid1
        kill -9 $program_pid2
        kill -9 $program_pid3
        kill -9 $program_pid4


