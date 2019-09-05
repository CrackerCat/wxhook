/*-----------------------------------------------------------------------
��12��  ע�뼼��
����������ܣ����İ棩��
(c)  ��ѩѧԺ www.kanxue.com 2000-2018
-----------------------------------------------------------------------*/

// MsgDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
#define ReciveMessage 0x315E98			//������Ϣ
#define ReciveMessageParam 0x126D7F8		//������Ϣ�Ĳ���ƫ��
#define LoginSign_Offset 0x126D860		//��½��־λ
//��Ϣ�ṹ��
struct Message
{
	wchar_t type[10];		//��Ϣ����
	wchar_t source[20];		//��Ϣ��Դ
	wchar_t wxid[40];		//΢��ID/ȺID
	wchar_t msgSender[40];	//��Ϣ������
	wchar_t content[200];	//��Ϣ����
};



typedef unsigned long       DWORD;

VOID Msg();

void GetInformation();
void InitWindow(HMODULE hModule);
void WriteLog(char *info,char *logfilename);

BOOL APIENTRY DllMain(HMODULE hModule,
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)InitWindow, hModule,0,NULL);
	}
    return TRUE;
}

//************************************************************
// ��������: RegisterWindow
// ����˵��: ע�ᴰ��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: HMODULE hModule ���ھ��
// �� �� ֵ: void 
//************************************************************
void InitWindow(HMODULE hModule)
{
	
		Sleep(5000);
		//��ȡWeChatWin�Ļ�ַ
		DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle("WeChatWin.dll");

		//���΢���Ƿ��½
		DWORD dwIsLogin = dwWeChatWinAddr + LoginSign_Offset + 0x194;
		if (*(DWORD*)dwIsLogin == 0)	//����0˵��΢��δ��¼
		{
			
			GetInformation();
			
			
		}
	
	

}


void WriteLog(char *info,char *logfilename)
{
	HANDLE	hFile;
	static char	tmp[100];
	DWORD	dwwritten=0;
	static SYSTEMTIME systime;
	GetLocalTime(&systime);
	sprintf(tmp,"%04dd-%02d-%02d %02d:%02d:%02d  ",systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);
	hFile=CreateFile(logfilename,GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(INVALID_HANDLE_VALUE!=hFile) 
	{
		SetFilePointer(hFile,0,0,SEEK_END);
		WriteFile(hFile,tmp,lstrlen(tmp),&dwwritten,NULL);
		WriteFile(hFile,info,lstrlen(info),&dwwritten,NULL);
		WriteFile(hFile,"\r\n",2,&dwwritten,NULL);
		CloseHandle(hFile);
	}
}


void GetInformation()
{	
	//�ǳƣ�WeChatWin.dll + 126D91C
	//΢���˺ţ�WeChatWin.dll + 126DA80
	//�ֻ��ţ�WeChatWin.dll + 126d950
	//��½�豸��WeChatWin.dll + 126DD48
	//������WeChatWin.dll + 126DAF8
	//ʡ�ݣ�WeChatWin.dll + 126DA08
	//���У�WeChatWin.dll + 126DA20
	//ͷ��ָ�룺WeChatWin.dll + 126DBE4
	//΢��IDָ�룺WeChatWin.dll + 126D8A4
	//�Ա�WeChatWin.dll+126DA04

	//��ȡWeChatWin�Ļ�ַ
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle("WeChatWin.dll");

	//΢��ID
	//char wxid[0x1000] = { 0 };
	//DWORD pWxid = dwWeChatWinAddr + 0x126D8A4;
	//sprintf_s(wxid, "%s", (char*)(*(DWORD*)pWxid));
	//if (strlen(wxid) < 40)
	//{
	//	WriteLog(wxid, "info.log");
	//}
	//else
	//{
	//	WriteLog(wxid, "info.log");
	//}
	//
	//

	////΢���Ա�
	//char sex[0x1000] = { 0 };
	//memcpy(sex, (void*)(dwWeChatWinAddr + 0x126DA04), 1);

	//if (sex[0] == 1)
	//{
	//	WriteLog("��","info.log");
	//}
	//if (sex[0] == 2)
	//{
	//	WriteLog("Ů","info.log");
	//}

	////΢���ǳ�
	//char nickname[0x1000] = { 0 };
	//sprintf_s(nickname, "%s", (char*)(dwWeChatWinAddr + 0x126D91C));
	//WriteLog(nickname,"info.log");
	

	//΢���˺�
	/*char wxcount[0x1000] = { 0 };
	sprintf_s(wxcount, "%s", (char*)(dwWeChatWinAddr + 0x126DA80));
	WriteLog(wxcount,"info.log");*/

	//�ֻ���
	char phone[0x1000] = { 0 };
	sprintf_s(phone, "%s", (char*)(dwWeChatWinAddr + 0x126d950));
	WriteLog(phone, "info.log");

	////��½�豸
	//char device[0x1000] = { 0 };
	//sprintf_s(device, "%s", (char*)(dwWeChatWinAddr + 0x126DD48));
	//WriteLog(device, "info.log");

	////����
	//char nation[0x1000] = { 0 };
	//sprintf_s(nation, "%s", (char*)(dwWeChatWinAddr + 0x126DAF8));
	//WriteLog(nation, "info.log");

	////ʡ��
	//char province[0x1000] = { 0 };
	//sprintf_s(province, "%s", (char*)(dwWeChatWinAddr + 0x126DA08));
	//WriteLog(province, "info.log");

	////����
	//char city[0x1000] = { 0 };
	//sprintf_s(city, "%s", (char*)(dwWeChatWinAddr + 0x126DA20));
	//WriteLog(city, "info.log");


	////ͷ��
	//char header[0x1000] = { 0 };
	//DWORD pHeader = dwWeChatWinAddr + 0x126DBE4;
	//sprintf_s(header, "%s", (char*)(*(DWORD*)pHeader));
	//WriteLog(header, "info.log");

}

//��������
VOID Msg()
{

}