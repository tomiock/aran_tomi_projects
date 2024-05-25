/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 2

laHt ge.h
Header of adjacency matrix - data structures required by the project 2.
This is the large case, however it's an empty case

We've already declared, but not initialized, both data structures:
- adjacency matrix 
- cities info
*/

#ifndef MEDIUM_H
#define MEDIUM_H

#define NUMBER_CITIES 20 
#define MAX_NAME 10
#define MAX_CITY_NAME 20

int adjacency_matrix[NUMBER_CITIES][NUMBER_CITIES] = 
{
    {0, 100, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75, 0},
    {100, 0, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90, 165, 0, 0, 0},
    {50, 0, 0, 130, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0},
    {0, 120, 130, 0, 0, 0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0},
    {0, 0, 110, 0, 0, 70, 80, 0, 0, 0, 0, 0, 0, 0, 120, 0, 0, 0, 0},
    {0, 0, 0, 0, 70, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0},
    {0, 0, 0, 0, 80, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0},
    {0, 0, 0, 0, 0, 40, 50, 0, 30, 100, 0, 0, 0, 0, 0, 0, 0, 0 , 0},
    {0, 0, 0, 80, 0, 0, 0, 30, 0, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 100, 90, 0, 100, 0, 0, 0, 0, 95, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 135, 135, 95, 0, 0, 0, 0, 0, 0 , 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 125, 95, 120, 130, 130, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 85, 95, 70, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 125, 105, 115, 0 , 0},
    {0, 0, 0, 0, 115, 0, 0, 0, 0, 0, 0, 0, 0, 130, 55, 120, 0, 0, 0},
    {0, 0, 0, 0, 0, 130, 0, 0, 0, 0, 0, 0, 0, 0, 105, 65, 150, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 0, 0, 205, 55, 135, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 85, 130, 10, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 130, 40, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 140, 0}
};

struct CivilRegistry
{
    int city_id;
    char city_name[MAX_CITY_NAME];
    char mother_name[MAX_NAME];
    char father_name[MAX_NAME];
    int mother_parents_city_id;
    int father_parents_city_id;
};

struct CivilRegistry citiesInfo[NUMBER_CITIES] =
{
    {0, "Barcelona", "Maria", "Jordi", 3, 5},
    {1, "Lisbon", "Madalena", "Lourenço", 15, 16},
    {2, "Madrid", "Cristina", "Ignasi", -1, -1},
    {3, "Paris", "Louise", "Paul", 9, 4},
    {4, "Rome", "Agnese", "Leonardo", 13, 14},
    {5, "Zurich", "Eva", "Albert", 1, 6},
    {6, "Amsterdam", "Amber", "Finn", 17, 18},
    {7, "Viena", "Marta", "Jose", -1, -1},
    {8, "Berlin", "Miska", "Muska", -1, -1},
    {9, "Varsovia", "Anna", "Kazimierz", 11, 12},
    {10, "Tokyo", "Hana", "Kenji", -1, -1},
    {11, "Sydney", "Olivia", "Liam", -1, -1},
    {12, "New York", "Jake", "Rosa", -1, -1},
    {13, "London", "Sophie", "Jack", -1, -1},
    {14, "Toronto", "Isabella", "Lucas", -1, -1},
    {15, "Dublin", "Aoife", "Cillian", -1, -1},
    {16, "Copenhagen", "Freja", "Emil", -1, -1},
    {17, "Helsinki", "Forense", "Cadaver", -1, -1},
    {18, "Oslo", "Elsa", "Gustav", -1, -1},
    {19, "Stockholm", "Astrid", "Bjorn", -1, -1}
};

struct FamilyTreeNode
{
    char motherName[MAX_NAME];
    char fatherName[MAX_NAME];
    int city_id;
    struct FamilyTreeNode * mother_parents;
    struct FamilyTreeNode * father_parents;
};

struct RoadMap
{
    int city_id;
    int total_cost;
    struct RoadMap * next;
};

#endif // MEDIUM_H
