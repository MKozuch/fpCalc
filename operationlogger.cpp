#include "operationlogger.h"

#include <QDateTime>
#include <QDir>
#include <QTextStream>

OperationLogger::OperationLogger(QObject *parent) : QObject(parent)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    this->fileName = dateTime.toString("yy.MM.dd'_'hh.mm_") + QString("fpCalc_logfile.txt");
    this->logFile.setFileName(fileName);
    this->logStream.setDevice(&logFile);

    this->logDir = QDir::current();
    bool logDirExists = logDir.mkpath(logDir.absolutePath() + "/log");
    logDir.cd("log");
    QDir::setCurrent(logDir.canonicalPath());

    this->logFile.open(QIODevice::Append);
    this->logFile.close();
}

void OperationLogger::logMsg(QString message)
{
    this->logFile.open(QIODevice::Append);
    this->logStream << message;
    this->logStream << "\r\n";
    this->logFile.close();
}

QString OperationLogger::getLogUrl()
{
    return (this->logDir.absolutePath() + "/" + this->fileName);
}


