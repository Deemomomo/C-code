#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")//��������ͷ�ļ���

//��������
typedef struct point
{
	int x, y;
}MYPOINT;
//��
struct snake
{
	MYPOINT xy[100];//����
	int position; //����
	int num;	  //����
}snake;
//ʳ��
struct
{
	MYPOINT fdxy;    //����
	int flag;	   //���
	int grade;     //����
}food;
//ö�� ����
enum position { up, down, left, right };
//ģ�黯
//����
//��ʼ����
void initsnake()
{
	//ǰ����
	snake.xy[2].x = 0;
	snake.xy[2].y = 0;

	snake.xy[1].x = 10;
	snake.xy[1].y = 0;

	snake.xy[0].x = 20;
	snake.xy[0].y = 0;

	snake.position = right;
	snake.num = 3;

}
//����
void drawsnake()
{
	//������
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(BLACK);
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}
}
//������
void movesnake()
{
	//����ת��
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	//��ͷ
	switch (snake.position)
	{
	case up:
		snake.xy[0].y -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case right:
		snake.xy[0].x += 10;
		break;
	}
}
//��������
void keyDown()
{
	char userKey = _getch();
	switch (userKey)
	{
	case 'W':
	case 'w':
	case 72:
		if (snake.position != down)
			snake.position = up;
		break;
	case 'S':
	case 's':
	case 80:
		if (snake.position != up)
			snake.position = down;
		break;
	case 'A':
	case 'a':
	case 75:
		if (snake.position != right)
			snake.position = left;
		break;
	case 'D':
	case 'd':
	case 77:
		if (snake.position != left)
			snake.position = right;
		break;
	}
}

//��ʳ��
void initFood()
{
	food.fdxy.x = rand() % 80 * 10;
	food.fdxy.y = rand() % 60 * 10;
	food.flag = 1;//1�����
	//ʳ�ﲻ�ܳ���.y == snake.xy[i]������
	for (int i = 0; i < snake.num; i++)
	{
		if (food.fdxy.x == snake.xy[i].x && food.fdxy.y == snake.xy[i].y)
		{
			food.fdxy.x = rand() % 80 * 10;
			food.fdxy.y = rand() % 60 * 10;
		}

	}
}
//��ʳ��
void drawFood()
{
	setlinecolor(BLACK);
	setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);
}

//��ʳ��
void eatFood()
{
	if (snake.xy[0].x == food.fdxy.x && snake.xy[0].y == food.fdxy.y)
	{
		snake.num++;
		food.flag = 0;
		food.grade += 10;
	}
}

//��ʾ����
void showGrade()
{
	//��ʽ����ӡ
	char grade[20] = "";
	sprintf_s(grade, "grade;%d", food.grade);
	settextcolor(LIGHTRED);
	settextstyle(25, 0, "����");
	outtextxy(600, 50, grade);
}

HWND hwnd = NULL;
int snakeDie()
{
	if (snake.xy[0].x > 800 || snake.xy[0].x < 0 || snake.xy[0].y>600 || snake.xy[0].y < 0)
	{
		mciSendString("close 1.mp3", 0, 0, 0);
		MessageBox(hwnd, "collide", "gameover", MB_OK);
		return 1;
	}

	for (int i = 1; i < snake.num; i++)
	{
		if(snake.xy[0].x == snake.xy[i].x&&snake.xy[0].y == snake.xy[i].y)
		{
	    mciSendString("close 1.mp3", 0, 0, 0);
	    MessageBox(hwnd, "Suicide.", "gameover", MB_OK);
	    return 1;
		}
	}
	return 0;
}

int main()
{
	srand((unsigned int)time(NULL));
	//����ͼ�δ���
	initgraph(800, 600);
	setbkcolor(RGB(110, 120, 200));//����
	cleardevice();//����

	mciSendString("open 1.mp3", 0, 0, 0);
	mciSendString("play 1.mp3", 0, 0, 0);


	initsnake();
	drawsnake();
	while (1)
	{
		cleardevice();//����
		movesnake();
		drawsnake();
		if (food.flag == 0)
		{
			initFood();
		}
		if (_kbhit())
		{
			keyDown();
		}
		if (snakeDie())
		{
			break;
		}
		
		drawFood();
		eatFood();
		showGrade();

		Sleep(100);
	}


	_getch();            //������
	closegraph();
	return 0;
}
