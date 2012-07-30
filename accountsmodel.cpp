#include <QProcess>
#include <QDebug>

#include "accountsmodel.h"

AccountsModel::AccountsModel(QObject *parent)
    : QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles.insert(AccountRole, "account");
    setRoleNames(roles);

    refresh();
}

void AccountsModel::refresh()
{
    QProcess ls;
    ls.start("mc-tool list");
    if (!ls.waitForFinished()) {
        qWarning() << Q_FUNC_INFO << "Can't wait for finished";
        return;
    }

    QByteArray result = ls.readAll();

    beginResetModel();
    qDeleteAll(accounts);
    accounts.clear();

    foreach (QString id, result.split('\n')) {
        Account *account = new Account(this);
        connect(account, SIGNAL(accountRemoved()), SLOT(refresh()));
        account->setId(id);
        accounts.append(account);
        qDebug() << Q_FUNC_INFO << id;
    }

    endResetModel();
}

int AccountsModel::rowCount(const QModelIndex&) const
{
    return accounts.length();
}

QVariant AccountsModel::data(const QModelIndex &idx, int role) const
{
    if (role == AccountRole)
        return QVariant::fromValue<Account *>(accounts.at(idx.row()));
    return QVariant();
}

bool AccountsModel::createAccount(const QString &protocol, const QString &user, const QString &password)
{
    errstring = QString("no error");

    if (protocol == "XMPP") {
        QStringList args;
        args.append("add");
        args.append("gabble/jabber");
        args.append(user);
        args.append("string:account=" + user);
        args.append("string:password=" + password);

        QProcess ls;
        ls.start("mc-tool", args);
        if (!ls.waitForFinished()) {
            errstring = QString("mc-tool waitForFinished failed, QProcess says:%1").arg(ls.error());
            qWarning() << Q_FUNC_INFO << "Can't wait for finished";
            return false;
        }

        if (ls.exitCode() != 0) {
            errstring = QString("mc-tool add returned: %1").arg(ls.exitCode());
            qWarning() << Q_FUNC_INFO << "mc-tool add returned: " << ls.exitCode();
            return false;
        }

        QByteArray result = ls.readAll();
        args.clear();

        args.append("enable");
        args.append(result);
        ls.start("mc-tool", args);

        args.clear();
        args.append("auto-connect");
        args.append(result);
        args.append("on");
        refresh();
        return true;
    } else if (protocol == "SIP") {
        errstring = QString("Don't know what to do for a SIP account yet");
        return false;
    } else {
        errstring = QString("Unknown protocol: %1").arg(protocol);
        return false;
    }
}
