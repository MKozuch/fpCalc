#ifndef MEDIANINPUTDIALOG_H
#define MEDIANINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class MedianInputDialog;
}

class MedianInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MedianInputDialog(QWidget *parent = 0);
    ~MedianInputDialog();

private:
    Ui::MedianInputDialog *ui;
};

#endif // MEDIANINPUTDIALOG_H
