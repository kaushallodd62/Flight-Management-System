#ifndef _HEADER_H
#define _HEADER_H

#define FLIGHT_NAME_LEN 50
#define FLIGHT_ID_LEN 10
#define TIME_LEN 5 // Military Time System, eg 1400 = 2:00pm, 0600 = 6:00am
#define STATUS_LEN 20

typedef enum Bool_tag{FALSE, TRUE}Bool;
typedef enum status_tag{FAILURE, SUCCESS}statusCode;
typedef enum flightClassTag{PUBLIC = 1, VIP, VVIP} flightClassDT;

typedef struct flight_record_tag {
	char flight_name[FLIGHT_NAME_LEN];
	char flight_id[FLIGHT_ID_LEN];
	unsigned int flight_capacity;
	char flight_arr_time[TIME_LEN];
	char flight_dept_time[TIME_LEN];
    char flight_status[STATUS_LEN];
	char flight_delay_time[TIME_LEN];
	flightClassDT flight_class; // 1 = PUBLIC, 2 = VIP, 3 = VVIP
}flight_record;

typedef struct node_tag {
    flight_record record;
    struct node_tag* next;
}flightNode;

statusCode insertAtEnd(flightNode** head_ptr, char flightName[], char flightId[], int flightCapacity, char flightArrTime[], char flightDeptTime[], char flightStatus[], char delayTime[], flightClassDT flightClass);
statusCode insert_update(flightNode** head_ptr, flightNode** list1_ptr, flightNode** list2_ptr, flightNode** list3_ptr, char flightName[], char flightId[], int flightCapacity, char flightArrTime[], char flightDeptTime[], char flightStatus[], char delayTime[], flightClassDT flightClass);
statusCode Delete(flightNode** head_ptr, char flightId[], char flightArrTime[]);
unsigned int getNumFlights(flightNode** head_ptr);
Bool isEmpty(flightNode** head_ptr);
Bool isFull(flightNode** head_ptr);
void getFlightWithtLongeststay(flightNode** head_ptr, flightNode** temp_DB);
void getSortedOnArrivalTime(flightNode** head_ptr);
flightNode* mergeArrivalTime(flightNode* firsthalf, flightNode* secondhalf);
void getSortedOnDepartureTime(flightNode** head_ptr);
flightNode* mergeDepartureTime(flightNode* firsthalf, flightNode* secondhalf);
void getSortedOnStayTime(flightNode** head_ptr);
flightNode* mergeStayTime(flightNode* firsthalf, flightNode* secondhalf);
void divide(flightNode* head, flightNode**fronthalf, flightNode** backhalf);
statusCode UpdateFlightStatus(flightNode** head_ptr, flightNode** list1_ptr, flightNode** list2_ptr, flightNode** list3_ptr, char flightId[], char flightArrTime[], char flightStatus[], char delayTime[]);
statusCode listUnique(flightNode** head_ptr);
void insertion_sort(flightNode** head_ptr);
void sortedInsert(flightNode** head_ptr, flightNode* new_node);
int getch(void);

#endif