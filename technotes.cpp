#include "technotes.h"
#include "ui_technotes.h"
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>

#ifdef Q_OS_LINUX
QString data_path = QDir::homePath() + "/.config/Fluffyware/TechServiceNotes";
#endif
#ifdef Q_OS_WIN32
QString data_path = "/ProgramData/Fluffyware/TechServiceNotes";
#endif

TechNotes::TechNotes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TechNotes)
{
    ui->setupUi(this);

    currentService = new NoteData;

    currentServiceList = &openServiceList;
    loadServiceList();

    updateInterface(ViewMode);

    connect(ui->newServiceButton, SIGNAL(clicked()), this, SLOT(newService()));
    connect(ui->servicesComboBox, SIGNAL(activated(QString)), this, SLOT(loadServiceList()));
    connect(ui->servicesListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectService()));
    connect(ui->editServiceButton, SIGNAL(clicked()), this, SLOT(editService()));
    connect(ui->updateServiceButton, SIGNAL(clicked()), this, SLOT(updateService()));
    connect(ui->exportServiceButton, SIGNAL(clicked()), this, SLOT(exportService()));
    connect(ui->popOutButton, SIGNAL(clicked()), this, SLOT(popOutService()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->deleteServiceButton, SIGNAL(clicked()), this, SLOT(deleteService()));
    connect(ui->serviceStatusComboBox, SIGNAL(activated(QString)), this, SLOT(changeServiceStatus()));
    connect(ui->applyButton, SIGNAL(clicked()), this, SLOT(saveService()));
    connect(ui->servicesListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(popOutService()));
    connect(ui->printServiceButton, SIGNAL(clicked()), this, SLOT(printService()));

    setWindowTitle("Tech Service Notes");
}

TechNotes::~TechNotes()
{
    delete ui;
}

void TechNotes::updateInterface(TechNotes::Mode mode)
{
    currentMode = mode;

    switch (currentMode) {
    case ViewMode: {
        //turn off stuff we can't use while viewing
        ui->firstNameEdit->setReadOnly(true);
        ui->firstNameEdit->setEnabled(false);
        ui->lastNameEdit->setReadOnly(true);
        ui->lastNameEdit->setEnabled(false);
        ui->phoneNumberEdit->setReadOnly(true);
        ui->phoneNumberEdit->setEnabled(false);
        ui->servicesEdit->setReadOnly(true);
        ui->servicesEdit->setEnabled(false);
        ui->startedDateTimeEdit->setReadOnly(true);
        ui->startedDateTimeEdit->setEnabled(false);
        ui->dueDateTimeEdit->setReadOnly(true);
        ui->dueDateTimeEdit->setEnabled(false);
        ui->computerTypeComboBox->setEnabled(false);
        ui->computerModelEdit->setReadOnly(true);
        ui->computerModelEdit->setEnabled(false);
        ui->locationComboBox->setEnabled(false);
        ui->additionalItemsEdit->setReadOnly(true);
        ui->notesEdit->setReadOnly(true);
        ui->applyButton->setEnabled(false);
        ui->cancelButton->setEnabled(false);

        //check to see if a service is present, and enable/disable relevant UI elements
        bool presentService = !currentService->isEmpty();

        ui->exportServiceButton->setEnabled(presentService);
        ui->deleteServiceButton->setEnabled(presentService);
        ui->updateServiceButton->setEnabled(presentService);
        ui->editServiceButton->setEnabled(presentService);
        ui->popOutButton->setEnabled(presentService);
        ui->currentTechnicianComboBox->setEnabled(presentService);
        ui->serviceStatusComboBox->setEnabled(presentService);
        ui->printServiceButton->setEnabled(presentService);

        //turn on stuff we can use while viewing
        ui->servicesComboBox->setEnabled(true);
        ui->servicesListWidget->setEnabled(true);
        ui->newServiceButton->setEnabled(true);

    }break;

    case UpdateMode: {
        //turn off stuff we can't use while updating the service
        ui->servicesComboBox->setEnabled(false);
        ui->servicesListWidget->setEnabled(false);
        ui->exportServiceButton->setEnabled(false);
        ui->deleteServiceButton->setEnabled(false);
        ui->updateServiceButton->setEnabled(false);
        ui->newServiceButton->setEnabled(false);
        ui->editServiceButton->setEnabled(false);

        ui->firstNameEdit->setEnabled(false);
        ui->lastNameEdit->setEnabled(false);
        ui->phoneNumberEdit->setEnabled(false);
        ui->servicesEdit->setEnabled(false);
        ui->startedDateTimeEdit->setEnabled(false);
        ui->dueDateTimeEdit->setEnabled(false);
        ui->computerTypeComboBox->setEnabled(false);
        ui->computerModelEdit->setEnabled(false);
        ui->locationComboBox->setEnabled(false);
        ui->additionalItemsEdit->setEnabled(false);

        //turn on stuff we can use while updating the service
        ui->notesEdit->setReadOnly(false);
        ui->notesEdit->setEnabled(true);
        ui->applyButton->setEnabled(true);
        ui->currentTechnicianComboBox->setEnabled(true);
        ui->serviceStatusComboBox->setEnabled(true);
        ui->cancelButton->setEnabled(true);
    }break;

    case EditMode: {
        //turn off stuff we can't use while editing the service
        ui->servicesComboBox->setEnabled(false);
        ui->servicesListWidget->setEnabled(false);
        ui->exportServiceButton->setEnabled(false);
        ui->deleteServiceButton->setEnabled(false);
        ui->updateServiceButton->setEnabled(false);
        ui->newServiceButton->setEnabled(false);
        ui->editServiceButton->setEnabled(false);

        //turn on stuff we can use while editing the service
        ui->firstNameEdit->setReadOnly(false);
        ui->firstNameEdit->setEnabled(true);
        ui->lastNameEdit->setReadOnly(false);
        ui->lastNameEdit->setEnabled(true);
        ui->phoneNumberEdit->setReadOnly(false);
        ui->phoneNumberEdit->setEnabled(true);
        ui->servicesEdit->setReadOnly(false);
        ui->servicesEdit->setEnabled(true);
        ui->startedDateTimeEdit->setReadOnly(false);
        ui->startedDateTimeEdit->setEnabled(true);
        ui->dueDateTimeEdit->setReadOnly(false);
        ui->dueDateTimeEdit->setEnabled(true);
        ui->computerTypeComboBox->setEnabled(true);
        ui->computerModelEdit->setReadOnly(false);
        ui->computerModelEdit->setEnabled(true);
        ui->locationComboBox->setEnabled(true);
        ui->additionalItemsEdit->setReadOnly(false);
        ui->additionalItemsEdit->setEnabled(true);
        ui->notesEdit->setReadOnly(false);
        ui->notesEdit->setEnabled(true);
        ui->currentTechnicianComboBox->setEnabled(true);
        ui->serviceStatusComboBox->setEnabled(true);
        ui->applyButton->setEnabled(true);
        ui->cancelButton->setEnabled(true);
    }break;
    }
}

