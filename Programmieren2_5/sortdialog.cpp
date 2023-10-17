#include "sortdialog.h"
#include "ui_sortdialog.h"
#include "sortfunktor.h"
#include <QMessageBox>

SortDialog::SortDialog(std::shared_ptr<TravelAgency> pTravelAgency, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortDialog)
{
    travelagency = pTravelAgency;
    ui->setupUi(this);
}

SortDialog::~SortDialog()
{
    delete ui;
}

void SortDialog::on_buttonBox_accepted()
{
    try {
        if (ui->radioButtonPreis->isChecked()) {
            travelagency->saveToJSON(SortFunktor::price);
        } else if (ui->radioButtonAbreise->isChecked()) {
            travelagency->saveToJSON(SortFunktor::fromDate);
        } else if (ui->radioButtonAnkunft->isChecked()) {
            travelagency->saveToJSON(SortFunktor::toDate);
        } else if (ui->radioButtonReiseID->isChecked()) {
            travelagency->saveToJSON(SortFunktor::travelId);
        }
    }
    catch (std::runtime_error& e) {
        QString exceptionText = QString::fromStdString(e.what());
        QMessageBox::information(this, "Fehler beim Schreiben der Buchungen", exceptionText);
    }

    QMessageBox::information(this, "Speichern", "Daten wurden erfolgreich gespeichert");
}

