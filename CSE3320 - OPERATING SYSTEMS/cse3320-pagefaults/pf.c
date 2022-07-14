/*
 * Tiffany Frias
 * ID 1001631229
 *
 * Daniel Tam
 * ID 1001724986
	
   Replacement Assignment
   Description:
	This program takes a working size and page reference string, 
	and prints the number of page faults if it were to be using
	optimal, MFU, LRU and FIFO.
 *
 */

// The MIT License (MIT)
//
// Copyright (c) 2020 Trevor Bakker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1024
#define MAX_PGS 80

/*
This method returns the number of page faults that occur with 
FIFO. Takes working set size, size of page reference string, and
int ptr which holds page ref. string */

int FIFO(int wset, int size, int *string)
{
	int frame[wset];
	int i=0;
	int j=0;
	int faults =0;
	int hit_signal; //will be 1 if hit, 0 if not
	int fifo;

	//initializes the frame to all -1's
	for(i =0; i<wset; i++)
	{
		frame[i]= -1;
	}

	/* The very first in is going to be placed at index 0 of frames,
	 * then from there fifo is determined by manipulation 
	 * of the algorithm
	 */
	fifo =0;

	for(i=0; i<=size-1; i++)
	{
		//printf("string: %d ",string[i]);
		hit_signal =0;

		//iterate thru frame to find new page 
		for(j=0; j<wset;j++)
		{
			//we already have that number in the frame,
			//no need to perform more 
			//-declare a hit
			if(frame[j] == string[i])
			{
				hit_signal =1;
			}
		}
			//however, we for sure have a page fault if we
			//did not have a hit .. need to change frames
			if(hit_signal ==0)
			{
				frame[fifo] = string[i];
				
				//find our new fifo	
				fifo = (fifo+1)%wset;

				faults++;

			/*This was just to keep track of frames:
				printf("frame: ");
				for(j=0; j<wset;j++)
				{
					printf(" %d", frame[j]);
				}
			*/
				
			}
			//printf("\n");
		}
	return faults;
}

/*This method will find the index of the LRU page to swap out
  takes the time array and size of the working set
 */

int find_LRU(int t[],int wset)
{
	int i =0;
	int min = t[0];
	int ind = 0;

	for(i =1; i< wset; i++)
	{
		if(t[i] < min)
		{
			min = t[i];
			ind =i;
		}
	}
	return ind;
}
/*
This method returns the number of page faults through
the least recently used algorithm. Takes working set size,
int array (int pointer) and the size of the array */

int LRU(int wset, int size, int *string)
{
	int frame[wset];
	int i,j,ind =0;
	int faults =0;
	int signal;
	int LRU_CTR;
	int t[size];

	for(i=0; i<wset;i++)
	{
		frame[i] = -1;
	}

	for(i=0; i < size; i++)
	{
		//printf("string: %d",string[i]);
		signal =0;
		for(j =0; j < wset; j++)
		{
			if(frame[j] == -1)
			{
				LRU_CTR++;
				faults++;
				frame[j] = string[i];
				t[j] = LRU_CTR;
				signal =1;
				break;
			}
			if(frame[j] == string[i])
			{
				LRU_CTR++;
				t[j] = LRU_CTR;
				signal = 1;
				break;
			}
		}
	
		/*If signal = 0, this means frames werent empty or that 
		 * the page we're looking for is not there,
		 * so we need to find the LRU frame index to swap
		 */

		if(signal==0)
		{
			ind = find_LRU(t,wset);
			LRU_CTR++;
			faults++;
			frame[ind] = string[i];
			t[ind] = LRU_CTR++;
		}

		/*
		//print out frames
		printf(" frame: ");
		for(j=0; j<wset;j++)
		{
			printf(" %d", frame[j]);
		}
		printf("\n");
		*/
	}

	return faults;
}

/*
This function will return the number of page faults through most frequently used.
Takes working set size, array size, and int ptr representing the page reference 
string
*/

