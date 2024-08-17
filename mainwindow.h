#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_actionNew_Game_triggered();

    void on_colorPicker1_clicked();

    void on_colorPicker2_clicked();

    void on_colorPicker3_clicked();

    void on_colorPicker4_clicked();

    void on_colorPicker5_clicked();

    void on_colorPicker6_clicked();

    void on_colorPicker7_clicked();

    void on_colorPicker8_clicked();

    void on_confirmButton_clicked();

    void on_canceButton_clicked();

private:
    Ui::MainWindow *ui;
    void switchColor(int i, int j, int colorNumber);
    void compare();
    void buttonClick(int buttonNumber);

    QLabel* squares[10][4];
    QPushButton* colorButtons[8];
    QLabel* gpgcArray[10];
    QLabel* gcArray[10];

    int turnNumber = 1;
    int code[4];
    int guess[4];
    bool pendingInput = false;
    bool gameOver = true;
    int inputNumber = 0;

    QString colors[8] = {"rgb(255, 0, 0)",
                         "rgb(0, 0, 255)",
                         "rgb(0, 255, 0)",
                         "rgb(255, 0, 127)",
                         "rgb(255, 255, 51)",
                         "rgb(200, 200, 200)",
                         "rgb(255, 154, 0)",
                         "rgb(255, 255, 255)"};

    void resetGame();
};
#endif // MAINWINDOW_H
