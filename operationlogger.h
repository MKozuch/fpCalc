#ifndef OPERATIONLOGGER_H
#define OPERATIONLOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDir>

class OperationLogger : public QObject
{
    Q_OBJECT

public:
    explicit OperationLogger(QObject *parent = 0);
    QString getLogUrl();

private:
    QFile logFile;
    QTextStream logStream;
    QDir logDir;
    QString fileName;

public slots:
    void logMsg(QString);
};

#endif // OPERATIONLOGGER_H
