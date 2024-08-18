#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Mastermind");

    int labelCounter = 41;

    for (int i=0; i<10; i++){

        QString gpgc_labelName = QString("gpgcLabel_%1").arg(i+1);
        gpgcArray[i] = findChild<QLabel*>(gpgc_labelName);

        QString gc_labelName = QString("gcLabel_%1").arg(i+1);
        gcArray[i] = findChild<QLabel*>(gc_labelName);

        for (int j=0; j<4; j++){
            QString labelName = QString("square1_%1").arg(labelCounter);
            squares[i][j] = findChild<QLabel*>(labelName);
            labelCounter++;
        }
    }

    for (int i=1; i<9; i++)
    {
        QString buttonName = QString("colorPicker%1").arg(i);
        colorButtons[i-1] = findChild<QPushButton*>(buttonName);
        colorButtons[i-1]->setStyleSheet("background-color: " + colors[i-1] + ";");
    }

    for (int i=1; i<5; i++) {
        QString labelName = QString("codeSquare%1").arg(i);
        solutionLabelArray[i-1] = findChild<QLabel*>(labelName);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchColor(int i, int j, int colorNumber)
{
    squares[i][j]->setStyleSheet("background-color: " + colors[colorNumber] + ";");
}

bool mem(int vect[4], int n) {
    for (int i=0; i<4; i++) {
        if (n== vect[i]) {
            return true;
        }
    }

    return false;
}

void MainWindow::on_confirmButton_clicked()
{
    if (inputNumber == 4){
        compare();
        inputNumber = 0;
        for (int i=0; i<4; i++){
            guess[i]=0;
        }
    }
}


void MainWindow::on_canceButton_clicked()
{
    for (int i=0; i<4; i++){
        guess[i]=0;
        squares[turnNumber-1][i]->setStyleSheet("background-color: rgb(0, 0, 0);");
        pendingInput = true;
        inputNumber = 0;
    }
}


void MainWindow::buttonClick(int buttonNumber)
{
    if (!(mem(guess, buttonNumber))){
        guess[inputNumber] = buttonNumber;
        switchColor(turnNumber-1, inputNumber, buttonNumber-1);
        inputNumber++;

        if (inputNumber==4){
            ui->announcementLabel->setText("Confirm input");
            pendingInput = false;
        }
    }

    else {
        ui->announcementLabel->setText("You can't choose that color!");
    }
}

void randomColors(int code[4]) {
    int randInt = 0;
    srand(time(NULL));

    for (int i=0; i<4; i++) {
        while (mem(code, randInt)) {
            randInt = random()%8+1;
        }
        code[i] = randInt;
    }
}

void MainWindow::resetGame()
{
    ui->announcementLabel->setText("Pick a color");

    for (int i =0; i<4; i++) {
        code[i]=0;
    }
    randomColors(code);

    for (int i=0; i<10; i++){

        gpgcArray[i]->setText("");
        gcArray[i]->setText("");

        for (int j=0; j<4; j++){
            squares[i][j]->setStyleSheet("background-color: rgb(0, 0, 0)");
        }
    }

    for (int i=0; i<4; i++){
        solutionLabelArray[i]->setStyleSheet("background-color: rgb(0, 0, 0);");
    }

    gameOver = false;
    pendingInput = false;
    inputNumber = 0;
    turnNumber = 1;
}

void MainWindow::showCode()
{
    for (int i=0; i<4; i++){
        solutionLabelArray[i]->setStyleSheet("background-color: " + colors[code[i]-1] + ";");
    }
}

void MainWindow::compare()
{

    int gpgc=0, gc=0;  //goodPositionGoodColor and goodColor

    for (int i=0; i<4; i++) {
        if (code[i] == guess[i]) {
            gpgc++;
        }

        else if (mem(code, guess[i])) {
            gc++;
        }
    }

    if (gpgc == 4) {
        gameOver = true;
        ui->announcementLabel->setText("You won!");
        showCode();
    }

    else if (turnNumber == 10) {
        gameOver = true;
        ui->announcementLabel->setText("You lost.");
        showCode();
    }

    else {

         ui->announcementLabel->setText("Pick 4 colors");
         pendingInput = true;
         gpgcArray[turnNumber-1]->setText(QString::number(gpgc));
         gcArray[turnNumber-1]->setText(QString::number(gc));
         turnNumber++;
    }
}

void MainWindow::on_actionNew_Game_triggered()
{
    resetGame();

    ui->announcementLabel->setText("Pick 4 colors");

    pendingInput = true;
}


void MainWindow::on_colorPicker1_clicked()
{
    if (pendingInput) {
        buttonClick(1);
    }
}

void MainWindow::on_colorPicker2_clicked()
{
    if (pendingInput) {
        buttonClick(2);
    }
}

void MainWindow::on_colorPicker3_clicked()
{
    if (pendingInput) {
        buttonClick(3);
    }
}

void MainWindow::on_colorPicker4_clicked()
{
    if (pendingInput) {
        buttonClick(4);
    }
}

void MainWindow::on_colorPicker5_clicked()
{
    if (pendingInput) {
        buttonClick(5);
    }
}

void MainWindow::on_colorPicker6_clicked()
{
    if (pendingInput) {
        buttonClick(6);
    }
}

void MainWindow::on_colorPicker7_clicked()
{
    if (pendingInput) {
        buttonClick(7);
    }
}

void MainWindow::on_colorPicker8_clicked()
{
    if (pendingInput) {
        buttonClick(8);
    }
}



void MainWindow::on_actionDark_Mode_triggered(bool checked)
{
    if (checked){
        this->setStyleSheet("background-color: rgb(0, 0, 102)");
    }

    else {
        this->setStyleSheet("background-color: rgb(65, 121, 206)");
    }
}
