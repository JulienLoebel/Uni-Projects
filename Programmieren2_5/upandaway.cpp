#include "upandaway.h"
#include "ui_upandaway.h"
#include <iostream>
#include <vector>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include "booking.h"
#include "flightbooking.h"
#include "rentalcarreservation.h"
#include "hotelbooking.h"
#include <typeinfo>
#include <QDate>
#include <QDesktopServices>
#include "addcustomerdialog.h"
#include "addbookingdialog.h"
#include "sortdialog.h"
#include "checkdialog.h"
#include "abcdialog.h"


using namespace std;

UpAndAway::UpAndAway(std::shared_ptr<TravelAgency> pTravelAgency, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UpAndAway)
{
    travelagency = pTravelAgency;
    ui->setupUi(this);

    ui->tableWidgetKunde->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetReise->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

UpAndAway::~UpAndAway()
{
    delete ui;
}


void UpAndAway::on_actionEinlesen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open A File", "C://");
    try {
        travelagency->readFile(filename.toStdString(),false);
    }
    catch (invalid_argument& e) {
        QString exceptionText = QString::fromStdString(e.what());
        QMessageBox::information(this, "Fehler beim Einlesen der Buchungen", exceptionText);
    }


}


void UpAndAway::on_pushButtonSuche_clicked()
{
    QStringList header = {"Reise-ID", "Beginn der Reise", "Ende der Reise"};
    ui->tableWidgetKunde->clear();
    ui->tableWidgetKunde->setHorizontalHeaderLabels(header);
    ui->tableWidgetKunde->setEditTriggers(QAbstractItemView::NoEditTriggers);

    std::shared_ptr<Customer> customer = travelagency->findCustomer(ui->spinBoxSuche->value());

    if (customer) {
        ui->lineEditKundenID->setText(QString::number(customer->getId()));
        ui->lineEditKundenName->setText(QString::fromStdString(customer->getName()));

        int rows = customer->getTravelList().size();
        ui->tableWidgetKunde->setRowCount(rows);

        QTableWidgetItem *item;

        for (int i = 0; i < rows; i++) {
            item = new QTableWidgetItem(QString::number(customer->getTravelList()[i]->getId()));
            ui->tableWidgetKunde->setItem(i,0,item);

            item = new QTableWidgetItem(customer->getTravelList()[i]->getFirstDate().toString("dddd, d. MMMM yyyy"));
            ui->tableWidgetKunde->setItem(i,1,item);

            item = new QTableWidgetItem(customer->getTravelList()[i]->getLastDate().toString("dddd, d. MMMM yyyy"));
            ui->tableWidgetKunde->setItem(i,2,item);

        }
    } else {
        QMessageBox::information(this, "Fehler", "Es gibt keinen Kunden mit dieser ID");
    }
}

