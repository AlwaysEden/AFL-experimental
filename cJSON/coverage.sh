cd ../../
make distclean

CC=clang CCASFLAGS="-fprofile-instr-generate -fcoverage-mapping" CFLAGS="-fprofile-instr-generate -fcoverage-mapping" ./configure

make
cd -
gcc -o exec exec_test.c -DDEBUG

./exec

llvm-profdata merge -sparse rawdata* -o covdata

rm rawdata*

llvm-cov show ../../.libs/pngfix -instr-profile=covdata >> covdata_file.txt

