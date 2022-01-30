#ifndef BLANKPOPUP_H
#define BLANKPOPUP_H

#include <QDialog>

namespace Ui {
class BlankPopup;
}

class BlankPopup : public QDialog
{
    Q_OBJECT

public:
    explicit BlankPopup(QWidget *parent = nullptr);
    ~BlankPopup();

    char GetLetter();

    void reject();

private slots:
    void on_pushButton_clicked();

private:
    Ui::BlankPopup *ui;
    char letter;
};

#endif // BLANKPOPUP_H
