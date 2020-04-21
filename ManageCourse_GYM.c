/*
	Jimmy is a body building instructor and needs a program to manage the courses provided by his gym, the Gold's Gym. Specifically, the program must make the following features available
	1. Inserting a new course. A course is characterized by a code (alphanumeric), a name, an instructor and a maximum number of participants (between a minimum of 10 and a maximum of 50).
	2. Membership of a new customer. A customer is characterized by a code, a name, a surname and an age and a sex. The code consists of two parts: a letter indicating the type of subscription, B (children aged between 6 and 12 years), M (men over the age of 12) and F (women over the age of 12), and a numerical progressive. The customer's code is automatically generated upon insertion and must be displayed on the screen immediately after the new customer's membership.
	3. View the courses delivered by the gym. It is necessary to view the code, the name of the course and the number of enrolled students.
	4. Display of members. It is necessary to view the code, surname and name of each cardholder.
	5. Registration of a card to a course. The functionality takes the customer's code and the course code as input, displays the information relating to the codes entered (i.e. customer's name and surname and course name) and asks for confirmation of registration.
 */

  /*
   * To change this license header, choose License Headers in Project Properties.
   * To change this template file, choose Tools | Templates
   * and open the template in the editor.
   */

 /*
	* File:   ManageCourse_HYM.c
	* Author: dtfabio96
	*
	* Created on 14 febbraio 2016, 17.53
	*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Costanti per la gestione delle stringhe
#define STRING_MAX_SIZE 50
#define CODE_SIZE 10

// Costanti per la gestione degli archivi
#define COURSES_SIZE 10
#define CUSTOMERS_SIZE 10

// Numero massimo di partecipanti ad un corso
#define MAX_PARTICIPANTS_ALLOWED 50

// Codifica tipi di abbonamento
#define CHILD 'B'
#define FEMALE 'F'
#define MALE 'M'

// Codifica dell'esito di una funzione
#define OK 0
#define FULL_ARCHIVE -1
#define ITEM_NOT_FOUND -2
#define NO_MORE_PARTICIPANTS_ALLOWED -3

// Codifica voci del menu
#define INSERT_COURSE 1
#define INSERT_CUSTOMER 2
#define SHOW_COURSES 3
#define SHOW_PARTICIPANTS 4
#define REGISTER_PARTICIPANT_TO_COURSE 5
#define EXIT 0

// Struttura per la codifica del codice di un cliente
typedef struct {
	char pass_type;
	int number;
} customer_code;

// Stuttura per la codifica di un cliente
typedef struct {
	customer_code code;
	char name[STRING_MAX_SIZE];
	char surname[STRING_MAX_SIZE];
	int age;
	char gender;
} customer;

// Stuttura per la codifica di un corso
typedef struct {
	char code[CODE_SIZE];
	char title[STRING_MAX_SIZE];
	char trainer[STRING_MAX_SIZE];
	int max_participants;
	int num_participants;
	customer_code participants[MAX_PARTICIPANTS_ALLOWED]; // Codice dei partecipanti iscritti al corso
} course;

// Struttura usata per codificare l'archivio dei medici
typedef struct {
	course course_list[COURSES_SIZE]; // Array contenente i corsi erogati
	int num_courses; // Dimensione logica dell'array
} courses;

typedef struct {
	customer customer_list[CUSTOMERS_SIZE]; // Array contenente i clienti della palestra
	int num_customers; // Dimensione logica dell'array
} customers;

// Funzioni per la gestione dei corsi
void init_course_archive(courses *);
course read_course();
int add_course(courses *, course);
int search_course(courses, char[]);
void print_courses();

// Funzioni per la gestione dei pazienti
void init_customer_archive(customers *);
customer read_customer();
int add_customer(customers *, customer *);
void assign_code(customers, customer *);
int search_customer(customers, customer_code);
int register_customer(courses*, customers, int, int);
void print_customers();

int main(int argc, char** argv) {
	int choice, result, index, course_index, participant_index;
	char answer;
	course new_course;
	customer new_customer;
	customer_code customer_to_search;
	char code_course_to_search[STRING_MAX_SIZE];
	courses courses_archive;
	customers customers_archive;

	init_course_archive(&courses_archive);
	init_customer_archive(&customers_archive);

	do {
		system("clear"); // MAC Users
		// system("cls"); // WIN Users
		printf("********** MENU' **********\n\n");
		printf("1. New course.\n");
		printf("2. New client.\n");
		printf("3. Courses provided.\n");
		printf("4. Registered customers.\n");
		printf("5. New registration.\n");
		printf("0. Exit.\n\n");
		printf("**************************\n\n");
		printf("Choice: ");
		scanf("%d", &choice);

		switch (choice) {
       		case EXIT:
			system("clear"); // MAC Users
			// system("cls"); // WIN Users
			break;
		    case INSERT_COURSE:
			system("clear"); // MAC Users
			// system("cls"); // WIN Users
			new_course = read_course();
			result = add_course(&courses_archive, new_course);

			switch (result) {
			case OK:
				printf("Course entered correctly.\n");
				break;
			case FULL_ARCHIVE:
				printf("Course archive full.\n");
				break;
			}
			system("read -n 1 -s -p \"Press a key to continue...\""); // MAC Users
			// system("PAUSE"); // WIN Users
			break;
		case INSERT_CUSTOMER:
			system("clear"); // MAC Users
			// system("cls"); // WIN Users
			new_customer = read_customer();
			result = add_customer(&customers_archive, &new_customer);

			switch (result) {
			case OK:
				printf("Customer entered correctly with code: %c%d. \n",
						new_customer.code.pass_type, new_customer.code.number);
				break;
			case FULL_ARCHIVE:
				printf("Full customer archive.");
				break;
			}

			system("read -n 1 -s -p \"Press a key to continue...\""); // MAC Users
			// system("PAUSE"); // WIN Users
			break;
		case SHOW_COURSES:
			system("clear"); // MAC Users
			// system("cls"); // WIN Users

			print_courses(courses_archive);

			system("read -n 1 -s -p \"Press a key to continue...\""); // MAC Users
			// system("PAUSE"); // WIN Users
			break;
		case SHOW_PARTICIPANTS:
			system("clear"); // MAC Users
			// system("cls"); // WIN Users

			print_customers(customers_archive);

			system("read -n 1 -s -p \"Press a key to continue...\""); // MAC Users
			// system("PAUSE"); // WIN Users
			break;
		case REGISTER_PARTICIPANT_TO_COURSE:
			system("clear"); // MAC Users
			// system("cls"); // WIN Users

			do {
				printf("Course code: ");
				scanf("%s", code_course_to_search);
				course_index = search_course(courses_archive,
						code_course_to_search);
				if (course_index == ITEM_NOT_FOUND)
					printf("Course code not present in the archive.");
			} while (course_index == ITEM_NOT_FOUND);

			do {
				printf("Type of customer subscription: ");
				scanf("\n%c", &customer_to_search.pass_type);
				printf("Progressive customer subscription: ");
				scanf("%d", &customer_to_search.number);
				participant_index = search_customer(customers_archive,
						customer_to_search);
				if (participant_index == ITEM_NOT_FOUND)
					printf("Customer code not present in the archive.");
			} while (participant_index == ITEM_NOT_FOUND);

			printf("Do you want to register %s %s to course %s (s to confirm, n to cancel)?\n",
					customers_archive.customer_list[participant_index].name,
					customers_archive.customer_list[participant_index].surname,
					courses_archive.course_list[course_index].title);
			scanf("\n%c", &answer);

			if (answer == 's') {
				result = register_customer(&courses_archive, customers_archive,
						course_index, participant_index);
				switch (result) {
				case OK:
					printf("Customer successfully enrolled in the course.\n");
					break;
				case NO_MORE_PARTICIPANTS_ALLOWED:
					printf("It is not possible register other customers in the course.\n");
					break;
				}
			} else
				printf("Operation canceled.\n");

			system("read -n 1 -s -p \"Press a key to continue...\""); // MAC Users
			// system("PAUSE"); // WIN Users
			break;
                default:
                        system("clear");
                        printf("Wrong choice.\n");
                        system("read -n 1 -s -p \"Press a key to continue...\""); // MAC Users
                        break;
		}

	} while (choice != 0);

	return (EXIT_SUCCESS);
}

void init_course_archive(courses *_courses) {
	_courses->num_courses = 0;
}

course read_course() {
	course _new_course;

	printf("Code: ");
	scanf("%s", _new_course.code);
	printf("Name of the course: ");
	scanf("%s", _new_course.title);
	printf("Instructor: ");
	scanf("%s", _new_course.trainer);
	do {
		printf("Maximum number of participants: ");
		scanf("%d", &_new_course.max_participants);
		if ((_new_course.max_participants < 10) || (_new_course.max_participants > MAX_PARTICIPANTS_ALLOWED))
			printf("The maximum number of participants must be between 10 and 50.\n");
	} while ((_new_course.max_participants < 10) || (_new_course.max_participants > MAX_PARTICIPANTS_ALLOWED));
	_new_course.num_participants = 0;

	return _new_course;
}


int add_course(courses *_courses, course _new_course) {
	int index;

	index = _courses->num_courses;
	if (index == COURSES_SIZE)
		return FULL_ARCHIVE;

    else {
		strcpy(_courses->course_list[index].title, _new_course.title);
		strcpy(_courses->course_list[index].code, _new_course.code);
		strcpy(_courses->course_list[index].trainer, _new_course.trainer);
		(*_courses).course_list[index].max_participants =
				_new_course.max_participants;
		_courses->course_list[index].num_participants =
				_new_course.num_participants;
		_courses->num_courses++;
		return OK;
	}

}

int search_course(courses _courses, char _course_code_to_search[]) {
	int index, result;

	index = 0;
	while ((index < _courses.num_courses) && (strcmp(_course_code_to_search, _courses.course_list[index].code)!= 0)) {
		index++;
	}

	if (index >= _courses.num_courses)
		return ITEM_NOT_FOUND;
	else
		return index;
}

void print_courses(courses _courses) {
	int i;
	for (i = 0; i < _courses.num_courses; i++) {
		printf("Code: %s\nName: %s\nNumbers of members: %d\n",
				_courses.course_list[i].code, _courses.course_list[i].title,
				_courses.course_list[i].num_participants);
	}
}

void init_customer_archive(customers *_customers) {
	_customers->num_customers = 0;
}

customer read_customer() {
	customer _new_customer;

	printf("Name: ");
	scanf("%s", _new_customer.name);
	printf("Surname: ");
	scanf("%s", _new_customer.surname);
	printf("Age: ");
	scanf("%d", &_new_customer.age);
	printf("Sex (m/f): ");
	scanf("\n%c", &_new_customer.gender);

	return _new_customer;
}

int add_customer(customers *_customers, customer *_new_customer) {
	int index;
	index = _customers->num_customers;

	if (index == CUSTOMERS_SIZE)
		return FULL_ARCHIVE;
	else {
		assign_code(*_customers, _new_customer);
		strcpy(_customers->customer_list[index].name,
				_new_customer->name);
		strcpy(_customers->customer_list[index].surname,
				_new_customer->surname);
		_customers->customer_list[index].age = _new_customer->age;
		_customers->customer_list[index].gender = _new_customer->gender;
		_customers->customer_list[index].code.pass_type = _new_customer->code.pass_type;
		_customers->customer_list[index].code.number = _new_customer->code.number;
		_customers->num_customers++;
		return OK;
	}
}

int search_customer(customers _customers, customer_code _code_customer_to_search) {
	int index;
	int number;
	char pass_type;

	index = 0;
	number = _code_customer_to_search.number;
	pass_type = _code_customer_to_search.pass_type;

	while ((index < _customers.num_customers) && (number != _customers.customer_list[index].code.number)) {
		index++;
	}

        if(index<_customers.num_customers){
            while ((index < _customers.num_customers) && (pass_type != _customers.customer_list[index].code.pass_type))
                index++;
        }

	if (index >= COURSES_SIZE)
		return ITEM_NOT_FOUND;
	else
		return index;
}

int register_customer(courses *_courses, customers _customers,
		int _course_index, int _participant_index) {
	int index;

	index = _courses->course_list[_course_index].num_participants;

	if (index < _courses->course_list[_course_index].max_participants) {
		_courses->course_list[_course_index].participants[index].number =
				_customers.customer_list[_participant_index].code.number;
		_courses->course_list[_course_index].participants[index].pass_type =
				_customers.customer_list[_participant_index].code.pass_type;
		_courses->course_list[_course_index].num_participants++;
		return OK;
	} else
		return NO_MORE_PARTICIPANTS_ALLOWED;
}

void assign_code(customers _customers, customer *_customer) {
	int index;
	int number;
	char pass_type;

	if (_customer->age <= 12)
		pass_type = CHILD;
	else
		if (_customer->gender == 'f')
			pass_type = FEMALE;
		else pass_type = MALE;

	index = _customers.num_customers - 1;

	printf("%d\n", index);
	printf("%c\n", pass_type);

	// Si ricerca l'ultimo abbonamento dello stesso tipo inserito in archivio
	while ((index >= 0) && (_customers.customer_list[index].code.pass_type != pass_type)) {
		index--; //scorre per cercare il pass_type uguale
	}

	if (index < 0)
		number = 1;
	else
		number = _customers.customer_list[index].code.number + 1;

	_customer->code.pass_type = pass_type;
	_customer->code.number = number;
}

void print_customers(customers _customers) {
	int i;
	for (i = 0; i < _customers.num_customers; i++) {
		printf("Code: %c%d\nName: %s\nSurname: %s\n",
				_customers.customer_list[i].code.pass_type,
				_customers.customer_list[i].code.number,
				_customers.customer_list[i].name,
				_customers.customer_list[i].surname);
	}
}
