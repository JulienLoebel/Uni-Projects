#include "checkdialog.h"
#include "ui_checkdialog.h"

CheckDialog::CheckDialog(std::shared_ptr<TravelAgency> pTravelAgency, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkDialog)
{
    travelagency = pTravelAgency;
    ui->setupUi(this);

    createTable();
}

CheckDialog::~CheckDialog()
{
    delete ui;
}

void CheckDialog::createTable()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int rows = travelagency->getAllTravels().size();
    ui->tableWidget->setRowCount(rows);

    QIcon checked = QIcon("C:\\Users\\Julien\\Downloads\\images.png");
    QIcon unChecked = QIcon("C:\\Users\\Julien\\Downloads\\169779.png");

    QTableWidgetItem *item;

    std::shared_ptr<Travel> travel;

    for(int i = 1; i <= rows; i++) {

        travel = travelagency->findTravel(i);

        item = new QTableWidgetItem(QString::number(i));
        ui->tableWidget->setItem(i-1, 0, item);

        if (travel->checkEnoughHotels()){
            item = new QTableWidgetItem();
            item->setIcon(checked);
        } else {
            item = new QTableWidgetItem();
            item->setIcon(unChecked);
        }
        ui->tableWidget->setItem(i-1, 1, item);

        if (travel->checkNoUselessHotel()){
            item = new QTableWidgetItem();
            item->setIcon(checked);
        } else {
            item = new QTableWidgetItem();
            item->setIcon(unChecked);
        }
        ui->tableWidget->setItem(i-1, 2, item);

        if (travel->checkNoUselessRentalCar()){
            item = new QTableWidgetItem();
            item->setIcon(checked);
        } else {
            item = new QTableWidgetItem();
            item->setIcon(unChecked);
        }
        ui->tableWidget->setItem(i-1, 3, item);

        if (travel->checkRoundtrip()){
            item = new QTableWidgetItem();
            item->setIcon(checked);
        } else {
            item = new QTableWidgetItem();
            item->setIcon(unChecked);
        }
        ui->tableWidget->setItem(i-1, 4, item);
    }
}
