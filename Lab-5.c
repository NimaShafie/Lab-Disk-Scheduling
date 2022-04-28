/*
Lab 5 - Disk Scheduling
Comp 322/L
Nima Shafie
Date Here

Description:
•	To compare the performance of disk scheduling algorithms:
First-in-first-out (FIFO), Shortest-seek-time-first (SSTF), Scan, and C-Scan.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <limits.h>

// Declare global variables, including dynamic array to store sequence of traversed tracks
int seq_size = 0;

struct arrayType {
	int value;
} *array_prototype = NULL, **array_tracks = NULL;
typedef struct arrayType type_array;

// global variables and structs above ********************/


// option 1
/*********************************************************/
void EnterParameters() {
	// local variables
	int track;
	int starting_track;

	// prompt for the sequence size
	printf("Enter size of sequence: ");
	scanf("%d", &seq_size);
	// ensure sequence size is a positive number
	do {
		if (seq_size < 0) {
			printf("\nSequence size cannot be a negative number.\n");
			printf("Enter size of sequence: ");
			scanf("%d", &seq_size);
		}
	} while (seq_size < 0);

	// allocate memory for the sequence of traversed tracks
	array_tracks = (type_array**)malloc(seq_size * sizeof(array_tracks));
	for (int i = 0; i < seq_size; i++) {
		array_tracks[i] = (type_array*)malloc(seq_size * sizeof(array_tracks));
	}

	// prompt for starting track, store in index 0
	printf("Enter starting track: ");
	scanf("%d", &starting_track);
	// ensure starting track is a positive number
	do {
		if (starting_track < 0) {
			printf("\nSequence size cannot be a negative number.\n");
			printf("Enter starting track: ");
			scanf("%d", &starting_track);
		}
	} while (starting_track < 0);
	array_tracks[0]->value = starting_track;

	// prompt for sequence of tracks to seek, store in index 1 to "sequence size-1"
	printf("Enter sequence of tracks to seek: ");
	for (int i = 1; i <= (seq_size - 1); i++) {
		do {
			scanf("%d", &track);
			if (track < 0) {
				printf("\nTrack cannot be a negative number.\n");
				printf("Enter sequence of tracks to seek: ");
				i = 1;
				scanf("%d", &track);
			}
		} while (track < 0);
		array_tracks[i]->value = track;
	}

	// just for debugging purposes
	/*
	printf("\nOuputting the track list: ");
	for (int j = 0; j < seq_size; j++)
		printf("%d ", array_tracks[j]->value);
	*/
	
	printf("\n");
	return;
} // "OPTION #1"


// option 2
/*
first in first out
disk will traverse the queue in first come first serve order, the simplest form of disk scheduling
*/
/*********************************************************/
void Traverse_FIFO() {
	// declare local variables
	int total_distance = 0;
	int temp_distance = 0;

	// base case (only 0/1 element exists then we simply return that value)
	if (seq_size == 1)
		total_distance = array_tracks[0]->value;
	if (seq_size == 0)
		total_distance = 0;
	else {
		for (int i = 0; i < seq_size; i++) {
			if ((i + 1) != seq_size) {
				temp_distance = abs(array_tracks[i]->value - array_tracks[i + 1]->value);
				total_distance += temp_distance;
				// debugging purpsoses
				/*
				printf("\nTemp Distance between %d and %d is = %d\n",
					array_tracks[i]->value, array_tracks[i + 1]->value, temp_distance);
					*/
			}
		}
	}

	// print sequence of traversal
	printf("\nTraversed sequence: ");
	for (int j = 0; j < seq_size; j++) {
		printf("%d ", array_tracks[j]->value);
	}
	// print total distance of tracks traversed
	printf("\nThe distance of the traversed tracks is: %d\n\n", total_distance);

	return;
} // "OPTION #2"	


// option 3
/*********************************************************/
void Traverse_SSTF() {
	// declare local variables
	// initialize current track and distance traversed to starting track
	// begin printing sequence of traversal 
	// until every track is traversed
		// initilize shortest distance to INT_MAX
		// for each track in sequence
			// if not already traversed
				//if distance to traverse is shorter than current shortest distance
					// set current shortest distance and index of the track	w/ shortest distance
		// set "done" value for track w/shortest distance to 1 (mark as traversed)
		// increment number of tracks that have been traversed
		// update total distance traversed
		//set current track to new position, print position						
	// print total distance traversed
	return;
} // "OPTION #3" 


