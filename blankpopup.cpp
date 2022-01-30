#include "blankpopup.h"
#include "ui_blankpopup.h"

#include "iostream"
using namespace std;

BlankPopup::BlankPopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlankPopup)
{
    this->letter = ' ';
    ui->setupUi(this);
    ui->lineEdit->setMaxLength(1);
    ui->lineEdit->hasFocus();
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::WindowTitleHint);
}

BlankPopup::~BlankPopup()
{
    delete ui;
}

char BlankPopup::GetLetter() {
    string letter_input = ui->lineEdit->text().toStdString();
    return letter_input[0];
}

void BlankPopup::reject() {}

void BlankPopup::on_pushButton_clicked()
{
    if (GetLetter() == 0) {
        cout << "invalid input" << endl;
    } else {
        accept();
    }
}

