#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qlabel.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QString str;
    bool isEmpty;
    double currentRes;
    int currentAction;
    Ui::MainWindow *ui;
    bool checkZero();
private slots:
    void NumbersClicked();
    void ButtonPlusClick();
    void ButtonClearClick();
    void ButtonResultClick();
    void ButtonMinusClicked();
    void ButtonUmnojClick();
    void ButtonDelClick();
    void ButtonPointClick();
    void AboutClick();
    void setLabel(QString value, QString * str);
};
#endif // MAINWINDOW_H
