#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDate"
#include "QTime"
#include <string>
#include "Database.h"

#include "masters_add_window.h"
#include "masters_remove_window.h"
#include "records_add_window.h"
#include "records_remove_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString ask_file_read_path();

    QString ask_file_save_path();

    void debug_message(std::string message);

    void add_master_to_treewidget(Master master);

    void add_record_to_treewidget(Record record);

    void update_masters_treewidget();

    void update_records_treewidget();

    void update_treewidgets();

public slots:
    void on_get_add_master(std::string full_name, std::string salon, double rating);

    void on_get_remove_master(std::string full_name);

    void on_get_add_record(std::string full_name, std::string service, QDate date, QTime start, QTime end, bool status);

    void on_get_remove_record(std::string full_name, std::string service, QDate date);

private slots:
    void on_action_files_triggered();

    void on_action_masters_triggered();

    void on_action_records_triggered();

    void on_action_search_triggered();

    void on_action_debug_triggered();

    void on_pushButton_import_masters_path_clicked();

    void on_pushButton_import_records_path_clicked();

    void on_pushButton_export_masters_path_clicked();

    void on_pushButton_export_records_path_clicked();

    void on_pushButton_masters_add_clicked();

    void on_pushButton_masters_remove_clicked();

    void on_pushButton_records_add_clicked();

    void on_pushButton_records_remove_clicked();

    void on_pushButton_debug_1_clicked();

    void on_pushButton_debug_2_clicked();

    void on_pushButton_debug_3_clicked();

    void on_pushButton_search_export_path_clicked();

    void on_pushButton_import_files_clicked();

    void on_pushButton_import_default_files_clicked();

    void on_pushButton_export_files_clicked();

    void on_pushButton_export_default_files_clicked();

    void on_pushButton_master_search_pass_clicked();

    void on_pushButton_masters_reset_search_clicked();

    void on_pushButton_records_reset_search_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_search_export_clicked();

    void on_pushButton_search_export_default_clicked();

    void on_pushButton_search_status_clicked();

    void on_pushButton_master_search_salon_clicked();

private:
    Ui::MainWindow *ui;
    Database database;

    // Пути по умолчанию
    std::string default_import_masters_path = "./masters.txt";
    std::string default_import_records_path = "./records.txt";
    std::string default_export_masters_path = "./masters.txt";
    std::string default_export_records_path = "./records.txt";
    std::string default_export_search_path = "./report.txt";

    // Названия файлов. Любые другие названия не будут приниматься
    std::string masters_filename = "masters.txt";
    std::string records_filename = "records.txt";
    std::string report_filename = "report.txt";

    bool check_masters_path(std::string path);
    bool check_records_path(std::string path);
    bool check_report_path(std::string path);

};
#endif // MAINWINDOW_H
