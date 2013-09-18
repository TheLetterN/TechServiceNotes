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


#include "notedata.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

NoteData::NoteData()
{
    firstName = "";
    lastName = "";
    phoneNumber = "";
    orderNumber = "";
    services = "";
    startedDate = QDateTime::currentDateTime();
    dueDate = QDateTime::currentDateTime().addDays(2);
    cType = Other;
    computerModel = "";
    additionalItems = "";
    notes = "";
    currentTechnician = "";
    sStatus = NotStarted;


}

NoteData::NoteData(const QString &fn,                   //First Name
                   const QString &ln,                   //Last Name
                   const QString &pn,                   //Phone Number
                   const QString &on,                   //Order Number
                   const QString &sv,                   //Services
                   const QDateTime &sd,                 //Start Date
                   const QDateTime &dd,                 //Due Date
                   const NoteData::ComputerType &ct,    //Computer Type
                   const QString &cm,                   //Computer Model
                   const QString &lc,                   //Location
                   const QString &ai,                   //Additional Items
                   const QString &nt,                   //Notes
                   const QString &tc,                   //Current Technician
                   const NoteData::ServiceStatus &ss)   //Service Status
{
    firstName = fn;
    lastName = ln;
    phoneNumber = pn;
    orderNumber = on;
    services = sv;
    startedDate = sd;
    dueDate = dd;
    cType = ct;
    computerModel = cm;
    location = lc;
    additionalItems = ai;
    notes = nt;
    currentTechnician = tc;
    sStatus = ss;
}

void NoteData::saveToFile(const QString &fileName)
{
    QFile outFile(fileName);
    if (!outFile.open(QIODevice::WriteOnly)) {
        return;
    } else {
        QDataStream outFileStream(&outFile);
        outFileStream.setVersion(QDataStream::Qt_4_8);

        outFileStream <<
                         "FIRST_NAME=" + firstName <<
                         "LAST_NAME=" + lastName <<
                         "PHONE_NUMBER=" + phoneNumber <<
                         "ORDER_NUMBER=" + orderNumber <<
                         "SERVICES=" + services <<
                         "STARTED_DATE=" + startedDate.toString() <<
                         "DUE_DATE=" + dueDate.toString() <<
                         "COMPUTER_TYPE=" + computerTypeToText() <<
                         "COMPUTER_MODEL=" + computerModel <<
                         "LOCATION=" + location <<
                         "ADDITIONAL_ITEMS=" + additionalItems <<
                         "NOTES=" + notes <<
                         "CURRENT_TECHNICIAN=" + currentTechnician <<
                         "SERVICES_STATUS=" + serviceStatusToText();
        outFile.close();
    }
}

void NoteData::loadFromFile(const QString &fileName)
{

    QTextStream textOut(stdout);
    QFile inFile(fileName);
    if(!inFile.open(QIODevice::ReadOnly)) {
        textOut << "Error, could not load file: " << fileName << endl;
        return;
    } else {
        QDataStream inFileStream(&inFile);
        inFileStream.setVersion(QDataStream::Qt_4_8);

        QString tempCompType;
        QString tempStatusType;

        QString tempText;

        //Gets the first chunk of data so we can test it to see what format the database is in

        inFileStream >> tempText;

        //Checks to see if files are in the original, not-very-expandable format, and fixes them if so
        if (!tempText.contains("=")) {

            firstName = tempText;

            inFileStream >>  lastName >>
                             phoneNumber >>
                             services >>
                             startedDate >>
                             dueDate >>
                             tempCompType >>
                             computerModel >>
                             location >>
                             additionalItems >>
                             notes >>
                             currentTechnician >>
                             tempStatusType;
            cType = computerTypeFromText(tempCompType);
            sStatus = serviceStatusFromText(tempStatusType);
            textOut << fileName << " is using an outdated format. Converting to new format..." << endl;

            saveToFile(fileName);



        } else {
            textOut << "Loaded file: " << fileName << endl;
            parseFromFile(tempText);

            while (!inFileStream.atEnd()) {
                inFileStream >> tempText;
                parseFromFile(tempText);
            }
        }
    }
}

QString NoteData::formatForText()
{
    QString formattedNote = "";
    formattedNote += "Customer: " + firstName + " " + lastName + "\n";
    formattedNote += "Phone Number: " + phoneNumber + "\n";
    formattedNote += "Order Number: " + orderNumber + "\n";
    formattedNote += "Services: " + services + "\n";
    formattedNote += "Status: " + serviceStatusToText() + "\n";
    formattedNote += "Started: " + startedDate.toString() + "\t\t" + "Due: " + dueDate.toString() + "\n";
    formattedNote += "Computer Type: " + computerTypeToText() + "\t\t\t" + "Model: " + computerModel + "\n";
    formattedNote += "Location: " + location + "\n";
    formattedNote += "Additional Items: " + additionalItems + "\n";
    formattedNote += "\n---\n\n";
    formattedNote += "Notes:\n" + notes;

    return formattedNote;
}

QString NoteData::computerTypeToText()
{
    switch (cType) {
    case Laptop:
        return "Laptop";
        break;
    case Desktop:
        return "Desktop";
        break;
    case Other:
        return "Other";
        break;
    }
}

