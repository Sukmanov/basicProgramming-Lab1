#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "businessLogic.h"


#define STR_LENGTH 30


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    double mRead = CLEAR;
    double memoryCalc = CLEAR;
    int lastAction = CLEAR;

    QString getStringLabel();
    void setStringLabel(QString newLabel);
    void validationCalc(action temp);
    QString validationLabel (QString str);
    void statusWriteInLabel(bool status);
    void message(QString str);
    void connectDigits();

private slots:
    void onBtnDigitClicked(QString digit);
    void onBtnOperarionClicked(int sign);
    void onBtnClearClicked();
    void onBtnDotClicked();
    void onBtnPlusMinusClicked();
    void onBtnDelClicked();
    void onBtnEqulsClicked();
    void onBtnMRClicked();
    void onBtnMCClicked();
};
#endif // MAINWINDOW_H
