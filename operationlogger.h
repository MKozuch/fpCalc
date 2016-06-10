#ifndef OPERATIONLOGGER_H
#define OPERATIONLOGGER_H

#include <QObject>

class OperationLogger : public QObject
{
    Q_OBJECT
public:
    explicit OperationLogger(QObject *parent = 0);

signals:

public slots:
};

#endif // OPERATIONLOGGER_H