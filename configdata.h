#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <QString>

class ConfigData
{
public:
    ConfigData();
    void loadData(const QString &filename);
    void saveData(const QString &filename);
    void dataFolderExists(const QString &path);
    bool getLicenseStatus();
    void setLicenseStatus(bool);

    QString licenseStatusToText();

protected:
    bool license_status;
};

#endif // CONFIGDATA_H
