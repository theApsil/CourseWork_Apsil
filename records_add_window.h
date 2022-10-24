#ifndef recordS_ADD_WINDOW_H
#define recordS_ADD_WINDOW_H

#include <QDialog>
#include "QDate"
#include "QTime"

namespace Ui {
class records_add_window;
}

class records_add_window : public QDialog
{
    Q_OBJECT

public:
    explicit records_add_window(QWidget *parent = nullptr);
    ~records_add_window();

signals:
    void send_data(std::string full_name, std::string service, QDate date, QTime start, QTime end, bool status);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::records_add_window *ui;
};

#endif // recordS_ADD_WINDOW_H
