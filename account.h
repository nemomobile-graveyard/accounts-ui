#include <QObject>
#include <QMetaType>

class Account : public QObject
{
    Q_OBJECT
public:
    Account(QObject *parent = 0);

    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    void setId(const QString &id);
    QString id() const;

    Q_PROPERTY(QString details READ details NOTIFY detailsChanged)
    QString details() const;

    Q_INVOKABLE void refresh();

    Q_INVOKABLE void enable();
    Q_INVOKABLE void disable();
    Q_INVOKABLE void remove();

    Q_INVOKABLE void goOnline();
    Q_INVOKABLE void goOffline();

signals:
    void idChanged();
    void detailsChanged();
    void accountRemoved();

private:
    QString accountid;
    QString accountDetails;
};

Q_DECLARE_METATYPE(Account*)

