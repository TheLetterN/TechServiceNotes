#ifndef NOTEDATA_H
#define NOTEDATA_H
#include <QString>
#include <QDateTime>

class NoteData
{
public:
    enum ComputerType { Desktop, Laptop, Other };
    enum ServiceStatus { NotStarted, InProgress, CustomerCalled, Closed };

    NoteData();
    NoteData(const QString &fn, const QString &ln, const QString &pn, const QString &sv,
             const QDateTime &sd, const QDateTime &dd, const ComputerType &ct,
             const QString &cm, const QString &lc, const QString &ai, const QString &nt, const QString &tc,
             const ServiceStatus &ss);

    void saveToFile(const QString &fileName);
    void loadFromFile(const QString &fileName);
    QString formatForText();
    QString computerTypeToText();
    QString serviceStatusToText();
    ComputerType computerTypeFromText(const QString &text);
    ServiceStatus serviceStatusFromText(const QString &text);

    bool isEmpty();

    QString getPhoneNumber() const;
    void setPhoneNumber(const QString &value);

    QString getServices() const;
    void setServices(const QString &value);

    QDateTime getStartedDate() const;
    void setStartedDate(const QDateTime &value);

    QDateTime getDueDate() const;
    void setDueDate(const QDateTime &value);

    ComputerType getCType() const;
    void setCType(const ComputerType &value);

    QString getComputerModel() const;
    void setComputerModel(const QString &value);

    QString getAdditionalItems() const;
    void setAdditionalItems(const QString &value);

    QString getNotes() const;
    void setNotes(const QString &value);

    QString getCurrentTechnician() const;
    void setCurrentTechnician(const QString &value);

    ServiceStatus getSStatus() const;
    void setSStatus(const ServiceStatus &value);

    QString getFirstName() const;
    void setFirstName(const QString &value);

    QString getLastName() const;
    void setLastName(const QString &value);

    QString getLocation() const;
    void setLocation(const QString &value);

private:
    QString firstName;
    QString lastName;
    QString phoneNumber;
    QString services;
    QDateTime startedDate;
    QDateTime dueDate;
    ComputerType cType;
    QString computerModel;
    QString location;
    QString additionalItems;
    QString notes;
    QString currentTechnician;
    ServiceStatus sStatus;



};

#endif // NOTEDATA_H
