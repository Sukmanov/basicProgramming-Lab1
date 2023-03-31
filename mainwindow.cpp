#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <string>
#include <iostream>
#include "businessLogic.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectDigits();
    connect(ui->btnPlus, &QPushButton::clicked, this, [this]{MainWindow::onBtnOperarionClicked(PLUS);});
    connect(ui->btnMinus, &QPushButton::clicked, this, [this]{MainWindow::onBtnOperarionClicked(MINUS);});
    connect(ui->btnMultiple, &QPushButton::clicked, this, [this]{MainWindow::onBtnOperarionClicked(MULTIPLY);});
    connect(ui->btnDiv, &QPushButton::clicked, this, [this]{MainWindow::onBtnOperarionClicked(DIVIDE);});

    connect(ui->btnSin, &QPushButton::clicked, this, [this]{MainWindow::onBtnOperarionClicked(SIN);});
    connect(ui->btnCos, &QPushButton::clicked, this, [this]{MainWindow::onBtnOperarionClicked(COS);});
    connect(ui->btnTan, &QPushButton::clicked, this, [this]{MainWindow::onBtnOperarionClicked(TAN);});
    connect(ui->btnCtan, &QPushButton::clicked, this, [this]{MainWindow::onBtnOperarionClicked(CTAN);});

    connect(ui->btn1x, &QPushButton::clicked, this, [this]{MainWindow::onBtnOperarionClicked(X1);});
    connect(ui->btnSqrt, &QPushButton::clicked, this, [this]{MainWindow::onBtnOperarionClicked(SQRT);});

    connect(ui->btnMPlus, &QPushButton::clicked, this, [this]{MainWindow::onBtnOperarionClicked(MPLUS);});
    connect(ui->btnMMinus, &QPushButton::clicked, this, [this]{MainWindow::onBtnOperarionClicked(MMINUS);});

    connect(ui->btnAC, &QPushButton::clicked, this, &MainWindow::onBtnClearClicked);
    connect(ui->btnDot, &QPushButton::clicked, this, &MainWindow::onBtnDotClicked);
    connect(ui->btnPlusMinus, &QPushButton::clicked, this, &MainWindow::onBtnPlusMinusClicked);
    connect(ui->btnDel, &QPushButton::clicked, this, &MainWindow::onBtnDelClicked);

    connect(ui->btnMRead, &QPushButton::clicked, this, &MainWindow::onBtnMRClicked);
    connect(ui->btnMClear, &QPushButton::clicked, this, &MainWindow::onBtnMCClicked);
    connect(ui->btnEqual, &QPushButton::clicked, this, &MainWindow::onBtnEqulsClicked);
}

void MainWindow::connectDigits(){
    connect(ui->btnZero, &QPushButton::clicked, this, [this]{MainWindow::onBtnDigitClicked("0");});
    connect(ui->btnOne, &QPushButton::clicked, this, [this]{MainWindow::onBtnDigitClicked("1");});
    connect(ui->btnTwo, &QPushButton::clicked, this, [this]{MainWindow::onBtnDigitClicked("2");});
    connect(ui->btnThree, &QPushButton::clicked, this, [this]{MainWindow::onBtnDigitClicked("3");});
    connect(ui->btnFour, &QPushButton::clicked, this, [this]{MainWindow::onBtnDigitClicked("4");});
    connect(ui->btnFive, &QPushButton::clicked, this, [this]{MainWindow::onBtnDigitClicked("5");});
    connect(ui->btnSix, &QPushButton::clicked, this, [this]{MainWindow::onBtnDigitClicked("6");});
    connect(ui->btnSeven, &QPushButton::clicked, this, [this]{MainWindow::onBtnDigitClicked("7");});
    connect(ui->btnEight, &QPushButton::clicked, this, [this]{MainWindow::onBtnDigitClicked("8");});
    connect(ui->btnNine, &QPushButton::clicked, this, [this]{MainWindow::onBtnDigitClicked("9");});
}

MainWindow::~MainWindow(){
    delete ui;
}

QString MainWindow::getStringLabel(){
    return ui->lblAnswer->text();
}

void MainWindow::statusWriteInLabel(bool status){
    ui->btnZero->setEnabled(status);
    ui->btnOne->setEnabled(status);
    ui->btnTwo->setEnabled(status);
    ui->btnThree->setEnabled(status);
    ui->btnFour->setEnabled(status);
    ui->btnFive->setEnabled(status);
    ui->btnSix->setEnabled(status);
    ui->btnSeven->setEnabled(status);
    ui->btnEight->setEnabled(status);
    ui->btnNine->setEnabled(status);
    ui->btnDot->setEnabled(status);
}

void MainWindow::setStringLabel(QString newLabel){
    ui->lblAnswer->setText(newLabel);
}

QString MainWindow::validationLabel(QString str){
    if (str == "nan" || str == "inf" || str == "-inf") {
        str = "";
    }
    return str;
}

