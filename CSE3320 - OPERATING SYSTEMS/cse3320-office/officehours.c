/*
Name: Daniel Tam
ID:

Name: Tiffany Frias
ID: 1001631229
*/

// Copyright (c) 2020 Trevor Bakker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/***** REQUIREMENTS: *****
 * [x] Only allow 3 students in at a time
 * [x] Do not allow other classes to enter at the same time
 * [x] Professor takes a break after 10 students
 * [x] Only allow for 5 consecutive students from a single class, then switch classes
 * [x] Ensure progress
 * [x] No deadlocks
 * [x] Good comments
 * [x] Consistent spacing
*/


#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <time.h>

/*** Constants that define parameters of the simulation ***/

// Number of students in the professor's office, we set this number to one more than allowed
// since we do some funny math below that requires us to be one over the limit here
// check the professorthread function
#define MAX_SEATS 4
#define professor_LIMIT 10 // Number of students the professor can help before he needs a break
#define MAX_STUDENTS 1000  // Maximum number of students in the simulation

#define CLASSA 0
#define CLASSB 1
#define CLASSC 2
#define CLASSD 3
#define CLASSE 4

/* TODO */
/* Add your synchronization variables here */

/* Basic information about simulation.	They are printed/checked at the end 
 * and in assert statements during execution.
 *
 * You are responsible for maintaining the integrity of these variables in the 
 * code that you develop. 
 */

// semaphore to keep track of how many chairs are opened in the office
sem_t office_chairs;

// mutex that a student will lock when they are waiting to be
// signaled by the professor
pthread_mutex_t studenta_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t studentb_mutex = PTHREAD_MUTEX_INITIALIZER;

// mutex to ensure only one person can update the amount of 
// students in the office
pthread_mutex_t students_in_office_lock = PTHREAD_MUTEX_INITIALIZER;

// conditions that the students will wait for so that the professor
// will signal the student when they can enter
pthread_cond_t studenta_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t studentb_cond = PTHREAD_COND_INITIALIZER;

static int students_in_office; // Total numbers of students currently in the office
static int classa_inoffice; // Total numbers of students from class A currently in the office 
static int classb_inoffice; // Total numbers of students from class B in the office
static int students_since_break = 0;
static int classa_total;  //Total number of class a students expected
static int classb_total;  //Total number of class b students expected
static int classa_consec; //Counter for consecutive class A students
static int classb_consec; //Counter for consecutive class B students
static int chair_count;  

typedef struct 
{
	int arrival_time;  // time between the arrival of this student and the previous student
	int question_time; // time the student needs to spend with the professor
	int student_id;
	int class;
} student_info;

/* Called at beginning of simulation.  
 * TODO: Create/initialize all synchronization
 * variables and other global variables that you add.
 */
static int initialize(student_info *si, char *filename) 
{
	students_in_office = 0;
	classa_inoffice = 0;
	classb_inoffice = 0;
	students_since_break = 0;
	classa_total = 0;
	classb_total = 0;
	classa_consec = 0;
	classb_consec = 0;
	chair_count = 0;

	/* Initialize your synchronization variables (and 
	 * other variables you might use) here
	 */

	// initilize semaphore with the maximum amount of seats possible
	sem_init(&office_chairs, 0, 3);

	/* Read in the data file and initialize the student array */
	FILE *fp;

	if((fp=fopen(filename, "r")) == NULL) 
	{
		printf("Cannot open input file %s for reading.\n", filename);
		exit(1);
	}

	int i = 0;
	while ( (fscanf(fp, "%d%d%d\n", &(si[i].class), &(si[i].arrival_time), &(si[i].question_time))!=EOF) && 
					 i < MAX_STUDENTS ) 
	{
		i++;
	}

	fclose(fp);
	return i;
}

/* Code executed by professor to simulate taking a break 
 * You do not need to add anything here.	
 */
static void take_break() 
{
	printf("The professor is taking a break now.\n");
	sleep(5);
	assert( students_in_office == 0 );
	students_since_break = 0;
}

