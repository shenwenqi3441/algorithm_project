// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//int main()
//{
//    std::cout << "Hello World!\n";
//
//
//}

#include <stdio.h> 
#include <malloc.h> 
#include <math.h> 
#include <string.h> 
#include <ctype.h> 
#define M 256 

///*定义堆栈*/
//typedef struct {
//	double data[M];
//	int top;
//}Stack;

///*初始化堆栈*/
//int InitStack(Stack* s)
//{
//	s->top = 0;
//	return true;
//}
///*判断栈是否为空*/
//int StEmpty(Stack* s)
//{
//	if (s->top == 0)
//	{
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}

///*入栈操作*/
//int StPush(Stack* s, double x)
//{
//	if (s->top == M)
//	{
//		printf("The stack is overflow!");
//	}
//	else
//	{
//		s->top = s->top + 1;
//		s->data[s->top] = x;
//	}
//
//	return true;
//}

///*出栈操作*/
//double StPop(Stack* s)
//{
//	double t;
//	if (!StEmpty(s))
//	{
//		t = s->data[s->top];
//		s->top = s->top - 1;
//	}
//	else
//	{
//		printf("StPop:The stack is empty!");
//		t = NULL;
//	}
//	return t;
//}
//
///*获取栈顶元素*/
//double StGetTop(Stack* s)
//{
//	double t;
//	if (!StEmpty(s))
//	{
//		t = s->data[s->top];
//	}
//	else
//	{
//		printf("StGeTop:The stack is empty!");
//		t = NULL;
//	}
//	return t;
//}

/*将数字字符转换成整形*/
int ChrTransferint(char c)
{
	int n;
	switch (c)
	{
	case '0': n = 0; break;
	case '1': n = 1; break;
	case '2': n = 2; break;
	case '3': n = 3; break;
	case '4': n = 4; break;
	case '5': n = 5; break;
	case '6': n = 6; break;
	case '7': n = 7; break;
	case '8': n = 8; break;
	case '9': n = 9; break;
	}
	return n;
}

/*获取两个操作符之间数字字符的个数,返回的是最后一个数字字符的位置*/
int GetNumsize(char str[], int n1)
{
	int n2 = n1;
	while (isdigit(str[n2]) || (str[n2]) == 46)/*isdigit()判断是否数字字符*/
	{
		n2 = n2 + 1;
	}
	return n2;
}
/*判断上个函数中获得的数字字符串中是否包含小数点，并返回它的位置，不包含，返回-1*/
int IsIncludepoint(char str[], int n1, int n2)
{
	int n3 = -1;
	int i;
	for (i = n1; i <= n2; i++)
	{
		if (str[i] == '.')
		{
			n3 = i;
			break;
		}
	}
	return n3;
}

/*将数字字符转换成数值*/
double Transfer(char str[], int n1, int n2, int n3)
{
	double data = 0;
	int i, ct;
	if (n3 < 0)
	{
		for (i = n2; i >= n1; i--)
		{
			ct = ChrTransferint(str[i]);
			data = data + ct * pow(10, n2 - i);
		}
	}
	else
	{
		for (i = n3 - 1; i >= n1; i--)
		{
			ct = ChrTransferint(str[i]);
			data = data + ct * pow(10, n3 - 1 - i);
		}
		for (i = n3 + 1; i <= n2; i++)
		{
			ct = ChrTransferint(str[i]);
			data = data + ct * pow(0.1, i - n3);
		}
	}
	return data;
}

