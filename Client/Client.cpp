// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "afxsock.h"
#include <cctype>
#include <cstring>
#include <cstdio>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {		
			// Khởi tạp thư viện
			if (AfxSocketInit() == 0) {
				cout << "Kết nối thư viện thất bại !!!";
					return FALSE;
			}
			
			// Tạo socket
			CSocket client;
			// 3// Khởi tạo Client
			client.Create();
			//3//Kết nối đến server
			if (client.Connect(_T("127.0.0.1"), 12319) != 0) {
				cout << "Server connected !!!" << endl << endl;

				char ClientMsg[100];
				int	MsgSize;
				char *temp;

				do {
					// 6 // Nhận độ dài thông điệp từ Server
					client.Receive((char*)&MsgSize, sizeof(int), 0);
					temp = new char[MsgSize + 1];
					// 6 // Nhận thông điệp từ Server
					client.Receive((char*)temp, MsgSize, 0);

					//In thông điệp
					temp[MsgSize] = 0;
					cout << "Server: " << temp << endl;

					// Viết tin nhắn, gửi tin nhắn
					cout << "Client: ";
					cin.getline(ClientMsg, 100);
					MsgSize = strlen(ClientMsg);


					// 7 //  gửi đi độ dài thông điệp để server biết được độ dài này
					client.Send(&MsgSize, sizeof(MsgSize), 0);
					// 7 // gửi thông điệp đi
					client.Send(ClientMsg, MsgSize, 0);
					delete temp;


				} while (1);
			}
			else {
				cout << "Không thể kết nối đến server !!!" << endl;

			}
			// 10 // đóng kết nối 
			client.Close();		
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