void UpAndAway::on_tableWidgetKunde_cellDoubleClicked(int row)
{
    ui->tableWidgetReise->setEditTriggers(QAbstractItemView::NoEditTriggers);

    long id = ui->lineEditKundenID->text().toLong();

    std::shared_ptr<Customer> customer = travelagency->findCustomer(id);
    ui->lineEditReiseID->setText(QString::number(customer->getTravelList()[row]->getId()));

    int size = customer->getTravelList()[row]->getTravelBookings().size();
    ui->tableWidgetReise->setRowCount(size);

    QIcon hotelIcon = QIcon("C:\\Users\\Julien\\Downloads\\bed_icon.png");
    QIcon fligtIcon = QIcon("C:\\Users\\Julien\\Downloads\\Plane_icon.png");
    QIcon carIcon = QIcon("C:\\Users\\Julien\\Downloads\\car_icon.png");

    QTableWidgetItem *item;

    for (int i = 0; i < size; i++){
        item = new QTableWidgetItem(customer->getTravelList()[row]->getTravelBookings()[i]->getQFromDate().toString("dddd, d. MMMM yyyy"));
        ui->tableWidgetReise->setItem(i,1,item);

        item = new QTableWidgetItem(customer->getTravelList()[row]->getTravelBookings()[i]->getQToDate().toString("dddd, d. MMMM yyyy"));
        ui->tableWidgetReise->setItem(i,2,item);

        item = new QTableWidgetItem(QString::number(customer->getTravelList()[row]->getTravelBookings()[i]->getPrice()));
        ui->tableWidgetReise->setItem(i,3,item);

        std::shared_ptr<Booking> type = customer->getTravelList()[row]->getTravelBookings()[i];

        if (typeid(FlightBooking) == typeid(*type)) {
            item = new QTableWidgetItem();
            item->setIcon(fligtIcon);
            ui->tableWidgetReise->setItem(i,0,item);
        }
        else if (typeid(HotelBooking) == typeid(*type)) {
            item = new QTableWidgetItem();
            item->setIcon(hotelIcon);
            ui->tableWidgetReise->setItem(i,0,item);
        }
        else if (typeid(RentalCarReservation) == typeid(*type)) {
            item = new QTableWidgetItem();
            item->setIcon(carIcon);
            ui->tableWidgetReise->setItem(i,0,item);
        }
    }
}


void UpAndAway::on_tableWidgetReise_cellDoubleClicked(int row)
{
    long idKunde = ui->lineEditKundenID->text().toLong();
    long idReise = ui->lineEditReiseID->text().toLong();

    std::shared_ptr<Customer> customer = travelagency->findCustomer(idKunde);
    std::shared_ptr<Travel> travel = customer->checkTravelList(idReise);

    std::shared_ptr<Booking> type = travel->getTravelBookings()[row];

    if (typeid(FlightBooking) == typeid(*type)) {
        ui->lineEditId->setText(QString::fromStdString(type->getId()));
        ui->doubleSpinBoxPreis->setValue(type->getPrice());
        ui->dateEditAnkunft->setDate(type->getQFromDate());
        ui->dateEditAbreise->setDate(type->getQToDate());

        std::shared_ptr<FlightBooking> flightType = static_pointer_cast<FlightBooking>(type);

        ui->lineEditAbflugort->setText(QString::fromStdString(flightType->getFromDestination()));
        ui->lineEditAnkunftsort->setText(QString::fromStdString(flightType->getToDestination()));
        ui->lineEditAirline->setText(QString::fromStdString(flightType->getAirline()));
        ui->lineEditFlugklasse->setText(QString::fromStdString(flightType->getFullBookingClass()));

        ui->doubleSpinBoxPreis->setReadOnly(false);
        ui->dateEditAnkunft->setReadOnly(false);
        ui->dateEditAbreise->setReadOnly(false);
        ui->lineEditAbflugort->setReadOnly(false);
        ui->lineEditAnkunftsort->setReadOnly(false);
        ui->lineEditAirline->setReadOnly(false);
        ui->lineEditFlugklasse->setReadOnly(false);

        ui->tabWidget->setCurrentIndex(0);
    }
    else if (typeid(HotelBooking) == typeid(*type)) {
        ui->lineEditId_3->setText(QString::fromStdString(type->getId()));
        ui->doubleSpinBoxPreis_3->setValue(type->getPrice());
        ui->dateEditAnkunft_3->setDate(type->getQFromDate());
        ui->dateEditAbreise_3->setDate(type->getQToDate());

        shared_ptr<HotelBooking> hotelType = static_pointer_cast<HotelBooking>(type);

        ui->lineEditHotel->setText(QString::fromStdString(hotelType->getHotel()));
        ui->lineEditStadt->setText(QString::fromStdString(hotelType->getTown()));
        ui->lineEditZimmer->setText(QString::fromStdString(hotelType->getFullRoomType()));

        ui->doubleSpinBoxPreis_3->setReadOnly(false);
        ui->dateEditAnkunft_3->setReadOnly(false);
        ui->dateEditAbreise_3->setReadOnly(false);
        ui->lineEditHotel->setReadOnly(false);
        ui->lineEditStadt->setReadOnly(false);
        ui->lineEditZimmer->setReadOnly(false);

        ui->tabWidget->setCurrentIndex(2);
    }
    else if (typeid(RentalCarReservation) == typeid(*type)) {
        ui->lineEditId_2->setText(QString::fromStdString(type->getId()));
        ui->doubleSpinBoxPreis_2->setValue(type->getPrice());
        ui->dateEditAnkunft_2->setDate(type->getQFromDate());
        ui->dateEditAbreise_2->setDate(type->getQToDate());

        shared_ptr<RentalCarReservation> carType = static_pointer_cast<RentalCarReservation>(type);

        ui->lineEditAbholort->setText(QString::fromStdString(carType->getPickupLocation()));
        ui->lineEditRueckgabeort->setText(QString::fromStdString(carType->getReturnLocation()));
        ui->lineEditFirma->setText(QString::fromStdString(carType->getCompany()));
        ui->lineEditFahrzeugklasse->setText(QString::fromStdString(carType->getVehicleClass()));

        ui->doubleSpinBoxPreis_2->setReadOnly(false);
        ui->dateEditAnkunft_2->setReadOnly(false);
        ui->dateEditAbreise_2->setReadOnly(false);
        ui->lineEditAbholort->setReadOnly(false);
        ui->lineEditRueckgabeort->setReadOnly(false);
        ui->lineEditFirma->setReadOnly(false);
        ui->lineEditFahrzeugklasse->setReadOnly(false);

        ui->tabWidget->setCurrentIndex(1);
    }

}


