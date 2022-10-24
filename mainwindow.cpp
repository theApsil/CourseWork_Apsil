#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_default_import_masters->setText(QString::fromStdString("Путь по умолчанию: " + this->default_import_masters_path));
    ui->label_default_import_records->setText(QString::fromStdString("Путь по умолчанию: " + this->default_import_records_path));
    ui->label_default_export_masters->setText(QString::fromStdString("Путь по умолчанию: " + this->default_export_masters_path));
    ui->label_default_export_records->setText(QString::fromStdString("Путь по умолчанию: " + this->default_export_records_path));
    ui->label_default_search_export->setText(QString::fromStdString("Путь по умолчанию: " + this->default_export_search_path));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::ask_file_path_write
 * Создаёт окно с выбором пути на переписывание файла и возвращает строку, выбранный путь
 *
 * @return Путь до выбранного файла
 */
QString MainWindow::ask_file_save_path() {
    QString path = QFileDialog::getSaveFileName(this, "Выберите файл");
    return path;
}

/**
 * @brief MainWindow::ask_file_path_write
 * Создаёт окно с выбором пути на чтение файла и возвращает строку, выбранный путь
 *
 * @return Путь до выбранного файла
 */
QString MainWindow::ask_file_read_path() {
    QString path = QFileDialog::getOpenFileName(this, "Выберите файл");
    return path;
}

/**
 * @brief MainWindow::debug_message
 * Записывает сообщение message в окно отладки
 *
 * @param message Сообщение, которое хотим записать в отладку
 */
void MainWindow::debug_message(std::string message) {
    std::string text = ui->textEdit_debug->toPlainText().toStdString() + message + "\n";
    ui->textEdit_debug->setText(QString::fromStdString(text));
}

void MainWindow::on_action_files_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_action_masters_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_action_records_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_action_search_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_action_debug_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_import_masters_path_clicked()
{
    QString path = this->ask_file_read_path();
    ui->lineEdit_import_masters_path->setText(path);
}


void MainWindow::on_pushButton_import_records_path_clicked()
{
    QString path = this->ask_file_read_path();
    ui->lineEdit_import_records_path->setText(path);
}


void MainWindow::on_pushButton_export_masters_path_clicked()
{
    QString path = this->ask_file_save_path();
    ui->lineEdit_export_masters_path->setText(path);
}


void MainWindow::on_pushButton_export_records_path_clicked()
{
    QString path = this->ask_file_save_path();
    ui->lineEdit_export_records_path->setText(path);
}

void MainWindow::on_pushButton_search_export_path_clicked()
{
    QString path = this->ask_file_save_path();
    ui->lineEdit_search_export_path->setText(path);
}



void MainWindow::on_pushButton_masters_add_clicked()
{
    masters_add_window win(this);
    win.setWindowTitle("Добавление мастера");
    connect(&win, &masters_add_window::send_data,
            this, &MainWindow::on_get_add_master);
    win.setModal(true);
    win.exec();
}


void MainWindow::on_pushButton_masters_remove_clicked()
{
    masters_remove_window win(this);
    win.setWindowTitle("Удаление мастера");
    connect(&win, &masters_remove_window::send_data,
            this, &MainWindow::on_get_remove_master);
    win.setModal(true);
    win.exec();
}


void MainWindow::on_pushButton_records_add_clicked()
{
    records_add_window win(this);
    win.setWindowTitle("Добавление записи");
    connect(&win, &records_add_window::send_data,
            this, &MainWindow::on_get_add_record);
    win.setModal(true);
    win.exec();
}


void MainWindow::on_pushButton_records_remove_clicked()
{
    records_remove_window win(this);
    win.setWindowTitle("Удаление записи");
    connect(&win, &records_remove_window::send_data,
            this, &MainWindow::on_get_remove_record);
    win.setModal(true);
    win.exec();
}


void MainWindow::on_pushButton_debug_1_clicked()
{
    QString new_text = ui->textEdit_debug->toPlainText();
    new_text += QString::fromStdString(this->database.to_string_masters_table() + "\n\n");
    ui->textEdit_debug->setText(new_text);

}


void MainWindow::on_pushButton_debug_2_clicked()
{
    QString new_text = ui->textEdit_debug->toPlainText();
    new_text += QString::fromStdString(this->database.to_string_masters_FIO_tree() + "\n\n");
    ui->textEdit_debug->setText(new_text);
}


void MainWindow::on_pushButton_debug_3_clicked()
{
    QString new_text = ui->textEdit_debug->toPlainText();
    new_text += QString::fromStdString(this->database.to_string_records_date_status_tree() + "\n\n");
    ui->textEdit_debug->setText(new_text);
}

