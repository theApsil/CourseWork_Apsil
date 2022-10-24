#ifndef masterS_REMOVE_WINDOW_H
#define masterS_REMOVE_WINDOW_H

#include <QDialog>

namespace Ui {
class masters_remove_window;
}

class masters_remove_window : public QDialog
{
    Q_OBJECT

public:
    explicit masters_remove_window(QWidget *parent = nullptr);
    ~masters_remove_window();

signals:
    void send_data(std::string full_name);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::masters_remove_window *ui;
};

#endif // masterS_REMOVE_WINDOW_H
