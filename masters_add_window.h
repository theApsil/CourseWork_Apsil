#ifndef MASTERS_ADD_WINDOW_H
#define MASTERS_ADD_WINDOW_H

#include <QDialog>
#include "ui_masters_add_window.h"

namespace Ui {
class masters_add_window;
}

class masters_add_window : public QDialog
{
    Q_OBJECT

public:
    explicit masters_add_window(QWidget *parent = nullptr);
    ~masters_add_window();

signals:
    void send_data(std::string full_name, std::string salon, double rating);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::masters_add_window *ui;
};

#endif // masterS_ADD_WINDOW_H