void MainWindow::add_master_to_treewidget(Master master) {
    QTreeWidgetItem* table_item = new QTreeWidgetItem(ui->treeWidget_masters);
    table_item->setText(0, QString::fromStdString(master.full_name));
    table_item->setText(1, QString::fromStdString(master.salon));
    table_item->setText(2, QString::number(master.rating));
    ui->treeWidget_masters->addTopLevelItem(table_item);
}

void MainWindow::add_record_to_treewidget(Record record) {
    QTreeWidgetItem* table_item = new QTreeWidgetItem(ui->treeWidget_records);
    table_item->setText(0, QString::fromStdString(record.full_name));
    table_item->setText(1, QString::fromStdString(record.service));
    table_item->setText(2, QString::fromStdString(record.date.to_string()));
    table_item->setText(3, QString::fromStdString(record.start.to_string()));
    table_item->setText(4, QString::fromStdString(record.end.to_string()));
    if (record.status == 0) {
        table_item->setText(5, "Свободно");
    } else {
        table_item->setText(5, "Занято");
    }
    ui->treeWidget_masters->addTopLevelItem(table_item);
}

void MainWindow::update_masters_treewidget() {
    ui->treeWidget_masters->clear();
    auto masters = this->database.get_all_masters();
    for (auto& master: masters) {
        this->add_master_to_treewidget(master);
    }
}

void MainWindow::update_records_treewidget() {
    ui->treeWidget_records->clear();
    auto records = this->database.get_all_records();
    for (auto& record: records) {
        this->add_record_to_treewidget(record);
    }
}

void MainWindow::update_treewidgets() {
    this->update_masters_treewidget();
    this->update_records_treewidget();
}

void MainWindow::on_pushButton_import_files_clicked()
{
    std::string masters_import_path = ui->lineEdit_import_masters_path->text().toStdString();
    std::string records_import_path = ui->lineEdit_import_records_path->text().toStdString();
    if (this->check_masters_path(masters_import_path) && this->check_records_path(records_import_path)) {  // Проверяем соответствие названия файлов заданным названиям
        this->database.load_masters_file(masters_import_path);
        this->database.load_records_file(records_import_path);
        this->update_treewidgets();
        QMessageBox::information(this, "Успех", "Загрузка прошла успешно");
    } else {
        QMessageBox::critical(this, "Ошибка", "Неверный файл(ы)");
    }

}


void MainWindow::on_pushButton_import_default_files_clicked()
{
    if (this->check_masters_path(this->default_import_masters_path) && this->check_records_path(this->default_import_records_path)) {  // Проверяем соответствие названия файлов заданным названиям
        this->database.load_masters_file(this->default_import_masters_path);
        this->database.load_records_file(this->default_import_records_path);
        this->update_treewidgets();
        QMessageBox::information(this, "Успех", "Загрузка прошла успешно");
    } else {
        QMessageBox::critical(this, "Ошибка", "Неверный файл(ы)");
    }
}


void MainWindow::on_pushButton_export_files_clicked()
{
    std::string masters_export_path = ui->lineEdit_export_masters_path->text().toStdString();
    std::string records_export_path = ui->lineEdit_export_records_path->text().toStdString();
    this->database.save_masters_to_file(masters_export_path);
    this->database.save_records_to_file(records_export_path);
    QMessageBox::information(this, "Успех", "Справочники сохранены");
}


void MainWindow::on_pushButton_export_default_files_clicked()
{
    this->database.save_masters_to_file(this->default_export_masters_path);
    this->database.save_records_to_file(this->default_export_records_path);
    QMessageBox::information(this, "Успех", "Справочники сохранены");
}

void MainWindow::on_pushButton_master_search_pass_clicked()
{
    double rating = this->ui->doubleSpinBox->value();
    std::vector<Master> masters_higher_rating = this->database.find_masters_higher_rating(rating);
    ui->treeWidget_masters->clear();
    for (Master master: masters_higher_rating) {
        this->add_master_to_treewidget(master);
    }
}

void MainWindow::on_pushButton_masters_reset_search_clicked()
{
    this->update_masters_treewidget();
}

void MainWindow::on_pushButton_search_status_clicked()
{
    QDate qdate = this->ui->dateEdit->date();
    Date date = {qdate.day(), qdate.month(), qdate.year()};
    QString chosen_status = ui->comboBox->currentText();
    bool status;
    if (chosen_status == "Свободно") {
        status = 0;
    } else {
        status = 1;
    }
    auto records = this->database.find_records_by_date_stauts(date, status);
    ui->treeWidget_records->clear();
    for (Record record: records) {
        this->add_record_to_treewidget(record);
    }
}

void MainWindow::on_pushButton_records_reset_search_clicked()
{
    this->update_records_treewidget();
}

