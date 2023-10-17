#include "abcdialog.h"
#include "ui_abcdialog.h"

ABCDialog::ABCDialog(std::shared_ptr<TravelAgency> pTravelAgency, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::abcDialog)
{
    travelagency = pTravelAgency;
    ui->setupUi(this);

    showABCAnalyse();
}

ABCDialog::~ABCDialog()
{
    delete ui;
}

void ABCDialog::showABCAnalyse()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    double totalPrice = travelagency->getTotalPrice();
    double kumuliert = 0;
    double customerPrice{}, anteil{};

    int rows = travelagency->getAllCustomers().size();
    ui->tableWidget->setRowCount(rows);

    std::shared_ptr<Customer> customer;

    QTableWidgetItem *item;

    for (int i = 0; i < rows; i++) {
        customer = travelagency->getAllCustomers()[i];

        customerPrice = customer->getTotalCustomerPrice();

        item = new QTableWidgetItem(QString::number((customer->getId())));
        ui->tableWidget->setItem(i, 0, item);

        item = new QTableWidgetItem(QString::fromStdString(customer->getName()));
        ui->tableWidget->setItem(i, 1, item);

        item = new QTableWidgetItem(QString::number(customerPrice));
        ui->tableWidget->setItem(i, 2, item);

        anteil = customerPrice / totalPrice;

        item = new QTableWidgetItem(QString::number(anteil*100));
        ui->tableWidget->setItem(i, 3, item);

        kumuliert = kumuliert + anteil;

        item = new QTableWidgetItem(QString::number(kumuliert*100));
        ui->tableWidget->setItem(i, 4, item);

        if (kumuliert <= 0.8) {
            item = new QTableWidgetItem("A");
            ui->tableWidget->setItem(i, 5, item);
            ui->tableWidget->item(i,5)->setBackground(QBrush(QColor("green")));
        } else if (kumuliert <= 0.9) {
            item = new QTableWidgetItem("B");
            ui->tableWidget->setItem(i, 5, item);
            ui->tableWidget->item(i,5)->setBackground(QBrush(QColor("yellow")));
        } else {
            item = new QTableWidgetItem("C");
            ui->tableWidget->setItem(i, 5, item);
            ui->tableWidget->item(i,5)->setBackground(QBrush(QColor("red")));
        }

    }
}
