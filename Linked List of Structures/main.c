//Flight Managment System
//Author: Kaushal Lodd
//Roll Number: BT19CSE052

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "header.h"

int main() {
	flightNode* head = NULL;
    flightNode *list1 = NULL, *list2 = NULL, *list3 = NULL;	 // 3 Sorted list provided, one for each flight class.
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
                        char flightStatus[STATUS_LEN], delayTime[TIME_LEN] = {'\0'};
 						unsigned int flightCapacity;
 						flightClassDT flightClass;
                        statusCode status_code;
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
                        printf("Enter Flight Status of the Flight (DELAY, ON_TIME, CANCELLED, PROMOTED): ");
 						scanf("%s", flightStatus);
 						if (!strcmp(flightStatus, "DELAY"))
 						{
 							printf("Enter delay time (in hhmm format): ");
 							scanf("%s", delayTime);
 						}
 						printf("Enter Flight Class (1 for Public, 2 for VIP, 3 for VVIP): ");
 						scanf("%d", &flightClass);
 						status_code = insert_update(&head, &list1, &list2, &list3, flightName, flightId, flightCapacity, flightArrTime, flightDeptTime, flightStatus, delayTime, flightClass);
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
 						statusCode status_code;
 						puts("--------------------------------------------------------------------------------");
 						puts("                          ENTER THE FOLLOWING INFORMATION");
 						puts("--------------------------------------------------------------------------------");
 						printf("Enter the flight ID: ");
 						scanf("%s", flightId);
 						printf("Enter Flight Arrival Time (In Military Time System): ");
 						scanf("%s", flightArrTime);
 						status_code = Delete(&head, flightId, flightArrTime);
						Delete(&list1, flightId, flightArrTime);
						Delete(&list2, flightId, flightArrTime);
						Delete(&list3, flightId, flightArrTime);
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
 						unsigned int num_of_flights;
 						num_of_flights = getNumFlights(&head);
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
 						puts("--------------------------------------------------------------------------------");
						 if(isEmpty(&head)) {
 							printf("Database is EMPTY.\n");
						}
 						else if (isFull(&head)) {
 							printf("Database is FULL.\n");
						}
 						else {
 							printf("Database is neither EMPTY nor FULL.\n");
						}
						puts("--------------------------------------------------------------------------------");
						printf("Enter any key to go back.");
						getch();
						getch();
 						break;
 			}
 			case 5: {
 						system("clear");
 						flightNode* temp_DB = NULL;
 						int dept_time, arr_time, stay_time;
 						getFlightWithtLongeststay(&head, &temp_DB);
 						puts("--------------------------------------------------------------------------------");
 						puts("                    THESE ARE THE FLIGHTS WITH MAX STAY TIME");
 						puts("--------------------------------------------------------------------------------");
 						printf("Flight Name\tFlight ID\tFlight Arrival Time\tStay Time\n");
 						puts("--------------------------------------------------------------------------------");
 						dept_time = atoi(temp_DB->record.flight_dept_time);
 						arr_time = atoi(temp_DB->record.flight_arr_time);
 						stay_time = abs(dept_time - arr_time);
 						for (flightNode* tnptr = temp_DB; tnptr != NULL; tnptr = tnptr->next)
 						{
 							printf("%s\t\t%s\t\t%s\t\t\t%d\n", tnptr->record.flight_name, tnptr->record.flight_id, tnptr->record.flight_arr_time, stay_time);
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
 										getSortedOnArrivalTime(&head);
										flightNode* nptr = head;
										puts("--------------------------------------------------------------------------------");
										puts("                           SORTED ON ARRIVAL TIME");
										puts("--------------------------------------------------------------------------------");
										printf("Flight Name\tFlight ID\tFlight Arrival Time\tFlight Departure Time\n");
										puts("--------------------------------------------------------------------------------");
										for (nptr = head; nptr != NULL; nptr = nptr->next)
										{
											printf("%s\t\t%s\t\t%s\t\t\t%s\n", nptr->record.flight_name, nptr->record.flight_id, nptr->record.flight_arr_time, nptr->record.flight_dept_time);
										}
										puts("--------------------------------------------------------------------------------");
										printf("Enter any key to go back.");
										getch();
										getch();
 										break;
 							}
 							case 2: {
 										system("clear");
 										getSortedOnDepartureTime(&head);
										flightNode* nptr;
										puts("--------------------------------------------------------------------------------");
										puts("                           SORTED ON DEPARTURE TIME");
										puts("--------------------------------------------------------------------------------");
										printf("Flight Name\tFlight ID\tFlight Arrival Time\tFlight Departure Time\n");
										puts("--------------------------------------------------------------------------------");
										for (nptr = head; nptr != NULL; nptr = nptr->next)
										{
											printf("%s\t\t%s\t\t%s\t\t\t%s\n", nptr->record.flight_name, nptr->record.flight_id, nptr->record.flight_arr_time, nptr->record.flight_dept_time);
										}
										puts("--------------------------------------------------------------------------------");
										printf("Enter any key to go back.");
										getch();
										getch();
 										break;
 							}
 							case 3: {
 										system("clear");
 										getSortedOnStayTime(&head);
										flightNode* nptr;
										puts("--------------------------------------------------------------------------------");
										puts("                           SORTED ON STAY TIME");
										puts("--------------------------------------------------------------------------------");
										printf("Flight Name\tFlight ID\tFlight Arrival Time\tFlight Departure Time\tStay Time\n");
										puts("--------------------------------------------------------------------------------");
										for (nptr = head; nptr != NULL; nptr = nptr->next)
										{
											int stay_time = abs(atoi(nptr->record.flight_dept_time) - atoi(nptr->record.flight_arr_time));
											printf("%s\t\t%s\t\t%s\t\t\t%s\t\t\t%d\n", nptr->record.flight_name, nptr->record.flight_id, nptr->record.flight_arr_time, nptr->record.flight_dept_time, stay_time);
										}
										puts("--------------------------------------------------------------------------------");
										printf("Enter any key to go back.");
										getch();
										getch();
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
 						statusCode status_code;
 						char flightId[FLIGHT_ID_LEN], flightArrTime[TIME_LEN];
						char flightStatus[STATUS_LEN], delayTime[TIME_LEN] = {'\0'};
 						puts("--------------------------------------------------------------------------------");
 						puts("                          ENTER THE FOLLOWING INFORMATION");
 						puts("--------------------------------------------------------------------------------");
 						printf("Enter the Flight ID: ");
 						scanf("%s", flightId);
 						printf("Enter Flight Arrival Time (In Military Time System): ");
 						scanf("%s", flightArrTime);
 						printf("Enter Flight Status of the Flight: ");
 						scanf("%s", flightStatus);
 						if (!strcmp(flightStatus, "DELAY"))
 						{
 							printf("Enter delay time (in hhmm format): ");
 							scanf("%s", delayTime);
 						}
 						status_code = UpdateFlightStatus(&head, &list1, &list2, &list3, flightId, flightArrTime, flightStatus, delayTime);
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
 						statusCode status_code;
 						status_code = listUnique(&head);
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