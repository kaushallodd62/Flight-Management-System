//Flight Managment System
//Author: Kaushal Lodd

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define FLIGHT_NAME_LEN 50
#define FLIGHT_ID_LEN 10
#define TIME_LEN 4 // Military Time System, eg 1400 = 2:00pm, 0600 = 6:00am
#define STATUS_LEN 20
#define DB_SIZE 100
#define PUBLIC 1
#define VIP 2
#define VVIP 3

struct flight_record
{
	char flight_name[FLIGHT_NAME_LEN];
	char flight_id[FLIGHT_ID_LEN];
	unsigned int flight_capacity;
	char flight_arr_time[TIME_LEN];
	char flight_dept_time[TIME_LEN];
	int flight_class; // 1 = PUBLIC, 2 = VIP, 3 = VVIP
}list1[DB_SIZE], list2[DB_SIZE], list3[DB_SIZE];	 // 3 Sorted list provided, one each for every class.

struct updated_flight_record
{
	struct flight_record record;
	char flight_status[STATUS_LEN];
	int flight_delay_time;
};

void Initialize(struct flight_record flight_DB[], int size);
void Initialize_updated_DB(struct updated_flight_record updated_flight_DB[], int size);
int insert(struct flight_record flight_DB[], int size, char flightName[], char flightId[], int flightCapacity, char flightArrTime[], char flightDeptTime[], int flightClass);
int insert_update(struct flight_record flight_DB[], int size, char flightName[], char flightId[], int flightCapacity, char flightArrTime[], char flightDeptTime[], int flightClass);
int delete(struct flight_record flight_DB[], int size, char flightId[], char flightArrTime[]);
void delete_updated_DB(struct updated_flight_record updated_flight_DB[], int size, char flightId[], char flightName[], int delayTime);
int getNumFlights(struct flight_record flight_DB[], int size);
int isEmpty(struct flight_record flight_DB[], int size);
int isFull(struct flight_record flight_DB[], int size);
int getFlightWithtLongeststay(struct flight_record flight_DB[], struct flight_record temp_DB[], int size);
void getSortedOnArrivalTime(struct flight_record flight_DB[], int size);
void getSortedOnDepartureTime(struct flight_record flight_DB[], int size);
void getSortedOnStayTime(struct flight_record flight_DB[], int size);
int UpdateFlightStatus(struct flight_record flight_DB[], struct updated_flight_record updated_flight_DB[], char flightId[], char flightArrTime[], char flightStatus[], int delayTime, int size);
int listUnique(struct updated_flight_record updated_flight_DB[], int size);
void insertion_sort(struct flight_record flight_DB[], int size);
int getch(void);