void MainWindow::on_pushButton_search_clicked()
{
    QDate qdate = ui->dateEdit_2->date();
    Date date = {qdate.day(), qdate.month(), qdate.year()};

    double rating = this->ui->doubleSpinBox_2->value();

    QString chosen_status = ui->comboBox_2->currentText();
    bool status;
    if (chosen_status == "Свободно") {
        status = 0;
    } else {
        status = 1;
    }

    std::string search_result = this->database.search_to_string(rating, date, status);
    ui->textEdit_search->setText(QString::fromStdString(search_result));
}


void MainWindow::on_pushButton_search_export_clicked()
{
    std::string path = ui->lineEdit_search_export_path->text().toStdString();
    if (this->check_report_path(path)) {
        std::ofstream out(path);
        out << ui->textEdit_search->toPlainText().toStdString();
        out.close();
        QMessageBox::information(this, "Успех", "Отчёт сохранен");
    } else {
        QMessageBox::critical(this, "Ошибка", "Неверный файл(ы)");
    }
}


void MainWindow::on_pushButton_search_export_default_clicked()
{
    std::ofstream out(this->default_export_search_path);
    out << ui->textEdit_search->toPlainText().toStdString();
    out.close();
    QMessageBox::information(this, "Успех", "Отчёт сохранен");
}

void MainWindow::on_get_add_master(std::string full_name, std::string salon, double rating) {
    AddResult result = this->database.add_master(full_name, salon, rating);
    if (result == AddResult::EXIST) {
        QMessageBox::critical(this, "Ошибка", "Нельзя добавить. Такое ФИО есть в таблице");
        return;
    }
    this->update_masters_treewidget();
    QMessageBox::information(this, "Успех", "Запись добавлена");
}

void MainWindow::on_get_remove_master(std::string full_name) {
    RemoveResult result = this->database.remove_master(full_name);
    if (result == RemoveResult::NOT_FOUND) {
        QMessageBox::critical(this, "Ошибка", "Мастер не найден");
        return;
    } else if (result == RemoveResult::LINKED_RECORDS) {
        QMessageBox::critical(this, "Ошибка", "Нельзя удалить. У мастера есть связанные записи");
        return;
    }
    this->update_treewidgets();
    QMessageBox::information(this, "Успех", "Запись удалена");
}

void MainWindow::on_get_add_record(std::string full_name, std::string service, QDate date, QTime start, QTime end, bool status) {
    if (start > end) {
        QMessageBox::critical(this, "Ошибка", "Время начала больше времени окончания");
        return;
    }

    AddResult result = this->database.add_record(full_name, service, {date.day(), date.month(), date.year()},
                                                 {start.hour(), start.minute()},
                                                 {end.hour(), end.minute()}, status);
    if (result == AddResult::NO_LINKED_MASTER) {
        QMessageBox::critical(this, "Ошибка", "Нельзя добавить услугу для несуществующего мастера");
        return;
    }
    if (result == AddResult::TIME_INTERSECT) {
        QMessageBox::critical(this, "Ошибка", "Записи мастера пересекаются");
        return;
    }

    this->update_records_treewidget();
    QMessageBox::information(this, "Успех", "Запись добавлена");
}

void MainWindow::on_get_remove_record(std::string full_name, std::string service, QDate date) {
    RemoveResult result = this->database.remove_record(full_name, service, {date.day(), date.month(), date.year()});
    if (result == RemoveResult::NOT_FOUND) {
        QMessageBox::critical(this, "Ошибка", "Запись не найдена");
        return;
    }
    this->update_records_treewidget();
    QMessageBox::information(this, "Успех", "Запись удалена");
}

bool MainWindow::check_masters_path(std::string path) {
    std::string pattern = this->masters_filename;
    int patt_len = pattern.size();
    if (patt_len <= path.size()) {
        return path.substr(path.size() - patt_len, patt_len) == pattern;
    } else {
        return false;
    }
}

bool MainWindow::check_records_path(std::string path) {
    std::string pattern = this->records_filename;
    int patt_len = pattern.size();
    if (patt_len <= path.size()) {
        return path.substr(path.size() - patt_len, patt_len) == pattern;
    } else {
        return false;
    }
}

bool MainWindow::check_report_path(std::string path) {
    std::string pattern = this->report_filename;
    int patt_len = pattern.size();
    if (patt_len <= path.size()) {
        return path.substr(path.size() - patt_len, patt_len) == pattern;
    } else {
        return false;
    }
}


void MainWindow::on_pushButton_master_search_salon_clicked()
{
    std::string salon = this->ui->lineEdit_master_search_salon->text().toStdString();
    vector<Master> salon_masters = this->database.find_masters_by_salon(salon);
    this->ui->treeWidget_masters->clear();
    for (Master& master: salon_masters) {
        this->add_master_to_treewidget(master);
    }
}

