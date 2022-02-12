/* CS261-Assignment1-Q.0 */
/* Name: Xiaoying Li
 * Date: 10/14/2019
 * Solution description: get started with programming in C and
 *                       practice of pointer manipulation.
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void fooA(int* iptr){  
    /*Print the value and address of the integer pointed to by iptr*/
    printf("Value of the integer pointed to by iptr: %d\n", *iptr);
    printf("Address of the integer pointed to by iptr: %p\n", &(*iptr)); 
          
    /*Increment the value of the integer pointed to by iptr by 5*/
    *iptr=*iptr+5;

    /*Print the address of iptr itself*/
    printf("Address of iptr itself: %p\n", &iptr);

    /*Dummy variable, ignore the warning*/
    /*int c=5;*/  
}


void fooB(int* jptr){  
    /*Print the value and address of the integer pointed to by jptr*/
    printf("Value of the integer pointed to by jptr: %d\n", *jptr);
    printf("Address of the integer pointed to by jptr: %p\n", &(*jptr));    

    /*Decrement the address by 1 pointed to by jptr using jptr*/
    jptr=jptr-1;
      
    /*Print the address of jptr itself*/
    printf("Address of jptr itself: %p\n", &jptr);
}


int main(){
    /*Declare an integer x and initialize it randomly to a value in [0,10]*/
    srand(time(NULL));
    int x=rand()%11;

    /*Print the value and address of x*/
    printf("Value of x: %d\n", x);
    printf("Address of x: %p\n", &x);

    /*Call fooA() with the address of x*/
    fooA(&x);
    
    /*Print the value of x*/
    printf("Value of x: %d\n", x);
    /*The value of x is different from the value that was printed at first.
     *The value of x is 5 more than the value that was printed at first.
     *Because we passed the address of x to fooA(), so when we added 5 to the 
     *value in fooA(), we were acctually adding 5 to the value at the address 
     *of x, which was x. So after fooA(), the value of x changed.*/

    /*Call fooB() with the address of x*/
    fooB(&x);
    
    /*Print the value and address of x*/
    printf("Value of x: %d\n", x);
    printf("Address of x: %p\n", &x);
    /*The value and address of x are both same as the value and address that 
     *were printed before the call to fooB(). Because the value we changed in 
     *fooB() is the address pointed to by jptr, not the value of the integer 
     *pointed to by jptr. So the value of x won't change after fooB(). And for 
     *the address of x itself, it's pass by value to fooB(), not by reference, 
     *so the value of the address of x won't change after fooB().*/ 

    return 0;
}
