#include "subim_main.h"
#include "ui_subim_main.h"

SuBIM_main::SuBIM_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SuBIM_main)
{
    ui->setupUi(this);
}

SuBIM_main::~SuBIM_main()
{
    delete ui;
}
