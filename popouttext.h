#ifndef POPOUTTEXT_H
#define POPOUTTEXT_H

#include <QWidget>
#include <QString>

namespace Ui {
class PopOutText;
}

class PopOutText : public QWidget
{
    Q_OBJECT
    
public:
    explicit PopOutText(QWidget *parent = 0);
    ~PopOutText();
    void setText(QString content);
    
private:
    Ui::PopOutText *ui;
};

#endif // POPOUTTEXT_H
