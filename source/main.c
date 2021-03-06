#include <stdio.h>
#include <stdlib.h>
//===========變數定義===============
int whodelete;
int flag = 0;
int a;
char c;
FILE *user;
char b;
int filelinecount = 0;
int adminfunction,mainmenuchoice, accountmanagerfunction ,count = 0;
char changeadminpw[20];
char inputpassword[20];
char lf;
//==================================
void refreshthefile();
void initprogram();
int printtheline(char content[200]);
int usercreate();
int people;
int userloggin();
int adminuserfunction();
//==================================
typedef struct _new
{
	int usersn;
	char username[10];
	char userpw[10];
	char doorlockpw[10];
	char accountrfidnum[10];

}new;
new one[100];
void main()
{
	initprogram();
	while (1){
		printtheline("Door Lock Control System");
		printtheline("Function Select");
		printtheline("1.Create New Account\n2.User Login\n3.Use Admin Account\n4.Exit");		
		printf("Your Choice:");
		scanf("%d", &a);
		switch (a){
		case 1:
			system("CLS");
			usercreate();
			break;
		case 2:;
			system("CLS");
			userloggin();
			break;
		case 3:
			system("CLS");
			adminuserfunction();
			break;
		case 4:
			return 0;
			break;
		}
		
	}
	system("pause");
	return 0;
}


void initprogram(){
	//讀取使用者記錄檔市否存在
	printf("Reading the account information.\nPlease wait....");
	user = fopen("user.txt", "r");
	if (user == NULL)
		printf("\nAccount File not Found!!\n");
	else
		printf("Sucssced!\n");
	while ((c = fgetc(user)) != EOF) {
		if (c == '\n')
			filelinecount++;
	}
	fclose(user);
	//將檔案中的使用者紀錄放入資料結構之中
	user = fopen("user.txt", "r");
	printf("Account Amount:%d\n", filelinecount);
	people = filelinecount;
	for (int i = 0; i < 100; i++){
		fscanf(user, "%d", &one[i].usersn);
		fscanf(user, "%s", one[i].username);
		fscanf(user, "%s", one[i].userpw);
		fscanf(user, "%s", one[i].doorlockpw);
		fscanf(user, "%s", one[i].accountrfidnum);
	}
	fclose(user);
}

int printtheline(char content[200]){
	printf("==========================================================\n%s\n==========================================================\n",content);
}

void refreshthefile(){
	printf("%d", filelinecount);
	user = fopen("user.txt", "w+");
	for (int w = 0; w < filelinecount; w++)
		fprintf(user, "%d\t%s\t%s\t%s\t%s\n", one[w].usersn, one[w].username, one[w].userpw, one[w].doorlockpw, &one[w].accountrfidnum);
	fclose(user);	
}

