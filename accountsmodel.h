#include <QAbstractListModel>

#include "account.h"

class AccountsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    AccountsModel(QObject *parent = 0);

    enum Roles {
        AccountRole = Qt::UserRole
    };

    Q_INVOKABLE void refresh();
    int rowCount(const QModelIndex&) const;
    QVariant data(const QModelIndex&, int) const;

    Q_INVOKABLE bool createAccount(const QString &protocol, const QString &user, const QString &password);
    Q_INVOKABLE QString errorString() const { return errstring; }

private:
    QList<Account *> accounts;
    QString errstring;
};

