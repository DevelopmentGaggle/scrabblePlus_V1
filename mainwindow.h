#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "Game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Game* game, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_change_turn_button_clicked();

    void on_undo_button_clicked();

    void on_undo_button_2_clicked();

private:
    void update_window();
    void update_player();

    Game *game;
    QGraphicsScene *graphic;
    Tile** board;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
