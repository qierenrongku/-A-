// 哆啦A梦.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "哆啦A梦.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_A, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_A));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_A));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_A);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, holdpen;
	HBRUSH hBlueBrush,hRedBrush, hYellowBrush, holdBrush;
	POINT apt[128];
	static int cxClient, cyClient;



    switch (message)
    {
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...

			// 辅助线
			hPen = CreatePen(PS_DOT, 1, RGB(192, 192,192));
			holdpen = (HPEN)SelectObject(hdc, hPen);
			
			MoveToEx(hdc, cxClient / 2, 0, NULL);
			LineTo(hdc, cxClient / 2, cyClient);
			MoveToEx(hdc, 0, cyClient/2, NULL);
			LineTo(hdc, cxClient, cyClient/2);
			SelectObject(hdc, holdpen);

			//头部
			hBlueBrush = CreateSolidBrush(RGB(0, 159, 232));
			holdBrush = (HBRUSH) SelectObject(hdc, hBlueBrush);
			Ellipse(hdc, cxClient / 2 - 120, cyClient / 2 - 200, cxClient / 2 + 120, cyClient / 2 + 40);
			SelectObject(hdc, holdBrush);
			//脸 d=200
			Ellipse(hdc, cxClient / 2 - 100, cyClient / 2 - 160, cxClient / 2 + 100, cyClient / 2 + 40);
			//眼睛 
			Ellipse(hdc, cxClient / 2 - 50, cyClient / 2 - 180, cxClient / 2, cyClient / 2-120);//
			Ellipse(hdc, cxClient / 2 + 50, cyClient / 2 - 180, cxClient / 2, cyClient / 2-120);
			   //眼珠
			holdBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));
			Ellipse(hdc, cxClient / 2 - 20, cyClient / 2 - 160, cxClient / 2-5, cyClient / 2 - 140);//
			Ellipse(hdc, cxClient / 2 + 20, cyClient / 2 - 160, cxClient / 2+5, cyClient / 2 - 140);
			(HBRUSH)SelectObject(hdc, GetStockObject(WHITE_BRUSH));
			Ellipse(hdc, cxClient / 2 - 15, cyClient / 2 - 155, cxClient / 2 - 10, cyClient / 2 - 145);
			Ellipse(hdc, cxClient / 2 + 15, cyClient / 2 - 155, cxClient / 2 + 10, cyClient / 2 - 145);
			SelectObject(hdc, holdBrush);
			//鼻子
			hRedBrush=CreateSolidBrush(RGB(255, 0, 0));
			holdBrush= (HBRUSH)SelectObject(hdc, hRedBrush);
			Ellipse(hdc, cxClient / 2 - 10, cyClient / 2 - 135, cxClient / 2 + 10, cyClient / 2 - 115);
			MoveToEx(hdc, cxClient / 2, cyClient / 2 - 115,NULL);
			LineTo(hdc, cxClient / 2, cyClient / 2 - 30);
			SelectObject(hdc, holdBrush);
			//嘴巴
			Arc(hdc, cxClient / 2 - 70, cyClient / 2 - 120, cxClient / 2 + 70, cyClient / 2 - 30, cxClient / 2 - 60, cyClient / 2 - 50, cxClient / 2 + 60, cyClient / 2 - 50);
			//胡须
			MoveToEx(hdc, cxClient / 2 - 70, cyClient / 2 - 115, NULL);
			LineTo(hdc, cxClient / 2-20, cyClient / 2 - 100);
			MoveToEx(hdc, cxClient / 2 - 80, cyClient / 2 - 85, NULL);
			LineTo(hdc, cxClient / 2 - 20, cyClient / 2 - 85);
			MoveToEx(hdc, cxClient / 2 - 70, cyClient / 2 - 55, NULL);
			LineTo(hdc, cxClient / 2-20, cyClient / 2 - 70);


			MoveToEx(hdc, cxClient / 2 + 70, cyClient / 2 - 115, NULL);
			LineTo(hdc, cxClient / 2 + 20, cyClient / 2 -100);
			MoveToEx(hdc, cxClient / 2 + 80, cyClient / 2- 85, NULL);
			LineTo(hdc, cxClient / 2 + 20, cyClient / 2 - 85);
			MoveToEx(hdc, cxClient / 2 + 70, cyClient / 2 - 55, NULL);
			LineTo(hdc, cxClient / 2 + 20, cyClient / 2- 70);

			
			//身体
			holdBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
			Rectangle(hdc, cxClient / 2 - 90, cyClient / 2, cxClient / 2 + 90, cyClient / 2 + 150);
			SelectObject(hdc, holdBrush);
			//肚子
			Ellipse(hdc, cxClient / 2 - 70, cyClient / 2 - 20, cxClient / 2 +70, cyClient / 2 +120);
			hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
			holdpen = (HPEN)SelectObject(hdc, hPen);
			Arc(hdc, cxClient / 2 - 70, cyClient / 2 - 20, cxClient / 2 + 70, cyClient / 2 + 120, cxClient / +60, cyClient / 2 - 10, cxClient / 2 - 60, cyClient / 2 - 10);
			SelectObject(hdc, holdpen);
			//项圈
			holdBrush = (HBRUSH)SelectObject(hdc, hRedBrush);
			RoundRect(hdc, cxClient / 2 - 95,cyClient/2-5,cxClient/2+95,cyClient/2+10,20,20);
			SelectObject(hdc, holdBrush);
			//铃铛
			hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
			holdBrush = (HBRUSH)SelectObject(hdc, hYellowBrush);
			Ellipse(hdc, cxClient / 2 - 15, cyClient / 2, cxClient / 2 + 15, cyClient / 2 + 30);
			RoundRect(hdc, cxClient / 2 - 15, cyClient / 2 +10, cxClient / 2 + 15, cyClient / 2 + 15, 2, 2);
			SelectObject(hdc, hRedBrush);
			Ellipse(hdc, cxClient / 2 - 4, cyClient / 2+18, cxClient / 2 +4, cyClient / 2 + 26);
			MoveToEx(hdc, cxClient / 2-4, cyClient / 2 +26, NULL);
			LineTo(hdc, cxClient / 2 , cyClient / 2+30);
			SelectObject(hdc, holdBrush);
			//口袋
			Pie(hdc, cxClient / 2 - 50, cyClient / 2, cxClient / 2 + 50, cyClient / 2 + 100, cxClient / 2 - 50, cyClient / 2 + 50, cxClient / 2 + 50, cyClient / 2 + 50);
			//腿脚
			Pie(hdc, cxClient / 2 - 20, cyClient / 2+130, cxClient / 2 + 20, cyClient / 2 + 170, cxClient / 2+20, cyClient / 2 +150, cxClient / 2 - 20, cyClient / 2 + 150);
			hPen = CreatePen(PS_DOT, 2, RGB(255, 255, 255));
			holdpen = (HPEN)SelectObject(hdc, hPen);
			MoveToEx(hdc, cxClient / 2 - 20, cyClient / 2 +150, NULL);
			LineTo(hdc, cxClient / 2+20, cyClient / 2 + 150);
			SelectObject(hdc, holdpen);
			Ellipse(hdc, cxClient / 2 - 110, cyClient / 2 + 130, cxClient / 2 -10, cyClient / 2 + 170);
			Ellipse(hdc, cxClient / 2 + 110, cyClient / 2 + 130, cxClient / 2 + 10, cyClient / 2 + 170);
		    //援手
			holdBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
			apt[0].x = cxClient / 2 - 90;
			apt[0].y = cyClient / 2 + 10;
			apt[1].x = cxClient / 2 - 130;
			apt[1].y = cyClient / 2 +50;
			apt[2].x = cxClient / 2 - 110;
			apt[2].y = cyClient / 2 + 70;
			apt[3].x = cxClient / 2 - 90;
			apt[3].y = cyClient / 2 + 60;
			Polygon(hdc, apt, 4);
			SelectObject(hdc, holdBrush);
			Ellipse(hdc, cxClient / 2-150, cyClient / 2 +46, cxClient / 2 -110, cyClient / 2 + 86);
		   
			holdBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
			apt[0].x = cxClient / 2 +90;
			apt[0].y = cyClient / 2 + 10;
			apt[1].x = cxClient / 2 + 130;
			apt[1].y = cyClient / 2 + 50;
			apt[2].x = cxClient / 2 + 110;
			apt[2].y = cyClient / 2 + 70;
			apt[3].x = cxClient / 2 + 90;
			apt[3].y = cyClient / 2 + 60;
			Polygon(hdc, apt, 4);
			SelectObject(hdc, holdBrush);
			Ellipse(hdc, cxClient / 2 + 150, cyClient / 2 + 46, cxClient / 2 +110, cyClient / 2 + 86);

			hPen = CreatePen(PS_DOT, 2, RGB(0, 159, 232));
			holdpen = (HPEN)SelectObject(hdc, hPen);
			MoveToEx(hdc, cxClient / 2 - 90, cyClient / 2 + 10, NULL);
			LineTo(hdc, cxClient / 2 -90, cyClient / 2 + 50);
			MoveToEx(hdc, cxClient / 2 + 90, cyClient / 2 + 10, NULL);
			LineTo(hdc, cxClient / 2 + 90, cyClient / 2 + 50);
			SelectObject(hdc, holdpen);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
