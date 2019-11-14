
#include <QLabel>

#include "include/config.h"
#include "./include/wkeyboard.h"
#include "ui_wkeyboard.h"



const char KEYBOARD_ORDER_EN[] =
{
    KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
    KEY_A, KEY_Z, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P,
    KEY_Q, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_M,
    KEY_W, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_000, KEY_RET, KEY_000, KEY_000
};

const char KEYBOARD_ORDER_FR[] =
{
    KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
    KEY_A, KEY_Z, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P,
    KEY_Q, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_M,
    KEY_W, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_000, KEY_RET, KEY_000, KEY_000
};

const int KEYBOARD_LENGTH_LINE[] = {10, 10, 10, 8};


WKeyboard::WKeyboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WKeyboard)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(100,100,100);");

    set_language(KEYBOARD_EN);
    b = new QPushButton*[40];

    for (int j=0; j<4; j++)
    {
        for (int i=0; i<KEYBOARD_LENGTH_LINE[j]; i++)
        {
            int add = j*10+i;
            // b[add] = new QPushButton(QIcon("./data/b2jaunebl.jpg"), "", this);
            b[add] = new QPushButton(QIcon("./data/key_model1.jpg"), "", this);
            b[add]->setGeometry(0+50*i, 0+50*j,50,50);
            b[add]->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
            // b[add]->setIcon(QIcon("./data/b2jaunebl.jpg"));
            b[add]->setIcon(QIcon("./data/key_model1.jpg"));
            b[add]->setIconSize(QSize(50, 50));

            char t[2]; t[0] = KEYBOARD_ORDER_EN[add]; t[1] = 0;
            QLabel *l = new QLabel(t);
            l->setAttribute(Qt::WA_TranslucentBackground);
            l->setGeometry(10, 12, 20, 20);
            QFont f = l->font();
            f.setPointSize(14);
            f.setBold(true);
            l->setFont(f);

            l->setParent(b[add]);
                        // t[0] = KEYBOARD_ORDER_FR[add]; t[1] = 0;
            // b[add]->setText(t);

            connect(b[add], SIGNAL (released()), this, SLOT (handle_Trt_BKey()));
        }
    }
}

WKeyboard::~WKeyboard()
{
    delete ui;
}

void WKeyboard::set_language(int val)
{
    this->language = val;
}

void WKeyboard::setCallBack(void(*f)(void*, char))
{
    this->callback = f;
}

int WKeyboard::getKeyNo(QObject *sender_, QPushButton **b, int size)
{
    for (int i=0; i<size; i++)
        if ( b[i] == sender_)
            return i;
    return -1;
}

char *WKeyboard::get_keyboard_order(int num)
{
    if ( num == KEYBOARD_EN) return (char*)KEYBOARD_ORDER_EN;
    else if ( num == KEYBOARD_FR) return (char*)KEYBOARD_ORDER_FR;
    else return (char*)KEYBOARD_ORDER_EN;
}

void WKeyboard::handle_Trt_BKey()
{
    // QAction *action = qobject_cast<QAction *>(this->sender());
    int no = getKeyNo(this->sender(), this->b, 40);
    if ( this->callback != NULL )
    {
        char *tab = get_keyboard_order(no);
        this->callback(this->parent(), tab[no]);
    }
}

/*
void CustomWidget::paintEvent(QPaintEvent* event)
{
 QStyleOption opt;
 opt.init(this);
 QPainter p(this);
 style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

 QWidget::paintEvent(event);
}
*/
