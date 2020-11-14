#ifndef TRACE_NODE_H
#define TRACE_NODE_H

typedef struct TRACE_NODE_STRUCT {
	char * functionid;
	struct TRACE_NODE_STRUCT * next;
} TRACE_NODE;

/* function prototypes */
void PUSH_TRACE(char * p);

void POP_TRACE();

char * PRINT_TRACE();

void * REALLOC(void * p, int t, char * file, int line);

void * MALLOC(int t, char * file, int line);

void FREE(void * p, char * file, int line);

#endif