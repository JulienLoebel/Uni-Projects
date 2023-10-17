#ifndef ADDCUSTOMERDIALOG_H
#define ADDCUSTOMERDIALOG_H
#include "travelagency.h"

#include <QDialog>

namespace Ui {
class AddCustomerDialog;
}

class AddCustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomerDialog(std::shared_ptr<TravelAgency> pTravelAgency, QWidget *parent = nullptr);
    ~AddCustomerDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddCustomerDialog *ui;
    std::shared_ptr<TravelAgency> travelagency;
};

#endif // ADDCUSTOMERDIALOG_H
