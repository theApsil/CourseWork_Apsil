#include "records_add_window.h"
#include "ui_records_add_window.h"

records_add_window::records_add_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::records_add_window)
{
    ui->setupUi(this);
}

records_add_window::~records_add_window()
{
    delete ui;
}

void records_add_window::on_buttonBox_accepted()
{
    std::string f_name = ui->lineEdit_fname->text().toStdString();
    std::string s_name = ui->lineEdit_sname->text().toStdString();
    std::string th_name = ui->lineEdit_thname->text().toStdString();
    std::string full_name = f_name + " " + s_name + " " + th_name;

    std::string service = ui->lineEdit_service->text().toStdString();

    QDate date = ui->dateEdit_date->date();
    QTime start = ui->timeEdit_start->time();
    QTime end = ui->timeEdit_end->time();

    std::string str_status = ui->comboBox_status->currentText().toStdString();
    bool status;
    if (str_status == "Свободно") {
        status = 0;
    } else {
        status = 1;
    }

    emit send_data(full_name, service, date, start, end, status);
}


