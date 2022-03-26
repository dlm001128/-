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
//通过id查找学生是否存在
bool idSearch(LinkedList_t* list, int id);
//通过姓名查找学生是否存在
bool nameSearch(LinkedList_t* list, char name[STU_NAME_LEN]);
//更新学生信息
bool updateStudent(LinkedList_t* list);
//删除学生信息（根据id）
bool removeStudent(LinkedList_t* list);