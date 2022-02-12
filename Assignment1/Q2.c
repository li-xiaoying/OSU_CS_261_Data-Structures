/* CS261-Assignment1-Q.2 */
/* Name: Xiaoying Li
 * Date: 10/14/2019
 * Solution description: get started with programming in C and
 *                       practice of pointer manipulation.
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/
    int* temp=a;
    a=b;
    b=temp;

    /*Decrement the value of integer variable c*/
    c--;
    
    /*Return c*/
    return c;
}


int main(){
    /*Declare three integers x,y and z and 
      initialize them randomly to values in [0,10]*/
    srand(time(NULL));
    int x=rand()%11;
    int y=rand()%11;
    int z=rand()%11;
    
    /*Print the values of x, y and z*/
    printf("value of x: %d\n", x);
    printf("value of y: %d\n", y);
    printf("value of z: %d\n", z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    int result=foo(&x, &y, z);

    /*Print the values of x, y and z*/
    printf("value of x: %d\n", x);
    printf("value of y: %d\n", y);
    printf("value of z: %d\n", z);

    /*Print the value returned by foo*/
    printf("value returned by foo: %d\n", result);

    return 0;
}
    
    
/* a. The return value is different from the value of integer z. The return 
 *    value is 1 less than the value of integer z. Because we pass z as an 
 *    arguement to foo(), not by reference, so the actual value of z remain 
 *    untouched. The function then decrements the copy of z's value by 1 and 
 *    return it, so the return value is different from the value of z. */


/* b. No.The values of integers x and y are same before and after calling the 
 *    function foo(). Because inside the function foo(), the addresses of a 
 *    and b are swaped but will not reflect outside the function since the 
 *    address of x and y are not pass by reference, only a copy of their 
 *    address are passed to foo(), their actual address remain untouched. So 
 *    the values of x and y remain unchanged. */
