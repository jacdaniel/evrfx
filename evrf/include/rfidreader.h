#ifndef RFIDREADER_H
#define RFIDREADER_H

#include <QLabel>
#include <QMainWindow>

namespace Ui {
class RFIDReader;
}

class RFIDReader : public QMainWindow
{
    Q_OBJECT

public:
    explicit RFIDReader(QWidget *parent = NULL);
    ~RFIDReader();

private:
    Ui::RFIDReader *ui;
    QLabel *lrfidlogo;
};

#endif // RFIDREADER_H
