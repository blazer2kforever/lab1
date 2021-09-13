#include <windows.h>
#include <stdio.h>

/* P.S. � ����� ��� ������� ������,
�� � ����� ������� ��������� ������
� ������������ ������� ������� �������
��� ����������� ������� � ������.
�� ��� ������ �����-����� ������� ��� ���������� 
(� ���� ���� ������ �����)
*/

#define programName "SGN3-13B : Vasilyev F.D. : lab1.1" // �������� ���������, �������� ����� ���������� ��������� ������� 
#define visualMode TRUE // ��������� ��� ���������, ���������� ������ ���������� ���������
#define randomNumber TRUE // ��������� ��� ���������, ���������� ������ ��������� ��������� �������� ��� �����

#define lowerText "Point is below the line" // 3 ��������� ��� ������ ������
#define higherText "Point is above the line"
#define onTheLineText "Point is on the line"

/* ���������� �������, �������������� ��� ������ ���������
����������� �� ������ �� �������� � ������ ��������� � ���� ����� ������� */
float printAndScan(char* text);
HDC setupConsoleGraphics(HDC hDC, char* consoleTitle);
void drawCoordSystem(HDC hDC, boolean numberVisibility);
void drawLine(HDC hDC, int x1, int y1, int x2, int y2);
void drawPoint(HDC hDC, int x, int y, int thickness);

int main()
{
    HDC hDC = 0; // Device context handle; ��� ��������� ����� WinAPI

    float x1 = 0, y1 = 0,   // ���������� ������ ����� ������
        x2 = -0, y2 = 0,    // ���������� ������ ����� ������
        x3 = 0, y3 = 0;     // ���������� ������� �����

    hDC = setupConsoleGraphics(hDC, programName); // ������������� hDC � ��������� ������, �������� � �.�.

    if (randomNumber) // ���� ������� ����� ���������� �������������, �� ��������� ���������� �������� �� ������� rand() �� -60 �� 60 (��� �����������)
    {
        srand(time(NULL)); // ������������� ������� ���� ��� "����" ����������������� ����������
        x1 = -60 + rand() % 60;
        y1 = -60 + rand() % 60;
        x2 = -60 + rand() % 60;
        y2 = -60 + rand() % 60;
        x3 = -60 + rand() % 60;
        y3 = -60 + rand() % 60;
    }
    else //���� �� ����� ���������� ������������� ��������, �� �������� �������� � ���������� � ������� ������� printAndScan()
    {
        x1 = printAndScan("Enter x1 value: ");
        y1 = printAndScan("Enter y1 value: ");
        x2 = printAndScan("Enter x2 value: ");
        y2 = printAndScan("Enter y2 value: ");
        x3 = printAndScan("Enter x2 value: ");
        y3 = printAndScan("Enter y3 value: ");
    }

    // ����� ��������� ���� ��� �����
    printf("First point: (%.0f, %.0f);\n", x1, y1);
    printf("Second point: (%.0f, %.0f);\n", x2, y2);
    printf("Third point: (%.0f, %.0f);\n", x3, y3);

    /* ������ �������� �� ������� f(x) = kx + b;
    ����� ������ ������������ �������, ���������� ����� k � b, �������� �� �� �������� �������� ���������;
    ����� �������������� �� ������, ���������� ��������� ���������: k = (y2 - y1) / (x2 - x1); b = y1 - k * x1;
    ������ ��� ����������� � ����
    */

    if (x1 == x2 && y1 == y2) // ��� ���������� ���������� ��������� ���� �����
    {
        printf("Error: can't build a line (point1 = point2)\n");
        Sleep(1500);
        return;
    }

    if ((x2 - x1) == 0) // ��� ���������� ������� �� ����
    {
        printf("Error: can't divide by zero\n");
        Sleep(1500);
        return;
    } 

    float k = (y2 - y1) / (x2 - x1);
    float b = y1 - k * x1;

    printf("k: %.5f; b: %.5f", k, b); // ����� k � b
    Sleep(1000);

    while (TRUE) { // ����������� ���� ��� ������ ���������� ���������

        if (y3 < k * x3 + b) // ���� �������� ������� ����� ���� ����������� � ������
        {
            TextOut(hDC, 25, 100, lowerText, sizeof(lowerText));
        }

        else if (y3 > k * x3 + b) // ���� �������� ������� ����� ���� ����������� � ������
        {
            TextOut(hDC, 25, 100, higherText, sizeof(higherText));
        }

        // ������ �� ����������, � ��������� ������ ����� �������� �� ������
        else TextOut(hDC, 25, 100, onTheLineText, sizeof(onTheLineText));

        // ^^^ 
        // ||| ��� ������ ������ ������������ WinAPI ������� TextOut()

        if (visualMode) { // ���� ������� ����� ��������� ���������, �� ����������� ��������� �������
            
            drawCoordSystem(hDC, TRUE); // ������ ������� ���������, ������ �������� �������� �� ����������� ����������� ������������ �������

            // "������" ������������ ��� ������ ��� ������������, �� ����� ������� �������� (��� �����������)

            // ���������� ������ ����� ��� ���������� ������
            float lineX1 = -500;
            float lineY1 = k * lineX1 + b;
            
            // ���������� ������ ����� ��� ���������� ������
            float lineX2 = 500;
            float lineY2 = k * lineX2 + b;

            drawLine(hDC, lineX1, lineY1, lineX2, lineY2);

            // ��������� ������ ���� �����, ���������� ������
            drawPoint(hDC, x1, y1, 4);
            drawPoint(hDC, x2, y2, 4);

            // ��������� ������� �����
            drawPoint(hDC, x3, y3, 4);

        }

        Sleep(60); // �������� 60 �� ��� �����������
    }

    return 0;
}

