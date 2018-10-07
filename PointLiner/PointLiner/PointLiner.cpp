// PointLiner.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include<Windows.h>
#include<stdlib.h>
#define M 5000

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE h1,
	               HINSTANCE hPrevInstance,
				   LPSTR CmdLine,
				   int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wc;

	wc.cbClsExtra=0;
	wc.cbSize=sizeof(WNDCLASSEX);
	wc.cbWndExtra=0;
	wc.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
	wc.hInstance=h1;
	wc.lpfnWndProc=WndProc;
	wc.lpszClassName=TEXT("c1");
	wc.lpszMenuName=NULL;
	wc.style=CS_HREDRAW|CS_VREDRAW;

	RegisterClassEx(&wc);

	hwnd=CreateWindow(TEXT("c1"),TEXT("Point Liner"),WS_OVERLAPPEDWINDOW,50,50,900,700,NULL,NULL,h1,NULL);
	ShowWindow(hwnd,SW_MAXIMIZE);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,NULL,0,0))
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND h,UINT m,WPARAM w,LPARAM l)
{
	HDC hdc;
	static int ic,x,y;
	static POINT p[M];
	int i,j;
	bool flag;
	PAINTSTRUCT ps;
	HPEN P;
	TCHAR buff[10];

	switch(m)
	{
	case WM_CREATE:
		MessageBox(NULL,TEXT("1.Click Left mouse button & drag to make design patterns.\n2.Click Right mouse button to erase the Canvas.\n\nEnjoy!!!"),TEXT("Instructions"),MB_OK);
		return 0;
	case WM_LBUTTONDOWN:
		ic=0;
		x=LOWORD(l);
		y=HIWORD(l);
		InvalidateRect(h,NULL,FALSE);
		return 0;

	case WM_RBUTTONDOWN:
		ic=0;
		InvalidateRect(h,NULL,TRUE);
	return 0;

	case WM_MOUSEMOVE:
		if(w & MK_LBUTTON && ic < 5000)
		{
			p[ic].x=LOWORD(l);
			p[ic++].y=HIWORD(l);
			hdc=GetDC(h);
			SetPixel(hdc,LOWORD(l),HIWORD(l),0);
			MoveToEx(hdc,x,y,NULL);
			LineTo(hdc,LOWORD(l),HIWORD(l));
			x=LOWORD(l);
			y=HIWORD(l);
		}
		wsprintf(buff,TEXT("%d"),ic);
		TextOut(hdc,20,20,TEXT("No. of points u used:"),21);
		TextOut(hdc,158,20,buff,4);
		ReleaseDC(h,hdc);
		return 0;

	case WM_LBUTTONUP:
		InvalidateRect(h,NULL,FALSE);
		return 0;

	case WM_PAINT:
		hdc=BeginPaint(h,&ps);

		SetCursor(LoadCursor(NULL,IDC_WAIT));
		ShowCursor(TRUE);
		for(i=0;i<ic-1;i++)
		{
			
			for(j=i+1;j<ic;j++)
			{
				P=CreatePen(1,1,RGB(rand()%255,rand()%255,rand()%255));
				SelectObject(hdc,P);
				MoveToEx(hdc,p[i].x,p[i].y,NULL);
				LineTo(hdc,p[j].x,p[j].y);
				SetPixel(hdc,i+j,j,RGB(rand()%255,0,0));
				TextOut(hdc,20,40,TEXT("No. of points while processing design:"),38);
				wsprintf(buff,TEXT("%d"),i);
		        TextOut(hdc,270,40,buff,4);
				DeleteObject(P);
			}
			
		}
		ShowCursor(FALSE);
		SetCursor(LoadCursor(NULL,IDC_ARROW));

		TextOut(hdc,20,60,TEXT("No. of points after completing Design:"),38);
		wsprintf(buff,TEXT("%d"),ic);
		TextOut(hdc,270,60,buff,4);

		EndPaint(h,&ps);

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;

	default:
		return DefWindowProc(h,m,w,l);

	}

	return 0;
}