QString NoteData::serviceStatusToText()
{
    switch (sStatus) {
    case NotStarted:
        return "Not Started";
        break;
    case InProgress:
        return "In Progress";
        break;
    case CustomerCalled:
        return "Customer Called";
        break;
    case Closed:
        return "Closed";
        break;
    }
}

NoteData::ComputerType NoteData::computerTypeFromText(const QString &text)
{
    if (text == "Laptop")
        return Laptop;
    else if (text == "Desktop")
        return Desktop;
    else
        return Other;
}

NoteData::ServiceStatus NoteData::serviceStatusFromText(const QString &text)
{
    if (text == "Not Started") {
        return NotStarted;
    } else if (text == "In Progress") {
        return InProgress;
    } else if (text == "Customer Called") {
        return CustomerCalled;
    } else {
        return Closed;
    }
}


bool NoteData::isEmpty()
{
    if (lastName == "")
        return true;
    else
        return false;
}

//Getters and Setters
NoteData::ServiceStatus NoteData::getSStatus() const
{
    return sStatus;
}

void NoteData::setSStatus(const ServiceStatus &value)
{
    sStatus = value;
}

QString NoteData::getCurrentTechnician() const
{
    return currentTechnician;
}

void NoteData::setCurrentTechnician(const QString &value)
{
    currentTechnician = value;
}

QString NoteData::getNotes() const
{
    return notes;
}

void NoteData::setNotes(const QString &value)
{
    notes = value;
}

QString NoteData::getAdditionalItems() const
{
    return additionalItems;
}

void NoteData::setAdditionalItems(const QString &value)
{
    additionalItems = value;
}

QString NoteData::getComputerModel() const
{
    return computerModel;
}

void NoteData::setComputerModel(const QString &value)
{
    computerModel = value;
}

NoteData::ComputerType NoteData::getCType() const
{
    return cType;
}

void NoteData::setCType(const ComputerType &value)
{
    cType = value;
}

QDateTime NoteData::getDueDate() const
{
    return dueDate;
}

void NoteData::setDueDate(const QDateTime &value)
{
    dueDate = value;
}

QDateTime NoteData::getStartedDate() const
{
    return startedDate;
}

void NoteData::setStartedDate(const QDateTime &value)
{
    startedDate = value;
}

QString NoteData::getServices() const
{
    return services;
}

void NoteData::setServices(const QString &value)
{
    services = value;
}

QString NoteData::getPhoneNumber() const
{
    return phoneNumber;
}

void NoteData::setPhoneNumber(const QString &value)
{
    phoneNumber = value;
}

QString NoteData::getLastName() const
{
    return lastName;
}

void NoteData::setLastName(const QString &value)
{
    lastName = value;
}

QString NoteData::getFirstName() const
{
    return firstName;
}

void NoteData::setFirstName(const QString &value)
{
    firstName = value;
}

QString NoteData::getLocation() const
{
    return location;
}

void NoteData::setLocation(const QString &value)
{
    location = value;
}

void NoteData::parseFromFile(QString tempText) {
    if (tempText.contains("FIRST_NAME=")) {
        firstName = tempText.remove(0, tempText.indexOf("=") + 1);
    } else if (tempText.contains("LAST_NAME=")) {
        lastName = tempText.remove(0, tempText.indexOf("=") + 1);
    } else if (tempText.contains("PHONE_NUMBER=")) {
        phoneNumber = tempText.remove(0, tempText.indexOf("=") + 1);
    } else if (tempText.contains("ORDER_NUMBER=")) {
        orderNumber = tempText.remove(0, tempText.indexOf("=") + 1);
    } else if (tempText.contains("SERVICES=")) {
        services = tempText.remove(0, tempText.indexOf("=") + 1);
    } else if (tempText.contains("STARTED_DATE=")) {
        startedDate = QDateTime::fromString(tempText.remove(0, tempText.indexOf("=") + 1));
    } else if (tempText.contains("DUE_DATE=")) {
        dueDate = QDateTime::fromString(tempText.remove(0, tempText.indexOf("=") + 1));
    } else if (tempText.contains("COMPUTER_TYPE=")) {
        cType = computerTypeFromText(tempText.remove(0, tempText.indexOf("=") + 1));
    } else if (tempText.contains("COMPUTER_MODEL=")) {
        computerModel = tempText.remove(0, tempText.indexOf("=") + 1);
    } else if (tempText.contains("LOCATION=")) {
        location = tempText.remove(0, tempText.indexOf("=") + 1);
    } else if (tempText.contains("ADDITIONAL_ITEMS=")) {
        additionalItems = tempText.remove(0, tempText.indexOf("=") + 1);
    } else if (tempText.contains("NOTES=")) {
        notes = tempText.remove(0, tempText.indexOf("=") + 1);
    } else if (tempText.contains("CURRENT_TECHNICIAN=")) {
        currentTechnician = tempText.remove(0, tempText.indexOf("=") + 1);
    } else if (tempText.contains("SERVICES_STATUS=")) {
        sStatus = serviceStatusFromText(tempText.remove(0, tempText.indexOf("=") + 1));
    }
}

QString NoteData::getOrderNumber() const
{
    return orderNumber;
}

void NoteData::setOrderNumber(const QString &value)
{
    orderNumber = value;
}