int main()
{
	struct flight_record flight_DB[DB_SIZE]; // list
	struct updated_flight_record updated_flight_DB[DB_SIZE];
	Initialize(flight_DB, DB_SIZE);
	Initialize_updated_DB(updated_flight_DB, DB_SIZE);
	Initialize(list1, DB_SIZE);
	Initialize(list2, DB_SIZE);
	Initialize(list3, DB_SIZE);
	int choice;
 	do
 	{
 		system("clear");
 		puts("--------------------------------------------------------------------------------");
 		puts("                             FLIGHT MANAGMENT SYSTEM");
 		puts("--------------------------------------------------------------------------------");
 		printf("1.Insert/Update Record\n2.Delete Record\n3.Number of Flights\n4.Database status(Empty/full).\n");
 		printf("5.Flights with max stay time\n6.View sorted Database.\n7.Update Flight Status.\n8.View Unique Database\n9.Exit\n");
 		puts("--------------------------------------------------------------------------------");
 		printf("Enter Choice: ");
 		scanf("%d",&choice);
 		switch (choice)
 		{
 			case 1:	{
 						system("clear");
 						char flightName[FLIGHT_NAME_LEN], flightId[FLIGHT_ID_LEN], flightArrTime[TIME_LEN], flightDeptTime[TIME_LEN];
 						unsigned int flightCapacity;
 						int flightClass, status_code;
 						puts("--------------------------------------------------------------------------------");
 						puts("                          ENTER THE FOLLOWING INFORMATION");
 						puts("--------------------------------------------------------------------------------");
 						printf("Enter the Flight Name: ");
 						scanf("%s", flightName);
 						printf("Enter the flight ID: ");
 						scanf("%s", flightId);
 						printf("Enter the Flight Capacity: ");
 						scanf("%d", &flightCapacity);
 						printf("Enter Flight Arrival Time (In Military Time System): ");
 						scanf("%s", flightArrTime);
 						printf("Enter Flight Departure Time (In Military Time System): ");
 						scanf("%s", flightDeptTime);
 						printf("Enter Flight Class (1 for Public, 2 for VIP, 3 for VVIP): ");
 						scanf("%d", &flightClass);
 						status_code = insert_update(flight_DB, DB_SIZE, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightClass);
 						system("clear");
 						if (status_code)
 						{
 							puts("--------------------------------------------------------------------------------");
 							puts("                           DATA ENTERED SUCCESSFULLY!!");
 							puts("--------------------------------------------------------------------------------");
 							printf("Enter any key to go back.");
 							getch();
 							getch();
 						}
 						else
 						{
 							puts("--------------------------------------------------------------------------------");
 							puts("                        DATABASE FULL! COULD NOT ENTER DATA!");
 							puts("--------------------------------------------------------------------------------");
 							printf("Enter any key to go back.");
 							getch();
 							getch();
 						}
 						break;
 			}
 			case 2:	{
 						system("clear");
 						char flightId[FLIGHT_ID_LEN], flightArrTime[TIME_LEN];
 						int status_code;
 						puts("--------------------------------------------------------------------------------");
 						puts("                          ENTER THE FOLLOWING INFORMATION");
 						puts("--------------------------------------------------------------------------------");
 						printf("Enter the flight ID: ");
 						scanf("%s", flightId);
 						printf("Enter Flight Arrival Time (In Military Time System): ");
 						scanf("%s", flightArrTime);
 						status_code = delete(flight_DB, DB_SIZE, flightId, flightArrTime);
 						system("clear");
 						if (status_code)
 						{
 							puts("--------------------------------------------------------------------------------");
 							puts("                         RECORD DELETED SUCCESSFULLY!!");
 							puts("--------------------------------------------------------------------------------");
 							printf("Enter any key to go back.");
 							getch();
 							getch();
 						}
 						else
 						{
 							puts("--------------------------------------------------------------------------------");
 							puts("                    RECORD WAS NOT FOUND! OPERATION FAILED!");
 							puts("--------------------------------------------------------------------------------");
 							printf("Enter any key to go back.");
 							getch();
 							getch();
 						}
 						break;
 			}
 			case 3:	{
 						system("clear");
 						int num_of_flights;
 						num_of_flights = getNumFlights(flight_DB, DB_SIZE);
 						puts("--------------------------------------------------------------------------------");
 						printf("                 TOTAL NUMBER OF FLIGHTS IN THE DATABASE: %d\n", num_of_flights);
 						puts("--------------------------------------------------------------------------------");
 						printf("Enter any key to go back.");
 						getch();
 						getch();
 						break;
 			}
 			case 4: {
 						system("clear");
 						if(isEmpty(flight_DB, DB_SIZE))
 							printf("Database is EMPTY.\n");
 						else if (isFull(flight_DB, DB_SIZE))
 							printf("Database is FULL.\n");
 						else
 							printf("Database is neither EMPTY nor FULL.\n");
 						break;
 			}
 			case 5: {
 						system("clear");
 						struct flight_record temp_DB[DB_SIZE];
 						int i, count, dept_time, arr_time, stay_time;
 						Initialize(temp_DB, DB_SIZE);
 						count = getFlightWithtLongeststay(flight_DB, temp_DB, DB_SIZE);
 						puts("--------------------------------------------------------------------------------");
 						puts("                    THESE ARE THE FLIGHTS WITH MAX STAY TIME");
 						puts("--------------------------------------------------------------------------------");
 						printf("Flight Name\tFlight ID\tFlight Arrival Time\tStay Time\n");
 						puts("--------------------------------------------------------------------------------");
 						dept_time = atoi(temp_DB[0].flight_dept_time);
 						arr_time = atoi(temp_DB[0].flight_arr_time);
 						stay_time = abs(dept_time - arr_time);
 						for (i = 0; i < count; ++i)
 						{
 							printf("%s\t%s\t%s\t%d\n", temp_DB[i].flight_name, temp_DB[i].flight_id, temp_DB[i].flight_arr_time, stay_time);
 						}
 						puts("--------------------------------------------------------------------------------");
 						printf("Enter any key to go back.");
 						getch();
 						getch();
 						break;
 			}
 			case 6: {
 						system("clear");
 						int sort_choice;
 						puts("--------------------------------------------------------------------------------");
 						puts("                             FLIGHT MANAGMENT SYSTEM");
 						puts("--------------------------------------------------------------------------------");
 						printf("1.Sort on Arrival Time.\n2.Sort on Departure Time.\n3.Sort on Stay Time\n");
 						puts("--------------------------------------------------------------------------------");
 						printf("Enter Choice: ");
 						scanf("%d",&sort_choice);
 						switch (sort_choice)
 						{
 							case 1: {
 										system("clear");	
 										getSortedOnArrivalTime(flight_DB, DB_SIZE);
 										break;
 							}
 							case 2: {
 										system("clear");
 										getSortedOnDepartureTime(flight_DB, DB_SIZE);
 										break;
 							}
 							case 3: {
 										system("clear");
 										getSortedOnStayTime(flight_DB, DB_SIZE);
 										break;
 							}
 							default:{
 										break;
 							}
 						}
 						break;
 			}
 			case 7: {
 						system("clear");
 						int i, delayTime = -1, status_code;
 						char flightId[FLIGHT_ID_LEN], flightArrTime[TIME_LEN], flightStatus[STATUS_LEN];
 						i = 0;
 						while (i < DB_SIZE)
 						{
 							updated_flight_DB[i].record = flight_DB[i];
 							i++;
 						}
 						puts("--------------------------------------------------------------------------------");
 						puts("                          ENTER THE FOLLOWING INFORMATION");
 						puts("--------------------------------------------------------------------------------");
 						printf("Enter the Flight ID: ");
 						scanf("%s", flightId);
 						printf("Enter Flight Arrival Time (In Military Time System): ");
 						scanf("%s", flightArrTime);
 						printf("Enter Flight Status of the Flight");
 						scanf("%s", flightStatus);
 						if (!strcmp(flightStatus, "DELAY"))
 						{
 							printf("Enter delay time (In Military Time System): ");
 							scanf("%d", &delayTime);
 						}
 						status_code = UpdateFlightStatus(flight_DB, updated_flight_DB, flightId, flightArrTime, flightStatus, delayTime, DB_SIZE);
 						system("clear");
 						if (status_code)
 						{
 							puts("--------------------------------------------------------------------------------");
 							puts("                           DATA UPDATED SUCCESSFULLY!!");
 							puts("--------------------------------------------------------------------------------");
 							printf("Enter any key to go back.");
 							getch();
 							getch();
 						}
 						else
 						{
 							puts("--------------------------------------------------------------------------------");
 							puts("                      RECORD WAS NOT FOUND! OPERATION FAILED!");
 							puts("--------------------------------------------------------------------------------");
 							printf("Enter any key to go back.");
 							getch();
 							getch();
 						}
 						break;
 			}
 			case 8: {
 						int status_code;
 						status_code = listUnique(updated_flight_DB, DB_SIZE);
 						system("clear");
 						if (status_code)
 						{
 							puts("--------------------------------------------------------------------------------");
 							puts("                       DUPLICATE RECORDS DELETED SUCCESSFULLY!!");
 							puts("--------------------------------------------------------------------------------");
 							printf("Enter any key to go back.");
 							getch();
 							getch();
 						}
 						else
 						{
 							puts("--------------------------------------------------------------------------------");
 							puts("                      NO DUPLICATE RECORDS FOUND!");
 							puts("--------------------------------------------------------------------------------");
 							printf("Enter any key to go back.");
 							getch();
 							getch();
 						}
 						break;
 			}
 			case 9: {
 						break;
 			}
 			default: {
 						system("clear");
 						printf("Invalid Input\nPlease Try again\n");
 						printf("Enter any key to go back.");
 						getch();
 						getch();
 						break;
 			}		
 		}
 	}
	while(choice != 9);
	return 0;
}

 void Initialize(struct flight_record flight_DB[], int size)
 {
 	for (int i = 0; i < size; ++i) //Initializing Array of Structure
 	{
 		flight_DB[i].flight_name[0] = '\0';
 		flight_DB[i].flight_id[0] = '\0';
 		flight_DB[i].flight_capacity = 0;
 		flight_DB[i].flight_arr_time[0] = '\0';
 		flight_DB[i].flight_dept_time[0] = '\0';
 		flight_DB[i].flight_class = -1;
 	}
 }

 void Initialize_updated_DB(struct updated_flight_record updated_flight_DB[], int size)
 {		
 	for (int i = 0; i < size; ++i)	//Initializing Array of Structure
	{
 		updated_flight_DB[i].record.flight_name[0] = '\0';
 	 	updated_flight_DB[i].record.flight_id[0] = '\0';
 	 	updated_flight_DB[i].record.flight_capacity = 0;
 	 	updated_flight_DB[i].record.flight_arr_time[0] = '\0';
 		updated_flight_DB[i].record.flight_dept_time[0] = '\0';
  		updated_flight_DB[i].record.flight_class = -1;
 	 	updated_flight_DB[i].flight_status[0] = '\0';
 	 	updated_flight_DB[i].flight_delay_time = -1;
 	}
 }

 int insert(struct flight_record flight_DB[], int size, char flightName[], char flightId[], int flightCapacity, char flightArrTime[], char flightDeptTime[], int flightClass)
 {
 	int i = 0, is_freeLoc = 0, status_code = 1;
 	while(i < size && !is_freeLoc)
 	{
 		if(flight_DB[i].flight_id[0] == '\0' && flight_DB[i].flight_arr_time[0] == '\0')
 			is_freeLoc = 1;
 	 	else 
 	 		i++;
 	}
 	if (is_freeLoc)
  	{
 		strcpy(flight_DB[i].flight_name, flightName);
 	 	strcpy(flight_DB[i].flight_id, flightId);
 	 	flight_DB[i].flight_capacity = flightCapacity;
 	 	strcpy(flight_DB[i].flight_arr_time, flightArrTime);
 	 	strcpy(flight_DB[i].flight_dept_time, flightDeptTime);
 	 	flight_DB[i].flight_class = flightClass;
 	}
 	else
 	 	status_code = 0;
 	return status_code;
 }

 int insert_update(struct flight_record flight_DB[], int size, char flightName[], char flightId[], int flightCapacity, char flightArrTime[], char flightDeptTime[], int flightClass)
 {
 	int i = 0, loc1 = -1, loc2 = -1, loc3 = -1, found = 0, found_in_list1 = 0, found_in_list2 = 0, found_in_list3 = 0, status_code = 1;
 	while (flight_DB[i].flight_id[0] != '\0')	// to find the number of filled records
 		i++;
 	size = i; i = 0;
 	while(i < size && !found)
 	{
 		if (loc1 == -1 && !strcmp(flightId, list1[i].flight_id) && !strcmp(flightArrTime, list1[i].flight_arr_time))
 		{	
 			found_in_list1 = 1;
 			loc1 = i;
 		}
 		else if (loc2 == -1 && !strcmp(flightId, list2[i].flight_id) && !strcmp(flightArrTime, list2[i].flight_arr_time))
 		{	
 			found_in_list2 = 1;
 			loc2 = i;
 		}
 		else if (loc3 == -1 && !strcmp(flightId, list3[i].flight_id) && !strcmp(flightArrTime, list3[i].flight_arr_time))
 		{	
 			found_in_list3 = 1;
 			loc3 = i;
 		}

 		if(!strcmp(flightId, flight_DB[i].flight_id) && !strcmp(flightArrTime, flight_DB[i].flight_arr_time))
 			found = 1;
 		else 
 			i++;
 	}
 	
 	if (found)
 	{
 		int deleted = 0;
 		if(found_in_list1)
 		{
 			int old_flightClass;
 			old_flightClass = list1[loc1].flight_class;
 			if (old_flightClass != flightClass)
 			{
 				delete(list1, size, flightId, flightArrTime);
 				deleted = 1;
 			}
 		}
 		else if(found_in_list2)
 		{
 			int old_flightClass;
 			old_flightClass = list2[loc2].flight_class;
 			if (old_flightClass != flightClass)
 			{
 				delete(list2, size, flightId, flightArrTime);
 				deleted = 1;
 			}
 		}
 		else if(found_in_list3)
 		{
 			int old_flightClass;
 			old_flightClass = list3[loc3].flight_class;
 			if (old_flightClass != flightClass)
 			{
 				delete(list3, size, flightId, flightArrTime);
 				deleted = 1;
 			}
 		}
 		if (deleted)
 		{
 			switch (flightClass)
 			{
 				case 1: 
 				{
 					insert(list1, DB_SIZE, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightClass);
 				 	break;
 				}
 				case 2: 
 				{
 					insert(list2, DB_SIZE, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightClass);
 				 	break;
 				}
 				case 3: 
 				{
 					insert(list3, DB_SIZE, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightClass);
 				 	break;
 				}
 			}
 		}
 		strcpy(flight_DB[i].flight_name, flightName);
 		flight_DB[i].flight_capacity = flightCapacity;
 		strcpy(flight_DB[i].flight_dept_time, flightDeptTime);
 		flight_DB[i].flight_class = flightClass;
 	}
 	else
 	{
 		status_code = insert(flight_DB, DB_SIZE, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightClass);
 	 	switch (flightClass)
 	 	{
 	 		case 1: 
 	 		{
 	 			insert(list1, DB_SIZE, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightClass);
 				break;
 	 		}
 	 		case 2: 
 	 		{
 	 			insert(list2, DB_SIZE, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightClass);
 				break;
 	 		}
 	 		case 3: 
 	 		{
 	 			insert(list3, DB_SIZE, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightClass);
 	 			break;
 	 		}
 		}
 	}
 	insertion_sort(flight_DB, size);
 	insertion_sort(list1, size);
 	insertion_sort(list2, size);
 	insertion_sort(list3, size);
 	return status_code;
 }

 int delete(struct flight_record flight_DB[], int size, char flightId[], char flightArrTime[])
 {
 	int i, found, status_code;
 	i = 0; found = 0; status_code = 1;
 	while(i < size && !found)
 	{
 		if(!strcmp(flightId, flight_DB[i].flight_id) && !strcmp(flightArrTime, flight_DB[i].flight_arr_time))
 			found = 1;
 		else 
 			i++;
 	}
 	if (found)
 	{
 		flight_DB[i].flight_name[0] = '\0';
 		flight_DB[i].flight_id[0] = '\0';
 		flight_DB[i].flight_capacity = 0;
 		flight_DB[i].flight_arr_time[0] = '\0';
 		flight_DB[i].flight_dept_time[0] = '\0';
 		flight_DB[i].flight_class = -1;
 	}
 	else
 		status_code = 0;
 	insertion_sort(flight_DB, size);
 	return status_code;
 }

 void delete_updated_DB(struct updated_flight_record updated_flight_DB[], int size, char flightId[], char flightName[], int delayTime)
 {
 	int i, found;
 	struct flight_record temp_DB[DB_SIZE];
 	i = 0; found = 0;
 	while(i < size && !found)
 	{
 		if(!strcmp(flightId, updated_flight_DB[i].record.flight_id) && !strcmp(flightName, updated_flight_DB[i].record.flight_name) && delayTime == updated_flight_DB[i].flight_delay_time)
 			found = 1;
 		else 
 			i++;
 	}
 	if (found)
 	{
 		updated_flight_DB[i].record.flight_name[0] = '\0';
 	 	updated_flight_DB[i].record.flight_id[0] = '\0';
 	 	updated_flight_DB[i].record.flight_capacity = 0;
 	 	updated_flight_DB[i].record.flight_arr_time[0] = '\0';
 		updated_flight_DB[i].record.flight_dept_time[0] = '\0';
  		updated_flight_DB[i].record.flight_class = -1;
 	 	updated_flight_DB[i].flight_status[0] = '\0';
 	 	updated_flight_DB[i].flight_delay_time = -1;
 	}
 	i = 0;
 	while (i < DB_SIZE)			// Copying updated_flight_DB[] to temp_DB[] so that temp_DB[] can be sorted and copied back to updated_flight_DB[], thus sorting updated_flight_DB[]
 	{
 		temp_DB[i] = updated_flight_DB[i].record;
 		i++;
 	}
 	insertion_sort(temp_DB, size);
 	i = 0;
 	while (i < DB_SIZE)
 	{
 		updated_flight_DB[i].record = temp_DB[i];
 		i++;
 	}
 }

 int getNumFlights(struct flight_record flight_DB[], int size)
 {
 	int i, j, count, duplicate;
 	count = 0; duplicate = 0;
 	for (i = 0; (i < size - 1) && (flight_DB[i].flight_id[0] != '\0'); ++i) //Database is already sorted, so we only go till the last filled records
 	{
 		for (j = i+1; (j < size) && (!duplicate) && (flight_DB[i].flight_id[0] != '\0'); ++j) // To reduce no. of checks of the conditions, we only go till the last filled records
 		{
 			if (!strcmp(flight_DB[i].flight_id, flight_DB[j].flight_id) && !strcmp(flight_DB[i].flight_arr_time, flight_DB[j].flight_arr_time))
 				duplicate = 1;
 		}
 		if (!duplicate)
 			count++;
 	}
 	return count;
 }

 int isEmpty(struct flight_record flight_DB[], int size)
 {
 	int i, empty;
 	i = 0; empty = 1; // Assuming it is true
 	while(i < size && empty)
 	{
 		if(flight_DB[i].flight_id[0] != '\0')
 			empty = 0;
 	}
 	return empty;
 }
 
 int isFull(struct flight_record flight_DB[], int size)
 {
 	int i, full;
 	i = 0; full = 1; // Assuming it is true
 	while(i < size && full)
 	{
 		if(flight_DB[i].flight_id[0] == '\0')
 			full = 0;
 	}
 	return full;
 }

 int getFlightWithtLongeststay(struct flight_record flight_DB[], struct flight_record temp_DB[], int size) 
 // temp_DB stores flight records of flights having longest stay
 // max dept_time - arr_time
 {
 	int dept_time, arr_time, max, i, j, count=1; 
 	dept_time = atoi(flight_DB[0].flight_dept_time);
 	arr_time = atoi(flight_DB[0].flight_arr_time);
 	max = abs(dept_time - arr_time);
 	j = 0;
 	temp_DB[j] = flight_DB[0];
 	for (i = 1; (i < size) && (flight_DB[i].flight_id[0] != '\0'); ++i)	// we only go till the last filled records
 	{
 		dept_time = atoi(flight_DB[i].flight_dept_time);
 		arr_time = atoi(flight_DB[i].flight_arr_time);
 		if (max < abs(dept_time - arr_time))
 		{
 			max = abs(dept_time - arr_time);
 			j = 0;
 			temp_DB[j] = flight_DB[i];
 			count = 1;								// count of number of flights with max stay time
 		}
 		else if(max == abs(dept_time - arr_time))
 		{
 			count++;
 			j++;
 			temp_DB[j] = flight_DB[i];				// storing all those records which have max stay time in a temp database
 		}
 	}
 	return count;
 }

 void getSortedOnArrivalTime(struct flight_record flight_DB[], int size)
 {
 	int i, j, count, sorted, arr_time1, arr_time2;
 	struct flight_record temp;
 	i = 0;
 	while (flight_DB[i].flight_id[0] != '\0')	// to find the number of filled records
 		i++;
 	count = i;
 	sorted = 0;
 	for (i = 0; (i < count) && (!sorted); ++i)
 	{
 		sorted = 1;
 		for (j = 0; j < count - i -1; j++)
 		{
 			arr_time1 = atoi(flight_DB[j].flight_arr_time);
 			arr_time2 = atoi(flight_DB[j+1].flight_arr_time);
 			if(arr_time1 > arr_time2)
 			{
 				temp = flight_DB[j];
 				flight_DB[j] = flight_DB[j+1];
 				flight_DB[j+1] = temp;
 				sorted = 0;
 			}
 		}
 	}
 	puts("--------------------------------------------------------------------------------");
 	puts("                           SORTED ON ARRIVAL TIME");
 	puts("--------------------------------------------------------------------------------");
 	printf("Flight Name\tFlight ID\tFlight Arrival Time\tFlight Departure Time\n");
 	puts("--------------------------------------------------------------------------------");
 	for (i = 0; i < count; ++i)
 	{
 		printf("%s\t%s\t%s\t%s\n", flight_DB[i].flight_name, flight_DB[i].flight_id, flight_DB[i].flight_arr_time, flight_DB[i].flight_dept_time);
	}
 	puts("--------------------------------------------------------------------------------");
 	printf("Enter any key to go back.");
 	getch();
 	getch();
 }

 void getSortedOnDepartureTime(struct flight_record flight_DB[], int size)
 {
 	int i, j, count, sorted, dept_time1, dept_time2;
 	struct flight_record temp;
 	i = 0;
 	while (flight_DB[i].flight_id[0] != '\0')	// to find the number of filled records
 		i++;
 	count = i;
 	sorted = 0;
 	for (i = 0; (i < count) && (!sorted); ++i)
 	{
 		sorted = 1;
 		for (j = 0; j < count - i -1; j++)
 		{
 			dept_time1 = atoi(flight_DB[j].flight_dept_time);
 			dept_time2 = atoi(flight_DB[j+1].flight_dept_time);
 			if(dept_time1 > dept_time2)
 			{
 				temp = flight_DB[j];
 				flight_DB[j] = flight_DB[j+1];
 				flight_DB[j+1] = temp;
 				sorted = 0;
 			}
 		}
 	}
 	puts("--------------------------------------------------------------------------------");
 	puts("                           SORTED ON DEPARTURE TIME");
 	puts("--------------------------------------------------------------------------------");
 	printf("Flight Name\tFlight ID\tFlight Arrival Time\tFlight Departure Time\n");
 	puts("--------------------------------------------------------------------------------");
 	for (i = 0; i < count; ++i)
 	{
 		printf("%s\t%s\t%s\t%s\n", flight_DB[i].flight_name, flight_DB[i].flight_id, flight_DB[i].flight_arr_time, flight_DB[i].flight_dept_time);
	}
 	puts("--------------------------------------------------------------------------------");
 	printf("Enter any key to go back.");
 	getch();
 	getch();
 }

 void getSortedOnStayTime(struct flight_record flight_DB[], int size)
 {
 	int i, j, count, sorted, dept_time, arr_time, stay_time, stay_time1, stay_time2;
 	struct flight_record temp;
 	i = 0;
 	while (flight_DB[i].flight_id[0] != '\0')	// to find the number of filled records
 		i++;
 	count = i;
 	sorted = 0;
 	for (i = 0; (i < count) && (!sorted); ++i)
 	{
 		sorted = 1;
 		for (j = 0; j < count - i -1; j++)
 		{
 			dept_time = atoi(flight_DB[j].flight_dept_time);
 			arr_time = atoi(flight_DB[j].flight_arr_time);
 			stay_time1 = abs(dept_time - arr_time);

 			dept_time = atoi(flight_DB[j+1].flight_dept_time);
 			arr_time = atoi(flight_DB[j+1].flight_arr_time);
 			stay_time2 = abs(dept_time - arr_time);

 			if(stay_time1 > stay_time2)
 			{
 				temp = flight_DB[j];
 				flight_DB[j] = flight_DB[j+1];
 				flight_DB[j+1] = temp;
 				sorted = 0;
 			}
 		}
 	}
 	puts("--------------------------------------------------------------------------------");
 	puts("                           SORTED ON STAY TIME");
 	puts("--------------------------------------------------------------------------------");
 	printf("Flight Name\tFlight ID\tFlight Arrival Time\tFlight Departure Time\tStay Time\n");
 	puts("--------------------------------------------------------------------------------");
 	for (i = 0; i < count; ++i)
 	{
 		dept_time = atoi(flight_DB[j].flight_dept_time);
 		arr_time = atoi(flight_DB[j].flight_arr_time);
 		stay_time = abs(dept_time - arr_time);
 		printf("%s\t%s\t%s\t%s\t%d\n", flight_DB[i].flight_name, flight_DB[i].flight_id, flight_DB[i].flight_arr_time, flight_DB[i].flight_dept_time, stay_time);
	}
 	puts("--------------------------------------------------------------------------------");
 	printf("Enter any key to go back.");
 	getch();
 	getch();
 }

 int UpdateFlightStatus(struct flight_record flight_DB[], struct updated_flight_record updated_flight_DB[], char flightId[], char flightArrTime[], char flightStatus[], int delayTime, int size)
 {
 	int i, found, status_code;
 	i = 0; found = 0; status_code = 1;
 	while(i < size && !found)
 	{
 		if(!strcmp(flightId, updated_flight_DB[i].record.flight_id) && !strcmp(flightArrTime, updated_flight_DB[i].record.flight_arr_time))
 			found = 1;
 		else 
 			i++;
 	}
 	if (found)
 	{
 		strcpy(updated_flight_DB[i].flight_status, flightStatus);
 		if (!strcmp(updated_flight_DB[i].flight_status, "DELAY"))
 		{
 			int dept_time, arr_time;
 			updated_flight_DB[i].flight_delay_time = delayTime;
 			dept_time = atoi(flight_DB[i].flight_dept_time);
 			arr_time = atoi(flight_DB[i].flight_arr_time);
 			dept_time = dept_time + delayTime;	// Updated Departure and Arrival Time
 			arr_time = arr_time + delayTime;
 			sprintf(flight_DB[i].flight_dept_time, "%d", dept_time);	// Converting int to string
 			sprintf(flight_DB[i].flight_arr_time, "%d", arr_time);
 		}
 		else if (!strcmp(updated_flight_DB[i].flight_status, "PROMOTED"))
 		{
 			int original_flight_class, updated_flight_class;
 			original_flight_class = flight_DB[i].flight_class;
 			if(original_flight_class != 3)	// If it is 1(PUBLIC) or 2(VIP)
 				updated_flight_class = original_flight_class + 1;	// PUBLIC TO VIP, VIP TO VVIP
 			else							// If it is 3(VVIP)		
 				updated_flight_class = original_flight_class;
 			flight_DB[i].flight_class = updated_flight_class;
 			if(original_flight_class != updated_flight_class)	// Only when class = 1 or 2
 			{
 				switch (original_flight_class)
 				{
 					case 1: 
 					{
 						delete(list1, size, flightId, flightArrTime);
 						insert(list2, size, flight_DB[i].flight_name , flightId, flight_DB[i].flight_capacity, flightArrTime, flight_DB[i].flight_dept_time, updated_flight_class);
 					 	break;
 					}
 					case 2: 
 					{
 						delete(list2, size, flightId, flightArrTime);
  						insert(list3, size, flight_DB[i].flight_name , flightId, flight_DB[i].flight_capacity, flightArrTime, flight_DB[i].flight_dept_time, updated_flight_class);
 					 	break;
 					}
 					
 				}
 			}
 		}	
 	}
 	else
 		status_code = 0;

 	insertion_sort(flight_DB, size);	// Sorting updated flight_DB[]
 	insertion_sort(list1, size);
 	insertion_sort(list2, size);
 	insertion_sort(list3, size);
 	i = 0;
 	while (i < DB_SIZE)					// Copying flight_DB[] to updated_flight_DB[]
 	{
 		updated_flight_DB[i].record = flight_DB[i];
 		i++;
 	}
 	return status_code;
 }

 int listUnique(struct updated_flight_record updated_flight_DB[], int size)	// Updated_flight_DB[] has duplicate entries
 {
 	int i, j, min_delayTime, status_code = 0;
 	for (i = 0; (i < size) && (updated_flight_DB[i].record.flight_id[0] != '\0'); ++i)
 	{
 		min_delayTime = updated_flight_DB[i].flight_delay_time;
 		for (j = i+1; (j < size) && (updated_flight_DB[j].record.flight_id[0] != '\0'); ++j)
 		{
 			if (!strcmp(updated_flight_DB[i].record.flight_name, updated_flight_DB[j].record.flight_name) && !strcmp(updated_flight_DB[i].record.flight_id, updated_flight_DB[j].record.flight_id))
 			{
 				if (min_delayTime <= updated_flight_DB[j].flight_delay_time)	// deletes duplicate records with higher delayTime
 				{
 					delete_updated_DB(updated_flight_DB, size, updated_flight_DB[j].record.flight_id, updated_flight_DB[j].record.flight_name, updated_flight_DB[j].flight_delay_time);
 					j--;
 					status_code = 1;
 				}
 				else
 				{
 					updated_flight_DB[i] = updated_flight_DB[j];
 					delete_updated_DB(updated_flight_DB, size, updated_flight_DB[j].record.flight_id, updated_flight_DB[j].record.flight_name, updated_flight_DB[j].flight_delay_time);
 					j--;
 					status_code = 1;
 				}
 			}
 		}
 	}
 	return status_code;
 }

 void insertion_sort(struct flight_record flight_DB[], int size)
 {
 	int i, j, count, loc;
 	struct flight_record min_record, new_record;
 	i = 0;
 	while (flight_DB[i].flight_id[0] != '\0')	// to find the number of filled records
 		i++;
 	count = i;
 	min_record = flight_DB[0];
 	loc = 0;
 	for(i = 1; i < count; i++)
 	{
 		if(strcmp(flight_DB[i].flight_id, min_record.flight_id) < 0)
 		{
 			min_record = flight_DB[i];
 			loc = i;
 		}
 		else if(!strcmp(flight_DB[i].flight_id, min_record.flight_id))
 		{
 			if(strcmp(flight_DB[i].flight_arr_time, min_record.flight_arr_time) < 0)
 			{
 				min_record = flight_DB[i];
 				loc = i;
 			}
 		}
 	}
 	flight_DB[loc] = flight_DB[0]; 
 	flight_DB[0] = min_record;
 	for(i = 2; i < count; i++)
 	{
		new_record = flight_DB[i];
 		j = i;

 		//inserts new_record in the right place according to flight_id
 		while (strcmp(new_record.flight_id, flight_DB[j-1].flight_id) < 0) //flight_DB[j-1].flight_id[0] can never be '\0'
 		{
 			flight_DB[j] = flight_DB[j-1];
 			j--;
 		}
 		flight_DB[j] = new_record;

 		//inserts new_record in the right place according to flight_arr_time
 		while ((!strcmp(new_record.flight_id, flight_DB[j-1].flight_id)) && (strcmp(new_record.flight_arr_time, flight_DB[j-1].flight_arr_time) < 0))
 		{
 			flight_DB[j] = flight_DB[j-1];
 			j--;
 		}
 		flight_DB[j] = new_record;
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
