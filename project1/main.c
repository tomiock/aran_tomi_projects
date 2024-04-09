/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 1

Simulator - main program

Authors:
	Name: Ockier Poblet, Tomas      NIU: 1707185
	Name: Oliveras Sanchez, Aran    NIU: 1708069
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

#include "project1.h" // header with all data structures

#define NUMBER_OF_STACK 3
#define MAX_CAPACITY 3

//----------------------------------------------------------General
// WARNING: do not change this function
enum EventType GenerateEventType()
{
	return rand()%3;
}

void CheckArguments (int argc, char *argv[])
{
	// check the input introduced by the user
	/* there needs to be only one argument that is an int*/

	if (argc != 2)
	{
		printf("\033[0;31m" "One arguments needed, no more no less. Execution finished.\n");
		exit(1);
	}

	if (atol(argv[1]) > INT_MAX)
	{
		printf("\033[0;31m" "Too large of a number, does not fit in type `int`. Execution finished.\n");
		exit(1);
	}

	if ((atoi(argv[1]) < 1) || !isdigit(*argv[1]))
	{
		printf("\033[0;31m" "The argument must be a positive integer. Execution finished.\n");
		exit(1);
	}
}

//----------------------------------------------------------RobotPackages -> Sorted list
// WARNING: do not change this function
struct RobotPackage * GenerateRobotPackage()
// only defines a single package, another function is used to generate a list of packages
{
	// reserve memory for a RobotPackage
	struct RobotPackage * RobotPackage=malloc(sizeof(struct RobotPackage));
	int RobotPackageNum=rand()%8;
	// initialize the RobotPackage's fields
	strcpy (RobotPackage->supplier, suppliers[RobotPackageNum]);
	strcpy (RobotPackage->id, ids[RobotPackageNum]);
	int year=rand()%40+1980;
	RobotPackage->year=year;
	return RobotPackage;
}


// function to print a list of RobotPackages
void PrintRobotPackages()
{
	if (RobotPackagesHead==NULL)
	{
		printf("The list of RobotPackages is empty\n");
		return;
	}	
	struct RobotPackage *current = RobotPackagesHead;

	while (current != NULL)
	{
		printf("\nSupplier: %s\nID: %s\nYear: %d\n", current->supplier, current->id, current->year);
		current = current->next;
	}
	printf("\n");
}

// function to search for a RobotPackage
struct RobotPackage * SearchRobotPackage(struct RobotPackage *RobotPackage)
// used to order the packages, we need to search by provider
{

	struct RobotPackage *current = RobotPackagesHead;
	while(1)
	{
		if (strcmp(current->supplier, RobotPackage->supplier) == 0)
		{
			return current;
		}
		if (current->next==NULL)
		{
			return current;
		}
		current=current->next;
	}
}

// function to simulate an insertion of RobotPackages in a ordered way (sorted by supplier)
void SimulateManagingRobotPackages(struct RobotPackage * RobotPackage)
{
	if (RobotPackagesHead==NULL)
	{
		RobotPackagesHead = RobotPackage;
		RobotPackage->next = NULL;
	}
	else
	{
		RobotPackage->next = SearchRobotPackage(RobotPackage)->next;
		SearchRobotPackage(RobotPackage)->next=RobotPackage;
	}
}

// function to remove all the RobotPackages from the list at the end of the program
void RemoveAllRobotPackages()
{
	int number = 0;
	struct RobotPackage *current;
	struct RobotPackage *next;
	current = RobotPackagesHead;
	RobotPackagesHead = NULL;
	while(current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
		number++;
	}
	printf("\t\t%d packages has been removed.\n", number);
}

//----------------------------------------------------------Packages -> different Stacks
// WARNING: do not change this function
struct Package * GeneratePackage()
{
	// reserve memory for a Package
	struct Package * Package=malloc(sizeof(struct Package));
	// initialize the Package's fields
	enum PackageType type=rand()%3;
	enum Colors color=rand()%4;
	Package->type = type;
	Package->color = color;
	return Package;
}