void TechNotes::newService()
{
    updateInterface(EditMode);

    delete currentService;
    currentService = new NoteData;

    clearService();
}

void TechNotes::updateService()
{
    updateInterface(UpdateMode);
    //automatically insert a string into the Notes textEdit box in the format of:
    //Updated by: <current technician> @ <current date and time>:
    ui->notesEdit->setText(ui->notesEdit->toPlainText() + "\n\nUpdate by " +
                           ui->currentTechnicianComboBox->currentText() + " @ " +
                           QDateTime::currentDateTime().toString("MM/dd hh.mm AP") + ":\n\n");
}

void TechNotes::editService()
{
    updateInterface(EditMode);
}

//Exports the service to a plain text file using NoteData::formatForText() to format
void TechNotes::exportService()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Service to Text File"), "", tr("Text (*.txt);;All Files(*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile outFile(fileName);
        if (!outFile.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to save file "), outFile.errorString());
            return;
        } else {
            QTextStream out(&outFile);
            out << currentService->formatForText();
        }
    }
}

//Pops out service information in a more readable PopOutText window, using NoteData::formatForText() to format it
void TechNotes::popOutService()
{
    popout = new PopOutText;
    popout->setText(currentService->formatForText());
    popout->show();
}

void TechNotes::saveService()
{
    if (ui->firstNameEdit->text().isEmpty() ||
            ui->lastNameEdit->text().isEmpty() ||
            ui->phoneNumberEdit->text().isEmpty() ||
            ui->servicesEdit->text().isEmpty()) {

        QMessageBox::information(this, tr("Missing Information"), tr("You must enter a first name, last name, phone number, and list of services."));

    } else {
        //Save the list entry information so that we can delete it from the relevant *ServiceList map if the service info changes
        QString oldListEntry = listEntry();

        delete currentService;
        currentService = new NoteData(ui->firstNameEdit->text(),
                                      ui->lastNameEdit->text(),
                                      ui->phoneNumberEdit->text(),
                                      ui->servicesEdit->text(),
                                      ui->startedDateTimeEdit->dateTime(),
                                      ui->dueDateTimeEdit->dateTime(),
                                      currentService->computerTypeFromText(ui->computerTypeComboBox->currentText()),
                                      ui->computerModelEdit->text(),
                                      ui->locationComboBox->currentText(),
                                      ui->additionalItemsEdit->toPlainText(),
                                      ui->notesEdit->toPlainText(),
                                      ui->currentTechnicianComboBox->currentText(),
                                      currentService->serviceStatusFromText(ui->serviceStatusComboBox->currentText()));
        //check to see if the service previously existed (IE, was edited) and remove the stale list entry
        if (oldListEntry != "") {
            currentServiceList->remove(oldListEntry);
        }
        //insert a list entry into the active service list map
        currentServiceList->insert(listEntry(), *currentService);

        saveServiceToFile();

        updateInterface(ViewMode);
        loadServiceList();
    }
}

