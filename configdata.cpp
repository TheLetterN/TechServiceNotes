#include "configdata.h"
#include <QFile>
#include <QTextStream>
#include <QObject>

ConfigData::ConfigData()
{
    license_status = false;
}

//loads config data from file, and creates a new config file if none is found.
void ConfigData::loadData(const QString &filename)
{
    QTextStream sout(stdout);

    QFile inFile(filename);
    if(!inFile.exists()) {
        sout << QObject::tr("Configuration file does not exist, creating it... ");
        saveData(filename);
    }
    if(!inFile.open(QIODevice::ReadOnly)) {
        sout << QObject::tr("Error, could not open %1!").arg(filename) << endl;
        return;
    } else {
        sout << QObject::tr("Loading main config file.");
        QTextStream fin(&inFile);

        QString tempText;

        while(!fin.atEnd()) {
            fin >> tempText;

            if (tempText.contains("LICENSE_ACCEPTED=")) {
                if (tempText.endsWith("true")) {
                    license_status = true;
                } else {
                    license_status = false;
                }
            }
            inFile.close();
        }
    }
    sout << endl;
}

//saves config information to file
void ConfigData::saveData(const QString &filename)
{
    QTextStream sout(stdout);

    QFile outFile(filename);
    if(!outFile.open(QIODevice::WriteOnly)) {
        sout << QObject::tr("Error, could not open %1!").arg(filename) << endl;
        return;
    } else {
        sout << QObject::tr("Writing config data to %1.").arg(filename) << endl;

        QTextStream fout(&outFile);

        fout << "LICENSE_ACCEPTED=" + licenseStatusToText() << endl;
    }

}

bool ConfigData::getLicenseStatus()
{
    return license_status;
}

void ConfigData::setLicenseStatus(bool status)
{
    license_status = status;
}

QString ConfigData::licenseStatusToText()
{
    if (license_status == true)
        return "true";
    else
        return "false";
}
