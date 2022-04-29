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
	bool visited;
} *array_prototype = NULL, ** array_tracks = NULL, ** sstf_array = NULL, ** scan_array = NULL;
typedef struct arrayType type_array;

// global variables and structs above ********************/


// helper function
/*********************************************************/
// given a dynamic array, count the total distance traversed and return it
int _CountDistance(struct arrayType** count_array) {
	int temp_distance = 0;
	int total_distance = 0;

	for (int i = 0; i < seq_size; i++) {
		if ((i + 1) != seq_size) {
			temp_distance = abs(count_array[i]->value - count_array[i + 1]->value);
			total_distance += temp_distance;
			// debugging purpsoses
			/*
			printf("\nTemp Distance between %d and %d is = %d\n",
				array_tracks[i]->value, array_tracks[i + 1]->value, temp_distance);
				*/
		}
	}
	return total_distance;
} // HELPER


// helper function
/*********************************************************/
// given a dynamic array and a 0 (decreasing) or 1 (increasing)
// count the total distance traversed and return it
struct arrayType** _ScanDirection(struct arrayType** scan_array, bool direction) {
	int temp_distance = 0;
	int temp_value = 0;
	int starting_track_index = 0;
	int temp_track_index = 0;
	enum { DECREASING, INCREASING } initial_direction;