void TechNotes::loadServiceList()
{
    ui->servicesListWidget->clear();

    QDir path_to_files;
    QStringList filters;
    filters << "*.tsn";

    if (ui->servicesComboBox->currentText() == "Closed Services") {
        currentServiceList = &closedServiceList;
        if (currentServiceList->empty()) {
            path_to_files.setPath(data_path + "/closed");
            QStringList files = path_to_files.entryList(filters);
            foreach (QString fileName, files) {
                fileName = path_to_files.path() + "/" + fileName;
                currentService->loadFromFile(fileName);
                currentServiceList->insert(listEntry(), *currentService);
                //ui->servicesListWidget->addItem(listEntry());
            }
        }

    } else {
        currentServiceList = &openServiceList;
        if (currentServiceList->empty()) {
            path_to_files.setPath(data_path + "/open");
            QStringList files = path_to_files.entryList(filters);

            foreach (QString fileName, files) {
                fileName = path_to_files.path() + "/" + fileName;
                currentService->loadFromFile(fileName);
                currentServiceList->insert(listEntry(), *currentService);
                //ui->servicesListWidget->addItem(listEntry());
            }
        }
    }

    foreach (QString listEntryItem, currentServiceList->keys()) {
        ui->servicesListWidget->addItem(listEntryItem);
    }
    ui->servicesListWidget->sortItems(Qt::AscendingOrder);
}

void TechNotes::selectService()
{
    QString topSelectedService = ui->servicesListWidget->currentItem()->text();
    *currentService = currentServiceList->value(topSelectedService);

    populateServiceForm();
    updateInterface(ViewMode);
}

void TechNotes::changeServiceStatus()
{
    QString selectedStatus = ui->serviceStatusComboBox->currentText();
    currentService->serviceStatusFromText(selectedStatus);

    if (selectedStatus == "Closed") {
        closeService();
    } else {
        openService();
    }

    updateInterface(ViewMode);
    loadServiceList();
}

void TechNotes::deleteService()
{
    QString openOrClosed;
    if (currentService->getSStatus() == NoteData::Closed)
        openOrClosed = "/closed/";
    else
        openOrClosed = "/open/";

    QString fileName = data_path + openOrClosed +
            currentService->getStartedDate().toString("yyyy_MM_dd_hh_mm_ss_") +
            currentService->getLastName() + ".tsn";

    QFile file(fileName);

    int confirmDelete = QMessageBox::question(this, tr("Delete Service"),
                                              tr("Are you sure you want to delete %1's service?\nThis cannot be undone!").arg(currentService->getFirstName() + " " + currentService->getLastName()),
                                              QMessageBox::Yes | QMessageBox::No);
    if (confirmDelete == QMessageBox::Yes) {
        file.remove();
        QMessageBox::information(this, tr("Delete Successful"),
                                 tr("%1's service has been deleted!").arg(currentService->getFirstName() + " " + currentService->getLastName()));
        currentServiceList->remove(listEntry());
        delete currentService;
        currentService = new NoteData;
        clearService();
        loadServiceList();
    }


}

void TechNotes::cancel()
{
    updateInterface(ViewMode);
    populateServiceForm();
}

void TechNotes::printService()
{
    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print Service Note");

    if (dialog->exec() == QDialog::Accepted) {
        QPainter printPainter;
        printPainter.begin(&printer);

        printPainter.drawText(42, 42, 700, 1000, Qt::TextWordWrap, currentService->formatForText());

        printPainter.end();
    }
}

void TechNotes::clearService()
{
    ui->firstNameEdit->clear();
    ui->lastNameEdit->clear();
    ui->phoneNumberEdit->clear();
    ui->servicesEdit->clear();
    ui->startedDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dueDateTimeEdit->setDateTime(QDateTime::currentDateTime().addDays(2));
    ui->computerTypeComboBox->setCurrentIndex(0);
    ui->computerModelEdit->clear();
    ui->locationComboBox->setCurrentIndex(0);
    ui->additionalItemsEdit->clear();
    ui->notesEdit->clear();
    ui->currentTechnicianComboBox->setCurrentIndex(0);
    ui->serviceStatusComboBox->setCurrentIndex(0);
}

