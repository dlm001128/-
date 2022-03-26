#define _CRT_SECURE_NO_WARNINGS
#define STU_NAME_LEN 20
#define MAX_NUM 1000
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct student_s {
	int stu_id;
	char stu_name[STU_NAME_LEN];
	double stu_c_score;
}Student_t;

typedef struct node_s {
	Student_t student;
	struct node_s* next;
}Node_t;

typedef struct linkedlist_s {
	Node_t* head;
	int size;
}LinkedList_t;

void adminWelcome();
LinkedList_t* studentInit();
void inputStudent(LinkedList_t* list);
void printStudent(LinkedList_t* list);
void saveStudent(LinkedList_t* list);
void studentSearch(LinkedList_t* list);
//ͨ��id����ѧ���Ƿ����
bool idSearch(LinkedList_t* list, int id);
//ͨ����������ѧ���Ƿ����
bool nameSearch(LinkedList_t* list, char name[STU_NAME_LEN]);
//����ѧ����Ϣ
bool updateStudent(LinkedList_t* list);
//ɾ��ѧ����Ϣ������id��
bool removeStudent(LinkedList_t* list);