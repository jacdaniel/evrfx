#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QMainWindow>

namespace Ui {
class Protocol;
}

class Protocol : public QMainWindow
{
    Q_OBJECT

public:
    explicit Protocol(QWidget *parent = nullptr);
    ~Protocol();

private:
    Ui::Protocol *ui;
};

#endif // PROTOCOL_H
