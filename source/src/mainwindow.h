#pragma once

#include <QMainWindow>


namespace Ui
{
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionLoad_Scene_triggered();
    void slot_ResizeToCamera(int,int);

    void on_actionRender_triggered();

    void on_actionCamera_Controls_triggered();

private:
    Ui::MainWindow *ui;
};
