#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class Protocol;
}

class Protocol : public QMainWindow
{
    Q_OBJECT

public:
    explicit Protocol(QWidget *parent, int treatment_type, int treatment);
    ~Protocol();

private:
    Ui::Protocol *ui;
    QPushButton *bquit;
    QLabel *lab_info;

private slots:
    void handle_Trt_Exit();
};

#endif // PROTOCOL_H