/* Code for the professor thread. This is fully implemented except for synchronization
 * with the students.  See the comments within the function for details.
 */
void *professorthread(void *junk) 
{
	printf("The professor arrived and is starting his office hours\n");

	/* Loop while waiting for students to arrive. */
	while (1) 
	{

		/* TODO */
		/* Add code here to handle the student's request. */
		/* Currently the body of the loop is empty. There's */
		/* no communication between professor and students, i.e. all */
		/* students are admitted without regard of the number */ 
		/* of available seats, which class a student is in, */
		/* and whether the professor needs a break. You need to add */
		usleep(10);
                // lock so students cannot edit the value and enter the office
		pthread_mutex_lock(&students_in_office_lock);
                
                // ensure that the professor will take a break after a certain amount
                // of students. We add one since when we first set which class goes
                // first (below), we add one, so our totals will always be +1.
		if(students_since_break >= professor_LIMIT)
		{
			if((classa_inoffice == 1 && classb_inoffice == 0) || (classa_inoffice == 0 && classb_inoffice == 1))
			{
				classa_inoffice = 0;
				classb_inoffice = 0;
                        	// ensure there's no students in the office, if there is, continue
                        	// waiting for them to leave.
                    
                        	// take a break and reset the students since last break
				take_break();
				students_since_break = 0;

				int i=0;
				for(i = 0; i < 3; i++)
				{
					sem_post(&office_chairs);
				}
				pthread_mutex_unlock(&students_in_office_lock);
			}
			else
			{
				pthread_mutex_unlock(&students_in_office_lock);
			}
		}
		else
		{
			// if we're out of class a students and there's still class a
			// students in the office, wait for them to leave, then set to 0
			// a students in the office
			if(classa_total == 0)
			{
				if(classa_inoffice == 1)
				classa_inoffice = 0;
			}

			// if we're out of class b students and there's still class b
			// students in the office, wait for them to leave, then set to 0
			// b students in the office
			if(classb_total == 0)
			{
				if(classb_inoffice == 1)
				classb_inoffice = 0;
			}

			// if there are student b's in office, only let student b
			if(classb_inoffice > 0)
			{
			int b = sem_trywait(&office_chairs);

			if(b == 0)
			{
				if(classb_consec < 5 && classb_inoffice < MAX_SEATS)
				{
					usleep(10);
					// signal a student in class b to enter
					pthread_cond_signal(&studentb_cond);

					classb_consec++;
					classa_consec = 0;
				}
				else if(classa_total == 0 && classb_inoffice < MAX_SEATS)
				{
					pthread_cond_signal(&studentb_cond);
				}
				else
				{
					if(classb_inoffice == 1)
					{
						classb_inoffice = 0;
						classa_inoffice++;
						int i=0;
						for(i = 0; i < 3; i++)
						{
							sem_post(&office_chairs);
						}
					}
				}
			}
		}
		// else, there are student a's in the office
		else if(classa_inoffice > 0)
		{
			int a = sem_trywait(&office_chairs);

			if(a == 0)
			{
				if(classa_consec < 5 && classa_inoffice < MAX_SEATS)
				{
					usleep(10);
					// signal a student in class a to enter
					pthread_cond_signal(&studenta_cond);
                            
				classa_consec++;
				classb_consec = 0;
				}
				else if(classb_total == 0 && classa_inoffice < MAX_SEATS)
				{
					pthread_cond_signal(&studenta_cond);
				}
				else
				{
					if(classa_inoffice == 1)
					{
						//printf("\ndonea\n");
						classa_inoffice = 0;
						classb_inoffice++;
						int i=0;
						for(i = 0; i < 3; i++)
						{
							sem_post(&office_chairs);
						}
					}
				}
			}
		}
                    // else, office is empty, signal a class randomly
		else
		{
                        // randomly pick a class to enter
			if(rand() % 2)
			{
                            // ensure we do not select an empty class
				if(classa_total > 0)
				{
                                // signal a student in class a to enter
                            
                                // add one to the student that will be in the office
                                // to ensure that we don't hit this else loop again
                                // and it may randomly select the other class and throw
                                // an error (this is why we have +1 to some defined values)
					classa_inoffice++;
				}
			}
			else
			{
                            // ensure we do not select an empty class
				if(classb_total > 0)
				{
                                // signal a student in class b to enter

                                // add one to the student that will be in the office
                                // to ensure that we don't hit this else loop again
                                // and it may randomly select the other class and throw
                                // an error (this is why we have +1 to some defined values)
				classb_inoffice++;
				}
			}
		}
	}

	pthread_mutex_unlock(&students_in_office_lock);
	
	}

	pthread_exit(NULL);
}


