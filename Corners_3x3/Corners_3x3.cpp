#include "pch.h"
#include "CornersManager.h"

int main()
{
    char a;
    setlocale(LC_ALL, "Russian");
    CornersManager manager;
    manager.ShowBoard();

    cin >> a;
    return 0;
}
