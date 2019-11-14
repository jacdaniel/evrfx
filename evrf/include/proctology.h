#ifndef PROCTOLOGY_H
#define PROCTOLOGY_H

#include <QMainWindow>

namespace Ui {
class Proctology;
}

class Proctology : public QMainWindow
{
    Q_OBJECT

public:
    explicit Proctology(QWidget *parent = 0);
    ~Proctology();

private:
    Ui::Proctology *ui;
};

#endif // PROCTOLOGY_H
