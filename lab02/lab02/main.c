#include <windows.h>
#include <stdio.h>

/* P.S. Я помню про условие задачи,
но я решил немного усложнить работу
и организовать немного простой графики
для наглядности решения и ответа*/

//P.S. x2: Конкретно данная задачка у меня выполнена неправильно по условию, есть некоторые идею по исправлению, но не по реализации.

#define programName "SGN3-13B : Vasilyev F.D. : lab1.2" // Название программы, которому потом присвоится заголовок консоли
#define visualMode TRUE // Константа для включения, выключения режима визуальной отрисовки
#define randomNumber TRUE // Константа для включения, выключения режима генерации случайных значений для точек

/* Объявления функций, использоваемых для работы программы
Комментарии по поводу их значения и работы находятся в теле самих функций */
float printAndScan(char* text);
HDC setupConsoleGraphics(HDC hDC, char* consoleTitle);
void drawCoordSystem(HDC hDC, boolean numberVisibility);
void drawLine(HDC hDC, int x1, int y1, int x2, int y2);
void drawPoint(HDC hDC, int x, int y, int thickness);

int main()
{
    HDC hDC = 0; // Device context handle; Для отрисовки через WinAPI

    float x1 = -5, y1 = -7, // Координаты первой точки прямой
        x2 = -9, y2 = -22,    // Координаты второй точки прямой
        x3 = -18, y3 = -4,  // Координаты третьей точки
        x4 = 12, y4 = 15;  // Координаты четвёртой точки
    int sectorNumber = 0; // Номер сектора

    hDC = setupConsoleGraphics(hDC, programName); // Инициализация hDC и установка цветов, названия и т.д.

    if (randomNumber) // Если включен режим случайного генерирования, то значениям присвоятся значения из функции rand() от -25 до 25 (для наглядности)
    {
        srand(time(NULL)); // Использование текущей даты как "ключ" непредсказуемости результата
        x1 = -25 + rand() % 25;
        y1 = -25 + rand() % 25;
        x2 = -25 + rand() % 25;
        y2 = -25 + rand() % 25;
        x3 = -25 + rand() % 25;
        y3 = -25 + rand() % 25;
       // x4 = -25 + rand() % 25;
       // y4 = -25 + rand() % 25;
    }
    else //Если же режим случайного генерирования выключен, то значения вводятся с клавиатуры с помощью функции printAndScan()
    {
        x1 = printAndScan("Enter x1 value: ");
        y1 = printAndScan("Enter y1 value: ");
        x2 = printAndScan("Enter x2 value: ");
        y2 = printAndScan("Enter y2 value: ");
        x3 = printAndScan("Enter x2 value: ");
        y3 = printAndScan("Enter y3 value: ");
        x4 = printAndScan("Enter x4 value: ");
        y4 = printAndScan("Enter y4 value: ");
    }

    // Вывод координат всех четырёх точек
    printf("First point: (%.0f, %.0f);\n", x1, y1);
    printf("Second point: (%.0f, %.0f);\n", x2, y2);
    printf("Third point: (%.0f, %.0f);\n", x3, y3);
    printf("Fourth point : (% .0f, % .0f); \n", x4, y4);

    float k1 = (y2 - y1) / (x2 - x1);
    float b1 = y1 - k1 * x1;
    printf("k: %.5f; b: %.5f\n", k1, b1); // Вывод k1 и b1


    float k2 = (y3 - y2) / (x3 - x2);
    float b2 = y2 - k2 * x2;
    printf("k: %.5f; b: %.5f\n", k2, b2); // Вывод k2 и b2


    float k3 = (y1 - y3) / (x1 - x3);
    float b3 = y3 - k3 * x3;
    printf("k: %.5f; b: %.5f\n", k3, b3); // Вывод k3 и b3

    Sleep(1000);

    while (TRUE) { // Бесконечный цикл для работы визуальной отрисовки

        // Нахождение сектора путём сравнения "высоты" четвёртой точки и точки её проекции на прямую (прямые) 
        if (y4 < k2 * x4 + b2 && y4 > k3 * x4 + b3 && y4 > k1 * x4 + b1) sectorNumber = 5; //new
        if (y4 < k2 * x4 + b2 && y4 < k3 * x4 + b3 && y4 < k1 * x4 + b1) sectorNumber = 3; // new
        if (y4 > k2 * x4 + b2 && y4 < k3 * x4 + b3 && y4 < k1 * x4 + b1) sectorNumber = 2; // new
        if (y4 > k2 * x4 + b2 && y4 > k3 * x4 + b3 && y4 > k1 * x4 + b1) sectorNumber = 6; // ?
       /* ? */ if ((y4 < k2 * x4 + b2 && y4 > k3 * x4 + b3 && y4 < k1 * x4 + b1) || (y4 > k2 * x4 + b2 && y4 < k3 * x4 + b3 && y4 > k1 * x4 + b1)) sectorNumber = 7;
        if (y4 < k2 * x4 + b2 && y4 < k3 * x4 + b3 && y4 > k1 * x4 + b1) sectorNumber = 4; // new
        if (y4 > k2 * x4 + b2 && y4 > k3 * x4 + b3 && y4 < k1 * x4 + b1) sectorNumber = 1; // new

        // Если треугольник не построился или точка лежит на прямой
        if (sectorNumber == 0)
        {
            if (y4 == k1 * x4 + b1 || y4 == k2 * x4 + b2 || y4 == k3 * x4 + b3)
                printf("Error: point is on the line\n");
            else
                printf("Error: triangle does not exist\n");
            return;
        }

        char buf = sectorNumber;
        char str[sizeof(int)] = { 0 };
        itoa(buf, str, 10);
        TextOut(hDC, 25, 200, str, sizeof(str));
        // ^^^ 
        // ||| Для вывода ответа используется WinAPI функция TextOut()

        if (visualMode) { // Если включен режим визульной отрисовки, то выполняются следующие функции

            drawCoordSystem(hDC, TRUE); // Рисуем систему координат, второй аргумент отвечает на возможность отображения пронумеровки числами

            // Далее имплементирована отрисовка трёх линий по формуле f(x) = kx + b
            float firstLineX1 = -500;
            float firstLineY1 = k1 * firstLineX1 + b1;
            float firstLineX2 = 500;
            float firstLineY2 = k1 * firstLineX2 + b1;
            drawLine(hDC, firstLineX1, firstLineY1, firstLineX2, firstLineY2);

            float secondLineX1 = -500;
            float secondLineY1 = k2 * firstLineX1 + b2;
            float secondLineX2 = 500;
            float secondLineY2 = k2 * firstLineX2 + b2;
            drawLine(hDC, secondLineX1, secondLineY1, secondLineX2, secondLineY2);

            float thirdLineX1 = -500;
            float thirdLineY1 = k3 * firstLineX1 + b3;
            float thirdLineX2 = 500;
            float thirdLineY2 = k3 * firstLineX2 + b3;
            drawLine(hDC, thirdLineX1, thirdLineY1, thirdLineX2, thirdLineY2);

            // Отрисовка точек
            drawPoint(hDC, x1, y1, 4);
            drawPoint(hDC, x2, y2, 4);
            drawPoint(hDC, x3, y3, 4);
            drawPoint(hDC, x4, y4, 6);

            // Выделение сектора для наглядности
            for (int i = -100; i < 100; i++)
            {
                for (int j = -100; j < 100; j++)
                {
                    if (sectorNumber == 5) if (j < k2 * i + b2 && j > k3 * i + b3 && j > k1 * i + b1) TextOut(hDC, 500 + 5 * i, 400 - 5 * j, "-", sizeof("-")); // 1
                    if (sectorNumber == 3) if (j < k2 * i + b2 && j < k3 * i + b3 && j < k1 * i + b1) TextOut(hDC, 500 + 5 * i, 400 - 5 * j, "-", sizeof("-")); // 2
                    if (sectorNumber == 2) if (j > k2 * i + b2 && j < k3 * i + b3 && j < k1 * i + b1) TextOut(hDC, 500 + 5 * i, 400 - 5 * j, "-", sizeof("-")); // 3
                    if (sectorNumber == 6) if (j > k2 * i + b2 && j > k3 * i + b3 && j > k1 * i + b1) TextOut(hDC, 500 + 5 * i, 400 - 5 * j, "-", sizeof("-")); // 4
                    if (sectorNumber == 7) if ((j < k2 * i + b2 && j > k3 * i + b3 && j < k1 * i + b1) || (j > k2 * i + b2 && j < k3 * i + b3 && j > k1 * i + b1)) TextOut(hDC, 500 + 5 * i, 400 - 5 * j, "-", sizeof("-")); // 5
                    if (sectorNumber == 4) if (j < k2 * i + b2 && j < k3 * i + b3 && j > k1 * i + b1) TextOut(hDC, 500 + 5 * i, 400 - 5 * j, "-", sizeof("-")); // 6
                    if (sectorNumber == 1) if (j > k2 * i + b2 && j > k3 * i + b3 && j < k1 * i + b1) TextOut(hDC, 500 + 5 * i, 400 - 5 * j, "-", sizeof("-")); // 7
                }
            }
        }

        Sleep(60); // Задержка 60 мс для оптимизации
    }

    return 0;
}

