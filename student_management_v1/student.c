#include "student.h"
#include"user.h"

void adminWelcome() {
	printf("***********************************************\n");
	printf("*****Student Information Management System*****\n");
	printf("***********************************************\n");
	printf("*********1. search student information*********\n");
	printf("*********2.   add  student information*********\n");
	printf("*********3. update student information*********\n");
	printf("*********4. delete student information*********\n");
	printf("*********5.   add    user    account  *********\n");
	printf("*********6. update   user    account  *********\n");
	printf("*********7. delete   user    account  *********\n");
	printf("*********8. search   user    account  *********\n");
	printf("*********9.          exit             *********\n");
	printf("***********************************************\n");
}

LinkedList_t* studentInit() {
	LinkedList_t* list = (LinkedList_t*)calloc(1, sizeof(LinkedList_t));
	if (!list)
		return NULL;
	FILE* fp = fopen("student.txt", "r");
	if (fp == NULL) {
		printf("文件中没有学生信息\n");
		return list;
	}
	else {
		while (!feof(fp)) {
			Node_t* cur = (Node_t*)calloc(1, sizeof(Node_t));
			if (!cur)
				return NULL;
			(void)fscanf(fp, "%d%s%lf", &cur->student.stu_id, cur->student.stu_name, &cur->student.stu_c_score);
			cur->next = NULL;
			if (list->head == NULL) {
				list->head = cur;
				list->size++;
			}
			else {
				cur->next = list->head;
				list->head = cur;
				list->size++;
			}
		}
		fclose(fp);
		//list->head = list->head->next;
		//list->size--;
		return list;
	}
}

//录入学生信息
void inputStudent(LinkedList_t* list) {
	Node_t* newNode = (Node_t*)calloc(1, sizeof(Node_t));
	if (!newNode) {
		printf("Error: inputStudent(): newNode failed.\n");
		return;
	}
	else {
		newNode->next = NULL;
		if (list->head == NULL) {
			list->head = newNode;
			list->size++;
		}
		else {
			newNode->next = list->head;
			list->head = newNode;
			list->size++;
		}
		printf("请输入学生id: ");
		(void)scanf("%d", &newNode->student.stu_id);
		printf("请输入学生姓名: ");
		(void)scanf("%s", newNode->student.stu_name);
		printf("请输入学生C语言成绩: ");
		(void)scanf("%lf", &newNode->student.stu_c_score);

		printf("学生信息录入成功！\n");
		
	}
}

//打印学生信息
void printStudent(LinkedList_t* list) {
	printf("学号\t姓名\tC语言成绩\n");
	Node_t* cur = list->head;
	for (int i = 0; i < list->size; i++) {
		printf("%d\t%s\t%lf\n", cur->student.stu_id, cur->student.stu_name, cur->student.stu_c_score);
		cur = cur->next;
	}
	system("cls");
}

//保存学生信息
void saveStudent(LinkedList_t* list) {
	//打开文件
	FILE* fp = fopen("student.txt", "w");
	if (fp == NULL) {
		printf("打开文件失败\n");
		return;
	}
	Node_t* cur = list->head;
	for (int i = 0; i < list->size - 1; i++) {
		fprintf(fp, "%d %s %lf\n", cur->student.stu_id, cur->student.stu_name, cur->student.stu_c_score);
		cur = cur->next;
	}
	fprintf(fp, "%d %s %lf", cur->student.stu_id, cur->student.stu_name, cur->student.stu_c_score);
	//关闭文件
	fclose(fp);
	//printf("数据保存成功\n");
	system("cls");
}

void studentSearch(LinkedList_t* list) {
	system("cls");
	printf("请选择一种查找方式：\n");
	printf("1. 通过学生id进行查找\n");
	printf("2. 通过学生姓名进行查找\n");
	int n;
	(void)scanf("%d", &n);
	if (n == 1) {
		printf("请输入学生id：");
		int id;
		(void)scanf("%d", &id);
		idSearch(list, id);
	}
	else {
		printf("请输入学生姓名：");
		char name[STU_NAME_LEN];
		(void)scanf("%s", name);
		nameSearch(list, name);
	}
	system("pause");
	system("cls");
}

//通过id查找学生是否存在（id唯一）
bool idSearch(LinkedList_t* list, int id) {
	if (list == NULL) {
		printf("当前没有学生信息\n");
		return false;
	}
	Node_t* cur = list->head;
	for (int i = 0; i < list->size; i++) {
		if (cur->student.stu_id == id) {
			printf("该学生存在，信息如下：\n");
			printf("%d\t%s\t%lf\n", cur->student.stu_id, cur->student.stu_name, cur->student.stu_c_score);
			return true;
		}
		cur = cur->next;
	}
	printf("不存在该学生信息，请重新输入id\n");
	return false;
}

//通过姓名查找学生是否存在（名字不唯一）
bool nameSearch(LinkedList_t* list, char name[STU_NAME_LEN]) {
	if (list == NULL) {
		printf("当前没有学生信息\n");
		return false;
	}
	Node_t* cur = list->head;
	int count = 0;
	for (int i = 0; i < list->size; i++) {
		if (strcmp(cur->student.stu_name, name) == 0) {
			printf("该学生存在，信息如下：\n");
			printf("%d\t%s\t%lf\n", cur->student.stu_id, cur->student.stu_name, cur->student.stu_c_score);
			count++;
		}
		cur = cur->next;
	}
	if (count == 0) {
		printf("不存在该学生信息，请重新输入姓名\n");
		return false;
	}
	else
		return true;
}

//更新学生信息
bool updateStudent(LinkedList_t* list) {
	system("cls");
	if (list == NULL) {
		printf("没有学生信息，请先添加学生信息\n");
		return false;
	}
	printf("请输入要修改的学生id：");
	int id;
	(void)scanf("%d", &id);
	Node_t* cur = list->head;
	for (int i = 0; i < list->size; i++) {
		if (cur->student.stu_id == id) {
			printf("请输入要修改的内容（id不可修改）：\n");
			printf("请输入修改后的姓名：");
			char name[STU_NAME_LEN + 1];
			(void)scanf("%s", name);
			name[strlen(name)] = '\0';
			strcpy(cur->student.stu_name, name);
			printf("请输入修改后的C语言成绩：");
			double score;
			(void)scanf("%lf", &score);
			cur->student.stu_c_score = score;
			printf("学生信息修改成功！\n");
			system("pause");
			return true;
		}
		cur = cur->next;
	}
	printf("没有您要修改的学生信息，请重新输入id\n");
	return false;
}

//删除学生信息
bool removeStudent(LinkedList_t* list) {
	if (list == NULL) {
		printf("当前不存在学生信息，请先添加学生信息\n");
		return false;
	}
	Node_t* pre = NULL;
	Node_t* cur = list->head;
	printf("请输入要删除学生的id：");
	int id;
	(void)scanf("%d", &id);
	for (int i = 0; i < list->size; i++) {
		if (cur->student.stu_id == id) {
			if (pre == NULL) {
				list->head = cur->next;
				list->size--;
				free(cur);
			}
			else {
				pre->next = cur->next;
				list->size--;
				free(cur);
			}
			printf("学生信息删除成功\n");
			system("pause");
			return true;
		}
		pre = cur;
		cur = cur->next;
	}
	printf("没有您要删除的学生信息，请重新输入id\n");
	return false;
}