/*主程序*/
int main()
{
	char str[M], c;
	double Value[M];
	int Index = 0;
	char Operator[M];
	int opIndex = 0;
	char a;
	int n, p1, p2, p3;    
	double data;      
	int i = 0;
	//Stack* so = (Stack*)malloc(sizeof(Stack));
	//Stack* sd = (Stack*)malloc(sizeof(Stack));
	//InitStack(so);
	//InitStack(sd);
	printf("Please input formula :\n");
	n = 0;
	while ((a = getchar()) != '\n')
	{
		if (a != ' ')
		{
			str[n] = a;
			n++;
		}
	}
	if (n < 255) 
	{
		str[n] = '\n';
		n++;
	}

	while (i < n)
	{
		char c;
		c = str[i];

		if (c == '(')
		{                                        
			//StPush(so, 1);
			Operator[opIndex] = c;
			opIndex++;
			i++;
		}
		else if (isdigit(c))
		{
			p1 = i;                                           
			p2 = GetNumsize(str, p1);
			p3 = IsIncludepoint(str, p1, p2 - 1);  
			data = Transfer(str, p1, p2 - 1, p3);
			//StPush(sd, data);
			Index++;
			Value[Index] = data;

			i = p2;
		}
		else if (c == '+')
		{
			//StPush(so, 2);
			opIndex++;
			Operator[opIndex] = c;

			i++;
		}
		else if (c == '-')
		{
			//StPush(so, 3);  
			opIndex++;
			Operator[opIndex] = c;

			i++;
		}
		else if (c == '*')
		{
			if (str[i + 1] == '(')     
			{
				//StPush(so, 4);
				opIndex++;
				Operator[opIndex] = c;
				i++;
			}
			else
			{
				double t1, t2, t3;       
				//t1 = StPop(sd); 
				t1 = Value[Index];
				Index = Index - 1;
				p1 = i + 1;
				if (str[i + 1] == '-') 
				{
					p1 = p1 + 1;
					p2 = GetNumsize(str, p1);
					p3 = IsIncludepoint(str, p1, p2 - 1);
					t2 = Transfer(str, p1, p2 - 1, p3);
					t2 = 0 - t2;
				}
				else
				{
					p2 = GetNumsize(str, p1);
					p3 = IsIncludepoint(str, p1, p2 - 1);
					t2 = Transfer(str, p1, p2 - 1, p3);
				}

				t3 = t1 * t2;
				//StPush(sd, t3);
				Index = Index + 1;
				Value[Index] = t3;
				i = p2;
			}
		}
		else if (c == '/')
		{
			if (str[i + 1] == '(')
			{
				//StPush(so, 5);
				i++;
			}
			else
			{
				double t1, t2, t3;
				//t1 = StPop(sd); 
				t1 = Value[Index];
				Index = Index - 1;
				p1 = i + 1;
				if (str[i + 1] == '-')
				{
					p1 = p1 + 1;
					p2 = GetNumsize(str, p1);
					p3 = IsIncludepoint(str, p1, p2 - 1);
					t2 = Transfer(str, p1, p2 - 1, p3);
					t2 = 0 - t2;
				}
				else
				{
					p2 = GetNumsize(str, p1);
					p3 = IsIncludepoint(str, p1, p2 - 1);
					t2 = Transfer(str, p1, p2 - 1, p3);
				}

				if (t2 == 0)
				{
					printf("The divisor cannot be zero");
					while (true)
					{

						if (getchar() == '\n')
						{
							return true;
						}
					}
				}

				t3 = t1 / t2;
				//StPush(sd, t3);
				Index = Index + 1;
				Value[Index] = t3;
				i = p2;
			}
		}
		else if (c == ')')
		{
			double t1, t2, t3;
			int p;
			while ((p = Operator[opIndex]) != '(' /*&& !StEmpty(so)*/)
			{                                     
				//t1 = StPop(sd);
				t1 = Value[Index];
				Index = Index - 1;

				//t2 = StPop(sd);
				t2 = Value[Index];
				Index = Index - 1;

				if (p == 2)
				{
					t3 = t2 + t1;
					//StPush(sd, t3);

					Index = Index + 1;
					Value[Index] = t3;
					
				}
				else if (p == 3)
				{
					t3 = t2 - t1;
					//StPush(sd, t3);
					Index = Index + 1;
					Value[Index] = t3;
				}
			}
			opIndex = opIndex - 1;

			if (Operator[opIndex] == '*')                
			{
				//StPop(so);
				opIndex--;
				//t1 = StPop(sd);
				t1 = Value[Index];
				Index = Index - 1;

				//t2 = StPop(sd);
				t2 = Value[Index];
				Index = Index - 1;
				t3 = t2 * t1;
	/*			StPush(sd, t3);*/
				Index = Index + 1;
				Value[Index] = t3;
			}
			else if (Operator[opIndex] == '/')
			{
				//StPop(so);
				opIndex--;
				//t1 = StPop(sd);
				t1 = Value[Index];
				Index = Index - 1;

				//t2 = StPop(sd);
				t2 = Value[Index];
				Index = Index - 1;

				if (t1 == 0) 
				{
					printf("The divisor cannot be zero");
					while (true)
					{

						if (getchar() == '\n')
						{
							return true;
						}
					}
				}
				t3 = t2 / t1;
				//StPush(sd, t3);
				Index = Index + 1;
				Value[Index] = t3;
			}
			i++;
		}
		else if (c == '=' || c == '\n')
		{
			double t1, t2, t3;           

			for (int i = 1; i < opIndex + 1; i++)
			{
				
				//t1 = StPop(sd);
				t1 = Value[Index];
				Index = Index - 1;

				//t2 = StPop(sd);
				t2 = Value[Index];
				Index = Index - 1;
				if (Operator[i] == '+')
				{
					t3 = t2 + t1;
					//StPush(sd, t3);
					Index = Index + 1;
					Value[Index] = t3;
				}
				else if (Operator[i] == '-')
				{
					t3 = t2 - t1;
					//StPush(sd, t3);
					Index = Index + 1;
					Value[Index] = t3;
				}
			}

			/*while (!StEmpty(so))
			{
				t1 = StPop(sd);
				t2 = StPop(sd);
				p = StPop(so);
				if (p == '+')
				{
					t3 = t2 + t1;             
					StPush(sd, t3);
				}
				else if (p == '-')
				{
					t3 = t2 - t1;
					StPush(sd, t3);         
				}
			}*/

			i++;
		}
	}
	//if (!StEmpty(so) || StEmpty(sd))
	//{
	//	printf("Input error,Back!\n"); 
	//}
	//else
	{
		/*if (!hasEqual) 
		{
			double t1, t2, t3;
			int p;
			while (!StEmpty(so))
			{
				t1 = StPop(sd);
				t2 = StPop(sd);
				p = StPop(so);
				if (p == 2)
				{
					t3 = t2 + t1;
					StPush(sd, t3);
				}
				else if (p == 3)
				{
					t3 = t2 - t1;
					StPush(sd, t3);
				}
			}
		}*/

		double end;
		int i;                                  
		//end = StGetTop(sd);
		end = Value[Index];
		printf("The value of this formula:\n");
		for (i = 0; i < n; i++)
		{
			printf("%c", str[i]);
		}
		printf("%f\n", end);
		while (true)
		{
			
			if (getchar() == '\n')
			{
				return true;
			}
		}
	}
}