int usercreate(){
	printtheline("User Creating");
	user = fopen("user.txt", "a");
	one[people].usersn = people + 1;
	fprintf(user, "%d", one[people].usersn);
	printf("Enter Your UserName:");
	scanf("%s", &one[people].username);
	printf("Enter Your Password:");
	scanf("%s", &one[people].userpw);
	printf("Enter your DoorLock Password:");
	scanf("%s", &one[people].doorlockpw);
	printf("Enter your RFID card Number:");
	scanf("%s", &one[people].accountrfidnum);
	fprintf(user, "\t%s\t%s\t%s\t%s\n", one[people].username, one[people].userpw, one[people].doorlockpw, &one[people].accountrfidnum);
	fclose(user);
	system("CLS");
	printtheline("Add Succeed!");
	system("pause");
	system("CLS");
}
int userloggin(){
	
	char tempusername[10];
	while (strcmp(tempusername, "exit"))
	{
		system("CLS");
		printtheline("User Login(Enter \"exit\" to back main menu)");
		printf("Please Enter Your UserName:");
		char temppassword[10];
		int unstatus = 1, pwstatus = 0;
		int f = 0;
		scanf("%s", tempusername);
		char findusername[10];
		while (strcmp(tempusername, &one[f].username))
		{
			f++;
			if (!strcmp(tempusername, "exit")){
				system("CLS");
				return 0;
			}
			if (f > filelinecount){
				printf("User Not Found!!");
				printf("Please try again!\nYour UserName:");
				scanf("%s", tempusername);
				f = 0;
			}
		}
		if (!strcmp(tempusername, "exit"))
			continue;
		printf("Please Enter Your Password:");
		scanf("%s", temppassword);
		while (strcmp(temppassword, &one[f].userpw)){
			printf("password is wrong\tplease enter again :");
			scanf("%s", temppassword);
		}
		if (!strcmp(temppassword, &one[f].userpw)){
			system("CLS");
			printf("===============================\nAccount Infomation\n===============================\n");
			printf("Account Name:%s\nAccount Password:%s\nAccount Door Lock Passowrd:%s\nAccount RFID Card Number:%s\n", &one[f].username, &one[f].userpw, &one[f].doorlockpw, &one[people].accountrfidnum);
			printf("===============================\nWhat do you want do,%s?\n", &one[f].username);
			printf("1.Change Your Name\n2.Change Your Account Password\n3.Change your Door Lock Password\n4.Change Your RFID Card Number\n5.Logout\nYour choice:");
			int userfunction;
			scanf("%d", &userfunction);
			switch (userfunction){
			case 1:
				printf("Enter the Name that you want to change:");
				char changename[10];
				scanf("%s", changename);
				strcpy(one[f].username, changename);
				printf("%s", one[f].username);
				refreshthefile();
				break;
			case 2:
				printf("Enter the Account Password that you want to change:");
				char changepw[10];
				scanf("%s", changepw);
				strcpy(one[f].userpw, changepw);
				printf("%s", one[f].userpw);
				refreshthefile();
				break;
			case 3:
				printf("Enter the Door Lock Password that you want to change:");
				char changedoorlockpw[10];
				scanf("%s", changedoorlockpw);
				strcpy(one[f].doorlockpw, changedoorlockpw);
				printf("%s", one[f].doorlockpw);
				refreshthefile();
				break;
			case 4:
				printf("Enter the RFID Card Number that you want to change:");
				char changeaccountrfidnum[10];
				scanf("%s", changeaccountrfidnum);
				strcpy(one[f].accountrfidnum, changeaccountrfidnum);
				printf("%s", one[f].accountrfidnum);
				refreshthefile();
				break;
			case 5:
				break;
			}
		}
	}
}
int adminuserfunction(){
	adminfunction = 0;
	user = fopen("admin.txt", "r");
	char correct[20];
	fscanf(user, "%s", correct);
	fclose(user);
	printtheline("Adminstrator Login");
	printf("Use Admin Account Need Admin Password.\n");
	printf("Please enter your password:");
	inputpassword[20] = '/0';
	flag = 0;
	for (int j = 0; j < 10; j++)
	{
		inputpassword[j] = getch();
		if (inputpassword[j] != 13)      //在知識+查到在getch裡按enter會回傳一個13 
			flag++;
		else
			break;
		if (inputpassword[j] == '\b')
		{
			j = -1;
			printf("\b");
			printf(" ");
			printf("\b");
			inputpassword[20] = '/0';
			flag = 0;
		}
		else
		{
			printf("*");
		}
	}
	inputpassword[flag] = 0;
	while (strcmp(inputpassword, correct)){
		printf("\a\npassword is wrong\tplease enter again:");
		inputpassword[20] = '/0';
		flag = 0;
		for (int j = 0; j < 10; j++)
		{
			inputpassword[j] = getch();
			if (inputpassword[j] != 13)
				flag++;
			else
				break;
			if (inputpassword[j] == '\b')
			{
				j = -1;
				printf("\b");
				printf(" ");
				printf("\b");
				inputpassword[20] = '/0';
				flag = 0;
			}
			else
			{
				printf("*");
			}
		}
		inputpassword[flag] = 0;
	}

	printf("\n===============================\n");
	if (!strcmp(inputpassword, correct))
	{
		system("CLS");
		while(1){
		printtheline("Adminstrator Function");
		printtheline("1.print all ID information\n2.Change admin Password\n3.Logout");
		printf("Your Choice:");
		scanf("%d", &adminfunction);
		
			switch (adminfunction)
			{
			case 1:
				system("CLS");
				printf("===================================================\n");
				printf("     Name       Password        RFID Number\n");
				printf("===================================================\n");
				user = fopen("user.txt", "r");
				while ((b = getc(user)) != EOF)
				{
					printf("%c", b);
					count++;
				}
				fclose(user);
				printtheline("Account Manager");
				printtheline("1.Delete A User.2.Exit");
				printf("Your Choice:");
				scanf("%d", &accountmanagerfunction);
				switch (accountmanagerfunction)
				{
				case 1:
					printtheline("Which User Do You Want to Delete?Enter the SN:");
					scanf("%d", &whodelete);
					int t;
					for (t = whodelete - 1; t < filelinecount; t++)
					{
						*one[t].username = '\0';
						*one[t].userpw = '\0';
						*one[t].doorlockpw = '\0';
						*one[t].accountrfidnum = '\0';
						for (int r = 0; r < 10; r++)
						{
							one[t].username[r] = one[t + 1].username[r];
							one[t].userpw [r]= one[t + 1].userpw[r];
							one[t].doorlockpw[r] = one[t + 1].doorlockpw[r];
							one[t].accountrfidnum[r] = one[t + 1].accountrfidnum[r];
						}
						
					}
					filelinecount--;
					refreshthefile();
					break;
				case 2:
					system("CLS");
					break;
				default:
					break;
				}

				break;
			case 2:
				system("CLS");
				user = fopen("admin.txt", "w");
				printtheline("Enter Admin Password that you want to change:");
				scanf("%s", &changeadminpw);
				fprintf(user, "%s", changeadminpw);
				fclose(user);
				printtheline("Password Change Succeed!");
				system("pause");
				system("CLS");
				break;
			case 3:
				system("CLS");
				return 0;
				break;
			}
		}
	}
}