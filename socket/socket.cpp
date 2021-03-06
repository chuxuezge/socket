// socket.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
/*
		v1.0
*/
//

#include "pch.h"
#include <stdio.h>  
#include<iostream>
#include <winsock2.h>  
#include <stdlib.h>
#include <atlstr.h>
#include <windows.h>
#include <shellapi.h>
#include<fstream>
#include<string>
#include<thread>
#include<time.h>
#include "json.hpp"
#include"base64.h"
#define DATA_SIZE 10000 //这个数根据需要写
using json = nlohmann::json;
//using namespace std;
#pragma comment(lib,"ws2_32.lib")	//把ws2_32.lib加到Link页的连接库  
#define PORT 15001					//通信的端口（指服务器端）
#define ERROR 0  
#define BUFFER_SIZE 10	

/*
		全局变量，线程的标志位。
*/
bool hd_status0 = TRUE;
bool hd_status1 = TRUE;
bool hd_status2 = TRUE;
bool hd_status3 = TRUE;


void keyinput1(int keyvalue) {
	INPUT input[2];
	memset(input, 0, sizeof(input));
	//按下 向下方向键
	input[0].ki.wVk = keyvalue;
	input[0].type = INPUT_KEYBOARD;
	//松开 向下方向键
	input[1].ki.wVk = keyvalue;
	input[1].type = INPUT_KEYBOARD;
	input[1].ki.dwFlags = KEYEVENTF_KEYUP;
	//该函数合成键盘事件和鼠标事件，用来模拟鼠标或者键盘操作。事件将被插入在鼠标或者键盘处理队列里面
	SendInput(2, input, sizeof(INPUT));
}
void keyinput2(std::string temp) {
	int i = 0;
	while (i < temp.length()) {
		switch (temp[i])
		{
		case '0':
			/*keybd_event(0x30, 0, 0, 0);
			keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);*/
			keyinput1(0x30);
			Sleep(50);
			break;
		case '1':
			/*keybd_event(0x31, 0, 0, 0);
			keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);*/
			keyinput1(0x31);
			Sleep(50);
			break;
		case '2':
			/*keybd_event(0x32, 0, 0, 0);
			keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);*/
			keyinput1(0x32);
			Sleep(50);
			break;
		case '3':
			keyinput1(0x33);
			Sleep(50);
			break;
		case '4':
			keyinput1(0x34);
			Sleep(50);
			break;
		case '5':
			keyinput1(0x35);
			Sleep(50);
			break;
		case '6':
			keyinput1(0x36);
			Sleep(50);
			break;
		case '7':
			keyinput1(0x37);
			Sleep(50);
			break;
		case '8':
			keyinput1(0x38);
			Sleep(50);
			break;
		case '9':
			keyinput1(0x39);
			Sleep(50);
			break;
		case 'O':
			keyinput1(VK_BACK);
			Sleep(50);
			break;
			/*case 'X':
			keybd_event(0x33, 0, 0, 0);
			keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
			case 'A':
			keybd_event(0x33, 0, 0, 0);
			keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
			break;*/


		default:
			break;
		}
		i++;
	}
}
std::string getTime()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d", localtime(&timep));
	return tmp;
}
int mousemove(int x, int y) {
	::SetCursorPos(x, y);
	//mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(30);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	return 0;
}
std::string getIDCard()
{
	std::ifstream ifle;
	std::string temp = "0000000000000000000000000000000000000";
	std::string IDCard = "000000000000000000";
	//std::string tiem = "2018-9-26";
	std::cout << "2018-9-26" << "success" << std::endl;
	std::string tiem = getTime();//C:\Program Files\AuditRealNameMain\Logs\2018-10-23\\XinZhongXin_DKQ-116D.log
	std::cout << tiem << "success" << std::endl;
	std::string IDCardroute = "C:\\Program Files\\AuditRealNameMain\\Logs\\" + tiem + "\\XinZhongXin_DKQ-116D.log";
	std::cout << IDCardroute << "success" << std::endl;
	ifle.open(IDCardroute);

	std::string pfile, ppre;
	ifle >> ppre;
	while (!ifle.eof()) {
		/*pfile = ppre;*/
		pfile = ppre;
		ifle >> ppre;
	}
	ifle.close();
	std::cout << pfile << std::endl;
	//获得数字
	int j = 0;
	std::cout << "before length" << "success" << std::endl;
	for (int i = 0; i < pfile.length(); i++) {
		if (pfile[i] >= '0'&&pfile[i] <= '9'|| pfile[i]=='X'|| pfile[i] == 'Y') {
			temp[j] = pfile[i];
			j++;
		}
	}
	//获得身份证号
	for (int x = 0; x < IDCard.length(); x++) {
		IDCard[x] = temp[x + 1];
	}
	std::cout << IDCard << std::endl;
	return IDCard;
}
void closeit() {
	while (1) {
		if (hd_status0 ==TRUE) {
			HWND hd1 = FindWindow(NULL, "人脸比对结果");
			HWND hd2 = FindWindow(NULL, "激活临时卡");
			HWND hd3 = FindWindow(NULL, "添加会员");
			HWND hd4 = FindWindow(NULL, "激活会员卡");
			HWND hd5 = FindWindow(NULL, "客户机管理");
			SendMessage(hd1, WM_CLOSE, 0, 0);
			SendMessage(hd2, WM_CLOSE, 0, 0);
			SendMessage(hd3, WM_CLOSE, 0, 0);
			SendMessage(hd4, WM_CLOSE, 0, 0);
			SendMessage(hd5, WM_CLOSE, 0, 0);
		}
		
	}
	
}
void activeit(SOCKET msgsock) {
	while (hd_status1) {

		HWND hd1 = FindWindow(NULL, "人脸比对结果");
		HWND hd2 = FindWindow(NULL, "激活临时卡");
		HWND hd3 = FindWindow(NULL, "添加会员");
		HWND hd4 = FindWindow(NULL, "激活会员卡");
		HWND hd5 = FindWindow(NULL, "客户机管理");
		int hd_case = 0;
		if (hd1 != NULL) {
			hd_case = 1;
			std::cout << "you zhege chuangkou" << "success" << std::endl;
		}
		if (hd2 != NULL) {
			hd_case = 2;
		}
		if (hd3 != NULL) {
			hd_case = 3;
		}
		if (hd4 != NULL) {
			hd_case = 4;
		}
		if (hd5 != NULL) {
			hd_case = 5;
		}
		switch (hd_case)
		{
		case 1: {
			//std::cout << 1 << std::endl;
			/*
			人脸比对窗口。这个窗口所做的事：
			1.发送图片 和身份证卡号,和指令“10”。告诉前台开始进行开户操作。
			1.点击确定
			*/
			std::cout << "enter hd1" << "success" << std::endl;
			FILE *fIn1;
			fIn1 = fopen("C:\\Program Files\\AuditRealNameMain\\Drv\\IDCard2Reader\\XinZhongXin\\tmp.jpg", "rb");

			if (fIn1 == NULL)
			{
				printf("打开读取文件失败");
			}

			std::cout << "open  pic " << "success" << std::endl;
			int nRead1;
			char chBuf1[DATA_SIZE];
			nRead1 = fread(chBuf1, sizeof(char), DATA_SIZE, fIn1);
			std::string imgBase64_1 = base64_encode(chBuf1, nRead1);
			fclose(fIn1);
			std::cout << "base pic " << "success" << std::endl;
			if (hd_status1 == TRUE) {
			json j;
			j["command"] = "10";
			j["idcard"] = getIDCard();
			j["img"] = imgBase64_1;
			std::string s = j.dump();
			s = s + "\n";
			const char *sendData = s.c_str();//还有头像传输
			//std::cout << s << std::endl;
			//std::cout << *sendData<< std::endl;
			/*std::ofstream vlog;
			vlog.open("pubwinlog_end.txt");
			vlog << s;
			vlog.close();*/
			send(msgsock, sendData, s.length(), 0);
			}
			
			int temp = 0;
			while (FindWindow(NULL, "人脸比对结果")) {
				mousemove(891, 695);
				temp++;
				if (temp == 10) {
					break;
				}
			}
			//mousemove(891, 695);
			std::cout << "do it" << "success" << std::endl;
			break;

		}

		case 2:
		{
			/*
			激活临时卡窗口。这个窗口所做的事：
			1.发送命令“12”，代表是临时卡。
			2.点击添加会员。
			*/
			//std::cout << 2 << std::endl;
			int temp = 0;
			while (FindWindow(NULL, "激活临时卡")) {
				mousemove(123, 426);
				temp++;
				if (temp == 10) {
					break;
				}
			}
			if (hd_status1 == TRUE) {
				json j;
				j["command"] = "12";
				std::string s = j.dump();
				s = s + "\n";
				const char *sendData = s.c_str();//还有头像传输
				std::cout << s << std::endl;
				//std::cout << *sendData<< std::endl;
				send(msgsock, sendData, s.length(), 0);
			}
			
			Sleep(100);

			break;
		}

		case 3:
		{
			/*
			添加会员窗口。这个窗口所做的事：
			1.填写会员密码
			2.点击确定
			3.发送命令“121”，代表添加会员成功
			4.退出这个连接。
			*/
			//std::cout << 3 << std::endl;
			//keyinput2("123456");
			//Sleep(100);
			mousemove(272, 149);
			Sleep(50);
			keybd_event(0x31, 0, 0, 0);
			keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			Sleep(2000);
			int temp = 0;
			while (FindWindow(NULL, "添加会员")) {
				mousemove(309, 598);
				temp++;
				if (temp == 10) {
					break;
				}
			}
			//mousemove(309, 598);
			if (hd_status1 == TRUE) {
				json j;
				j["command"] = "121";
				std::string s = j.dump();
				s = s + "\n";
				const char *sendData = s.c_str();//还有头像传输
				std::cout << s << std::endl;
				//std::cout << *sendData<< std::endl;
				send(msgsock, sendData, s.length(), 0);
			}
			
			hd_status1 = FALSE;

			break;
		}

		case 4:
		{
			/*
			激活会员窗口。这个窗口所做的事：
			1.发送命令“13”。代表是会员。
			2.等待前台发送人脸识别的结果，即接收前台发送的数据。
			3.接收前台发送的数据，并进行判断。
				3.1 人脸比对通过，点击确定。
					3.1.1退出循环。代表完成一个连接。hd_status1
				3.2人脸比对失败，点击取消。
			*/
			//std::cout << 3 << std::endl;
			if (hd_status1 == TRUE) {
				json j;
				j["command"] = "13";
				std::string s = j.dump();
				s = s + "\n";
				const char *sendData = s.c_str();//还有头像传输
				std::cout << s << std::endl;
				//std::cout << *sendData<< std::endl;
				send(msgsock, sendData, s.length(), 0);
			}
			
			/*int temp = 0;
			while (FindWindow(NULL, "激活会员卡")) {
				mousemove(447, 468);
				temp++;
				std::cout << temp << std::endl;
				if (temp == 10) {
					break;
				}
			}*/
			//mousemove(447, 468);
			hd_status1 = FALSE;

			break;
		}

		case 5: {
			/*
			客户机管理窗口：这个窗口所做的事：
			1.关闭结账窗口。
			2.发送命令“11”，代表已经开户。
			3.退出循环。代表完成一个连接。hd_status1
			*/
			SendMessage(hd5, WM_CLOSE, 0, 0);
			if (hd_status1 == TRUE) {
				json j;
				j["command"] = "11";
				std::string s = j.dump();
				const char *sendData = s.c_str();
				std::cout << s << std::endl;
				//std::cout << *sendData<< std::endl;
				send(msgsock, sendData, s.length(), 0);
			}
			
			hd_status1 = FALSE;

			break;
		}

		default:
			break;
		}


	}

}
void payit(SOCKET msgsock) {
	bool hd_status = hd_status2;
	while (hd_status) {
		HWND hd1 = FindWindow(NULL, "人脸比对结果");
		HWND hd2 = FindWindow(NULL, "激活临时卡");
		HWND hd3 = FindWindow(NULL, "添加会员");
		HWND hd4 = FindWindow(NULL, "激活会员卡");
		HWND hd5 = FindWindow(NULL, "客户机管理");
		int hd_case = 0;
		if (hd1 != NULL) {
			hd_case = 1;
		}
		if (hd2 != NULL) {
			hd_case = 2;
		}
		if (hd3 != NULL) {
			hd_case = 3;
		}
		if (hd4 != NULL) {
			hd_case = 4;
		}
		if (hd5 != NULL) {
			hd_case = 5;
		}
		switch (hd_case)
		{
		case 1: {

			/*
			人脸比对窗口。这个窗口所做的事：
			1.发送指令“21”。代表还未开户
			2.点击取消
			3.3.退出循环，代表处理完一个连接
			*/
			SendMessage(hd1, WM_CLOSE, 0, 0);
			if (hd_status2 == TRUE) {
				json j;
				j["command"] = "21";
				std::string s = j.dump();
				const char *sendData = s.c_str();
				//std::cout << s << std::endl;
				//std::cout << *sendData<< std::endl;
				send(msgsock, sendData, s.length(), 0);
				std::cout << "buf  2    hd1  success" << std::endl;
				hd_status = FALSE;
			}
			
			break;
		}

		case 2:
		{
			/*
			激活临时卡窗口。这个窗口所做的事：
			1.关闭窗口。
			2.发送指令“22”。代表完成结账。
			3.推出循环。
			*/
			SendMessage(hd2, WM_CLOSE, 0, 0);
			break;
		}

		case 3:
		{
			/*
			添加会员窗口。这个窗口所做的事：
			1.关闭窗口。
			*/
			std::cout << 3 << std::endl;
			SendMessage(hd3, WM_CLOSE, 0, 0);
			break;
		}

		case 4:
		{
			/*
			激活会员窗口。这个窗口所做的事：
			1.关闭窗口。
			*/
			SendMessage(hd4, WM_CLOSE, 0, 0);
			std::cout << 3 << std::endl;
			break;
		}

		case 5: {
			/*
			客户机管理窗口：这个窗口所做的事：
			1.点击确定。
			2.发送指令“22”。代表结账成功。
			3.退出循环，代表处理完一个连接
			*/
			ShowWindow(hd5, 9);
			int temp = 0;
			while (FindWindow(NULL, "客户机管理")) {
				mousemove(1145, 506);
				temp++;
				if (temp == 10) {
					break;
				}
			}
			if (hd_status2 == TRUE) {
				json j;
				j["command"] = "22";
				std::string s = j.dump();
				const char *sendData = s.c_str();
				//std::cout << s << std::endl;
				//std::cout << *sendData<< std::endl;
				send(msgsock, sendData, s.length(), 0);
				hd_status = FALSE;
			}	
			std::cout << "buf  2    hd2  success" << std::endl;
			break;
		}

		default:
			break;
		}
	}
}
void checkit_getpicture(SOCKET msgsock) {
	
	std::string str = getIDCard();
	CString cstr = str.c_str();
	//LPCSTR lpcstr = (LPCSTR)cstr;
		HINSTANCE hNewExe = ShellExecuteA(NULL, "open", "cutpic.exe", cstr, NULL, SW_HIDE);
		if ((DWORD)hNewExe <= 32)
		{
			printf("return value:%d\n", (DWORD)hNewExe);
		}
		else
		{
			std::cout << "success" << std::endl;
		}
		Sleep(2000);
		FILE *fIn1;
		fIn1 = fopen("1.jpg", "rb");

		if (fIn1 == NULL)
		{
			printf("打开读取文件失败");
		}

		std::cout << "open  pic " << "success" << std::endl;
		int nRead1;
		char chBuf1[DATA_SIZE];
		nRead1 = fread(chBuf1, sizeof(char), DATA_SIZE, fIn1);
		std::string imgBase64_1 = base64_encode(chBuf1, nRead1);
		fclose(fIn1);
		std::cout << "base pic " << "success" << std::endl;
		if (hd_status1 == TRUE) {
			json j;
			j["command"] = "10";
			j["idcard"] = getIDCard();
			j["img"] = imgBase64_1;
			std::string s = j.dump();
			s = s + "\n";
			const char *sendData = s.c_str();//还有头像传输
			//std::cout << s << std::endl;
			//std::cout << *sendData<< std::endl;
			send(msgsock, sendData, s.length(), 0);
		}
}
void checkit(SOCKET msgsock) {
	bool hd_status = hd_status3;
	while (hd_status) {
		HWND hd1 = FindWindow(NULL, "人脸比对结果");
		HWND hd2 = FindWindow(NULL, "激活临时卡");
		HWND hd3 = FindWindow(NULL, "添加会员");
		HWND hd4 = FindWindow(NULL, "激活会员卡");
		HWND hd5 = FindWindow(NULL, "客户机管理");
		int hd_case = 0;
		if (hd1 != NULL) {
			hd_case = 1;
		}
		if (hd2 != NULL) {
			hd_case = 2;
		}
		if (hd3 != NULL) {
			hd_case = 3;
		}
		if (hd4 != NULL) {
			hd_case = 4;
		}
		if (hd5 != NULL) {
			hd_case = 5;
		}
		switch (hd_case)
		{
		case 1: {
			std::cout << 1 << std::endl;
			/*
			人脸比对窗口。这个窗口所做的事：
			1.关闭窗口
			*/
			SendMessage(hd1, WM_CLOSE, 0, 0);
			checkit_getpicture( msgsock);
			std::cout << "hd1 success" << std::endl;
			hd_status = FALSE;
			break;
		}

		case 2:
		{
			/*
			激活临时卡窗口。这个窗口所做的事：
			1.关闭窗口；
			*/
			SendMessage(hd2, WM_CLOSE, 0, 0);
			break;
		}

		case 3:
		{
			/*
			添加会员窗口。这个窗口所做的事：
			1.关闭窗口。
			*/
			std::cout << 3 << std::endl;
			SendMessage(hd3, WM_CLOSE, 0, 0);
			break;
		}

		case 4:
		{
			/*
			激活会员窗口。这个窗口所做的事：
			1.关闭窗口。
			*/
			SendMessage(hd4, WM_CLOSE, 0, 0);
			std::cout << 3 << std::endl;
			break;
		}

		case 5: {
			/*
			客户机管理窗口：这个窗口所做的事：
			1.关闭窗口
			*/
			SendMessage(hd5, WM_CLOSE, 0, 0);
			checkit_getpicture(msgsock);
			std::cout << "hd5 success" << std::endl;
			hd_status = FALSE;
			break;
		}

		default:
			break;
		}

	}
}
int serversocket()
{
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 0), &WSAData) == SOCKET_ERROR)  //启动winsock ，WSAStartup()函数对Winsock DLL进行初始化
	{

		exit(1);
	}
	SOCKET sock;										//服务进程创建套接字句柄（用于监听）
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)		//调用socket()函数创建一个流套接字，参数（网络地址类型，套接字类型，网络协议）
	{

		WSACleanup();
		exit(1);
	}
	struct sockaddr_in ServerAddr;			//sockaddr_in结构用来标识TCP/IP协议下的地址，可强制转换为sockaddr结构
	ServerAddr.sin_family = AF_INET;			//sin_family字段必须设为AF_INET，表示该Socket处于Internet域
	ServerAddr.sin_port = htons(PORT);		//sin_port字段用于指定服务端口，注意避免冲突
	ServerAddr.sin_addr.s_addr = INADDR_ANY;  //sin_addr字段用于把一个IP地址保存为一个4字节的数，无符号长整型，根据不同用法还可表示本地或远程IP地址
	if (bind(sock, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)  //调用bind()函数将本地地址绑定到所创建的套接字上，以在网络上标识该套接字
	{

		closesocket(sock);
		WSACleanup();
		exit(1);
	}

	if (listen(sock, 10) == SOCKET_ERROR)		//调用listen()函数将套接字置入监听模式并准备接受连接请求，参数（已捆绑未连接的套接字描述字，正在等待连接的最大队列长度）
	{

		closesocket(sock);
		WSACleanup();
		exit(1);
	}

	SOCKET msgsock;			//创建一个新的套接字（用于接收accept函数的返回值，即表示已经接受的那个客户端的连接，进而接收Client发来的数据）
	char buf[BUFFER_SIZE];
	while (1)
	{
		if ((msgsock = accept(sock, (LPSOCKADDR)0, (int *)0)) == INVALID_SOCKET)  //进入监听状态后，调用accept()函数接收客户端的连接请求，并把连接传给msgsock套接字，原sock套接字继续监听其他客户机连接请求
		{
			

			continue; 
		}
		memset(buf, 0, sizeof(buf));
		recv(msgsock, buf, BUFFER_SIZE, 0);
		hd_status0 = FALSE;
		printf("客户端消息>%s\n", buf);  //接收客户端发送过来的数据  
		if (buf[0] == '1')
		{
			//bool hd_status = TRUE;
			//while (hd_status) {
			//	
			//	HWND hd1 = FindWindow(NULL, "人脸比对结果");
			//	HWND hd2 = FindWindow(NULL, "激活临时卡");
			//	HWND hd3 = FindWindow(NULL, "添加会员");
			//	HWND hd4 = FindWindow(NULL, "激活会员卡");
			//	HWND hd5 = FindWindow(NULL, "客户机管理");
			//	int hd_case = 0;
			//	if (hd1 != NULL) {
			//		hd_case = 1;
			//		std::cout << "you zhege chuangkou" << "success" << std::endl;
			//	}
			//	if (hd2 != NULL) {
			//		hd_case = 2;
			//	}
			//	if (hd3 != NULL) {
			//		hd_case = 3;
			//	}
			//	if (hd4 != NULL) {
			//		hd_case = 4;
			//	}
			//	if (hd5 != NULL) {
			//		hd_case = 5;
			//	}
			//	switch (hd_case)
			//	{
			//	case 1: {
			//		//std::cout << 1 << std::endl;
			//		/*
			//		人脸比对窗口。这个窗口所做的事：
			//		1.发送图片 和身份证卡号,和指令“10”。告诉前台开始进行开户操作。
			//		1.点击确定
			//		*/
			//		std::cout << "enter hd1" << "success" << std::endl;
			//		FILE *fIn1;
			//		fIn1 = fopen("C:\\Program Files\\AuditRealNameMain\\Drv\\IDCard2Reader\\XinZhongXin\\tmp.jpg", "rb");

			//		if (fIn1 == NULL)
			//		{
			//			printf("打开读取文件失败");
			//		}

			//		std::cout << "open  pic " << "success" << std::endl;
			//		int nRead1;
			//		char chBuf1[DATA_SIZE];
			//		nRead1 = fread(chBuf1, sizeof(char), DATA_SIZE, fIn1);
			//		std::string imgBase64_1 = base64_encode(chBuf1, nRead1);
			//		fclose(fIn1);
			//		std::cout << "base pic " << "success" << std::endl;
			//		json j;
			//		j["command"] = "10";
			//		j["idcard"] = getIDCard();
			//		j["imag"] = imgBase64_1;
			//		std::string s = j.dump();
			//		s = s + "\n";
			//		const char *sendData = s.c_str();//还有头像传输
			//		std::cout << s << std::endl;
			//		//std::cout << *sendData<< std::endl;
			//		send(msgsock, sendData, s.length(), 0);
			//		int temp = 0;
			//		while (FindWindow(NULL, "人脸比对结果")) {
			//			mousemove(891, 695);
			//			temp++;
			//			if (temp == 10) {
			//				break;
			//			}
			//		}
			//		mousemove(891, 695);
			//		std::cout << "do it" << "success" << std::endl;
			//		break;
			//		
			//	}
			//		
			//	case 2:
			//	{
			//		/*
			//		激活临时卡窗口。这个窗口所做的事：
			//		1.发送命令“12”，代表是临时卡。
			//		2.点击添加会员。
			//		*/
			//		//std::cout << 2 << std::endl;
			//		int temp = 0;
			//		while (FindWindow(NULL, "激活临时卡")) {
			//			mousemove(123, 426);
			//			temp++;
			//			if (temp == 10) {
			//				break;
			//			}
			//		}
			//		json j;
			//		j["command"] = "12";
			//		std::string s = j.dump();
			//		s = s + "\n";
			//		const char *sendData = s.c_str();//还有头像传输
			//		std::cout << s << std::endl;
			//		//std::cout << *sendData<< std::endl;
			//		send(msgsock, sendData, s.length(), 0);
			//		Sleep(100);
			//		
			//		break;
			//	}
			//		
			//	case 3:
			//	{
			//		/*
			//		添加会员窗口。这个窗口所做的事：
			//		1.填写会员密码
			//		2.点击确定
			//		3.发送命令“121”，代表添加会员成功
			//		4.退出这个连接。
			//		*/
			//		//std::cout << 3 << std::endl;
			//		//keyinput2("123456");
			//		keybd_event(0x31, 0, 0, 0);
			//		keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			//		Sleep(50);
			//		keybd_event(0x32, 0, 0, 0);
			//		keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
			//		Sleep(50);
			//		keybd_event(0x33, 0, 0, 0);
			//		keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
			//		Sleep(50);
			//		keybd_event(0x34, 0, 0, 0);
			//		keybd_event(0x34, 0, KEYEVENTF_KEYUP, 0);
			//		Sleep(50);
			//		keybd_event(0x35, 0, 0, 0);
			//		keybd_event(0x35, 0, KEYEVENTF_KEYUP, 0);
			//		Sleep(50);
			//		keybd_event(0x36, 0, 0, 0);
			//		keybd_event(0x36, 0, KEYEVENTF_KEYUP, 0);
			//		Sleep(50);
			//		//Sleep(100);
			//		int temp = 0;
			//		while (FindWindow(NULL, "添加会员")) {
			//			mousemove(309, 598);
			//			temp++;
			//			if (temp == 10) {
			//				break;
			//			}
			//		}
			//		//mousemove(309, 598);
			//		json j;
			//		j["command"] = "121";
			//		std::string s = j.dump();
			//		s = s + "\n";
			//		const char *sendData = s.c_str();//还有头像传输
			//		std::cout << s << std::endl;
			//		//std::cout << *sendData<< std::endl;
			//		send(msgsock, sendData, s.length(), 0);
			//		hd_status = FALSE;
			//		
			//		break;
			//	}
			//		
			//	case 4:
			//	{
			//		/*
			//		激活会员窗口。这个窗口所做的事：
			//		1.发送命令“13”。代表是会员。
			//		2.等待前台发送人脸识别的结果，即接收前台发送的数据。
			//		3.接收前台发送的数据，并进行判断。
			//			3.1 人脸比对通过，点击确定。
			//				3.1.1退出循环。代表完成一个连接。hd_status
			//			3.2人脸比对失败，点击取消。
			//		*/
			//		//std::cout << 3 << std::endl;
			//		json j;
			//		j["command"] = "13";
			//		std::string s = j.dump();
			//		s = s + "\n";
			//		const char *sendData = s.c_str();//还有头像传输
			//		std::cout << s << std::endl;
			//		//std::cout << *sendData<< std::endl;
			//		send(msgsock, sendData, s.length(), 0);
			//		//char buf1[BUFFER_SIZE];
			//		//memset(buf1, 0, sizeof(buf1));
			//		//recv(msgsock, buf1, BUFFER_SIZE, 0);
			//		//if (buf1[0] == '2') {
			//		//	SendMessage(hd4, WM_CLOSE, 0, 0);
			//		//}
			//		//if (buf1[0] == '1') {
			//		//	mousemove(447, 468);
			//		//	json j1;
			//		//	j1["command"] = "131";
			//		//	std::string s1 = j1.dump();
			//		//	s1 = s1 + "\n";
			//		//	const char *sendData = s1.c_str();//还有头像传输
			//		//	std::cout << s1 << std::endl;
			//		//	//std::cout << *sendData<< std::endl;
			//		//	send(msgsock, sendData, s1.length(), 0);
			//		//}
			//		int temp = 0;
			//		while (FindWindow(NULL, "激活会员卡")) {
			//			mousemove(447, 468);
			//			temp++;
			//			std::cout << temp << std::endl;
			//			if (temp == 10) {
			//				break;
			//			}
			//		}
			//		//mousemove(447, 468);
			//		hd_status = FALSE;
			//		
			//		break;
			//	}
			//		
			//	case 5: {
			//		/*
			//		客户机管理窗口：这个窗口所做的事：
			//		1.关闭结账窗口。
			//		2.发送命令“11”，代表已经开户。
			//		3.退出循环。代表完成一个连接。hd_status
			//		*/
			//		SendMessage(hd5, WM_CLOSE, 0, 0);
			//		json j;
			//		j["command"] = "11";
			//		std::string s = j.dump();
			//		const char *sendData = s.c_str();
			//		//std::cout << s << std::endl;
			//		//std::cout << *sendData<< std::endl;
			//		send(msgsock, sendData, s.length(), 0);
			//		hd_status = FALSE;
			//		
			//		break;
			//	}
			//		
			//	default:
			//		break;
			//	}

			//	
			//}
			hd_status1 = TRUE;
			std::thread t1(activeit, msgsock);
			t1.detach();
			
			char buf1[BUFFER_SIZE];
			memset(buf1, 0, sizeof(buf1));
			recv(msgsock, buf1, BUFFER_SIZE, 0);
			HWND hd1 = FindWindow(NULL, "人脸比对结果");
			HWND hd2 = FindWindow(NULL, "激活临时卡");
			HWND hd3 = FindWindow(NULL, "添加会员");
			HWND hd4 = FindWindow(NULL, "激活会员卡");
			HWND hd5 = FindWindow(NULL, "客户机管理");
			if (buf1[0] == '0') {
				hd_status1 = FALSE;
				SendMessage(hd1, WM_CLOSE, 0, 0);
				SendMessage(hd2, WM_CLOSE, 0, 0);
				SendMessage(hd3, WM_CLOSE, 0, 0);
				SendMessage(hd4, WM_CLOSE, 0, 0);
				SendMessage(hd5, WM_CLOSE, 0, 0);
			}
			if (buf1[0] == '1') {
				//mousemove(447, 468);
				int temp = 0;
			while (FindWindow(NULL, "激活会员卡")) {
				mousemove(447, 468);
				temp++;
				std::cout << temp << std::endl;
				if (temp == 10) {
					break;
				}
			}
				json j1;
				j1["command"] = "131";
				std::string s1 = j1.dump();
				s1 = s1 + "\n";
				const char *sendData = s1.c_str();//还有头像传输
				std::cout << s1 << std::endl;
				//std::cout << *sendData<< std::endl;
				send(msgsock, sendData, s1.length(), 0);
			}

		}
		/*

							结账界面处理函数
	
		*/
		if (buf[0] == '2')
		{
			hd_status2 = TRUE;
			std::thread t2(payit, msgsock);
			t2.detach();

			char buf1[BUFFER_SIZE];
			memset(buf1, 0, sizeof(buf1));
			recv(msgsock, buf1, BUFFER_SIZE, 0);
			HWND hd1 = FindWindow(NULL, "人脸比对结果");
			HWND hd2 = FindWindow(NULL, "激活临时卡");
			HWND hd3 = FindWindow(NULL, "添加会员");
			HWND hd4 = FindWindow(NULL, "激活会员卡");
			HWND hd5 = FindWindow(NULL, "客户机管理");
			if (buf1[0] == '0') {
				hd_status2 = FALSE;
				SendMessage(hd1, WM_CLOSE, 0, 0);
				SendMessage(hd2, WM_CLOSE, 0, 0);
				SendMessage(hd3, WM_CLOSE, 0, 0);
				SendMessage(hd4, WM_CLOSE, 0, 0);
				SendMessage(hd5, WM_CLOSE, 0, 0);
			}
			
		}
		/*

							查询处理函数

		*/
		if (buf[0] == '3')
		{
			hd_status3 = TRUE;
			std::thread t3(checkit, msgsock);
			t3.detach();

			char buf1[BUFFER_SIZE];
			memset(buf1, 0, sizeof(buf1));
			recv(msgsock, buf1, BUFFER_SIZE, 0);
			HWND hd1 = FindWindow(NULL, "人脸比对结果");
			HWND hd2 = FindWindow(NULL, "激活临时卡");
			HWND hd3 = FindWindow(NULL, "添加会员");
			HWND hd4 = FindWindow(NULL, "激活会员卡");
			HWND hd5 = FindWindow(NULL, "客户机管理");
			if (buf1[0] == '0') {
				hd_status3 = FALSE;
				SendMessage(hd1, WM_CLOSE, 0, 0);
				SendMessage(hd2, WM_CLOSE, 0, 0);
				SendMessage(hd3, WM_CLOSE, 0, 0);
				SendMessage(hd4, WM_CLOSE, 0, 0);
				SendMessage(hd5, WM_CLOSE, 0, 0);
			}
			
		}

		closesocket(msgsock);
		hd_status0 = TRUE;
	}

	//closesocket(sock); //关闭套接字  
	//WSACleanup();	   //终止对Winsock DLL的使用，并释放资源
	return 0;
}
int main() {
	std::thread t0(closeit);
	t0.detach();
	serversocket();
	return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
