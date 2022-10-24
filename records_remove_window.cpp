#include "records_remove_window.h"
#include "ui_records_remove_window.h"

records_remove_window::records_remove_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::records_remove_window)
{
    ui->setupUi(this);
}

records_remove_window::~records_remove_window()
{
    delete ui;
}

void records_remove_window::on_buttonBox_accepted()
{
    std::string f_name = ui->lineEdit_fname->text().toStdString();
    std::string s_name = ui->lineEdit_sname->text().toStdString();
    std::string th_name = ui->lineEdit_thname->text().toStdString();
    std::string full_name = f_name + " " + s_name + " " + th_name;

    std::string service = ui->lineEdit_service->text().toStdString();

    QDate date = ui->dateEdit_date->date();

    emit send_data(full_name, service, date);
}