int MFU(int wset, int size, int *string)
{
	int faults = 0;
        int working[wset];
	int i =0;
	int j=0;
	int k =0;
        int found = 0;
        // array to keep track of our stats, the first item is what the value is,
        // the second item is how often it occured so far
        int tracker[size][2];
        
        // initilize our tracker values to 0
        for(i = 0; i < size; i++)
        {
            tracker[i][0] = -1;
            tracker[i][1] = 0;
        }

        // initilize our working set to -1
        for(i = 0; i < wset; i++)
        {
            working[i] = -1;
        }

        // loop through the string
        for(i = 0; i < size; i++)
        {
            found = 0;

            // check to see if our current string is in our working set
            for(k = 0; k < wset; k++)
            {
                // if we find it in our set, we can continue our loop
                if(string[i] == working[k])
                {
                    // if it's found, find it in our tracker, and increase it
                    for(j = 0; j < size; j++)
                    {
                        if(tracker[j][0] == string[i])
                        {
                            tracker[j][1] = tracker[j][1]+1;
                        }
                    }

                    found = 1;
                    break;
                }
            }
            
            // if it's not in our set already...
            if(found == 0)
            {
                // find the first empty slot in our working set
                for(k = 0; k < wset; k++)
                {
                    // if there is an empty slot, place this page into it
                    if(working[k] == -1)
                    {
                        working[k] = string[i];
                        found = 1;
                        faults++;

                        // also place this page into our tracker to keep track of
                        // its frequency
                        for(j = 0; j < size; j++)
                        {
                            if(tracker[j][0] == -1)
                            {
                                tracker[j][0] = string[i];
                                tracker[j][1] = tracker[j][1]+1;
                                break;
                            }
                        }
                        break;
                    }
                }
            }

            printf("working set(%d) %d: ", string[i], i);
            for(k = 0; k < wset; k++)
            {
                printf("%d ", working[k]);
            }
            printf("\n");

            printf("tracker set %d: ", i);
            for(k = 0; k < size; k++)
            {
                printf("%d:%d ", tracker[k][0], tracker[k][1]);
            }
            printf("\n\n");
            
            
            if(found == 1)
            {
                continue;
            }

            // we have a miss, so we need to find which page was most
            // frequently used previously
            int highest_page = -1;
            int highest_freq = 0;
            int highest_pos = 0;

            for(k = 0; k < wset; k++)
            {
                for(j = 0; j < size; j++)
                {
                    if(tracker[j][0] == working[k])
                    {
                        if(tracker[j][1] > highest_freq)
                        {
                            highest_freq = tracker[j][1];
                            highest_page = tracker[j][0];
                            highest_pos = k;
                            break;
                        }
                    }
                }
            }

            found = 0;

            // try to find our page in our tracker
            for(k = 0; k < size; k++)
            {
                if(string[i] == tracker[k][0])
                {
                    tracker[k][1] = tracker[k][1]+1;
                    found = 1;
                    break;
                }
            }

            // not found, so we add it to our tracker at the next available slot
            if(found == 0)
            {
                for(k = 0; k < size; k++)
                {
                    if(tracker[k][0] == -1)
                    {
                        tracker[k][0] = string[i];
                        tracker[k][1] = tracker[k][1]+1;
                        break;
                    }
                }
            }
            
            working[highest_pos] = string[i];
            faults++;
        }

        return faults;
}

/*This method returns the number of page faults through optimal 
replacemnt algorithm - will take int working set size, the size 
of the page ref. string, and int ptr */

