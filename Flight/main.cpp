#include <windows.h>
#include <iostream>
#include "flight.h"
#include <cmath>
#include <mysql.h>
#include <mysqld_error.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	UcusYonetimSistemi kullanici;
	
	switch(Message) {
		
		case WM_CREATE: 
			kullanici.hosGeldin(hwnd);
			break;
		
		case WM_COMMAND:
            {
            	switch (LOWORD(wParam)){
            		case 101:
            			kullanici.personelGiris(hwnd);
                		break;
                	
                	case 102:
                		kullanici.personelGeri(hwnd);
                		break;
                	
                	case 103:
                		kullanici.personelKontrol(hwnd);
                		break;
                		
                	case 104:
                		kullanici.personelCikis(hwnd);
                		break;
                		
                	case 106:
					    kullanici.seferEkle(hwnd);
						break;	
					
					case 107:
						kullanici.ucusEkle(hwnd);
						kullanici.personelGeri2(hwnd);
						break;
						
					case 108:
						kullanici.personelGeri2(hwnd);
						break;
						
					case 109:
					    kullanici.ucuslariGoruntule(hwnd);
						break;
						
					case 110:
					    kullanici.musteriUcuslariGoruntule(hwnd);
						break;
						
					case 111:
					    kullanici.ucuslariGoruntuleGeri(hwnd);
						break;	
						
					case 112:
					    kullanici.ucusSil(hwnd);
					    break;
					    
					case 113:
					    kullanici.ucusSilKontrol(hwnd);
						break;    
					
                	case 201:
                		kullanici.musteriGiris(hwnd);
                		break;
                	
                	case 202:
                		kullanici.musteriGeri(hwnd);
                		break;
                		
                	case 203:
                		kullanici.musteriKontrol(hwnd);
                		break;
                		
                	case 204:
                		kullanici.musteriKayit(hwnd);
                		break;	
                		
                	case 205:
                		kullanici.musteriKayitGeri(hwnd);
                		break;
                	
                	case 206:
                		kullanici.musteriKayitOl(hwnd);
                		break;
                		
                	case 207:
                		kullanici.musteriCikis(hwnd);
                		break;
                	
					case 208:
					    kullanici.musteriBiletAl(hwnd);
					    break;
						
					case 209:
					    kullanici.musteriBiletAlKontrol(hwnd);		
                		break;
                		
                    case 210:
                    	kullanici.musteriBiletGoruntule(hwnd);
                    	break;
                    	
                    case 211:
					    kullanici.musteriBiletSil(hwnd);
						break;
						
					case 212:
					    kullanici.musteriBiletSilKontrol(hwnd);
						break;		
				}
           }
           break;
           
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_HAND);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(9, 154, 198));
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */ //LoadIcon(hInstance, MAKEINTRESOURCE(MyIcon)); 
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Ahiret Hava Yollari",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	//	UcusYonetimSistemi kullanici; 

	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
