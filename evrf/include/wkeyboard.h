#ifndef WKEYBOARD_H
#define WKEYBOARD_H

#include <QMainWindow>
#include <QPushButton>

#define KEYBOARD_EN 1
#define KEYBOARD_FR 2


namespace Ui {
class WKeyboard;
}

class WKeyboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit WKeyboard(QWidget *parent = 0);
    ~WKeyboard();
    QPushButton **b;
    void setCallBack(void(*f)(void*, char));
    void set_language(int val);

private:
    Ui::WKeyboard *ui;
    int getKeyNo(QObject *sender_, QPushButton **b, int size);
    char *get_keyboard_order(int num);
    void(*callback)(void*,char);
    int language;

private slots:
    void handle_Trt_BKey();
};

#endif // WKEYBOARD_H