void UpAndAway::on_doubleSpinBoxPreis_valueChanged(double arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId->text().toStdString());
    booking->setPrice(arg1);
}


void UpAndAway::on_dateEditAnkunft_dateChanged(const QDate &date)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId->text().toStdString());
    booking->setQFromDate(date);
}


void UpAndAway::on_dateEditAbreise_dateChanged(const QDate &date)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId->text().toStdString());
    booking->setQToDate(date);
}


void UpAndAway::on_dateEditAnkunft_2_dateChanged(const QDate &date)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_2->text().toStdString());
    booking->setQFromDate(date);
}


void UpAndAway::on_dateEditAbreise_2_dateChanged(const QDate &date)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_2->text().toStdString());
    booking->setQToDate(date);
}


void UpAndAway::on_doubleSpinBoxPreis_2_valueChanged(double arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_2->text().toStdString());
    booking->setPrice(arg1);
}


void UpAndAway::on_dateEditAnkunft_3_dateChanged(const QDate &date)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_3->text().toStdString());
    booking->setQFromDate(date);
}


void UpAndAway::on_dateEditAbreise_3_dateChanged(const QDate &date)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_3->text().toStdString());
    booking->setQToDate(date);
}


void UpAndAway::on_doubleSpinBoxPreis_3_valueChanged(double arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_3->text().toStdString());
    booking->setPrice(arg1);
}


void UpAndAway::on_lineEditHotel_textChanged(const QString &arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_3->text().toStdString());
    shared_ptr<HotelBooking> hotel = static_pointer_cast<HotelBooking>(booking);
    hotel->setHotel(arg1.toStdString());
}


void UpAndAway::on_lineEditStadt_textEdited(const QString &arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_3->text().toStdString());
    shared_ptr<HotelBooking> hotel = static_pointer_cast<HotelBooking>(booking);
    hotel->setTown(arg1.toStdString());
}


void UpAndAway::on_lineEditAbholort_textChanged(const QString &arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_2->text().toStdString());
    shared_ptr<RentalCarReservation> car = static_pointer_cast<RentalCarReservation>(booking);
    car->setPickupLocation(arg1.toStdString());
}


