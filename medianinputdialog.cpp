#include "medianinputdialog.h"
#include "ui_medianinputdialog.h"

#include <QMessageBox>

MedianInputDialog::MedianInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedianInputDialog)
{
    ui->setupUi(this);
    this->values = QList<double>();
}

MedianInputDialog::~MedianInputDialog()
{
    delete ui;
}

void MedianInputDialog::on_acceptBtn_clicked()
{
    bool conversionResultOk = true;
    double newVal = this->ui->valueInput->text().toDouble(&conversionResultOk);
    if(conversionResultOk){
        this->values.append(newVal);
        this->ui->valueInput->clear();
        this->ui->listDisplay->insert(QString::number(newVal));
        this->ui->listDisplay->insert("; ");
    }
    else{
        QMessageBox::warning(this, "Error", "Invalid input");
    }
}
