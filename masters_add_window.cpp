#include "masters_add_window.h"
#include "ui_masters_add_window.h"

masters_add_window::masters_add_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::masters_add_window)
{
    ui->setupUi(this);
}

masters_add_window::~masters_add_window()
{
    delete ui;
}

void masters_add_window::on_buttonBox_accepted()
{
    std::string f_name = ui->lineEdit_fname->text().toStdString();
    std::string s_name = ui->lineEdit_sname->text().toStdString();
    std::string th_name = ui->lineEdit_thname->text().toStdString();
    std::string full_name = f_name + " " + s_name + " " + th_name;
    std::string salon = ui->lineEdit_salon->text().toStdString();
    double rating = ui->doubleSpinBox_rating->value();

    emit send_data(full_name, salon, rating);
}

