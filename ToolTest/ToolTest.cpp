﻿// ToolTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "StringTool.h"

#include "FileTool.h"
#include "ClassInstance.h"
#include "ProcessTool.h"
#include "ShareStruct.h"
#include <vector>
#include <thread>
#include <iostream>
#include <memory>
#include "HandleMy.h"
#include <assert.h>
#include "BoostLog.h"
#include <fstream>

#include "InlineHook.h"
using namespace std;

#include <string>

#include "ResManager.h"
#include <deque>
#include "PublicTool.h"

//测试韩服资源名称转换
#include "Language.h"
#include <functional>
#include "verification.h"
void MyMessageBox(const char * szBuff)
{
	if (szBuff)
		std::cout << "MessageBox内容:" <<szBuff<< std::endl;
}

_declspec(naked) void nakedPrivateChat()
{
	__asm
	{
		pushad  //保存寄存器

			mov ebp, esp  //这是固定的
			add ebp, 0x20   //这也是固定的 处理pushad的堆栈

			mov eax, [ebp + 0x8]
			push eax
			call MyMessageBox
			add esp, 4



			popad //保存寄存器取消


			/*
			下面要nop HOOK库会将下面的nop改成相应的代码
			*/
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
	}
}

#include <set>


struct CTestCopy
{
	CTestCopy(){}
	CTestCopy(const CTestCopy & t)
	{
		x = t.x;
	}
	int x ;
	int y ;
};

void MyReleaseMutex(HANDLE h)
{
	::CloseHandle(h);
}

struct Test
{
	int member_count;
	std::wstring fuben_name;
	std::string caree_group;
	bool is_cross_team;

	operator bool() const
	{
		return member_count == 10;
	}
};


#include "TimeTool.h"
int _tmain(int argc, _TCHAR* argv[])
{

// 	std::string temp = "zhangdongsheng";
// 
// 	std::vector<char> data;
// 	data.resize(temp.length());
// 	memset(data.data(), 1, data.size());

	//std::copy(szBuff, szBuff + strlen(szBuff), data.begin());
	//std::copy(temp.begin(), temp.end(), data.begin());
	//system("pause");

// 	CInlineHook Hook((DWORD)::MessageBoxA, (DWORD)nakedPrivateChat,0);
// 	Hook.Hook();
// 	::MessageBoxA(NULL, "4124141", NULL, MB_OK);
	
// 	HWND hWnd = FindWindow(NULL, L"LUA_SHOW_DEBUG");
// 	//SetWindowPos(hWnd, HWND_TOP, -100, 0, 500, 800, SWP_NOSIZE);
// 	MoveWindow(hWnd, -100, 0, 500, 800, TRUE);

// 	size_t len = std::wstring(L"이런. 아이 하나 때문에 곤란을").length();
// 
// 	CLanguage & language = CLanguage::GetInstance();
// 	std::wstring s = language.GetOtherText_By_LocalText(L"부서진 칼날");


// 	DWORD dwPid = process_tool::GetPidFromExeName(L"wuxia_client.exe", NULL);
// 	HANDLE hProcess = ::OpenProcess(PROCESS_VM_OPERATION, FALSE, dwPid);
// 	process_tool::mem_inject::MemLoadLibraryA(R"(E:\code\InjectDll\Debug\InjectDllLib.dll)", hProcess);


// 	std::list<int> vlist = { 0, 1, 2, 3, 4, 5 };
// 
// 	auto iter_beg = vlist.begin();
// 	std::cout << *iter_beg << std::endl;
// 
// 	auto iter_n = std::next(iter_beg);
// 	std::cout << *iter_n << std::endl;
// 	std::cout << *iter_beg << std::endl;
// 	
// 	std::deque<int> test = { 0, 1, 2, 3, 4, 5 };
// 
// 	int * pInt = &test[3];
// 
// 	std::cout << *pInt << std::endl;
// 	test.erase(test.begin() + 2);
// 	std::cout << *pInt << std::endl;
// 	test.erase(test.begin() + 2);
// 	std::cout << *pInt << std::endl;

	wchar_t value[MAX_PATH] = { 0 };
	wcscpy_s(value, L"vasfsfasdfsadfs");

	HKEY hKey = NULL;
	DWORD dwVal = 0;
	LONG lnRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Zds\\Hosp", 0, NULL, NULL, KEY_ALL_ACCESS, NULL, &hKey, &dwVal);
	if (lnRes == ERROR_SUCCESS)
	{

	}

	wchar_t msg_buffer[MAX_PATH] = { 0 };
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, lnRes, 0, msg_buffer, MAX_PATH, NULL);



	lnRes = RegSetValueEx(hKey,
		L"PC_UUID",
		0,
		REG_SZ,
		(CONST BYTE*)value,
		_tcslen(value) * sizeof(TCHAR));
	RegCloseKey(hKey);


	system("pause");
	return 0;
}