/* Code executed by a class A student to enter the office.
 * You have to implement this.	Do not delete the assert() statements,
 * but feel free to add your own.
 */
void classa_enter() 
{
        // attempt to lock so that other students have to wait
        // for this specific thread to enter
	pthread_mutex_lock(&studenta_mutex);

        // wait for the professor to let this thread in
	pthread_cond_wait(&studenta_cond, &studenta_mutex);

        // once the professor has signaled to let this thread in
        // we can unlock the mutex so another student can grab it
        // and wait to be signaled in
	pthread_mutex_unlock(&studenta_mutex);

        // lock so that we can edit the amount of students
	pthread_mutex_lock(&students_in_office_lock);
	students_in_office += 1;
	students_since_break += 1;
	classa_inoffice += 1;
	classa_total--;
	pthread_mutex_unlock(&students_in_office_lock);

}

/* Code executed by a class B student to enter the office.
 * You have to implement this.	Do not delete the assert() statements,
 * but feel free to add your own.
 */
void classb_enter() 
{
        // attempt to lock so that other students have to wait
        // for this specific thread to enter
	pthread_mutex_lock(&studentb_mutex);

        // wait for professor to let this thread in
	pthread_cond_wait(&studentb_cond, &studentb_mutex);

        // once the professor has signaled to let this thread in
        // we can unlock the mutex so another student can grab it
        // and wait to be signaled in
	pthread_mutex_unlock(&studentb_mutex);
        
        // lock so that we can edit the amount of students
	pthread_mutex_lock(&students_in_office_lock);
	students_in_office += 1;
	students_since_break += 1;
	classb_inoffice += 1;
	classb_total--;
	pthread_mutex_unlock(&students_in_office_lock);

}

/* Code executed by a student to simulate the time he spends in the office asking questions
 * You do not need to add anything here.	
 */
static void ask_questions(int t) 
{
	sleep(t);
}


/* Code executed by a class A student when leaving the office.
 * You need to implement this.	Do not delete the assert() statements,
 * but feel free to add as many of your own as you like.
 */
static void classa_leave() 
{
	pthread_mutex_lock(&students_in_office_lock);

	students_in_office -= 1;
	classa_inoffice -= 1;
	pthread_mutex_unlock(&students_in_office_lock);
	// release semaphore so that others could take the seat
	sem_post(&office_chairs);

}

/* Code executed by a class B student when leaving the office.
 * You need to implement this.	Do not delete the assert() statements,
 * but feel free to add as many of your own as you like.
 */
static void classb_leave() 
{

	pthread_mutex_lock(&students_in_office_lock);
	students_in_office -= 1;
	classb_inoffice -= 1;
	pthread_mutex_unlock(&students_in_office_lock);
	// release semaphore so that others could take the seat
	sem_post(&office_chairs);
}

/* Main code for class A student threads.  
 * You do not need to change anything here, but you can add
 * debug statements to help you during development/debugging.
 */
