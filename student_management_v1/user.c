#include "user.h"
#include"student.h"
#include<string.h>

void userWelcome() {
	printf("***********************************************\n");
	printf("*****Student Information Management System*****\n");
	printf("***********************************************\n");
	printf("*********1. search student information*********\n");
	printf("*********9.          exit             *********\n");
	printf("***********************************************\n");
}

int userRole(UserLinkedList_t* ulist, char name[USER_NAME_LEN + 1], char pwd[USER_PWD_LEN + 1]) {
	UserNode_t* ucur = ulist->uhead;
	for (int i = 0; i < ulist->usize; i++) {
		if (strcmp(ucur->user.user_name, name) == 0) {
			if (strcmp(ucur->user.user_pwd, pwd) == 0) {
				return ucur->user.user_role;
			}
			else {
				printf("���벻ƥ�䣬����������\n");
				return -1;
			}
		}
		ucur = ucur->unext;
	}
	printf("û�и��û�������ע��\n");
	return -1;
}

UserLinkedList_t* userInit() {
	UserLinkedList_t* ulist = (UserLinkedList_t*)calloc(1, sizeof(UserLinkedList_t));
	if (!ulist)
		return NULL;
	FILE* ufp = fopen("user.txt", "r");
	if (ufp == NULL) {
		printf("�ļ���û���û���Ϣ\n");
		return ulist;
	}
	else {
		while (!feof(ufp)) {
			UserNode_t* ucur = (UserNode_t*)calloc(1, sizeof(UserNode_t));
			if (!ucur)
				return NULL;
			(void)fscanf(ufp, "%s%s%d", ucur->user.user_name, ucur->user.user_pwd, &ucur->user.user_role);
			ucur->unext = NULL;
			if (ulist->uhead == NULL) {
				ulist->uhead = ucur;
				ulist->usize++;
			}
			else {
				ucur->unext = ulist->uhead;
				ulist->uhead = ucur;
				ulist->usize++;
			}
		}
		fclose(ufp);
		return ulist;
	}
}

void inputUser(UserLinkedList_t* ulist) {
	UserNode_t* uNewNode = (UserNode_t*)calloc(1, sizeof(UserNode_t));
	if (!uNewNode) {
		printf("Error: inputUser(): uNewNode failed.\n");
		return;
	}
	else {
		uNewNode->unext = NULL;
		if (ulist->uhead == NULL) {
			ulist->uhead = uNewNode;
			ulist->usize++;
		}
		else {
			uNewNode->unext = ulist->uhead;
			ulist->uhead = uNewNode;
			ulist->usize++;
		}
		printf("�������û���: ");
		(void)scanf("%s", uNewNode->user.user_name);
		printf("����������: ");
		(void)scanf("%s", uNewNode->user.user_pwd);
		printf("���������: ");
		(void)scanf("%d", &uNewNode->user.user_role);

		printf("�û���Ϣ¼��ɹ���\n");

	}
}

bool userSearch(UserLinkedList_t* ulist, char name[USER_NAME_LEN]) {
	if (ulist == NULL) {
		printf("��ǰû���û���Ϣ\n");
		return false;
	}
	UserNode_t* ucur = ulist->uhead;
	int count = 0;
	for (int i = 0; i < ulist->usize; i++) {
		if (strcmp(ucur->user.user_name, name) == 0) {
			printf("���û�����\n");
			printf("%s\t%d\n", ucur->user.user_name, ucur->user.user_role);
			count++;
		}
		ucur = ucur->unext;
	}
	if (count == 0) {
		printf("�����ڸ��û�\n");
		return false;
	}
	else
		return true;
}

void saveUser(UserLinkedList_t* ulist) {
	//���ļ�
	FILE* ufp = fopen("user.txt", "w");
	if (ufp == NULL) {
		printf("���ļ�ʧ��\n");
		return;
	}
	UserNode_t* ucur = ulist->uhead;
	for (int i = 0; i < ulist->usize - 1; i++) {
		fprintf(ufp, "%s %s %d\n", ucur->user.user_name, ucur->user.user_pwd, ucur->user.user_role);
		ucur = ucur->unext;
	}
	fprintf(ufp, "%s %s %d", ucur->user.user_name, ucur->user.user_pwd, ucur->user.user_role);
	//�ر��ļ�
	fclose(ufp);
	//printf("���ݱ���ɹ�\n");
	system("cls");
}

bool updateUser(UserLinkedList_t* ulist) {
	system("cls");
	if (ulist == NULL) {
		printf("û���û���Ϣ����������û���Ϣ\n");
		return false;
	}
	printf("������Ҫ�޸ĵ��û�����");
	char uname[USER_NAME_LEN + 1];
	(void)scanf("%s", uname);
	uname[strlen(uname)] = '\0';
	UserNode_t* ucur = ulist->uhead;
	for (int i = 0; i < ulist->usize; i++) {
		if (strcmp(ucur->user.user_name, uname) == 0) {
			printf("������Ҫ�޸ĵ����ݣ��û��������޸ģ���\n");
			printf("�������޸ĺ�����룺");
			char upwd[USER_PWD_LEN + 1];
			(void)scanf("%s", upwd);
			upwd[strlen(upwd)] = '\0';
			strcpy(ucur->user.user_pwd, upwd);
			printf("�������޸ĺ���ݣ�");
			int urole;
			(void)scanf("%d", &urole);
			ucur->user.user_role = urole;
			printf("�û���Ϣ�޸ĳɹ���\n");
			system("pause");
			return true;
		}
		ucur = ucur->unext;
	}
	printf("û����Ҫ�޸ĵ��û���Ϣ������������id\n");
	return false;
}

bool removeUser(UserLinkedList_t* ulist) {
	if (ulist == NULL) {
		printf("��ǰ�������û���Ϣ����������û���Ϣ\n");
		return false;
	}
	UserNode_t* upre = NULL;
	UserNode_t* ucur = ulist->uhead;
	printf("������Ҫɾ���û�����");
	char uname[USER_NAME_LEN + 1];
	(void)scanf("%s", uname);
	uname[strlen(uname)] = '\0';
	for (int i = 0; i < ulist->usize; i++) {
		if (strcmp(ucur->user.user_name, uname) == 0) {
			if (upre == NULL) {
				ulist->uhead = ucur->unext;
				ulist->usize--;
				free(ucur);
			}
			else {
				upre->unext = ucur->unext;
				ulist->usize--;
				free(ucur);
			}
			printf("�û���Ϣɾ���ɹ�\n");
			system("pause");
			return true;
		}
		upre = ucur;
		ucur = ucur->unext;
	}
	printf("û����Ҫɾ�����û���Ϣ�������������û���\n");
	return false;
}