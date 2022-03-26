#include"student.h"
#include"user.h"
#include<stdio.h>
#include<conio.h>


int main() {
	LinkedList_t* stulist = studentInit();
	UserLinkedList_t* userlist = userInit();
	bool stu_update, stu_remove;
	bool user_update, user_remove;
	int user_role;
	char name[USER_NAME_LEN + 1], pwd[USER_PWD_LEN + 1];
	printf("请输入用户名：");
	(void)scanf("%s", name);
	printf("请输入密码：");
	char ch;
	int i = 0;
	while ((ch = _getch()) != '\r') {
		pwd[i] = ch;
		i++;
		printf("*");
	}
	pwd[i] = '\0';
	printf("\b\n");
	user_role = userRole(userlist, name, pwd);
	if (user_role == 1) {
		while (1) {
			adminWelcome();
			char cadmin;
			(void)scanf(" %c", &cadmin);
			switch (cadmin) {
			case '1':	//search student information
				studentSearch(stulist);
				break;
			case '2':	//add student information
				inputStudent(stulist);
				saveStudent(stulist);
				break;
			case '3':	//update student information
				stu_update = updateStudent(stulist);
				if (stu_update)
					saveStudent(stulist);
				break;
			case '4':	//delete student information
				stu_remove = removeStudent(stulist);
				if (stu_remove)
					saveStudent(stulist);
				break;
			case '5':	//add user account
				inputUser(userlist);
				saveUser(userlist);
				break;
			case '6':	//update user account
				user_update = updateUser(userlist);
				if (user_update)
					saveUser(userlist);
				break;
			case '7':	//delete user account
				user_remove = removeUser(userlist);
				if (user_remove)
					saveUser(userlist);
				break;
			case '8':	//search user account
				userSearch(userlist, name);
				break;
			case '9':	//exit
				return 0;
				break;
			}
		}
	}
	else if (user_role == 0) {
		while (1) {
			userWelcome();
			char cuser;
			(void)scanf(" %c", &cuser);
			switch (cuser) {
			case '1':	//查看学生信息
				studentSearch(stulist);
				break;
			case'9':	//退出
				return 0;
				break;
			}
		}
	}
	else {
		printf("请找管理员\n");
	}
	
	return 0;
}