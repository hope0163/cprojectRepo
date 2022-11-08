#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <Windows.h>
#define SIZE 1000

typedef struct user {         //���� ȸ������ ������ ����ü�� ǥ��
	char name[SIZE]; // �̸�
	char phone[SIZE]; //�޴���
	char id[SIZE]; // ���̵�
	char password[SIZE]; //��й�ȣ
} USER;

void menu();  // �α���/ȸ������ ���ø޴�
USER information(FILE* fp); // ����ڷκ��� �����͸� �޾� ����ü�� ��ȯ
void sign_up(FILE* fp); //ȸ������
void overlap_check(FILE* fp);   // ���̵� �ߺ�Ȯ��
void login(FILE* fp);




int main(void)
{
	FILE* fp;
	int select;
	if ((fp = fopen("userinformation.text", "a+")) == NULL)
	{
		fprintf(stderr, "����");
		exit(1);
	}
	while (1)
	{
		menu();
		printf("\n���Ͻô� �޴��� �Է����ּ���: ");
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

	getchar();   //�ٹٲ� ���� ����
	Sleep(1000);
	system("cls");
	printf("�ȳ��ϼ���! ȸ�������� �����ϰڽ��ϴ�!\n\n");

	printf("�̸��� �Է����ּ��� : ");				gets_s(data.name, SIZE);
	printf("�ڵ��� ��ȣ�� �Է����ּ��� : ");		gets_s(data.phone, SIZE);
	printf("����Ͻ� ���̵� �Է����ּ��� : ");	gets_s(data.id, SIZE);
	printf("����Ͻ� ��й�ȣ�� �Է����ּ��� : ");  gets_s(data.password, SIZE);
	return data;
}


void menu()
{
	printf("�α��� - 1\nȸ������ - 2\n���� - 3\n");
}




void sign_up(FILE* fp)
{
	USER data;
	data = information();						// ����ڷκ��� �����͸� �޾Ƽ� ����ü�� ����
	fseek(fp, 0, SEEK_END);					// ������ ������ ����
	fwrite(&data, sizeof(data), 1, fp);		// ����ü �����͸� ���Ͽ� ����
}





void overlap_check(FILE* fp)	// ���̵� �ߺ�Ȯ��
{
	char id[SIZE];
	USER data;

	fseek(fp, 0, SEEK_SET);
	getchar(); //�ٹٲ� ���� ����
hi:
	printf("�ߺ�Ȯ��\n����Ͻ� ���̵� �Է����ּ��� : ");
	gets_s(id, SIZE);
	while (!feof(fp)) {
		fread(&data, sizeof(data), 1, fp);
		if (strcmp(data.id, id) == 0) {
			printf("�̹� �ִ� ���̵��Դϴ�.\n");
			goto hi;
		}
		else {
			printf("����Ͻ� �� �ִ� ���̵��Դϴ�!\n");
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
	printf("���̵� �Է��ϼ���: ");
	gets_s(id, SIZE);
	printf("��й�ȣ�� �Է��ϼ���: ");
	gets_s(password, SIZE);
	while (!feof(fp)) {
		fread(&data, sizeof(data), 1, fp);
		if (strcmp(data.id, id) == 0 && strcmp(data.password, password) == 0)
		{
			printf("�α��μ���\n");
			break;
		}
		else
		{
			printf("���̵� �Ǵ� ��й�ȣ�� Ʋ�Ƚ��ϴ�. �޴� ȭ������ ���ư��ϴ�.\n");
			break;
		}
	}
}