// option 4
/*********************************************************/
void Traverse_Scan() {
	// declare local variables
	//prompt for initial direction (0=descreasing, 1=increasing)
	// initialize current track and distance traversed to starting track
	// begin printing sequence of traversal 
	// until every track is traversed
		// initilize shortest distance to INT_MAX
		// for each track in sequence
			// if not already traversed
				//if distance to traverse is shorter than current shortest distance in the current direction
					// set current shortest distance and index of the track	w/ shortest distance
						// set flag that at least one track was traversed
		// if at least one track was traversed
				// set "done" value for track w/shortest distance to 1 (mark as traversed)
			// increment number of traversed tracks
			// update total distance traversed
			//set current track to new position, print position
		// else change direction
	// print total distance traversed
	return;
} // "OPTION #4"


// option 5
/*********************************************************/
void Traverse_C_Scan() {
	// declare local variables
	// initialize current track and number traversed to starting track
	// begin printing sequence of traversal 
	// until every track is traversed
		// initilize shortest distance to INT_MAX
		// for each track in sequence
			// if not already traversed
				//if distance to traverse is shorter than current shortest distance and a positive value (only increasing direction)
					// set current shortest distance and index of the track	w/ shortest distance
						// set flag that at least one track was traversed
		// if at least one track was traversed
				// set "done" value for track w/shortest distance to 1 (mark as traversed)
			// increment number of tracks that have been traversed
			// if largest track was reached
				// update total distance traversed by derementing by distance to track (subtracts distance from 0 to track)
				// reset "largest track" flag
			// else
				// update total distance traversed by distance to track
			//set current track to new position, print position
		// else (no track was traversed)
			// update total distance by current track (adds remaining distance before going back to 0)
			// reset current track to 0 (loop back around)
			// set "end reached" flag to 1
	// print total distance traversed
	return;
} // "OPTION #5


// option 6
/*******************************************************************/
void FreeMemoryQuitProgram() {
	// if sequence is not NULL, free sequence

	/*
	if (head == NULL) return;
	// else
		// recursively call procedure on node->link
		// deallocate memory from node
	else {
		FreeMemoryQuitProgram(head->link);
		free(head);
	}
	*/

	return;
}


/***************************************************************/
int main() {
	/* declare local vars */
	int choice = 0;
	enum { PARAM, FIFO, SSTF, SCAN, C_SCAN, QUIT, INVALID } menu_choice;

	while (choice != 6) {
		printf("Disk Scheduling\n------------------------------\n");
		printf("1) Enter parameters\n");
		printf("2) Calculate distance to traverse tracks using FIFO\n");
		printf("3) Calculate distance to traverse tracks using SSTF\n");
		printf("4) Calculate distance to traverse tracks using Scan\n");
		printf("5) Calculate distance to traverse tracks using C-Scan\n");
		printf("6) Quit program and free memory\n");
		printf("\nEnter selection: ");
		scanf("%d", &choice);
		if (choice == 1) menu_choice = PARAM;
		else if (choice == 2) menu_choice = FIFO;
		else if (choice == 3) menu_choice = SSTF;
		else if (choice == 4) menu_choice = SCAN;
		else if (choice == 5) menu_choice = C_SCAN;
		else if (choice == 6) menu_choice = QUIT;
		else menu_choice = INVALID;

		switch (menu_choice) {
		case PARAM:
			EnterParameters();
			break;
		case FIFO:
			Traverse_FIFO();
			break;
		case SSTF:
			//DeallocteBlockMemory();
			break;
		case SCAN:
			//DefragmentMemory();
			break;
		case C_SCAN:
			//DefragmentMemory();
			break;
		case QUIT:
			FreeMemoryQuitProgram();
			break;
		case INVALID:
			printf("Invalid selection made, try again.\n\n");
		}
	};
return 1; /* indicates success */
} // main	