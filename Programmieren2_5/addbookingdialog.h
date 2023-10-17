#ifndef ADDBOOKINGDIALOG_H
#define ADDBOOKINGDIALOG_H
#include "travelagency.h"

#include <QDialog>

namespace Ui {
class AddBookingDialog;
}

class AddBookingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookingDialog(std::shared_ptr<TravelAgency> pTravelAgency, QWidget *parent = nullptr);
    ~AddBookingDialog();

private slots:
    void on_radioButtonFlight_clicked();

    void on_radioButtonCar_clicked();

    void on_radioButtonHotel_clicked();

    void on_buttonBox_accepted();

    void on_radioButtonNeueReise_clicked();

    void on_radioButtonBestehendeReise_clicked();

private:
    Ui::AddBookingDialog *ui;
    std::shared_ptr<TravelAgency> travelagency;
};

#endif // ADDBOOKINGDIALOG_H
