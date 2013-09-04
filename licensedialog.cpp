#include "licensedialog.h"
#include "ui_licensedialog.h"

#include <QFile>
#include <QDir>
#include <QTextStream>

LicenseDialog::LicenseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LicenseDialog)
{
    ui->setupUi(this);
    ui->licenseBrowser->setReadOnly(true);

    QString license;

    QTextStream sout(stdout);

    //open the license file to display
    QFile inFile("license.txt");

    if(!inFile.open(QIODevice::ReadOnly)) {
        sout << "Error, could not load license file!" << endl;
        return;
    } else {
        QTextStream fin(&inFile);
        license = fin.readAll();
        inFile.close();

        ui->licenseBrowser->setText(license);
    }





    ui->licenseBrowser->setText(license);
}

LicenseDialog::~LicenseDialog()
{
    delete ui;
}