void* classa_student(void *si) 
{
	student_info *s_info = (student_info*)si;

	/* enter office */
	classa_enter();

	printf("Student %d from class A enters the office\n", s_info->student_id);

	assert(students_in_office <= MAX_SEATS && students_in_office >= 0);
	assert(classa_inoffice >= 0 && classa_inoffice <= MAX_SEATS);
	assert(classb_inoffice >= 0 && classb_inoffice <= MAX_SEATS);
	assert(classb_inoffice == 0 );
	
	/* ask questions	--- do not make changes to the 3 lines below*/
	printf("Student %d from class A starts asking questions for %d minutes\n", s_info->student_id, s_info->question_time);
	ask_questions(s_info->question_time);
	printf("Student %d from class A finishes asking questions and prepares to leave\n", s_info->student_id);

	/* leave office */
	classa_leave();  

	printf("Student %d from class A leaves the office\n", s_info->student_id);

	assert(students_in_office <= MAX_SEATS && students_in_office >= 0);
	assert(classb_inoffice >= 0 && classb_inoffice <= MAX_SEATS);
	assert(classa_inoffice >= 0 && classa_inoffice <= MAX_SEATS);

	pthread_exit(NULL);
}

/* Main code for class B student threads.
 * You do not need to change anything here, but you can add
 * debug statements to help you during development/debugging.
 */
void* classb_student(void *si) 
{
	student_info *s_info = (student_info*)si;

	/* enter office */
	classb_enter();

	printf("Student %d from class B enters the office\n", s_info->student_id);

	assert(students_in_office <= MAX_SEATS && students_in_office >= 0);
	assert(classb_inoffice >= 0 && classb_inoffice <= MAX_SEATS);
	assert(classa_inoffice >= 0 && classa_inoffice <= MAX_SEATS);
	assert(classa_inoffice == 0 );

	printf("Student %d from class B starts asking questions for %d minutes\n", s_info->student_id, s_info->question_time);
	ask_questions(s_info->question_time);
	printf("Student %d from class B finishes asking questions and prepares to leave\n", s_info->student_id);

	/* leave office */
	classb_leave();				 

	printf("Student %d from class B leaves the office\n", s_info->student_id);
	assert(students_in_office <= MAX_SEATS && students_in_office >= 0);
	assert(classb_inoffice >= 0 && classb_inoffice <= MAX_SEATS);
	assert(classa_inoffice >= 0 && classa_inoffice <= MAX_SEATS);

	pthread_exit(NULL);
}

/* Main function sets up simulation and prints report
 * at the end.
 */
int main(int nargs, char **args) 
{
	int i;
	int result;
	int student_type;
	int num_students;
	void *status;
	pthread_t professor_tid;
	pthread_t student_tid[MAX_STUDENTS];
	student_info s_info[MAX_STUDENTS];
        srand(time(0));

	if (nargs != 2) 
	{
		printf("Usage: officehour <name of inputfile>\n");
		return EINVAL;
	}

	num_students = initialize(s_info, args[1]);
	if (num_students > MAX_STUDENTS || num_students <= 0) 
	{
		printf("Error:	Bad number of student threads. "
					 "Maybe there was a problem with your input file?\n");
		return 1;
	}

	printf("Starting officehour simulation with %d students ...\n",
		num_students);

	result = pthread_create(&professor_tid, NULL, professorthread, NULL);

	if (result) 
	{
		printf("officehour:  pthread_create failed for professor: %s\n", strerror(result));
		exit(1);
	}

	for (i=0; i < num_students; i++) 
	{

		s_info[i].student_id = i;
		sleep(s_info[i].arrival_time);
								
		student_type = rand() % 2;

		if (s_info[i].class == CLASSA)
		{
                        classa_total++;
			result = pthread_create(&student_tid[i], NULL, classa_student, (void *)&s_info[i]);
		}
		else // student_type == CLASSB
		{
                        classb_total++;
			result = pthread_create(&student_tid[i], NULL, classb_student, (void *)&s_info[i]);
		}

		if (result) 
		{
			printf("officehour: thread_fork failed for student %d: %s\n", 
						i, strerror(result));
			exit(1);
		}
	}

	/* wait for all student threads to finish */
	for (i = 0; i < num_students; i++) 
	{
		pthread_join(student_tid[i], &status);
	}

	/* tell the professor to finish. */
	pthread_cancel(professor_tid);

	printf("Office hour simulation done.\n");

	return 0;
}