void UpAndAway::on_lineEditRueckgabeort_textChanged(const QString &arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_2->text().toStdString());
    shared_ptr<RentalCarReservation> car = static_pointer_cast<RentalCarReservation>(booking);
    car->setReturnLocation(arg1.toStdString());
}


void UpAndAway::on_lineEditFirma_textChanged(const QString &arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_2->text().toStdString());
    shared_ptr<RentalCarReservation> car = static_pointer_cast<RentalCarReservation>(booking);
    car->setCompany(arg1.toStdString());
}


void UpAndAway::on_lineEditFahrzeugklasse_textChanged(const QString &arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_2->text().toStdString());
    shared_ptr<RentalCarReservation> car = static_pointer_cast<RentalCarReservation>(booking);
    car->setVehicleClass(arg1.toStdString());
}


void UpAndAway::on_lineEditAbflugort_textChanged(const QString &arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId->text().toStdString());
    shared_ptr<FlightBooking> flight = static_pointer_cast<FlightBooking>(booking);
    flight->setFromDestination(arg1.toStdString());

    string airport = travelagency->findAirport(ui->lineEditAbflugort->text().toStdString());
    ui->lineEditAbflugort_2->setText(QString::fromStdString(airport));

    if (airport == "Ungueltiger Iata-Code") {
        ui->lineEditAbflugort_2->setStyleSheet("color: red");
    } else {
        ui->lineEditAbflugort_2->setStyleSheet("color: black");
    }

}
void UpAndAway::on_lineEditAnkunftsort_textChanged(const QString &arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId->text().toStdString());
    shared_ptr<FlightBooking> flight = static_pointer_cast<FlightBooking>(booking);
    flight->setToDestination(arg1.toStdString());

    string airport = travelagency->findAirport(ui->lineEditAnkunftsort->text().toStdString());
    ui->lineEditAnkunftsort_2->setText(QString::fromStdString(airport));

    if (airport == "Ungueltiger Iata-Code") {
        ui->lineEditAnkunftsort_2->setStyleSheet("color: red");
    } else {
        ui->lineEditAnkunftsort_2->setStyleSheet("color: black");
    }
}


void UpAndAway::on_lineEditAirline_textChanged(const QString &arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId->text().toStdString());
    shared_ptr<FlightBooking> flight = static_pointer_cast<FlightBooking>(booking);
    flight->setAirline(arg1.toStdString());
}


void UpAndAway::on_lineEditFlugklasse_textEdited(const QString &arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId->text().toStdString());
    shared_ptr<FlightBooking> flight = static_pointer_cast<FlightBooking>(booking);
    flight->setBookingClass(arg1.toStdString().c_str()[0]);
}


void UpAndAway::on_lineEditZimmer_textEdited(const QString &arg1)
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_3->text().toStdString());
    shared_ptr<HotelBooking> hotel = static_pointer_cast<HotelBooking>(booking);
    hotel->setRoomType(arg1.toStdString());
}

void UpAndAway::on_pushButtonFlugbuchung_clicked()
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId->text().toStdString());

    if (booking) {
        shared_ptr<FlightBooking> flight = static_pointer_cast<FlightBooking>(booking);

        QString url = "https://townsendjennings.com/geo/?geojson={\"type\":\"Feature\",\"geometry\":{\"type\":\"LineString\",\"coordinates\":[[";
        QString latitude1 = QString::fromStdString(flight->getFromDestLat());
        QString longitude1 = QString::fromStdString(flight->getFromDestLong());
        QString latitude2 = QString::fromStdString(flight->getToDestLat());
        QString longitude2 = QString::fromStdString(flight->getToDestLong());
        QString start = QString::fromStdString(travelagency->findAirport(flight->getFromDestination()));
        QString end = QString::fromStdString(travelagency->findAirport(flight->getToDestination()));

        url = url + longitude1 + "," + latitude1 + "],[" + longitude2 + "," + latitude2 + "]]},\"properties\":{\"Start\":\"" + start + "\",\"End\":\"" + end + "\"}}";
        QDesktopServices::openUrl(QUrl(url));

    } else {
        QMessageBox::information(this, "Fehler", "Waehlen Sie eine Buchung aus");
    }
}


