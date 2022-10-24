#include "masters_remove_window.h"
#include "ui_masters_remove_window.h"

masters_remove_window::masters_remove_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::masters_remove_window)
{
    ui->setupUi(this);
}

masters_remove_window::~masters_remove_window()
{
    delete ui;
}

void masters_remove_window::on_buttonBox_accepted()
{
    std::string f_name = ui->lineEdit_fname->text().toStdString();
    std::string s_name = ui->lineEdit_sname->text().toStdString();
    std::string th_name = ui->lineEdit_thname->text().toStdString();
    std::string full_name = f_name + " " + s_name + " " + th_name;

    emit send_data(full_name);
}

