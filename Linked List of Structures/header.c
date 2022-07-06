#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "header.h"

statusCode insertAtEnd(flightNode** head_ptr, char flightName[], char flightId[], int flightCapacity, char flightArrTime[], char flightDeptTime[], char flightStatus[], char delayTime[], flightClassDT flightClass) {
 	statusCode ret_val = FAILURE;
    flightNode* nptr = *head_ptr;
    flightNode* new = (flightNode*)malloc(sizeof(flightNode));
    if(new) {
        strcpy(new->record.flight_name, flightName);
 	 	strcpy(new->record.flight_id, flightId);
 	 	new->record.flight_capacity = flightCapacity;
 	 	strcpy(new->record.flight_arr_time, flightArrTime);
 	 	strcpy(new->record.flight_dept_time, flightDeptTime);
 	 	new->record.flight_class = flightClass;
        strcpy(new->record.flight_status, flightStatus);
        strcpy(new->record.flight_delay_time, delayTime);
        if(nptr) {
            while(nptr->next)
                nptr = nptr->next;
            nptr->next = new;
            new->next = NULL;
        }
        else {
            *head_ptr = new;
            new->next = NULL;
        }
        ret_val = SUCCESS;
    }
    return ret_val;
}

statusCode insert_update(flightNode** head_ptr, flightNode** list1_ptr, flightNode** list2_ptr, flightNode** list3_ptr, char flightName[], char flightId[], int flightCapacity, char flightArrTime[], char flightDeptTime[], char flightStatus[], char delayTime[], flightClassDT flightClass) {
	flightNode *nptr = *head_ptr, *nptr1 = *list1_ptr, *nptr2 = *list2_ptr, *nptr3 = *list3_ptr;
    Bool found = FALSE, found_in_list1 = FALSE, found_in_list2 = FALSE, found_in_list3 = FALSE;
	statusCode status_code = SUCCESS;
    flightNode* ptr1, ptr2, ptr3;
 	while(nptr && !found)
 	{
 		if (nptr1 && !found_in_list1)
 		{	
            if(!strcmp(flightId, nptr1->record.flight_id) && !strcmp(flightArrTime, nptr1->record.flight_arr_time))
 			    found_in_list1 = TRUE;
 			else
                nptr1 = nptr1->next;
 		}
 		if (nptr2 && !found_in_list2)
 		{	
            if(!strcmp(flightId, nptr2->record.flight_id) && !strcmp(flightArrTime, nptr2->record.flight_arr_time))
 			    found_in_list2 = TRUE;
 			else
                nptr2 = nptr2->next;
 		}
 		if (nptr3 && !found_in_list3)
 		{	
            if(!strcmp(flightId, nptr3->record.flight_id) && !strcmp(flightArrTime, nptr3->record.flight_arr_time))
 			    found_in_list3 = TRUE;
 			else
                nptr3 = nptr3->next;
 		}

 		if(!strcmp(flightId, nptr->record.flight_id) && !strcmp(flightArrTime, nptr->record.flight_arr_time))
 			found = TRUE;
        else
 		    nptr = nptr->next;
 	}
 	
 	if (found)
 	{
 		Bool deleted = FALSE;
 		if(found_in_list1)
 		{
 			flightClassDT old_flightClass;
 			old_flightClass = nptr1->record.flight_class;
 			if (old_flightClass != flightClass)
 			{
 				Delete(list1_ptr, flightId, flightArrTime);
 				deleted = TRUE;
 			}
			else {
				strcpy(nptr1->record.flight_name, flightName);
				nptr1->record.flight_capacity = flightCapacity;
				strcpy(nptr1->record.flight_dept_time, flightDeptTime);
				strcpy(nptr1->record.flight_status, flightStatus);
				strcpy(nptr1->record.flight_delay_time, delayTime);
			}
 		}
 		else if(found_in_list2)
 		{
 			flightClassDT old_flightClass;
 			old_flightClass = nptr2->record.flight_class;
 			if (old_flightClass != flightClass)
 			{
 				Delete(list2_ptr, flightId, flightArrTime);
 				deleted = TRUE;
 			}
			else {
				strcpy(nptr2->record.flight_name, flightName);
				nptr2->record.flight_capacity = flightCapacity;
				strcpy(nptr2->record.flight_dept_time, flightDeptTime);
				strcpy(nptr2->record.flight_status, flightStatus);
				strcpy(nptr2->record.flight_delay_time, delayTime);
			}
 		}
 		else if(found_in_list3)
 		{
 			flightClassDT old_flightClass;
 			old_flightClass = nptr3->record.flight_class;
 			if (old_flightClass != flightClass)
 			{
 				Delete(list3_ptr, flightId, flightArrTime);
 				deleted = TRUE;
 			}
			else {
				strcpy(nptr3->record.flight_name, flightName);
				nptr3->record.flight_capacity = flightCapacity;
				strcpy(nptr3->record.flight_dept_time, flightDeptTime);
				strcpy(nptr3->record.flight_status, flightStatus);
				strcpy(nptr3->record.flight_delay_time, delayTime);
			}
 		}
 		if (deleted)
 		{
 			switch (flightClass)
 			{
 				case 1: 
 				{
 					insertAtEnd(list1_ptr, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightStatus, delayTime, flightClass);
 				 	break;
 				}
 				case 2: 
 				{
 					insertAtEnd(list2_ptr, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightStatus, delayTime, flightClass);
 				 	break;
 				}
 				case 3: 
 				{
 					insertAtEnd(list3_ptr, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightStatus, delayTime, flightClass);
 				 	break;
 				}
 			}
 		}
 		strcpy(nptr->record.flight_name, flightName);
 		nptr->record.flight_capacity = flightCapacity;
 		strcpy(nptr->record.flight_dept_time, flightDeptTime);
 		strcpy(nptr->record.flight_status, flightStatus);
 		strcpy(nptr->record.flight_delay_time, delayTime);
 		nptr->record.flight_class = flightClass;
 	}
 	else
 	{
 		status_code = insertAtEnd(head_ptr, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightStatus, delayTime, flightClass);
 	 	switch (flightClass)
		{
			case 1: 
			{
				insertAtEnd(list1_ptr, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightStatus, delayTime, flightClass);
				break;
			}
			case 2: 
			{
				insertAtEnd(list2_ptr, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightStatus, delayTime, flightClass);
				break;
			}
			case 3: 
			{
				insertAtEnd(list3_ptr, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightStatus, delayTime, flightClass);
				break;
			}
		}
 	}
 	insertion_sort(head_ptr);
 	insertion_sort(list1_ptr);
 	insertion_sort(list2_ptr);
 	insertion_sort(list3_ptr);
    return status_code;
}