void MainWindow::onBtnDigitClicked(QString digit){
    QString label = getStringLabel();

    if ((digit != "0" || label != "" || label != "-0") && !label.contains("e")){
            if(label == ""){
                setStringLabel(digit);
            }else if(label == "-0"){
                setStringLabel("-" + digit);
            }else if(label == "0"){
                setStringLabel(digit);
            }else if(label.length() < STR_LENGTH){
                label = label + digit;
                setStringLabel(label);
            }else if(label.length() == STR_LENGTH){
                message("ERROR\n limit of quantity digits in number");
            }
        }
}

void MainWindow::onBtnOperarionClicked(int sign){
    QString label = getStringLabel();
    double number = label.toDouble();

    setStringLabel("");

    action temp;
    temp.mRead = MainWindow::mRead;
    temp.memory = MainWindow::memoryCalc;
    temp.action = MainWindow::lastAction;
    temp.number = number;

    if(lastAction == sign && label != ""){
        validationCalc(temp);
    }else if(lastAction == CLEAR){
        lastAction = sign;
        memoryCalc = number;
    }else{
        validationCalc(temp);
    }

    if((sign >= SIN && sign <= CTAN) || (sign >= SQRT && sign <= X1) || sign == MPLUS || sign == MMINUS){
        statusWriteInLabel(false);
    } else {
        ui->btnDot->setEnabled(true);
    }
    lastAction = sign;
}

void MainWindow::onBtnClearClicked(){
    statusWriteInLabel(true);
    setStringLabel("");
    lastAction = CLEAR;
    memoryCalc = CLEAR;
    mRead = CLEAR;
}

void MainWindow::onBtnEqulsClicked(){
    statusWriteInLabel(true);
    QString label = getStringLabel();
    double number = label.toDouble();

    action temp;
    temp.mRead = MainWindow::mRead;
    temp.memory = MainWindow::memoryCalc;
    temp.action = MainWindow::lastAction;
    temp.number = number;

    validationCalc(temp);
    QString newLabel = QString().setNum(memoryCalc, 'g', 12);
    newLabel = validationLabel(newLabel);
    setStringLabel(newLabel);

    if (getStringLabel().contains(".")) {
        ui->btnDot->setEnabled(false);
    } else {
        ui->btnDot->setEnabled(true);
    }

    lastAction = CLEAR;
}

void MainWindow::validationCalc(action temp){
    double tempMemory = typeOperation(temp);
    if(tempMemory == ERROR_TAN && temp.action == TAN){
        message("ERROR\n tan, cos cannot be zero");
    }else if(tempMemory == ERROR_CTAN && temp.action == CTAN){
        message("ERROR\n ctan, sin cannot be zero");
    }else if(tempMemory == ERROR_SQRT && temp.action == SQRT){
        message("ERROR\n number cannot be negative");
    }else if(tempMemory == ERROR_X1 && temp.action == X1){
        message("ERROR\n divide 1 on number, number cannot be zero");
    }else if(tempMemory == ERROR_DIV){
        message("ERROR\n divide on zero");
    }else if(tempMemory != INFINITY && tempMemory != -INFINITY){
        MainWindow::memoryCalc = tempMemory;
    }else{
        message("ERROR");
    }
}

void MainWindow::onBtnDotClicked(){
    QString label = getStringLabel();

    if(label.length() == 0){
        setStringLabel("0.");
    }else if(label == "-"){
        setStringLabel("-0.");
    }else if(label.length() < STR_LENGTH-1 && !label.contains("e") && !label.contains(".")){
            label = label + ".";
            setStringLabel(label);
    }
    ui->btnDot->setEnabled(false);
}

void MainWindow::onBtnPlusMinusClicked(){
    QString label = getStringLabel();
    QString newLabel;

    if(label.contains("-")){
        newLabel = label.remove(0, 1);
    }else if(label != "0" && !label.contains("-")){
        newLabel = "-" + label;
    }else{
        newLabel = "-0";
    }
    setStringLabel(newLabel);
}

void MainWindow::onBtnDelClicked(){
    QString label = getStringLabel();

    if(!label.contains("e")){
        label.remove(-1, 1);
    }

    if(!label.contains("."))
        ui->btnDot->setEnabled(true);
    setStringLabel(label);
}

void MainWindow::onBtnMCClicked(){
    mRead = CLEAR;
}

void MainWindow::onBtnMRClicked(){
    QString label = getStringLabel();
    if(label != "")
        mRead = label.toDouble();
    setStringLabel("");
}

void MainWindow::message(QString str){
    QMessageBox msg;
    msg.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    msg.setIcon(QMessageBox::Critical);
    msg.setText(str);
    msg.setStandardButtons(QMessageBox::Ok);
    msg.setStyleSheet("QLabel{background-color: rgb(255, 255, 255); color: rgb(0, 0, 0);}");
    if(msg.exec() == QMessageBox::Ok)
        msg.close();
}
