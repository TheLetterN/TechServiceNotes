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
    QString listEntry();
};

#endif // TECHNOTES_H
