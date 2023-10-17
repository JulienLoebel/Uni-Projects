#ifndef CHECKDIALOG_H
#define CHECKDIALOG_H
#include "travelagency.h"

#include <QDialog>

namespace Ui {
class checkDialog;
}

class CheckDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckDialog(std::shared_ptr<TravelAgency> pTravelAgency, QWidget *parent = nullptr);
    ~CheckDialog();
    void createTable();

private:
    Ui::checkDialog *ui;
    std::shared_ptr<TravelAgency> travelagency;
};

#endif // CHECKDIALOG_H
