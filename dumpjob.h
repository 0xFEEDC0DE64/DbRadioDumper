#pragma once

#include <QObject>
#include <QByteArray>
#include <QDir>
#include <QAbstractSocket>

class QTcpSocket;
class QFile;

class DumpJob : public QObject
{
    Q_OBJECT
public:
    explicit DumpJob(const QByteArray &jobName, const QByteArray &hostName, quint16 port, const QByteArray &path, QObject *parent = 0);

public Q_SLOTS:
    void reconnect();

private Q_SLOTS:
    void connected();
    void stateChanged(QAbstractSocket::SocketState state);
    void readyRead();

private:
    const QByteArray m_jobName;
    const QByteArray m_hostName;
    const quint16 m_port;
    const QByteArray m_path;

    QTcpSocket *m_socket;
    QFile *m_file;

    bool m_firstHeader;
    QByteArray m_buffer;
    QDir m_jobDir;

    quint64 m_lastTs;

    static const QByteArray m_userAgent;
    static QDir m_outputDir;
};
