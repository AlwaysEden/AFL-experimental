mkdir -p afl-build || exit 1
cd afl-build || exit 1
#cleanup
rm -r -- *

CC=../../../afl-clang-fast cmake ../.. -DENABLE_FUZZING=On -DENABLE_SANITIZERS=On -DBUILD_SHARED_LIBS=Off

cd fuzzing

make

clang -fsanitize=address -c ../../trace-pc-guard.c
clang -fsanitize=address -fsanitize-coverage=trace-pc-guard,func ../../afl.c ../../../cJSON.c trace-pc-guard.o -o target_For_FuncCov

cp ../../target.json ./

/mnt/hdd/fuzz_usability/AFL++experimental/afl-fuzz -i /mnt/hdd/fuzz_usability/AFL++experimental/cJSON/fuzzing/inputs -o ../../afl++_test/findings0 -R target.json ./afl-main yes 
program_pid0=$!

#/mnt/hdd/fuzz_usability/AFL++experimental/afl-fuzz -i /mnt/hdd/fuzz_usability/AFL++experimental/cJSON/fuzzing/inputs -o ../../afl++_test/findings0 -r target.json ./afl-main @@ yes &
program_pid1=$!

#/mnt/hdd/fuzz_usability/AFL++experimental/afl-fuzz -i /mnt/hdd/fuzz_usability/AFL++experimental/cJSON/fuzzing/inputs -o ../../afl++_test/findings0 -r target.json ./afl-main @@ yes &
program_pid2=$!

#/mnt/hdd/fuzz_usability/AFL++experimental/afl-fuzz -i /mnt/hdd/fuzz_usability/AFL++experimental/cJSON/fuzzing/inputs -o ../../afl++_test/findings0 -r target.json ./afl-main @@ yes &
program_pid3=$!

#/mnt/hdd/fuzz_usability/AFL++experimental/afl-fuzz -i /mnt/hdd/fuzz_usability/AFL++experimental/cJSON/fuzzing/inputs -o ../../afl++_test/findings0 -r target.json ./afl-main @@ yes &
program_pid4=$!

sleep 3700

kill -9 $program_pid0
kill -9 $program_pid1
kill -9 $program_pid2
kill -9 $program_pid3
kill -9 $program_pid4
	