void TechNotes::saveServiceToFile()
{
    QDir path_to_file;
    if (currentService->getSStatus() == NoteData::Closed) {
        path_to_file.setPath(data_path + "/closed");
    } else {
        path_to_file.setPath(data_path + "/open");
    }

    QTextStream textOut(stdout);

    if (!path_to_file.exists()) {
        textOut << tr("\"%1\" does not exist. Attempting to create it... ").arg(path_to_file.path());
        if (path_to_file.mkpath(path_to_file.path()))
            textOut << "successfully!";
        else
            textOut << "unsuccessfully. :(";
        textOut << endl;
    }

    if (path_to_file.exists()) {
        QString fileName = path_to_file.path() + "/" +
                currentService->getStartedDate().toString("yyyy_MM_dd_hh_mm_ss_") +
                currentService->getLastName() + ".tsn";

        currentService->saveToFile(fileName);
    }
}

void TechNotes::populateServiceForm()
{
    ui->firstNameEdit->setText(currentService->getFirstName());
    ui->lastNameEdit->setText(currentService->getLastName());
    ui->phoneNumberEdit->setText(currentService->getPhoneNumber());
    ui->servicesEdit->setText(currentService->getServices());
    ui->startedDateTimeEdit->setDateTime(currentService->getStartedDate());
    ui->dueDateTimeEdit->setDateTime(currentService->getDueDate());
    ui->computerTypeComboBox->setCurrentIndex(ui->computerTypeComboBox->findText(currentService->computerTypeToText()));
    ui->computerModelEdit->setText(currentService->getComputerModel());
    ui->locationComboBox->setCurrentIndex(ui->locationComboBox->findText(currentService->getLocation()));
    ui->additionalItemsEdit->setText(currentService->getAdditionalItems());
    ui->notesEdit->setText(currentService->getNotes());
    ui->currentTechnicianComboBox->setCurrentIndex(ui->currentTechnicianComboBox->findText(currentService->getCurrentTechnician()));
    ui->serviceStatusComboBox->setCurrentIndex(ui->serviceStatusComboBox->findText(currentService->serviceStatusToText()));

}

void TechNotes::closeService()
{
    QTextStream outt(stdout);
    QString openFileName = data_path + "/open/" +
            currentService->getStartedDate().toString("yyyy_MM_dd_hh_mm_ss_") +
            currentService->getLastName() + ".tsn";

    QString closedFileName = data_path + "/closed/" +
            currentService->getStartedDate().toString("yyyy_MM_dd_hh_mm_ss_") +
            currentService->getLastName() + ".tsn";

    QDir openFileLocation(openFileName);

    if (openFileLocation.exists(openFileName)) {
        openFileLocation.rename(openFileName, closedFileName);

        outt << "File " << openFileName << " moved to " << closedFileName << endl;
        saveService();
    } else {
        outt << "Error: " << openFileName << " could not be moved." << endl;
        saveService();
    }
    openServiceList.remove(listEntry());
    closedServiceList.insert(listEntry(), *currentService);
    loadServiceList();
}

void TechNotes::openService()
{
    QTextStream outt(stdout);

    QString openFileName = data_path + "/open/" +
            currentService->getStartedDate().toString("yyyy_MM_dd_hh_mm_ss_") +
            currentService->getLastName() + ".tsn";

    QString closedFileName = data_path + "/closed/" +
            currentService->getStartedDate().toString("yyyy_MM_dd_hh_mm_ss_") +
            currentService->getLastName() + ".tsn";

    QDir closedFileLocation(closedFileName);

    if (closedFileLocation.exists(closedFileName)) {
        closedFileLocation.rename(closedFileName, openFileName);

        outt << "File " << closedFileName << " moved to " << openFileName << endl;
        saveService();
    } else {
        saveService();
    }
    closedServiceList.remove(listEntry());
    openServiceList.insert(listEntry(), *currentService);
    loadServiceList();
}

QString TechNotes::listEntry()
{
    if (currentService->getLastName() == "") {
        return "";
    } else {
        QString entry = "Due: " + currentService->getDueDate().toString("MM/dd @ hh.mm AP") + "\t" +
                currentService->getLastName() + ", " + currentService->getFirstName() + "\t\t" +
                currentService->getComputerModel() + " in " + currentService->getLocation();
        return entry;
    }
}
