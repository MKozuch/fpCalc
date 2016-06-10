#include "medianinputdialog.h"
#include "ui_medianinputdialog.h"

MedianInputDialog::MedianInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedianInputDialog)
{
    ui->setupUi(this);
}

MedianInputDialog::~MedianInputDialog()
{
    delete ui;
}
