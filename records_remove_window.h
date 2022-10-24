#ifndef recordS_REMOVE_WINDOW_H
#define recordS_REMOVE_WINDOW_H

#include <QDialog>

namespace Ui {
class records_remove_window;
}

class records_remove_window : public QDialog
{
    Q_OBJECT

public:
    explicit records_remove_window(QWidget *parent = nullptr);
    ~records_remove_window();

signals:
    void send_data(std::string full_name, std::string service, QDate date);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::records_remove_window *ui;
};

#endif // recordS_REMOVE_WINDOW_H
