#ifndef ERRORS_H
#define	ERRORS_H

#define SUCCESS                     0
#define FAIL                        1
#define ERROR_INITIALIZE_EDGE       -1
#define ERROR_DESTROY_EDGE          -2
#define ERROR_MALLOC          -2

//int my_errorno;

void printError(int error_code);
   

#endif	/* ERRORS_H */