statusCode Delete(flightNode** head_ptr, char flightId[], char flightArrTime[]) {
	statusCode status_code = FAILURE;
	flightNode* nptr = *head_ptr, *prev = *head_ptr;
	Bool found = FALSE;
	if(nptr) {
		while(nptr && !found) {
			if(!strcmp(flightId, nptr->record.flight_id) && !strcmp(flightArrTime, nptr->record.flight_arr_time))
				found = TRUE;
			else {
				prev = nptr;
				nptr = nptr->next;
			}
		}
		if(found) {
			if(nptr == *head_ptr) {
				*head_ptr = nptr->next;
				free(nptr);
			}
			else {
				prev->next = nptr->next;
				free(nptr);
			}
			status_code = SUCCESS;
		}
	}
 	return status_code;
}

unsigned int getNumFlights(flightNode** head_ptr) {
	unsigned int count;
	flightNode* nptr = *head_ptr, *ptr;
	Bool duplicate;
 	count = 0;
	if(nptr) {
		if(nptr->next == NULL)
			count = 1;
		else {
			while(nptr->next != NULL)
			{
				duplicate = FALSE;
				ptr = nptr->next;
				while(ptr != NULL && !duplicate)
				{
					if (!strcmp(nptr->record.flight_id, ptr->record.flight_id) && !strcmp(nptr->record.flight_arr_time, ptr->record.flight_arr_time))
						duplicate = TRUE;
					ptr = ptr->next;
				}
				if (!duplicate)
					count++;
				nptr = nptr->next;
			}
			count++;
		}
	}
 	return count;
}

