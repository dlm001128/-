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
				printf("密码不匹配，请重新输入\n");
				return -1;
			}
		}
		ucur = ucur->unext;
	}
	printf("没有该用户，请先注册\n");
	return -1;
}

UserLinkedList_t* userInit() {
	UserLinkedList_t* ulist = (UserLinkedList_t*)calloc(1, sizeof(UserLinkedList_t));
	if (!ulist)
		return NULL;
	FILE* ufp = fopen("user.txt", "r");
	if (ufp == NULL) {
		printf("文件中没有用户信息\n");
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
		printf("请输入用户名: ");
		(void)scanf("%s", uNewNode->user.user_name);
		printf("请输入密码: ");
		(void)scanf("%s", uNewNode->user.user_pwd);
		printf("请输入身份: ");
		(void)scanf("%d", &uNewNode->user.user_role);

		printf("用户信息录入成功！\n");

	}
}

bool userSearch(UserLinkedList_t* ulist, char name[USER_NAME_LEN]) {
	if (ulist == NULL) {
		printf("当前没有用户信息\n");
		return false;
	}
	UserNode_t* ucur = ulist->uhead;
	int count = 0;
	for (int i = 0; i < ulist->usize; i++) {
		if (strcmp(ucur->user.user_name, name) == 0) {
			printf("该用户存在\n");
			printf("%s\t%d\n", ucur->user.user_name, ucur->user.user_role);
			count++;
		}
		ucur = ucur->unext;
	}
	if (count == 0) {
		printf("不存在该用户\n");
		return false;
	}
	else
		return true;
}

void saveUser(UserLinkedList_t* ulist) {
	//打开文件
	FILE* ufp = fopen("user.txt", "w");
	if (ufp == NULL) {
		printf("打开文件失败\n");
		return;
	}
	UserNode_t* ucur = ulist->uhead;
	for (int i = 0; i < ulist->usize - 1; i++) {
		fprintf(ufp, "%s %s %d\n", ucur->user.user_name, ucur->user.user_pwd, ucur->user.user_role);
		ucur = ucur->unext;
	}
	fprintf(ufp, "%s %s %d", ucur->user.user_name, ucur->user.user_pwd, ucur->user.user_role);
	//关闭文件
	fclose(ufp);
	//printf("数据保存成功\n");
	system("cls");
}

bool updateUser(UserLinkedList_t* ulist) {
	system("cls");
	if (ulist == NULL) {
		printf("没有用户信息，请先添加用户信息\n");
		return false;
	}
	printf("请输入要修改的用户名：");
	char uname[USER_NAME_LEN + 1];
	(void)scanf("%s", uname);
	uname[strlen(uname)] = '\0';
	UserNode_t* ucur = ulist->uhead;
	for (int i = 0; i < ulist->usize; i++) {
		if (strcmp(ucur->user.user_name, uname) == 0) {
			printf("请输入要修改的内容（用户名不可修改）：\n");
			printf("请输入修改后的密码：");
			char upwd[USER_PWD_LEN + 1];
			(void)scanf("%s", upwd);
			upwd[strlen(upwd)] = '\0';
			strcpy(ucur->user.user_pwd, upwd);
			printf("请输入修改后身份：");
			int urole;
			(void)scanf("%d", &urole);
			ucur->user.user_role = urole;
			printf("用户信息修改成功！\n");
			system("pause");
			return true;
		}
		ucur = ucur->unext;
	}
	printf("没有您要修改的用户信息，请重新输入id\n");
	return false;
}

bool removeUser(UserLinkedList_t* ulist) {
	if (ulist == NULL) {
		printf("当前不存在用户信息，请先添加用户信息\n");
		return false;
	}
	UserNode_t* upre = NULL;
	UserNode_t* ucur = ulist->uhead;
	printf("请输入要删除用户名：");
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
			printf("用户信息删除成功\n");
			system("pause");
			return true;
		}
		upre = ucur;
		ucur = ucur->unext;
	}
	printf("没有您要删除的用户信息，请重新输入用户名\n");
	return false;
}