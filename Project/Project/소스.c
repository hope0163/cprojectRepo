#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <Windows.h>
#define SIZE 1000

typedef struct user {         //유저 회원가입 정보를 구조체로 표현
	char name[SIZE]; // 이름
	char phone[SIZE]; //휴대폰
	char id[SIZE]; // 아이디
	char password[SIZE]; //비밀번호
} USER;

void menu();  // 로그인/회원가입 선택메뉴
USER information(FILE* fp); // 사용자로부터 데이터를 받아 구조체로 반환
void sign_up(FILE* fp); //회원가입
void overlap_check(FILE* fp);   // 아이디 중복확인
void login(FILE* fp);




int main(void)
{
	FILE* fp;
	int select;
	if ((fp = fopen("userinformation.text", "a+")) == NULL)
	{
		fprintf(stderr, "오류");
		exit(1);
	}
	while (1)
	{
		menu();
		printf("\n원하시는 메뉴를 입력해주세요: ");
		scanf("%d", &select);
		switch (select)
		{
		case 1: login(fp); break;
		case 2: sign_up(fp); break;
		case 3: return 0;
		}
	}
	fclose(fp);
	return 0;
}





USER information()
{
	USER data;

	getchar();   //줄바꿈 문자 제거
	Sleep(1000);
	system("cls");
	printf("안녕하세요! 회원가입을 시작하겠습니다!\n\n");

	printf("이름을 입력해주세요 : ");				gets_s(data.name, SIZE);
	printf("핸드폰 번호를 입력해주세요 : ");		gets_s(data.phone, SIZE);
	printf("사용하실 아이디를 입력해주세요 : ");	gets_s(data.id, SIZE);
	printf("사용하실 비밀번호를 입력해주세요 : ");  gets_s(data.password, SIZE);
	return data;
}


void menu()
{
	printf("로그인 - 1\n회원가입 - 2\n종료 - 3\n");
}




void sign_up(FILE* fp)
{
	USER data;
	data = information();						// 사용자로부터 데이터를 받아서 구조체에 저장
	fseek(fp, 0, SEEK_END);					// 파일의 끝으로 간다
	fwrite(&data, sizeof(data), 1, fp);		// 구조체 데이터를 파일에 쓴다
}





void overlap_check(FILE* fp)	// 아이디 중복확인
{
	char id[SIZE];
	USER data;

	fseek(fp, 0, SEEK_SET);
	getchar(); //줄바꿈 문자 제거
hi:
	printf("중복확인\n사용하실 아이디를 입력해주세요 : ");
	gets_s(id, SIZE);
	while (!feof(fp)) {
		fread(&data, sizeof(data), 1, fp);
		if (strcmp(data.id, id) == 0) {
			printf("이미 있는 아이디입니다.\n");
			goto hi;
		}
		else {
			printf("사용하실 수 있는 아이디입니다!\n");
			break;
		}
	}
}




void login(FILE* fp)
{
	char id[SIZE];
	char password[SIZE];
	USER data;


	Sleep(1000);
	system("cls");
	fseek(fp, 0, SEEK_SET);
	getchar();
	printf("아이디를 입력하세요: ");
	gets_s(id, SIZE);
	printf("비밀번호를 입력하세요: ");
	gets_s(password, SIZE);
	while (!feof(fp)) {
		fread(&data, sizeof(data), 1, fp);
		if (strcmp(data.id, id) == 0 && strcmp(data.password, password) == 0)
		{
			printf("로그인성공\n");
			break;
		}
		else
		{
			printf("아이디 또는 비밀번호가 틀렸습니다. 메뉴 화면으로 돌아갑니다.\n");
			break;
		}
	}
}