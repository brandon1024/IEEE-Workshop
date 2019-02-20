#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strbuf.h"

#define BUFF_LEN 64

void demonstrate_strbuf(void);
void print_buff(struct strbuf buff);
void print_buff_ptr(struct strbuf *buff);
void demonstrate_struct_usage();

int main(int argc, char *argv[])
{
	// Part 1: Demonstrate Struct Usage
	demonstrate_struct_usage();

	// Part 2: Using Structs
	demonstrate_strbuf();

	return 0;
}

void demonstrate_struct_usage()
{
	struct point_t {
		unsigned int x;
		unsigned int y;
		unsigned long id;
	};

	// Declare struct on stack
	struct point_t p0 = {.x = 1, .y = 12, .id = 0};

	// Allocate a struct on the heap
	struct point_t *p1 = (struct point_t *)malloc(sizeof(struct point_t));
	if(p1 == NULL) {
		perror("Fatal error: Cannot allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	p1->x = p0.x;
	p1->y = p0.y;
	p1->id = 1;

	free(p1);

	// Allocate an array of structs on the heap
	size_t len = 10;
	struct point_t *points = (struct point_t *)malloc(sizeof(struct point_t) * len);
	if(points == NULL) {
		perror("Fatal error: Cannot allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	free(points);
}

void demonstrate_strbuf(void)
{
	struct strbuf buff;
	strbuf_init(&buff);

	char *temporary = "C is a general-purpose";
	strbuf_attach(&buff, temporary, strlen(temporary));

	// Pass struct directly
	print_buff(buff);

	temporary = ", imperative computer programming language";
	strbuf_attach(&buff, temporary, strlen(temporary));

	// Pass by reference
	print_buff_ptr(&buff);

	strbuf_release(&buff);
}

void print_buff(struct strbuf buff)
{
	fprintf(stdout, "%.*s\n", (int)buff.len, buff.buff);
}

void print_buff_ptr(struct strbuf *buff)
{
	fprintf(stdout, "%.*s\n", (int)buff->len, buff->buff);
}