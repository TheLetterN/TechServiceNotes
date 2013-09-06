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


#ifndef TECHNOTES_H
#define TECHNOTES_H

#include <QMainWindow>
#include <QMap>
#include <QStringList>
#include "notedata.h"
#include "popouttext.h"

class QDateTime;
namespace Ui {
class TechNotes;
}

class TechNotes : public QMainWindow
{
    Q_OBJECT
    
public:
    enum Mode { ViewMode, EditMode, UpdateMode };

    explicit TechNotes(QWidget *parent = 0);
    ~TechNotes();

    void updateInterface(Mode mode);

private slots:
    void newService();
    void updateService();
    void editService();
    void exportService();
    void popOutService();
    void saveService();
    void loadServiceList();
    void selectService();
    void changeServiceStatus();
    void deleteService();
    void cancel();
    void printService();
    void editMiscNotes();
    void submitMiscNotes();

    
private:
    Ui::TechNotes *ui;
    NoteData *currentService;
    PopOutText *popout;

    QMap<QString, NoteData> *currentServiceList;
    QMap<QString, NoteData> openServiceList;
    QMap<QString, NoteData> closedServiceList;

    Mode currentMode;
    QStringList files;

    void clearService();
    void saveServiceToFile();
    void populateServiceForm();
    void closeService();
    void openService();
    void loadTechnicians();
    void loadMiscNotes();
    QString listEntry();
};

#endif // TECHNOTES_H