// function to initialize all stacks of Packages 
void InitStacks()
{
	// stacks are initialized empty, therefore must point to NULL
	Top_ofPackageStacks[0] = NULL;
	Top_ofPackageStacks[1] = NULL;
	Top_ofPackageStacks[2] = NULL;

	// initialize the number of packages in each stack
	CurrentState[0] = 0;
	CurrentState[1] = 0;
	CurrentState[2] = 0;
}

// function to print all stacks with all Packages
void PrintPackages()
{
	for (int i=0; i<3; i++) // loop through the 3 stacks
	{
		printf("Stack %d\n", i);
		struct Package *current = Top_ofPackageStacks[i];
		while(current != NULL) // loop through the whole stack
		{
			printf("Type: %d\nColor: %d\n", current->type, current->color);
			current = current->next;
		}
	}
}

// function to remove all packages from a given stack when its MAX_CAPACITY is reached
void RemoveStack(struct Package *head, int idx)
{
	struct Package * next;

	if (head == NULL)
	{
		printf("The stack is empty or pointer is wrongly provided (NULL pointer)\n");
		return;
	}

	while(head != NULL)
	{
		// free the packages one by one
		next = head->next;
		free(head);
		head = next;
	}
	
	Top_ofPackageStacks[idx] = NULL;
}

// function to simulate putting a generated Package to a corresponding stack depending on the type (size)
void SimulateClassifyPackage(struct Package * Package)
{
	switch (Package->type) {
		case small:
			Package->next = Top_ofPackageStacks[0];
			Top_ofPackageStacks[0] = Package;
			CurrentState[0]++;
		break;

		case medium:
			Package->next = Top_ofPackageStacks[1];
			Top_ofPackageStacks[1] = Package;
			CurrentState[1]++;
		break;

		case large:
			Package->next = Top_ofPackageStacks[2];
			Top_ofPackageStacks[2] = Package;
			CurrentState[2]++;
		break;

		default:
			printf("Type of Package not expected %d. Exeting execution.\n", Package->type);
		return;
	}
}

// function to clean all stacks before the end of the program
void CleanPackageStacks()
{
	int number=0;
	for (int idx=0; idx<3; idx++)
	{
		struct Package* top_stack = Top_ofPackageStacks[idx];
		struct Package* next = (struct Package *)malloc(sizeof(struct Package));
		next->next = NULL; // DO NOT FORGET AGAIN!!!

		while (next->next != NULL)
		{
			next = top_stack->next;		
			free(top_stack);
			number++;
		}
		free(next);
	}
	printf("\t\t%d packages has been removed\n", number);			
}

//----------------------------------------------------------Shopping -> Queue
// WARNING: do not change this function
struct Shopping *GenerateShopping() {
    // reserve memory for a Shopping
    struct Shopping *shopping = malloc(sizeof(struct Shopping));
    // initialize the shopping's fields
    int n = rand() % 5 + 1;
    shopping->numberThingsToBuy = n;
    shopping->robot_id = ++nextRobotID;
    shopping->next = NULL; 
    return shopping;
}

// function to print a list of robots in a shopping queue
void PrintShopping()
{
	if (queueFirst==NULL)
	{
		printf("The list of Shopping Queue is empty\n");
		return;
	}	
	struct Shopping *current = queueFirst;
	while(current!=NULL)
	{
		printf("Robot ID: %d\nNumber of things to buy: %d\n", current->robot_id, current->numberThingsToBuy);
		current = current->next;
	}
}

// function to add a robot to a shopping queue
void AddToQueue(struct Shopping * shopping)
{
	if (queueLast==NULL)
	{
		queueFirst = shopping;
		queueLast = shopping;
	}
	else
	{
		queueLast->next = shopping;
		queueLast = shopping;
	}
}

// function to remove a robot from the queue and serve it
// it may return the number of things to buy to simulate the time
int Dequeue()
{
	if (queueFirst == NULL) {
        printf("Queue empty\n");
        return 0;
    }
	int number_things = queueFirst->numberThingsToBuy;
	struct Shopping *temp_shopping = queueFirst;
	queueFirst = queueFirst->next;
	if(queueFirst == NULL)
	{
		queueLast = NULL;
	}
	free(temp_shopping);
	return number_things;
}