float printAndScan(char* text) // ������� ��� ����������� ����� � ������ ��������� �����
{
    float value;
    printf("%s", text);
    scanf("%f", &value);
    system("cls");
    return value;
}

HDC setupConsoleGraphics(HDC hDC, char* consoleTitle) // ������������� ����������� ������������ �� WinAPI
{
    TCHAR currentTitle[256];
    HPEN hPen;

    GetConsoleTitle(currentTitle, 256);
    hDC = GetDC(FindWindow(0, currentTitle)); // ���������� handl'� ��� ����������� ����
    hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    SelectObject(hDC, hPen);
    SetTextAlign(hDC, TA_LEFT | TA_NOUPDATECP);
    SetBkColor(hDC, RGB(0, 255, 0));
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));

    SetConsoleTitle(consoleTitle); // ��������� �������� ������� �� ���������
    return hDC;
}

/* ������� ��� ���������� ������������ ������,
������� � �����(�� �������),
�� ��������� / ���������� �� ��������� �������� ������ ��������*/
void drawCoordSystem(HDC hDC, boolean numberVisibility)
{
    MoveToEx(hDC, 0, 400, NULL); // ������ ����� �������������� "������"
    LineTo(hDC, 1000, 400); // ������ ����� �������������� "������", � ������������ - ����������
    MoveToEx(hDC, 500, 0, NULL);
    LineTo(hDC, 500, 1000);

    for (int i = -500; i < 500; i++) // ����������� �������������� ���������������� ������� � �����
    {
        MoveToEx(hDC, 500 + 50 * i, 400 - 5, NULL);
        LineTo(hDC, 500 + 50 * i, 400 + 5);

        if (!numberVisibility) continue; // ���������� ���������� ���, ���� ��� ��� �� ����� 

        char buf = i * 10;
        char str[sizeof(int)] = { 0 };
        itoa(buf, str, 10);
        TextOut(hDC, 500 + 50 * i, 400 + 10, str, sizeof(str));
    }

    for (int i = -500; i < 500; i++) // ����������� ������������ ���������������� ������� � �����
    {
        MoveToEx(hDC, 500 - 5, 400 - 50 * i, NULL);
        LineTo(hDC, 500 + 5, 400 - 50 * i);

        if (!numberVisibility) continue; // ���������� ���������� ���, ���� ��� ��� �� ����� 

        if (i == 0) continue;
        char buf = i * 10;
        char str[sizeof(int)] = { 0 };
        itoa(buf, str, 10);
        TextOut(hDC, 500 + 10, 400 - 50 * i, str, sizeof(str));
    }
}

void drawLine(HDC hDC, int x1, int y1, int x2, int y2) // ������� ��� ��������� ��������� �����
{
    MoveToEx(hDC, 500 + x1 * 5, 400 - y1 * 5, NULL); // ������ ����� �������������� "������"
    LineTo(hDC, 500 + x2 * 5, 400 - y2 * 5); // ������ ����� �������������� "������"
}

void drawPoint(HDC hDC, int x, int y, int thickness) // ������� ��� ��������� ��������� �����, ������ �������� �������� �� ������� ��������������, ����������� "�����"
{
    Rectangle(hDC, 500 + x * 5 - thickness / 2, 400 - y * 5 - thickness / 2, 500 + x * 5 + thickness / 2, 400 - y * 5 + thickness / 2);
}
