#ifndef WKEYBOARD_H
#define WKEYBOARD_H

#include <QMainWindow>

namespace Ui {
class WKeyboard;
}

class WKeyboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit WKeyboard(QWidget *parent = 0);
    ~WKeyboard();

private:
    Ui::WKeyboard *ui;
};

#endif // WKEYBOARD_H
