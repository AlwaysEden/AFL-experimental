clang -fprofile-instr-generate -fcoverage-mapping -o test ../afl.c ../../cJSON_origin.c

gcc -o exec exec_test.c -DDEBUG

./exec

llvm-profdata merge -sparse rawdata* -o covdata

rm rawdata*

llvm-cov show test -instr-profile=covdata > covdata_file.txt

