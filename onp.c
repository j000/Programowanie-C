#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <unicode/ustdio.h>
#include <unicode/uchar.h>

/* #define char UChar */

/* bools */
typedef int bool;
#define true 1
#define false 0

/* dzialania */

/* priorytety dzialan arytmetycznych:
^ 4
* / 3
+ - 2
= 1
inne 0
*/
unsigned priority(char op) {
	#ifdef _DEBUG
	fprintf(stderr, "priority(%c)\n", op);
	#endif
	switch (op) {
		case '^':
			return 4;
		case '*':
		case '/':
			return 3;
		case '+':
		case '-':
			return 2;
		case '=':
			return 1;
		default:
			return 0;
	}
}

bool czy_operator(char input) {
	#ifdef _DEBUG
	fprintf(stderr, "czy_operator(%c)\n", input);
	#endif
	if (priority(input) > 0)
		return true;
	return false;
}

bool czy_nawias_otwierajacy(char input) {
	#ifdef _DEBUG
	fprintf(stderr, "czy_nawias_zamykajacy(%c)\n", input);
	#endif
	if (input == '(')
		return true;
	return false;
}

bool czy_nawias_zamykajacy(char input) {
	#ifdef _DEBUG
	fprintf(stderr, "czy_nawias_zamykajacy(%c)\n", input);
	#endif
	if (input == ')')
		return true;
	return false;
}

void dopisz_na_wyjscie(char out) {
	printf("%c", out);
}

/* stos */

#define STACK_TYPE char

typedef struct s_node node;
struct s_node {
    STACK_TYPE data;
    node* next;
};

bool is_empty(node*);
void push(node**, STACK_TYPE);
STACK_TYPE pop(node**);
STACK_TYPE peek(node*);

/* implementacja */

bool is_empty(node* stack) {
	if (stack == NULL)
		return true;
	return false;
}

void push(node** stack, STACK_TYPE new) {
	node* tmp = (node*)malloc(sizeof(node));
	#ifdef _DEBUG
	fprintf(stderr, "push(%c)\n", new);
	#endif
	tmp->next = *stack;
	tmp->data = new;
	*stack = tmp;
	/* debug * /
	fprintf(stderr, "\t");
	while (tmp != NULL) {
		fprintf(stderr, "%c -> ", tmp->data);
		tmp = tmp->next;
	}
	fprintf(stderr, "NULL\n");
	/* */
}

STACK_TYPE pop(node** stack) {
	node* tmp;
	STACK_TYPE out;
	#ifdef _DEBUG
	fprintf(stderr, "pop()\n");
	#endif
	if (*stack == NULL) {
		/* TODO: gracefully recover */
		fprintf(stderr, "ERROR: Popping from empty stack.\n");
		exit(EXIT_FAILURE);
	}
	tmp = *stack;
	*stack = tmp->next;
	out = tmp->data;
	free(tmp);
	#ifdef _DEBUG
	fprintf(stderr, "pop()\n");
	#endif
	return out;
}

STACK_TYPE peek(node* stack) {
	if (stack == NULL) {
		/* TODO: gracefully recover */
		fprintf(stderr, "ERROR: Peeking from empty stack.\n");
		exit(EXIT_FAILURE);
	}
	return stack->data;
}

/* **** */

int main(int argc, char** argv) {
	char input = 0;
	node* stack = NULL;
	char* line = NULL;
	int check = 0;
	int iterator = 0;
	size_t tmp = 0;

	check = getline(&line, &tmp, stdin);
	if (check == -1) {
		fprintf(stderr, "ERROR: getline failed.\n");
		exit(EXIT_FAILURE);
	}
	line[--check] = '\0';
	/* TODO: support argv */
	while (iterator != check) {
		/* wez kolejny element */
		input = line[iterator++];
		if (czy_operator(input)) {
			while (!is_empty(stack) && priority(peek(stack)) >= priority(input)) {
				dopisz_na_wyjscie(pop(&stack));
			}
			push(&stack, input);
		} else if (czy_nawias_otwierajacy(input)) {
			/* wstaw '(' na stos */
			push(&stack, input);
		} else if (czy_nawias_zamykajacy(input)) {
			/* zdejmuj ze stosu az do '(' */
			while (czy_operator(peek(stack))) {
				dopisz_na_wyjscie(pop(&stack));
			}
			pop(&stack);
		} else {
			/* operand/element */
			dopisz_na_wyjscie(input);
		}
	}
	while (!is_empty(stack)) {
		dopisz_na_wyjscie(pop(&stack));
	}
	printf("\n");
	exit(EXIT_SUCCESS);
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