Bool isEmpty(flightNode** head_ptr) {
	return *head_ptr == NULL;
}

Bool isFull(flightNode** head_ptr) {
	return FALSE;	//Assuming Database can never be full and heap always has sufficient memory for creating new nodes.
}

void getFlightWithtLongeststay(flightNode** head_ptr, flightNode** temp_DB) {
	int dept_time, arr_time, max; 
	*temp_DB = (flightNode*)malloc(sizeof(flightNode));
	(*temp_DB)->next = NULL;
	flightNode* nptr = *head_ptr;
 	dept_time = atoi(nptr->record.flight_dept_time);
 	arr_time = atoi(nptr->record.flight_arr_time);
 	max = abs(dept_time - arr_time);
 	(*temp_DB)->record = nptr->record;
	nptr = nptr->next;
 	while(nptr != NULL)
 	{
 		dept_time = atoi(nptr->record.flight_dept_time);
 		arr_time = atoi(nptr->record.flight_arr_time);
 		if (max < abs(dept_time - arr_time))
 		{
 			max = abs(dept_time - arr_time);
 			(*temp_DB)->record = nptr->record;
 			(*temp_DB)->next = NULL;
 		}
 		else if(max == abs(dept_time - arr_time))
 		{
 			insertAtEnd(temp_DB, nptr->record.flight_name, nptr->record.flight_id, nptr->record.flight_capacity, nptr->record.flight_arr_time, nptr->record.flight_dept_time, nptr->record.flight_status, nptr->record.flight_delay_time, nptr->record.flight_class);
 		}
		nptr = nptr->next;
 	}
 	return;
}

void getSortedOnArrivalTime(flightNode** head_ptr) {
	flightNode *firsthalf, *secondhalf, *lptr = *head_ptr;
	if(lptr != NULL && (lptr->next != NULL))
	{	
		divide(lptr, &firsthalf, &secondhalf);
		getSortedOnArrivalTime(&firsthalf);
		getSortedOnArrivalTime(&secondhalf);
		*head_ptr = mergeArrivalTime(firsthalf, secondhalf);
	}
	return;
}

flightNode* mergeArrivalTime(flightNode* firsthalf, flightNode* secondhalf) {
	flightNode* result, *ptr1, *ptr2, *tail;
	ptr1 = firsthalf;
	ptr2 = secondhalf;
	if(strcmp(ptr1->record.flight_arr_time, ptr2->record.flight_arr_time) < 0)
	{
		result = ptr1;
		ptr1 = ptr1->next;
	}
	else
	{
		result = ptr2;
		ptr2 = ptr2->next;		
	}
	tail = result;
	while(ptr1 && ptr2)
	{
		if(strcmp(ptr1->record.flight_arr_time, ptr2->record.flight_arr_time) < 0)
		{
			tail->next = ptr1;
			ptr1 = ptr1->next;
			tail = tail->next;
		}
		else
		{
			tail->next = ptr2;
			ptr2 = ptr2->next;
			tail = tail->next;		
		}
	}
	if(ptr1)
		tail->next = ptr1;
	else
		tail->next = ptr2;
	return result;
}

void getSortedOnDepartureTime(flightNode** head_ptr) {
	flightNode *firsthalf, *secondhalf, *lptr = *head_ptr;
	if(lptr != NULL && (lptr->next != NULL))
	{	
		divide(lptr, &firsthalf, &secondhalf);
		getSortedOnDepartureTime(&firsthalf);
		getSortedOnDepartureTime(&secondhalf);
		*head_ptr = mergeDepartureTime(firsthalf, secondhalf);
	}
	return;
}

