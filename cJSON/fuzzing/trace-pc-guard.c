#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sanitizer/coverage_interface.h>

#define LENGTH 256
#define MAX_FUNC 5

FILE *fp;
void * PC_prev = 0x0;
char filepath_prev[LENGTH];
int total_func;
char name_func[MAX_FUNC][LENGTH];
int already_covered[MAX_FUNC];
char cover = '1';	
// This callback is inserted by the compiler as a module constructor
// into every DSO. 'start' and 'stop' correspond to the
// beginning and end of the section with the guards for the entire
// binary (executable or DSO). The callback will be called at least
// once per DSO and may be called multiple times with the same parameters.
extern 
void 
__sanitizer_cov_trace_pc_guard_init(uint32_t *start, uint32_t *stop) 
{
	static uint64_t N;  // Counter for the guards.
	if (start == stop || *start) return;  // Initialize only once.
	for (uint32_t *x = start; x < stop; x++)
		*x = ++N;  // Guards should start from 1.

	fp = fopen("parsed_json", "r");
	if(fp == NULL){
		fprintf(stderr, "ERROR: NO function coverage file\n");
		exit(1);
	}
	char line[LENGTH];
	fgets(line, LENGTH, fp);
	total_func = atoi(line);
	for(int i = 0; i < total_func; i++){
		fgets(line, LENGTH,fp);
		line[strlen(line)-1] = 0x0;
		memcpy(name_func[i],line,strlen(line));
		//printf("name: %s\n", name_func[i]);
	}
	fclose(fp);
	fp = fopen("function_coverage","w+");

}	

// This callback is inserted by the compiler on every edge in the
// control flow (some optimizations apply).
// Typically, the compiler will emit the code like this:
//    if(*guard)
//      __sanitizer_cov_trace_pc_guard(guard);
// But for large functions it will emit a simple call:
//    __sanitizer_cov_trace_pc_guard(guard);
extern 
void 
__sanitizer_cov_trace_pc_guard(uint32_t *guard) 
{
	if (!*guard) return;  // Duplicate the guard check.
	// If you set *guard to 0 this code will not be called again for this edge.
	// Now you can get the PC and do whatever you want:
	//   store it somewhere or symbolize it and print right away.
	// The values of `*guard` are as you set them in
	// __sanitizer_cov_trace_pc_guard_init and so you can make them consecutive
	// and use them to dereference an array or a bit vector.
	
	void *PC = __builtin_return_address(0);
	char PcDescr[1024];
	__sanitizer_symbolize_pc(PC, "%p %F %L", PcDescr, sizeof(PcDescr));
	
	int i = 0;
	char *extract_function;
	extract_function = strtok(PcDescr, " ");
	for(i = 0; i < 2; i++){
		extract_function = strtok(NULL, " ");
	}
	
	//printf("Func: %s\n",extract_function);
	for(i = 0; i < total_func; i++){
		if(strcmp(extract_function,name_func[i]) == 0 && already_covered[i] == 0){
			putc(1,fp);
			already_covered[i]++;
			break;
		}
	}

}


