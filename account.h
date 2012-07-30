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

signals:
    void idChanged();
    void detailsChanged();

private:
    QString accountid;
    QString accountDetails;
};

Q_DECLARE_METATYPE(Account*)