flightNode* mergeDepartureTime(flightNode* firsthalf, flightNode* secondhalf) {
	flightNode* result, *ptr1, *ptr2, *tail;
	ptr1 = firsthalf;
	ptr2 = secondhalf;
	if(strcmp(ptr1->record.flight_dept_time, ptr2->record.flight_dept_time) < 0)
	{
		result = ptr1;
		ptr1 = ptr1->next;
	}
	else
	{
		result = ptr2;
		ptr2 = ptr2->next;		
	}
	tail = result;
	while(ptr1 && ptr2)
	{
		if(strcmp(ptr1->record.flight_dept_time, ptr2->record.flight_dept_time) < 0)
		{
			tail->next = ptr1;
			ptr1 = ptr1->next;
			tail = tail->next;
		}
		else
		{
			tail->next = ptr2;
			ptr2 = ptr2->next;
			tail = tail->next;		
		}
	}
	if(ptr1)
		tail->next = ptr1;
	else
		tail->next = ptr2;
	return result;
}

void getSortedOnStayTime(flightNode** head_ptr) {
	flightNode *firsthalf, *secondhalf, *lptr = *head_ptr;
	if(lptr != NULL && (lptr->next != NULL))
	{	
		divide(lptr, &firsthalf, &secondhalf);
		getSortedOnStayTime(&firsthalf);
		getSortedOnStayTime(&secondhalf);
		*head_ptr = mergeStayTime(firsthalf, secondhalf);
	}
	return;
}

flightNode* mergeStayTime(flightNode* firsthalf, flightNode* secondhalf) {
	flightNode* result, *ptr1, *ptr2, *tail;
	ptr1 = firsthalf;
	ptr2 = secondhalf;
	int stay_time1 = abs(atoi(ptr1->record.flight_dept_time) - atoi(ptr1->record.flight_arr_time));
	int stay_time2 = abs(atoi(ptr2->record.flight_dept_time) - atoi(ptr2->record.flight_arr_time));
	if(stay_time1 < stay_time2)
	{
		result = ptr1;
		ptr1 = ptr1->next;
	}
	else
	{
		result = ptr2;
		ptr2 = ptr2->next;		
	}
	tail = result;
	while(ptr1 && ptr2)
	{
		stay_time1 = abs(atoi(ptr1->record.flight_dept_time) - atoi(ptr1->record.flight_arr_time));
		stay_time2 = abs(atoi(ptr2->record.flight_dept_time) - atoi(ptr2->record.flight_arr_time));
		if(stay_time1 < stay_time2)
		{
			tail->next = ptr1;
			ptr1 = ptr1->next;
			tail = tail->next;
		}
		else
		{
			tail->next = ptr2;
			ptr2 = ptr2->next;
			tail = tail->next;		
		}
	}
	if(ptr1)
		tail->next = ptr1;
	else
		tail->next = ptr2;
	return result;
}

void divide(flightNode* head, flightNode**fronthalf, flightNode** backhalf) {
	flightNode* fast; 
    flightNode* slow; 
    slow = head; 
    fast = head->next; 
  
    // Advance 'fast' two nodes, and advance 'slow' one node
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 

    *fronthalf = head; 
    *backhalf = slow->next; 
    slow->next = NULL; 
}

