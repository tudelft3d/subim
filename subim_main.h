#ifndef SUBIM_MAIN_H
#define SUBIM_MAIN_H

#include <QMainWindow>

namespace Ui {
class SuBIM_main;
}

class SuBIM_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit SuBIM_main(QWidget *parent = 0);
    ~SuBIM_main();

private:
    Ui::SuBIM_main *ui;
};

#endif // SUBIM_MAIN_H
