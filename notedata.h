//Tech Service Notes - A tracker for tech support services
//Copyright (C) 2013 by Fluffyware

//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.


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

    void parseFromFile(QString);



};

#endif // NOTEDATA_H