// function to simulate the time the robot is in the queue
void UpdateShoppingQueue(int * numberThingsToBuy_Current_Served)
{
	if(*numberThingsToBuy_Current_Served == 0)
	{
		*numberThingsToBuy_Current_Served = Dequeue();
		if(*numberThingsToBuy_Current_Served == 0)
			return;
		*numberThingsToBuy_Current_Served = *numberThingsToBuy_Current_Served - 1;
		return;
	}
	printf("\nnumberThingsToBuy_Current_Served: %d\n", *numberThingsToBuy_Current_Served);
	*numberThingsToBuy_Current_Served = *numberThingsToBuy_Current_Served - 1;
}

// function to simulate a robot going for shopping - add to the queue
void SimulateGoForShopping(struct Shopping * shopping)
{
	AddToQueue(shopping); // free the memory of the shopping, needed always - T
	// always at the end of the funcion
}

// function to clean shopping queue before the end of the program
void CleanShoppingQueue() // on the template file this function has parameters into it - T
{
	int number = 0;
	if (queueFirst==NULL)
	{
		return;
	}	
	struct Shopping *current;
	struct Shopping *next_robot; // here next is used as a temporal pointer in order to reassing current

	next_robot = NULL;

	current = queueFirst;

	while(current->next != NULL)
	{
		next_robot = current->next;
		current = next_robot;
		number++;
	}
	free(current);
	printf("\t\t%d robots has been removed\n", number);	
}

//----------------------------------------------------------main
// This is the main loop of the program. 
// It generates and consumes events.
void SimulationLoop(int EventNumbers)
{
	// declare and initialize necessary variables
	bool BREAK_FLAG = false;

	InitStacks();

	//Create the shopping robot being served
	int *numberThingsToBuy_Current_Served = malloc(sizeof(int)); // Allocate memory for the integer
	if (numberThingsToBuy_Current_Served != NULL) {
		*numberThingsToBuy_Current_Served = 0; // Assign a value to the allocated memory
	}
	
	for (int i=0; i<EventNumbers; i++)    
	{
		// printf("Event number %d\n", i); // debugging/testing purposes
		enum EventType event = GenerateEventType();
		printf("EventType %d\n", event); // debugging/testing purposes

		switch (event)
		{
			case robotPackage:
				printf("Running part 1\n");
				SimulateManagingRobotPackages(GenerateRobotPackage());
			break;

			case package:
				printf("Running part 2\n");
				SimulateClassifyPackage(GeneratePackage());

				// loop over all stacks to see if they are at MAX_CAPACITY
				for (int idx_stack=0; idx_stack<3; idx_stack++)
				{
					if (CurrentState[idx_stack] == MAX_CAPACITY)
					{
						printf("\tStack %d is full. Removing all packages.\n", idx_stack);
						RemoveStack(Top_ofPackageStacks[idx_stack], idx_stack);
						CurrentState[idx_stack] = 0;
					}
				}
			break;

			case shopping:
				printf("Running part 3\n");
				SimulateGoForShopping(GenerateShopping());
			break;

			default:
				printf("Error: event type not recognized. Exiting the main loop.\n");
				BREAK_FLAG = true;
		}
		printf("\n____\n");
		UpdateShoppingQueue(numberThingsToBuy_Current_Served);

		if (BREAK_FLAG) break; // if an error occurred, exit for loop and clean the simulation
	}
	// CLEANING THE SIMULATION
	printf("STATISTICS WHEN CLEANING THE SIMULATION:\n");
	printf("\tRemoving packages...\n");
	RemoveAllRobotPackages();
	printf("\tCleaning all stacks of packages...\n");
	CleanPackageStacks();
	printf("\tCleaning shopping queue...\n");
	CleanShoppingQueue();
	
}

int main (int argc, char ** argv)
{	int EventNumbers;
	printf("Starting... \n");
	CheckArguments(argc, argv);

	EventNumbers = atoi(argv[1]);

	SimulationLoop(EventNumbers);
	return 0;
}
