#define matrix vector<vector<int>>
#define stop_program { cout << "Некорректный ввод."; return 0; }

#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <windows.h>

using namespace std;

string FILE_NAME = "board.txt";

void genereateBoard(int width, int height, int letterCount)
{
    ofstream file(FILE_NAME);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
            file << (char)(rand() % letterCount + 'A') << " ";
        file << endl;
    }
}

matrix initBoard(int width, int height, char letterPicked)
{
    ifstream file(FILE_NAME);
    matrix board(height, vector<int>(width, 0));

    char tmp;
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
        {
            file >> tmp;
            if (tmp == letterPicked)
                board[x][y] = 1;
        }

    return board;
}

char lifeLevelSymbol(int lifeLevel)
{
    return (lifeLevel < 10) ? lifeLevel + 48 : 'A' + lifeLevel - 10;
}

void writeBoardToFile(matrix board)
{
    ofstream file(FILE_NAME, ios_base::app);

    file << endl;
    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[0].size(); y++)
            file << lifeLevelSymbol(board[x][y]) << " ";
        file << endl;
    }
}

vector<array<int, 2>> getNeighbors(int x0, int y0, int width, int height)
{
    vector<array<int, 2>> neighbors;

    for (int x = -1; x <= 1; x++)
        if (x0 + x >= 0 && x0 + x < width)
            for (int y = -1; y <= 1; y++)
                if (y0 + y >= 0 && y0 + y < height && (x != 0 || y != 0))
                    neighbors.push_back({ x0 + x, y0 + y });

    return neighbors;
}

matrix updateBoard(matrix board)
{
    int width = board.size(), height = board[0].size();
    matrix newBoard(height, vector<int>(width, 0));
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
        {
            vector<array<int, 2>> neighborsCoord = getNeighbors(x, y, width, height);
            int alive = 0;
            for (auto neighbor : neighborsCoord)
                if (board[neighbor[0]][neighbor[1]] != 0)
                    alive++;

            if (((alive == 2 && board[x][y] != 0) || alive == 3) && board[x][y] < 11)
                newBoard[x][y] = board[x][y] + 1;
        }
    return newBoard;
}

void printBoard(matrix board)
{
    cout << endl;
    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[0].size(); y++)
            cout << (board[x][y] != 0 ? lifeLevelSymbol(board[x][y]) : ' ') << " ";
        cout << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int letterCount;
    cout << "Введите, сколько букв использовать для генерации поля: ";
    cin >> letterCount;
    if (letterCount > 26 || letterCount < 1)
        stop_program

    int width, height;
    cout << "Введите длину и высоту поля: ";
    cin >> width >> height;
    genereateBoard(width, height, letterCount);

    char randomLetter = (rand() % letterCount) + 'A';
    matrix board = initBoard(width, height, randomLetter);
    writeBoardToFile(board);
    printBoard(board);

    int updateCount;
    cout << endl << "Введите количество ходов: ";
    cin >> updateCount;
    if (updateCount < 0)
        stop_program
        
    int delay;
    cout << "Введите время между обновлениями (в миллисекундах): ";
    cin >> delay;
    if (delay < 0)
        stop_program

    for (int i = 0; i < updateCount; i++)
    {
        board = updateBoard(board);
        writeBoardToFile(board);
        printBoard(board);
        Sleep(delay);
    }
}
