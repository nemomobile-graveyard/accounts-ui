#include <QProcess>
#include <QDebug>

#include "account.h"

Account
    ::
    Account(QObject *parent)
    : QObject(parent)
{
    refresh();
}

QString Account::id() const
{
    return accountid;
}

void Account::setId(const QString &id)
{
    accountid = id;
    emit idChanged();
    refresh();
}

QString Account::details() const
{
    return accountDetails;
}

void Account::refresh()
{
    QProcess ls;
    ls.start(QString("mc-tool show %1").arg(accountid));
    if (!ls.waitForFinished()) {
        qWarning() << Q_FUNC_INFO << "Can't wait for finished";
        return;
    }

    QByteArray result = ls.readAll();
    accountDetails = QString::fromUtf8(result);
    emit detailsChanged();
}

void Account::enable()
{
    QProcess ls;
    ls.start(QString("mc-tool enable %1").arg(accountid));
    if (!ls.waitForFinished()) {
        qWarning() << Q_FUNC_INFO << "Can't wait for finished";
        return;
    }

    refresh();
}

void Account::disable()
{
    QProcess ls;
    ls.start(QString("mc-tool disable %1").arg(accountid));
    if (!ls.waitForFinished()) {
        qWarning() << Q_FUNC_INFO << "Can't wait for finished";
        return;
    }

    refresh();
}

void Account::remove()
{
    QProcess ls;
    ls.start(QString("mc-tool remove %1").arg(accountid));
    if (!ls.waitForFinished()) {
        qWarning() << Q_FUNC_INFO << "Can't wait for finished";
        return;
    }

    emit accountRemoved();
}
