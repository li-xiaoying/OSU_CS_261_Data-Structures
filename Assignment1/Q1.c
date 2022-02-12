/* CS261-Assignment1-Q.1 */
/* Name: Xiaoying Li
 * Date: 10/14/2019
 * Solution description: get started with programming in C and
 *                       practice of pointer manipulation.
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


struct student{
    int id;
    int score;
};


struct student* allocate(){
    /*Allocate memory for ten students*/
    struct student* students=(struct student*) malloc(10*sizeof(struct student));
   
    /*Return the pointer*/
    return students;
}


void generate(struct student* students){
    /*Generate random and unique IDs and random scores for ten students,
      IDs being between 1 and 10, scores between 0 and 100*/
    for (int i=0; i<10; i++){
	students[i].id=rand()%10+1;
	if (i>0){
	    for (int j=0; j<i; j++){
		if (students[i].id==students[j].id){
		    i--;
		    break;
		}
	    }
	}
    }
    for (int k=0; k<10; k++){
	students[k].score=rand()%101;
    }	
}


void output(struct student* students){
    /*Output information about the ten students in the format:
	  ID1 Score1
	  ID2 score2
	  ID3 score3
	  ...
	  ID10 score10*/
    int i;
    for (i=0; i<10; i++){
	printf("%d %d\n", students[i].id, students[i].score);
    }
}


void summary(struct student* students){
    /*Compute and print the minimum, maximum and 
      average scores of the ten students*/
    int min=students[0].score;
    int max=students[0].score;
    int i;
    int total=0;
    double average=0;
    for (i=0; i<10; i++){
	if (students[i].score<min){
	    min=students[i].score;
	}
	if (students[i].score>max){
	    max=students[i].score;
	}
	total=total+students[i].score;
    }
    average=total/10.0;
    printf("Minimum score: %d\n", min);
    printf("Maximum score: %d\n", max);
    printf("Average score: %lf\n", average);
}


void deallocate(struct student* stud){
    /*Deallocate memory from stud*/
    if (stud!=NULL){
	free(stud);
    }
}


int main(){
    struct student* stud = NULL;
    srand(time(NULL));

    /*Call allocate*/
    stud=allocate();

    /*Call generate*/
    generate(stud);

    /*Call output*/
    output(stud);
    
    /*Call summary*/
    summary(stud);

    /*Call deallocate*/
    deallocate(stud);

    return 0;
}
