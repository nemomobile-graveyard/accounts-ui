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
    ls.start(QString("ls -al %1").arg(accountid));
    if (!ls.waitForFinished()) {
        qWarning() << Q_FUNC_INFO << "Can't wait for finished";
        return;
    }

    QByteArray result = ls.readAll();
    accountDetails = QString::fromUtf8(result);
    emit detailsChanged();
}

