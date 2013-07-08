#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>

#include "infixpostfix.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::convertStatement() {
    InfixPostfix converter;
    string instring = ui->statementEdit->text().toStdString();
    converter.convert(instring);
    QString outstring(instring.c_str());
    ui->resultLbl->setText(outstring);
}
