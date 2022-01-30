#include "mainwindow.h"

#include "Game.h"
#include <tesseract/

#include <QApplication>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{

    Game game(2);

    game.PrintBoard();
    cout << endl;

    QApplication a(argc, argv);
    MainWindow w(&game);
    w.show();
    return a.exec();
}
