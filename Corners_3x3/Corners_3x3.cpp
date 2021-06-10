#include "pch.h"
#include "CornersManager.h"

int main()
{
    srand(time(nullptr));
    char a;
    setlocale(LC_ALL, "Russian");
        
    CornersManager manager;
    
    while (!manager.IsGameFinished())
    {
        manager.MakeMove();
    }
    
    cin >> a;
    return 0;
}
