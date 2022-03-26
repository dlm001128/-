#define _CRT_SECURE_NO_WARNINGS
#define USER_NAME_LEN 20
#define USER_PWD_LEN 15
#include<stdbool.h>
#include<stdio.h>

typedef struct user_s {
	char user_name[USER_NAME_LEN];
	char user_pwd[USER_PWD_LEN];
	int user_role;	//0-普通用户 1-管理员
}User_t;

typedef struct usernode_s {
	User_t user;
	struct usernode_s* unext;
}UserNode_t;

typedef struct userlinkedlist_s {
	UserNode_t* uhead;
	int usize;
}UserLinkedList_t;

void userWelcome();
int userRole(UserLinkedList_t* ulist, char name[USER_NAME_LEN + 1], char pwd[USER_PWD_LEN + 1]);
UserLinkedList_t* userInit();
void inputUser(UserLinkedList_t* list);
bool userSearch(UserLinkedList_t* ulist, char name[USER_NAME_LEN]);
void saveUser(UserLinkedList_t* list);
bool updateUser(UserLinkedList_t* ulist);
bool removeUser(UserLinkedList_t* list);