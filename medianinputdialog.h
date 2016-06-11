#ifndef MEDIANINPUTDIALOG_H
#define MEDIANINPUTDIALOG_H

#include <QDialog>
#include <QList>

namespace Ui {
class MedianInputDialog;
}

class MedianInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MedianInputDialog(QWidget *parent = 0);
    ~MedianInputDialog();
    QList<double> values;

private:
    Ui::MedianInputDialog *ui;

private slots:
    void on_acceptBtn_clicked();
};

#endif // MEDIANINPUTDIALOG_H
