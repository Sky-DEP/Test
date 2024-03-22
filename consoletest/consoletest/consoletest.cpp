// consoletest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

DWORD temp = 0;

void __declspec(naked) IdtEntry()
{
	__asm {
		mov eax, dword ptr ds : [0x80b95500]
		mov temp, eax
		iretd
	}
}

void go()
{
	__asm int 0x20
}

void fun1()
{
	if ((DWORD)IdtEntry != 0x401040)
	{
		printf("wrong addr:%p", IdtEntry);
		exit(-1);
	}
	go();
	printf("%d\n", temp);

	system("pause");
}

void hello()
{
	printf("hello world!\n");
}

typedef void (*FunPtr)();

void fun2()
{
	int* p = (int*)hello;
	printf("%x\n", *p);
	((FunPtr)p)();
}

void fun3()
{
	std::vector<int> vecTest{ 1, 2, 3, 4, 5, 6, 4 };
	for (auto iter = vecTest.begin(); iter != vecTest.end(); )
	{
		if (*iter == 4)
		{
			iter = vecTest.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	for (auto i : vecTest)
	{
		std::cout << i << std::endl;
	}
}

void fun4()
{
	std::string* pstr = new std::string("i has beautiful girl");
}


int main()
{
	fun4();

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
