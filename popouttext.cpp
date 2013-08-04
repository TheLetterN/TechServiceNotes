#include "popouttext.h"
#include "ui_popouttext.h"

PopOutText::PopOutText(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PopOutText)
{
    ui->setupUi(this);

    ui->textBrowser->setReadOnly(true);
    setWindowTitle(tr("Service Notes"));
}


PopOutText::~PopOutText()
{
    delete ui;
}

void PopOutText::setText(QString content)
{
    ui->textBrowser->setText(content);
}
