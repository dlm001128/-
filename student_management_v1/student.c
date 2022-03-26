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
		printf("�ļ���û��ѧ����Ϣ\n");
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

//¼��ѧ����Ϣ
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
		printf("������ѧ��id: ");
		(void)scanf("%d", &newNode->student.stu_id);
		printf("������ѧ������: ");
		(void)scanf("%s", newNode->student.stu_name);
		printf("������ѧ��C���Գɼ�: ");
		(void)scanf("%lf", &newNode->student.stu_c_score);

		printf("ѧ����Ϣ¼��ɹ���\n");
		
	}
}

//��ӡѧ����Ϣ
void printStudent(LinkedList_t* list) {
	printf("ѧ��\t����\tC���Գɼ�\n");
	Node_t* cur = list->head;
	for (int i = 0; i < list->size; i++) {
		printf("%d\t%s\t%lf\n", cur->student.stu_id, cur->student.stu_name, cur->student.stu_c_score);
		cur = cur->next;
	}
	system("cls");
}

//����ѧ����Ϣ
void saveStudent(LinkedList_t* list) {
	//���ļ�
	FILE* fp = fopen("student.txt", "w");
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return;
	}
	Node_t* cur = list->head;
	for (int i = 0; i < list->size - 1; i++) {
		fprintf(fp, "%d %s %lf\n", cur->student.stu_id, cur->student.stu_name, cur->student.stu_c_score);
		cur = cur->next;
	}
	fprintf(fp, "%d %s %lf", cur->student.stu_id, cur->student.stu_name, cur->student.stu_c_score);
	//�ر��ļ�
	fclose(fp);
	//printf("���ݱ���ɹ�\n");
	system("cls");
}

void studentSearch(LinkedList_t* list) {
	system("cls");
	printf("��ѡ��һ�ֲ��ҷ�ʽ��\n");
	printf("1. ͨ��ѧ��id���в���\n");
	printf("2. ͨ��ѧ���������в���\n");
	int n;
	(void)scanf("%d", &n);
	if (n == 1) {
		printf("������ѧ��id��");
		int id;
		(void)scanf("%d", &id);
		idSearch(list, id);
	}
	else {
		printf("������ѧ��������");
		char name[STU_NAME_LEN];
		(void)scanf("%s", name);
		nameSearch(list, name);
	}
	system("pause");
	system("cls");
}

//ͨ��id����ѧ���Ƿ���ڣ�idΨһ��
bool idSearch(LinkedList_t* list, int id) {
	if (list == NULL) {
		printf("��ǰû��ѧ����Ϣ\n");
		return false;
	}
	Node_t* cur = list->head;
	for (int i = 0; i < list->size; i++) {
		if (cur->student.stu_id == id) {
			printf("��ѧ�����ڣ���Ϣ���£�\n");
			printf("%d\t%s\t%lf\n", cur->student.stu_id, cur->student.stu_name, cur->student.stu_c_score);
			return true;
		}
		cur = cur->next;
	}
	printf("�����ڸ�ѧ����Ϣ������������id\n");
	return false;
}

//ͨ����������ѧ���Ƿ���ڣ����ֲ�Ψһ��
bool nameSearch(LinkedList_t* list, char name[STU_NAME_LEN]) {
	if (list == NULL) {
		printf("��ǰû��ѧ����Ϣ\n");
		return false;
	}
	Node_t* cur = list->head;
	int count = 0;
	for (int i = 0; i < list->size; i++) {
		if (strcmp(cur->student.stu_name, name) == 0) {
			printf("��ѧ�����ڣ���Ϣ���£�\n");
			printf("%d\t%s\t%lf\n", cur->student.stu_id, cur->student.stu_name, cur->student.stu_c_score);
			count++;
		}
		cur = cur->next;
	}
	if (count == 0) {
		printf("�����ڸ�ѧ����Ϣ����������������\n");
		return false;
	}
	else
		return true;
}

//����ѧ����Ϣ
bool updateStudent(LinkedList_t* list) {
	system("cls");
	if (list == NULL) {
		printf("û��ѧ����Ϣ���������ѧ����Ϣ\n");
		return false;
	}
	printf("������Ҫ�޸ĵ�ѧ��id��");
	int id;
	(void)scanf("%d", &id);
	Node_t* cur = list->head;
	for (int i = 0; i < list->size; i++) {
		if (cur->student.stu_id == id) {
			printf("������Ҫ�޸ĵ����ݣ�id�����޸ģ���\n");
			printf("�������޸ĺ��������");
			char name[STU_NAME_LEN + 1];
			(void)scanf("%s", name);
			name[strlen(name)] = '\0';
			strcpy(cur->student.stu_name, name);
			printf("�������޸ĺ��C���Գɼ���");
			double score;
			(void)scanf("%lf", &score);
			cur->student.stu_c_score = score;
			printf("ѧ����Ϣ�޸ĳɹ���\n");
			system("pause");
			return true;
		}
		cur = cur->next;
	}
	printf("û����Ҫ�޸ĵ�ѧ����Ϣ������������id\n");
	return false;
}

//ɾ��ѧ����Ϣ
bool removeStudent(LinkedList_t* list) {
	if (list == NULL) {
		printf("��ǰ������ѧ����Ϣ���������ѧ����Ϣ\n");
		return false;
	}
	Node_t* pre = NULL;
	Node_t* cur = list->head;
	printf("������Ҫɾ��ѧ����id��");
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
			printf("ѧ����Ϣɾ���ɹ�\n");
			system("pause");
			return true;
		}
		pre = cur;
		cur = cur->next;
	}
	printf("û����Ҫɾ����ѧ����Ϣ������������id\n");
	return false;
}