	initial_direction = direction;
	scan_array[0]->visited = true;
	// traverse through the list going towards the direction given by user
	if (initial_direction == DECREASING) {
		printf("\nDecreasing Algorithm Starting\n");
		// sort the array for easier access (bubble sort from ascending order)
		for (int i = 0; i < seq_size; i++) {
			for (int k = 0; k < seq_size; k++) {
				// only iterate if there is an available element next in line
				if (k != (seq_size - 1)) {
					// if the current element is greater than the next one in line, we sort it
					if (scan_array[k]->value > scan_array[k + 1]->value) {
						// this means the starting track moved spots, tracking this for later use
						if (scan_array[k]->visited) {
							scan_array[k + 1]->visited = true;
							scan_array[k]->visited = false;
						}
						temp_value = scan_array[k]->value;
						scan_array[k]->value = scan_array[k + 1]->value;
						scan_array[k + 1]->value = temp_value;
					}
				}
			}
		}
	}
	else if (initial_direction == INCREASING) {
		// sort the array for easier access (bubble sort from descending order)
		for (int i = 0; i < seq_size; i++) {
			for (int k = 0; k < seq_size; k++) {
				// only iterate if there is an available element next in line
				if (k != (seq_size - 1)) {
					// if the current element is greater than the next one in line, we sort it
					if (scan_array[k]->value < scan_array[k + 1]->value) {
						// this means the starting track moved spots, tracking this for later use
						if (scan_array[k]->visited) {
							scan_array[k + 1]->visited = true;
							scan_array[k]->visited = false;
						}
						temp_value = scan_array[k]->value;
						scan_array[k]->value = scan_array[k + 1]->value;
						scan_array[k + 1]->value = temp_value;
					}
				}
			}
		}
	}
	// array is now bubble sorted
	// example input 5 12 3 7 4
	// is now 3 4 [5] 7 12		[x] = starting track
	// we will not locate the starting track (5) by seeing if it's been visited = true
	// (descending) we will scan throguh the left 5->4->3, then once we reach the front, we scan backwards 5->7->12
	// (ascending) will just be the opposite of descending, scan right first 5->7->12 then 5->4->3
	for (int n = 0; n < seq_size; n++) {
		// this is the first track, we will use this index
		if (scan_array[n]->visited) {
			starting_track_index = n;
			temp_track_index = starting_track_index;
		}
	}
	for (int j = 1; j <= starting_track_index; j++) {
		temp_distance = (scan_array[temp_track_index]->value - scan_array[temp_track_index - 1]->value);
		temp_track_index--;
		if (temp_track_index == 0)
			j++;
	}
	// swapping the smallest element with the starting track (starting track element still has visited = true)
	temp_value = scan_array[starting_track_index]->value;
	scan_array[starting_track_index]->value = scan_array[0]->value;
	scan_array[0]->value = temp_value;
	temp_track_index = starting_track_index;
	for (int j = 1; j <= starting_track_index; j++) {
		temp_distance = (scan_array[temp_track_index]->value - scan_array[temp_track_index + 1]->value);
		temp_track_index++;
		if (temp_track_index == seq_size)
			j++;
	}
	return scan_array;
} // HELPER


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
		if (seq_size <= 0) {
			printf("\nSequence size must be greater than 0.\n");
			printf("Enter size of sequence: ");
			scanf("%d", &seq_size);
		}
	} while (seq_size < 0);

	// allocate memory for the sequence of traversed tracks
	array_tracks = (type_array**)malloc(seq_size * sizeof(array_tracks));
	for (int i = 0; i < seq_size; i++) {
		array_tracks[i] = (type_array*)malloc(seq_size * sizeof(array_tracks));
		array_tracks[i]->visited = false;
	}

	// prompt for starting track, store in index 0
	printf("Enter starting track: ");
	scanf("%d", &starting_track);
	// ensure starting track is a positive number
	do {
		if (starting_track <= 0) {
			printf("\nSequence size must be greater than 0.\n");
			printf("Enter starting track: ");
			scanf("%d", &starting_track);
		}
	} while (starting_track <= 0);
	array_tracks[0]->value = starting_track;

	// prompt for sequence of tracks to seek, store in index 1 to "sequence size-1"
	if (seq_size >= 2) {
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
	}
	if (seq_size == 1)
		printf("\n");
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

	// base case (only 1 element exists then we simply return that value)
	if (seq_size == 1)
		total_distance = 0;
	else {
		total_distance = _CountDistance(array_tracks);
		/*
		for (int i = 0; i < seq_size; i++) {
			if ((i + 1) != seq_size) {
				temp_distance = abs(array_tracks[i]->value - array_tracks[i + 1]->value);
				total_distance += temp_distance;
				// debugging purpsoses
				/*
				printf("\nTemp Distance between %d and %d is = %d\n",
					array_tracks[i]->value, array_tracks[i + 1]->value, temp_distance);

			}
		}
		*/
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
/*
shortest seek time first (SSTF)
selects the request with the minimum seek time from the current head position
*/
/*********************************************************/
void Traverse_SSTF() {
	int temp_distance = 0;
	int total_distance = 0;
	int shortest_distance = INT_MAX;
	int shortest_index = 0;

	// base case if only 1 value exists from user input
	if (seq_size == 1)
		total_distance = 0;
	else {
		// initalize a new dynamic array for output the results
		sstf_array = (type_array**)malloc(seq_size * sizeof(sstf_array));
		for (int i = 0; i < seq_size; i++) {
			sstf_array[i] = (type_array*)malloc(seq_size * sizeof(sstf_array));
		}
		// set the starting track
		sstf_array[0]->value = array_tracks[0]->value;
		array_tracks[0]->visited = true;

		// iterate through entire queue and find the shortest distance to travel to next
		for (int i = 0; i < seq_size; i++) {
			// marks the track as visited, so we don't double count the same element in queue
			if (i != 0) {
				sstf_array[i]->value = array_tracks[shortest_index]->value;
				array_tracks[shortest_index]->visited = true;
				shortest_distance = INT_MAX;
			}
			for (int j = 1; j < seq_size; j++) {
				// only visit the elements that aren't already on the filtered array
				if (!array_tracks[j]->visited) {
					temp_distance = abs(sstf_array[i]->value - array_tracks[j]->value);
					// if we find that the temporary distance is less than the shortest distance, replace it
					if (shortest_distance > temp_distance) {
						shortest_distance = temp_distance;
						shortest_index = j;
					}
				}
			}
		}
		// print sequence of traversal
		printf("\nTraversed sequence: ");
		for (int j = 0; j < seq_size; j++) {
			printf("%d ", sstf_array[j]->value);
		}
		// print total distance of tracks traversed
		total_distance = _CountDistance(sstf_array);
		printf("\nThe distance of the traversed tracks is: %d\n\n", total_distance);
		// reset this in case we call this function once more
		for (int k = 0; k < seq_size; k++) {
			array_tracks[k]->visited = false;
		}
	}
	return;
} // "OPTION #3" 


// option 4
/*
sometimes called the elevator algorithm
The disk arm starts at one end of the disk, and moves toward the other end, servicing requests until it gets to the
other end of the disk, where the head movement is reversed and servicing continues.
we will implement a decreasing scan here (approach 0, then approach max queue number)
*/
/*********************************************************/
void Traverse_Scan() {
	// declare local variables
	int total_distance = 0;
	int temp_distance = 0;
	int largest_number = 0;
	int initial_direction = 0;
	int smallest_number = INT_MAX;

	// base case if only 1 value exists from user input
	if (seq_size == 1)
		total_distance = 0;
	else {
		// initalize a new dynamic array for output the results
		// make a copy of the array to use
		scan_array = (type_array**)malloc(seq_size * sizeof(scan_array));
		for (int i = 0; i < seq_size; i++) {
			scan_array[i] = (type_array*)malloc(seq_size * sizeof(scan_array));
			scan_array[i]->value = array_tracks[i]->value;
			scan_array[i]->visited = false;
		}

		// prompt for initial direction for the scan to start from
		printf("\nEnter initial direction (0 = decreasing, 1 = increasing): ");
		scanf("%d", &initial_direction);
		// ensure input is valid (0 or 1)
		do {
			if (initial_direction > 1 || initial_direction < 0) {
				printf("\nInitial direction must be either 0 (decreasing) or 1 (increasing)\n");
				printf("\nEnter initial direction (0 = decreasing, 1 = increasing): ");
				scanf("%d", &initial_direction);
			}
		} while (initial_direction > 1 || initial_direction < 0);

		scan_array = _ScanDirection(scan_array, initial_direction);
		total_distance = _CountDistance(scan_array);

		/*
		// iterate through entire queue and find the shortest distance to travel to next
		for (int i = 0; i < seq_size; i++) {
			// marks the track as visited, so we don't double count the same element in queue
			if (i != 0) {
				scan_array[i]->value = array_tracks[shortest_index]->value;
				array_tracks[shortest_index]->visited = true;
				shortest_distance = INT_MAX;
			}
			for (int j = 1; j < seq_size; j++) {
				// only visit the elements that aren't already on the filtered array
				if (!array_tracks[j]->visited) {
					temp_distance = abs(scan_array[i]->value - array_tracks[j]->value);
					// if we find that the temporary distance is less than the shortest distance, replace it
					if (shortest_distance > temp_distance) {
						shortest_distance = temp_distance;
						shortest_index = j;
					}
				}
			}
		}
		*/

		// print sequence of traversal
		printf("\nTraversed sequence: ");
		for (int j = 0; j < seq_size; j++) {
			printf("%d ", scan_array[j]->value);
		}
		// print total distance of tracks traversed
		printf("\nThe distance of the traversed tracks is: %d\n\n", total_distance);
	}

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
			Traverse_SSTF();
			break;
		case SCAN:
			Traverse_Scan();
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