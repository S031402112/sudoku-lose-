// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "cstdlib"
#include "stdio.h"



int main(int argc, char *argv[])
{
	short m, n;
	m = (short)argv[2];			//m 宫格阶级（3~9的整数）
	n = (short)argv[4];			//n 待解答盘面数目
	char *i = argv[6];			//刚开始忘了argv是*char,以为是FILE*
	char *o = argv[8];
	FILE *ip, *op;
	if ((ip = fopen(i, "r")) == NULL) {
		printf("open file fail!\n");
		exit(EXIT_SUCCESS);
	}
	
	short sudoku[10][10] = { 0 };				//记录原始的数独数据,其中0为未知
	short sudoku_s[10][10] = { 0 };				//记录原始的数独状态,1为已知,0为未知
	short sudoku_r[10][10] = { 0 };				//记录临时的数独数据,其中0为未知
	bool suduku_t[10][10][10] = { 0 };			//每个单元填入数据的合法性记录,值为1表示不可以选择该数字填入
	for (short i = 1; i <= m; i++)				//每次读文件效率太低也麻烦,直接保存在内存
	{
		for (short j = 1; j <= m; j++)
		{
			sudoku_r[i][j] = sudoku[i][j] = fgetc(ip); fgetc(ip);
			if (sudoku[i][j]!=0)
			{
				sudoku_s[i][j] = 1;
				for (short k = 1; k <= m; k++)
				{
					suduku_t[i][j][k] = 1;		//排除法记录每格允许填入的数字,配合猜测函数guess()使用
				}								//从这里就错了，QAQ
			}
		}
	}
	
	

	short guess(short sudoku[10][10], short sudoku_s[10][10],bool sudoku_t[10][10][10],short m) {
		for (short i = 1; i <= m; i++)				
		{
			for (short j = 1; j <= m; j++)
			{
				short k = 1;
				if (sudoku_s[i][j] == 0)
				{
					do
					{
						if (sudoku_t[i][j][k] == 0){
							suduku_r[i][j] = k;
							break;
							k++
						}
					} while (1);
				}
			}
		}

	}
	
	if ((ip = fopen(i, "w+")) == NULL) {
		printf("open file fail!\n");
		exit(EXIT_SUCCESS);
	}
	fclose(ip);
	fclose(op);
    return 0;
}