statusCode UpdateFlightStatus(flightNode** head_ptr, flightNode** list1_ptr, flightNode** list2_ptr, flightNode** list3_ptr, char flightId[], char flightArrTime[], char flightStatus[], char delayTime[]) {
	statusCode status_code = FAILURE;
	flightNode* nptr = *head_ptr;
	Bool found = FALSE;
	while(nptr && !found) {
		if(!strcmp(flightId, nptr->record.flight_id) && !strcmp(flightArrTime, nptr->record.flight_arr_time))
			found = TRUE;
		else
			nptr = nptr->next;
	}
	if(found) {
		strcpy(nptr->record.flight_status, flightStatus);
		if (!strcmp(nptr->record.flight_status, "DELAY"))
		{
			int dept_time, arr_time, delay_time;
			strcpy(nptr->record.flight_delay_time, delayTime);
			dept_time = atoi(nptr->record.flight_dept_time);
			arr_time = atoi(nptr->record.flight_arr_time);
			delay_time = atoi(nptr->record.flight_delay_time);
			dept_time = dept_time + delay_time;	// Updated Departure and Arrival Time
			arr_time = arr_time + delay_time;
			sprintf(nptr->record.flight_dept_time, "%d", dept_time);	// Converting int to string
			sprintf(nptr->record.flight_arr_time, "%d", arr_time);
		}
		else if (!strcmp(nptr->record.flight_status, "PROMOTED"))
 		{
 			flightClassDT original_flight_class, updated_flight_class;
 			original_flight_class = nptr->record.flight_class;

 			if(original_flight_class != VVIP)	// If it is 1(PUBLIC) or 2(VIP)
 				updated_flight_class = original_flight_class + 1;	// PUBLIC TO VIP, VIP TO VVIP
 			else		
 				updated_flight_class = original_flight_class;
 			nptr->record.flight_class = updated_flight_class;

 			if(original_flight_class != updated_flight_class)
 			{
 				switch(original_flight_class)
 				{
 					case PUBLIC: 
 					{
 						Delete(list1_ptr, flightId, flightArrTime);
 						insertAtEnd(list2_ptr, nptr->record.flight_name , flightId, nptr->record.flight_capacity, flightArrTime, nptr->record.flight_dept_time, flightStatus, delayTime, updated_flight_class);
 					 	break;
 					}
 					case VIP: 
 					{
 						Delete(list2_ptr, flightId, flightArrTime);
 						insertAtEnd(list3_ptr, nptr->record.flight_name , flightId, nptr->record.flight_capacity, flightArrTime, nptr->record.flight_dept_time, flightStatus, delayTime, updated_flight_class);
 					 	break;
 					}
 					default: break;
 				}
 			}
 		}
		status_code = SUCCESS;
	}
 	insertion_sort(head_ptr);
 	insertion_sort(list1_ptr);
 	insertion_sort(list2_ptr);
 	insertion_sort(list3_ptr);
 	return status_code;
}

statusCode listUnique(flightNode** head_ptr) {
	statusCode status_code = FAILURE;
	flightNode* nptr = *head_ptr, *ptr;
	int min_delayTime;
	if(nptr) {
		while(nptr->next != NULL)
		{
			min_delayTime = atoi(nptr->record.flight_delay_time);
			ptr = nptr->next;
			while(ptr != NULL)
			{
				if (!strcmp(nptr->record.flight_name, ptr->record.flight_name) && !strcmp(nptr->record.flight_id, ptr->record.flight_id))
				{
					if (min_delayTime <= atoi(ptr->record.flight_delay_time))	// deletes duplicate records with higher delayTime
					{
						Delete(head_ptr, ptr->record.flight_id, ptr->record.flight_arr_time);
					}	
					else
					{
						flight_record temp;
						temp = ptr->record;
						Delete(head_ptr, ptr->record.flight_id, ptr->record.flight_arr_time);
						nptr->record = temp;
					}
					status_code = SUCCESS;
				}
				ptr = ptr->next;
			}
			nptr = nptr->next;
		}
	}
 	return status_code;
}

void insertion_sort(flightNode** head_ptr) {
 	flightNode* sorted = NULL;
	flightNode* nptr = *head_ptr;
    while (nptr != NULL) { 
        flightNode* next = nptr->next;
        sortedInsert(&sorted, nptr);
        nptr = next;
    }  
    *head_ptr = sorted; 
}

void sortedInsert(flightNode** head_ptr, flightNode* new_node) { 
    flightNode* current; 
    // Special case for the head end
    if (*head_ptr == NULL || strcmp((*head_ptr)->record.flight_id, new_node->record.flight_id) > 0 || (!strcmp((*head_ptr)->record.flight_id, new_node->record.flight_id) && strcmp((*head_ptr)->record.flight_arr_time, new_node->record.flight_arr_time) > 0))
    { 
        new_node->next = *head_ptr; 
        *head_ptr = new_node; 
    } 
    else
    { 
        // Locate the node before the point of insertion
        current = *head_ptr; 
        while (current->next != NULL && (strcmp(current->record.flight_id, new_node->record.flight_id) < 0 || (!strcmp(current->record.flight_id, new_node->record.flight_id) && strcmp(current->record.flight_arr_time, new_node->record.flight_arr_time) < 0)))
        { 
            current = current->next; 
        } 
        new_node->next = current->next; 
        current->next = new_node; 
    } 
}

int getch(void) // Code extracted from Stack Overflow to get getch() functionality while executing in Linux/Unix OS.
{
   	struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}