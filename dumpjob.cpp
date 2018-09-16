#include "dumpjob.h"

#include <QTcpSocket>
#include <QFile>
#include <QTimer>
#include <QDateTime>

const QByteArray DumpJob::m_userAgent = QByteArrayLiteral("Wieder ein Stream-Dumper!");
QDir DumpJob::m_outputDir("radio");

DumpJob::DumpJob(const QByteArray &jobName, const QByteArray &hostName, quint16 port, const QByteArray &path, QObject *parent) :
    QObject(parent),
    m_jobName(jobName),
    m_hostName(hostName),
    m_port(port),
    m_path(path),
    m_socket(Q_NULLPTR),
    m_file(Q_NULLPTR),
    m_jobDir(m_outputDir.absoluteFilePath(jobName))
{
    reconnect();
}

void DumpJob::reconnect()
{
    if(m_socket)
    {
        disconnect(m_socket, &QAbstractSocket::stateChanged, this, &DumpJob::stateChanged);
        m_socket->deleteLater();
    }
    if(m_file)
        m_file->deleteLater();
    m_file = Q_NULLPTR;

    qDebug() << "[" << m_jobName << "] connecting to" << m_hostName << m_port;

    m_socket = new QTcpSocket(this);
    connect(m_socket, &QAbstractSocket::connected, this, &DumpJob::connected);
    connect(m_socket, &QAbstractSocket::stateChanged, this, &DumpJob::stateChanged);
    m_socket->connectToHost(m_hostName, m_port);
}

void DumpJob::connected()
{
    qDebug() << "[" << m_jobName << "] connected!";

    m_firstHeader = true;

    connect(m_socket, &QTcpSocket::readyRead, this, &DumpJob::readyRead);

    m_socket->write(QByteArrayLiteral("GET "));
    m_socket->write(m_path);
    m_socket->write(QByteArrayLiteral(" HTTP/1.1\r\nHost: "));
    m_socket->write(m_hostName);
    m_socket->write(QByteArrayLiteral("\r\nUser-Agent: "));
    m_socket->write(m_userAgent);
    m_socket->write(QByteArrayLiteral("\r\nConnection: close\r\n\r\n"));
}

void DumpJob::stateChanged(QAbstractSocket::SocketState state)
{
    if(state == QAbstractSocket::UnconnectedState)
    {
        qDebug() << "[" << m_jobName << "] lost connection";
        QTimer::singleShot(1000, this, &DumpJob::reconnect);
    }
}

void DumpJob::readyRead()
{
    if(m_file)
    {
        m_file->write(m_socket->readAll());

        quint64 ts = QDateTime::currentMSecsSinceEpoch();
        ts -= ts % 3600000;
        if(m_lastTs != ts)
        {
            qDebug() << "[" << m_jobName << "] split file";
            reconnect();
        }
    }
    else
    {
        m_buffer.append(m_socket->readAll());
        int index;
        while((index = m_buffer.indexOf(QByteArrayLiteral("\r\n"))) != -1)
        {
            auto line = QString(m_buffer.left(index));
            m_buffer.remove(0, index+2);

            if(line.isEmpty())
            {
                if(!m_jobDir.mkpath(m_jobDir.absolutePath()))
                    qFatal("could not create directory!");

                m_lastTs = QDateTime::currentMSecsSinceEpoch();
                m_lastTs -= m_lastTs % 3600000;

                m_file = new QFile(m_jobDir.absoluteFilePath(QString("%0_%1.mp3")
                                                             .arg(QString(m_jobName))
                                                             .arg(QDateTime::fromMSecsSinceEpoch(m_lastTs).toString(Qt::ISODate).replace("T", "_").replace(":", "-"))
                                                            ), this);
                if(!m_file->open(QIODevice::WriteOnly))
                    qCritical() << m_file->errorString();

                m_file->write(m_buffer);
                m_buffer.clear();

                qDebug() << "[" << m_jobName << "] started dump";

                break;
            }
            else if(m_firstHeader)
            {
                qDebug() << "[" << m_jobName << "] " << line;
                m_firstHeader = false;
            }
        }
    }


}
