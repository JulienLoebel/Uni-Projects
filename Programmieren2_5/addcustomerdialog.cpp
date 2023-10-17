#include "addcustomerdialog.h"
#include "ui_addcustomerdialog.h"
#include <iostream>

AddCustomerDialog::AddCustomerDialog(std::shared_ptr<TravelAgency> pTravelAgency, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCustomerDialog)
{
    travelagency = pTravelAgency;
    ui->setupUi(this);
}

AddCustomerDialog::~AddCustomerDialog()
{
    delete ui;
}

void AddCustomerDialog::on_buttonBox_accepted()
{
    std::string name = ui->lineEditName->text().toStdString();
    long id = travelagency->getAllCustomers().size() + 1;

    travelagency->addCustomer(id, name);
}