float printAndScan(char* text) // Функция для упрощённого ввода и вывода координат точек
{
    float value;
    printf("%s", text);
    scanf("%f", &value);
    system("cls");
    return value;
}

HDC setupConsoleGraphics(HDC hDC, char* consoleTitle) // Инициализация графических инструментов из WinAPI
{
    TCHAR currentTitle[256];
    HPEN hPen;

    GetConsoleTitle(currentTitle, 256);
    hDC = GetDC(FindWindow(0, currentTitle)); // Нахождение handl'а для консольного окна
    hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    SelectObject(hDC, hPen);
    SetTextAlign(hDC, TA_LEFT | TA_NOUPDATECP);
    SetBkColor(hDC, RGB(0, 255, 0));
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));

    SetConsoleTitle(consoleTitle); // Установка названия консоли из константы
    return hDC;
}

/* Функция для построения координатных прямых,
рисочек и чисел(по желанию),
за включение / выключения их отрисовки отвечает второй аргумент*/
void drawCoordSystem(HDC hDC, boolean numberVisibility)
{
    MoveToEx(hDC, 0, 400, NULL); // Первая точка горизонтальной "прямой"
    LineTo(hDC, 1000, 400); // Вторая точка горизонтальной "прямой", с вертикальной - аналогично
    MoveToEx(hDC, 500, 0, NULL);
    LineTo(hDC, 500, 1000);

    for (int i = -500; i < 500; i++) // Расстановка горизонтальных перпендикулярных рисочек и чисел
    {
        MoveToEx(hDC, 500 + 50 * i, 400 - 5, NULL);
        LineTo(hDC, 500 + 50 * i, 400 + 5);

        if (!numberVisibility) continue; // Пропускаем дальнейший код, если нам это не нужно 

        char buf = i * 10;
        char str[sizeof(int)] = { 0 };
        itoa(buf, str, 10);
        TextOut(hDC, 500 + 50 * i, 400 + 10, str, sizeof(str));
    }

    for (int i = -500; i < 500; i++) // Расстановка вертикальных перпендикулярных рисочек и чисел
    {
        MoveToEx(hDC, 500 - 5, 400 - 50 * i, NULL);
        LineTo(hDC, 500 + 5, 400 - 50 * i);

        if (!numberVisibility) continue; // Пропускаем дальнейший код, если нам это не нужно 

        if (i == 0) continue;
        char buf = i * 10;
        char str[sizeof(int)] = { 0 };
        itoa(buf, str, 10);
        TextOut(hDC, 500 + 10, 400 - 50 * i, str, sizeof(str));
    }
}

void drawLine(HDC hDC, int x1, int y1, int x2, int y2) // Функция для упрощения отрисовки линий
{
    MoveToEx(hDC, 500 + x1 * 5, 400 - y1 * 5, NULL); // Первая точка горизонтальной "прямой"
    LineTo(hDC, 500 + x2 * 5, 400 - y2 * 5); // Вторая точка горизонтальной "прямой"
}

void drawPoint(HDC hDC, int x, int y, int thickness) // Функция для упрощения отрисовки точек, второй аргумент отвечает за толщину прямоугольника, образующего "точку"
{
    Rectangle(hDC, 500 + x * 5 - thickness / 2, 400 - y * 5 - thickness / 2, 500 + x * 5 + thickness / 2, 400 - y * 5 + thickness / 2);
}
