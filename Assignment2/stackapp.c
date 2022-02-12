/* stack.c: Stack application. */
/* Name: Xiaoying Li
 * Date: 10/21/2019 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"



/****************************************************************
	Using stack to check for unbalanced parentheses.
******************************************************************/

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}


/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: 	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */
	if (s == NULL) {
		return 1;
	}
	DynArr* stack = newDynArr(20);
	char character = nextChar(s);
	while (character != '\0') {
		if (character == '(' || character == '[' || character == '{') {
			pushDynArr(stack, character);
		}
		if (character==')' && topDynArr(stack)=='(')
		{
			popDynArr(stack);
		}
		if (character == ']' && topDynArr(stack) == '[') {
			popDynArr(stack);
		}
		if (character == '}' && topDynArr(stack) == '{')
		{
			popDynArr(stack);
		}
		character = nextChar(s);
	}
	if (!isEmptyDynArr(stack)) {
		deleteDynArr(stack);
		return 0;
	}
	else {
		deleteDynArr(stack);
		return 1;
	}
}


int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}