int OPT(int wset, int size, int *string)
{
        // working variables
	int faults = 0; // keep track of the amount of faults
	int working[wset]; // keep tracking of our working set
        int clone[wset]; 
	int i =0;
	int k =0;
	int j =0;
        int found = 0;

        // set our working and clone set to zeros
        for(i = 0; i < wset; i++)
        {
            working[i] = -1;
            clone[i] = -1;
        }

        // loop through the string
        for(i = 0; i < size; i++)
        {
            found = 0;

            // check to see  if our current string is in our working set
            for(k = 0; k < wset; k++)
            {
                // if we find it in our set, we can continue our loop
                if(string[i] == working[k])
                {
                    found = 1;
                    break;
                }
            }
            
            // if it's not in our set already...
            if(found == 0)
            {
                // check to see if there's empty slots in our working set,
                // if so, set it to that
                for(k = 0; k < wset; k++)
                {
                    if(working[k] == -1)
                    {
                        working[k] = string[i];
                        found = 1;
                        faults++;
                        break;
                    }
                }
            }

            // continue the loop upon finding our page in the set
            if(found == 1)
            {
                continue;
            }

            // make a clone of the working set
            for(k = 0; k < wset; k++)
            {
                clone[k] = working[k];
            }

            // keep track of how many values we find in our working set
            found = wset;

            // check to see if our clone array has upcoming values, if it
            // does, we can set it to 0
            for(k = i; k < size; k++)
            {
                for(j = 0; j < wset; j++)
                {
                    if(clone[j] == string[k])
                    {
                        clone[j] = -1;
                        found--;
                        break;
                    }
                }

                // upon one remaining entry, we can exit this
                if(found == 1)
                {
                    break;
                }
            }

            // find the first non-negative one value in our clone so that we 
            // can input our current working page into our working set
                for(k = 0; k < wset; k++)
                {
                    if(clone[k] != -1)
                    {
                        working[k] = string[i];
                        faults++;
                        break;
                    }
                }
        }

        return faults;
}

/*
 * Calls and prints the number of page faults for
 * each algorithm given the working 
 * set size, size of array, and int ptr
 */
void printfaults(int wset, int size, int *string)
{
	int p1 = FIFO(wset, size,string); 
	int p2 = LRU(wset, size, string);
	int p3 = MFU(wset, size, string);
	int p4 = OPT(wset, size, string);

	printf("Page faults of FIFO: %d\n", p1);
        printf("Page faults of LRU: %d\n", p2);
	printf("Page faults of MFU: %d\n", p3);
	printf("Page faults of Optimal: %d\n",p4);
}

int main( int argc, char * argv[] ) 
{
  
	int *ref_string;  //int array of the page reference string
	int ctr =0;  //this counter keep tracks of the page reference string size
	char * line = NULL;
	size_t line_length = MAX_LINE;
	char * filename;

	FILE * file;

	if( argc < 2 )
	{
	printf("Error: You must provide a datafile as an argument.\n");
	printf("Example: ./fp datafile.txt\n");
	exit( EXIT_FAILURE );
	}

	filename = ( char * ) malloc( strlen( argv[1] ) + 1 );
	line     = ( char * ) malloc( MAX_LINE );

	memset( filename, 0, strlen( argv[1] + 1 ) );
	strncpy( filename, argv[1], strlen( argv[1] ) );

//	printf("Opening file %s\n", filename );
	file = fopen( filename , "r");

	if ( file ) 
	{

	  /*For every while iteration, there is a working set size and a whole set
	   * of reference strings. Instead of saving the data for once it's done iterating,then dealing with
	   * it later, I'd go ahead and call the printfaults() after each iteration
	   * once we collect the data of a line. That way we arent trying to malloc for more data,
	   * which is not needed since all we need to do is print out the page faults for each.
	   */
	while ( fgets( line, line_length, file ) )
	{
		char * token;

		token = strtok( line, " ");
		int working_set_size = atoi( token );

		//printf("\nWorking set size: %d\n", working_set_size );
 		ref_string = malloc(sizeof(int)*MAX_PGS);

		//handles allocation failure
		if(!ref_string)
		{
			perror("Memory allocation failed.");
			exit(0);
		}

		//clear the memory
		memset(ref_string,0,sizeof(int)*MAX_PGS);

		//this while loop is what builds and adds everything to the ref_string array
		while( token != NULL )
		{
			token = strtok( NULL, " " );
        
			if( token != NULL )
			{
				ref_string[ctr] = atoi(token); 
				//printf("Request: %d\n",ref_string[ctr]);   //atoi( token ) ); 
				ctr++;
			}
		}

		//handles printinf of pf's for this reference string
		printfaults(working_set_size,ctr,ref_string);
		ctr = 0; //set ctr back to 0
		printf("\n");
	}

	free( line );
	fclose(file);
	}

	return 0;
}
