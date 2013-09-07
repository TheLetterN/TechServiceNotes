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

//    QString license;

//    QTextStream sout(stdout);

//    //open the license file to display
//    QFile inFile("license.txt");

//    if(!inFile.open(QIODevice::ReadOnly)) {
//        sout << "Error, could not load license file!" << endl;
//        return;
//    } else {
//        QTextStream fin(&inFile);
//        license = fin.readAll();
//        inFile.close();

//        ui->licenseBrowser->setText(license);
//    }





//    ui->licenseBrowser->setText(license);
}

LicenseDialog::~LicenseDialog()
{
    delete ui;
}