void UpAndAway::on_pushButtonMietwagenreservierung_clicked()
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_2->text().toStdString());

    if (booking) {
        shared_ptr<RentalCarReservation> car = static_pointer_cast<RentalCarReservation>(booking);

        QString url{};
        QString latitude1 = QString::fromStdString(car->getPickupLocationLat());
        QString longitude1 = QString::fromStdString(car->getPickupLocationLong());
        QString latitude2 = QString::fromStdString(car->getReturnLocationLat());
        QString longitude2 = QString::fromStdString(car->getReturnLocationLong());
        QString start = QString::fromStdString(car->getPickupLocation());
        QString end = QString::fromStdString(car->getReturnLocation());

        if (car->getPickupLocation() == car->getReturnLocation()) {
            url = "https://townsendjennings.com/geo/?geojson={\"type\":\"Feature\",\"geometry\":{\"type\":\"Point\",\"coordinates\":[";
            url = url + longitude1 + "," + latitude1 + "]},\"properties\":{\"Location\":\"" + start + "\"}}";
        } else {
            url = "https://townsendjennings.com/geo/?geojson={\"type\":\"Feature\",\"geometry\":{\"type\":\"LineString\",\"coordinates\":[[";
            url = url + longitude1 + "," + latitude1 + "],[" + longitude2 + "," + latitude2 + "]]},\"properties\":{\"Start\":\"" + start + "\",\"End\":\"" + end + "\"}}";
        }

        QDesktopServices::openUrl(QUrl(url));

    } else {
        QMessageBox::information(this, "Fehler", "Waehlen Sie eine Buchung aus");
    }
}


void UpAndAway::on_pushButtonHotelreservierung_clicked()
{
    shared_ptr<Booking> booking = travelagency->findBooking(ui->lineEditId_3->text().toStdString());

    if (booking) {
        shared_ptr<HotelBooking> hotel = static_pointer_cast<HotelBooking>(booking);

        QString url = "https://townsendjennings.com/geo/?geojson={\"type\":\"Feature\",\"geometry\":{\"type\":\"Point\",\"coordinates\":[";
        QString latitude = QString::fromStdString(hotel->getHotelLat());
        QString longitude = QString::fromStdString(hotel->getHotelLong());
        QString name = QString::fromStdString(hotel->getHotel());

        url = url + longitude + "," + latitude + "]},\"properties\":{\"Hotel\":\"" + name + "\"}}";

        QDesktopServices::openUrl(QUrl(url));

    } else {
        QMessageBox::information(this, "Fehler", "Waehlen Sie eine Buchung aus");
    }
}


void UpAndAway::on_actionKunde_triggered()
{
    AddCustomerDialog customerDialog(travelagency);
    customerDialog.setModal(true);
    customerDialog.exec();
}


void UpAndAway::on_actionBuchung_triggered()
{
    AddBookingDialog bookingDialog(travelagency);
    bookingDialog.setModal(true);
    bookingDialog.exec();
}


void UpAndAway::on_actionSpeichern_triggered()
{
    SortDialog sortDialog(travelagency);
    sortDialog.setModal(true);
    sortDialog.exec();
}


void UpAndAway::on_actionChecks_triggered()
{
    CheckDialog checkDialog(travelagency);
    checkDialog.setModal(true);
    checkDialog.exec();
}


void UpAndAway::on_actionABC_Analyse_triggered()
{
    travelagency->abcAnalyse();

    ABCDialog abcDialog(travelagency);
    abcDialog.setModal(true);
    abcDialog.exec();
}

