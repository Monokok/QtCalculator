#include "mainwindow.h"
#include<QDebug>
#include "./ui_mainwindow.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("");
    str = "";
    currentRes = 0.0;
    isEmpty = true;
    //connect(that, SIGNAL(mySignal), this, SLOT(mySlot));
    //bool success = connect(ui->Button0, &QPushButton::clicked, this, SLOT(NumbersClicked));
    //кнопка - какой тригер - что привязываем - какой метод
    //Q_ASSERT(success);
    //connect(that, SIGNAL(mySignal), this, SLOT(mySlot));
    connect(ui->Button0, SIGNAL(clicked()), this, SLOT(NumbersClicked()));
    connect(ui->Button1, SIGNAL(clicked()), this, SLOT(NumbersClicked()));
    connect(ui->Button2, SIGNAL(clicked()), this, SLOT(NumbersClicked()));
    connect(ui->Button3, SIGNAL(clicked()), this, SLOT(NumbersClicked()));
    connect(ui->Button4, SIGNAL(clicked()), this, SLOT(NumbersClicked()));
    connect(ui->Button5, SIGNAL(clicked()), this, SLOT(NumbersClicked()));
    connect(ui->Button6, SIGNAL(clicked()), this, SLOT(NumbersClicked()));
    connect(ui->Button7, SIGNAL(clicked()), this, SLOT(NumbersClicked()));
    connect(ui->Button8, SIGNAL(clicked()), this, SLOT(NumbersClicked()));
    connect(ui->Button9, SIGNAL(clicked()), this, SLOT(NumbersClicked()));
    connect(ui->ButtonPlus, SIGNAL(clicked()), this, SLOT(ButtonPlusClick()));
    connect(ui->ButtonClear, SIGNAL(clicked()), this, SLOT(ButtonClearClick()));
    connect(ui->ButtonResult, SIGNAL(clicked()), this, SLOT(ButtonResultClick()));
    connect(ui->ButtonMinus, SIGNAL(clicked()), this, SLOT(ButtonMinusClicked()));
    connect(ui->ButtonUmnoj, SIGNAL(clicked()), this, SLOT(ButtonUmnojClick()));
    connect(ui->ButtonDel, SIGNAL(clicked()), this, SLOT(ButtonDelClick()));
    connect(ui->buttonPoint, SIGNAL(clicked()), this, SLOT(ButtonPointClick()));
    connect(ui->about, SIGNAL(triggered()), this, SLOT(AboutClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLabel(QString value, QString * str)
{
    (*str) += (value);/*QString::number*/
    ui->label->setText(*str);
}

void MainWindow::AboutClick()
{
    QMessageBox::about(this, "О программе", "Данная программа являет собой удобный кроссплатформенный\n\t\t\tкалькулятор.\n\t\t Пользуйтесь на здоровье!");
}

bool MainWindow::checkZero()
{
    if (str.length() == 1)//если набран 1 символ
    {
        if (str[0] == '0')
        return true;
        //и если этот символ 0 - мы не должны добавлять к нему ещё один.
        //т.е. не должно быть: 00, 01, 02, 03 ... 09
    }
    return false;
}

void MainWindow::ButtonClearClick()
{
    str.clear();
    isEmpty = true;
    ui->label->setText("");

}

void MainWindow::NumbersClicked()
{
    QPushButton *button = (QPushButton*) sender();

    if (checkZero()){}

    else setLabel(button->text(), &str);
}

void MainWindow::ButtonPlusClick()
{

    ButtonResultClick(); //выполнили предыдущую задачу что в очереди на выполнение
    currentRes = str.toDouble(); //занесли во вспом переменную
    currentAction = 1; //текущее действие на очереди выполнения = 1 ==== суммирование
    str = "";
    ui->label->setText("+");

}

void MainWindow::ButtonResultClick()
{//перед началом нового действия - выполнить предыдущее
    switch (currentAction)
    {
    case 0:
        //ничего
        break;
    case 1:
        //+
        currentRes += (ui->label->text().toDouble());
        str = QString::number(currentRes);
        ui->label->setText(str);
        currentAction = 0; //текущая задача для выполнения = 0 (ничего не требуется выполнять)
        break;
    case 2: //-


        currentRes -= (ui->label->text().toDouble());
        str = QString::number(currentRes);
        ui->label->setText(str);
        currentAction = 0; //текущая задача для выполнения = 0 (ничего не требуется выполнять)

        break;
    case 3://*
        currentRes *= (ui->label->text().toDouble());
        str = QString::number(currentRes);
        ui->label->setText(str);
        currentAction = 0; //текущая задача для выполнения = 0 (ничего не требуется выполнять)
        break;
    case 4://деление
        if (str.toDouble() == 0) // проверка деления на ноль
        {
            //ButtonClearClick();
            QMessageBox::warning(this, "Внимание!", "Ошибка деления на ноль!");
            ui->label->setText("");
            str = "";
            break;
        }
        else
        {
            currentRes /= (ui->label->text().toDouble());
            str = QString::number(currentRes);
            ui->label->setText(str);
            currentAction = 0; //текущая задача для выполнения = 0 (ничего не требуется выполнять)
        }

        break;
    default:
        break;
    }
}

void MainWindow::ButtonMinusClicked()
{
    if (currentAction == 3 || currentAction == 4) //если мы делим на отрицательное
    {
        // currentRes = str.toDouble(); //занесли во вспом переменную
        // currentAction = 2; //текущее действие на очереди выполнения = 2 ==== вычитание
        // str = "";
        ui->label->setText("-");
    }
    else
    {
        ButtonResultClick(); //выполнили предыдущую задачу что в очереди на выполнение
        currentRes = str.toDouble(); //занесли во вспом переменную
        currentAction = 2; //текущее действие на очереди выполнения = 2 ==== вычитание
        str = "";
        ui->label->setText("-");
    }
}

void MainWindow::ButtonUmnojClick()
{
    ButtonResultClick(); //выполнили предыдущую задачу что в очереди на выполнение
    currentRes = str.toDouble(); //занесли во вспом переменную
    currentAction = 3; //текущее действие на очереди выполнения = 3 ==== умножение
    str = "";
    ui->label->setText("×");
}

void MainWindow::ButtonDelClick()
{
    ButtonResultClick(); //выполнили предыдущую задачу что в очереди на выполнение
    currentRes = str.toDouble(); //занесли во вспом переменную
    currentAction = 4; //текущее действие на очереди выполнения = 4 ==== деление
    str = "";
    ui->label->setText("÷");
}

void MainWindow::ButtonPointClick()
{
    if (!str.contains("."))
    {
        str += '.';
        ui->label->setText(str);
    }
    else{
        QMessageBox::warning(this, "Внимание!", "Знак точки уже был введён!");
    }

}
