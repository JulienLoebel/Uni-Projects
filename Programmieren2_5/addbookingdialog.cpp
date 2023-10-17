#include "addbookingdialog.h"
#include "ui_addbookingdialog.h"
#include <QTabBar>
#include <QUuid>
#include "flightbooking.h"
#include "rentalcarreservation.h"
#include "hotelbooking.h"
#include <QMessageBox>

AddBookingDialog::AddBookingDialog(std::shared_ptr<TravelAgency> pTravelAgency, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookingDialog)
{
    travelagency = pTravelAgency;
    ui->setupUi(this);

    ui->tabWidget->setTabEnabled(0, false);
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);

    ui->tabWidget_2->setTabEnabled(0, false);
    ui->tabWidget_2->setTabEnabled(1, false);

    ui->groupBox_3->setDisabled(true);

    QTabBar *tabBar = ui->tabWidget->findChild<QTabBar*>();
    tabBar->hide();

    QTabBar *tabBar2 = ui->tabWidget_2->findChild<QTabBar*>();
    tabBar2->hide();
}

AddBookingDialog::~AddBookingDialog()
{
    delete ui;
}

void AddBookingDialog::on_radioButtonFlight_clicked()
{
    ui->tabWidget->setTabEnabled(0, true);
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);

    ui->tabWidget->setCurrentIndex(0);
}


void AddBookingDialog::on_radioButtonCar_clicked()
{
    ui->tabWidget->setTabEnabled(0, false);
    ui->tabWidget->setTabEnabled(1, true);
    ui->tabWidget->setTabEnabled(2, false);

    ui->tabWidget->setCurrentIndex(1);
}


void AddBookingDialog::on_radioButtonHotel_clicked()
{
    ui->tabWidget->setTabEnabled(0, false);
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, true);

    ui->tabWidget->setCurrentIndex(2);
}


void AddBookingDialog::on_buttonBox_accepted()
{

    if (ui->radioButtonFlight->isChecked()) {
        QUuid uuid = QUuid::createUuid();

        std::string id = uuid.toString().toStdString();
        double price = ui->doubleSpinBoxPreis->value();
        std::string fromDate = ui->dateEditAnkunft->date().toString("yyyyMMdd").toStdString();
        std::string toDate = ui->dateEditAbreise->date().toString("yyyyMMdd").toStdString();

        std::string fromDestination = ui->lineEditAbflugort->text().toStdString();
        std::string toDestination = ui->lineEditAnkunftsort->text().toStdString();
        std::string airline = ui->lineEditAirline->text().toStdString();
        char bookingClass = ui->lineEditFlugklasse->text().toStdString()[0];
        std::string fromDestLat{};
        std::string fromDestLong{};
        std::string toDestLat{};
        std::string toDestLong{};

        if (ui->radioButtonBestehendeReise->isChecked()) {
            long travelID =ui->spinBoxReiseID->value();
            std::shared_ptr<Travel> travel = travelagency->findTravel(travelID);

            if (travel) {
                std::shared_ptr<FlightBooking> flight(new FlightBooking(id, price, fromDate, toDate, fromDestination, toDestination, airline, bookingClass, fromDestLat, fromDestLong, toDestLat, toDestLong, travelID));

                travelagency->addBooking(flight);
                travel->addBooking(flight);

                std::string pre1ID = ui->lineEditPre1->text().toStdString();
                std::string pre2ID = ui->lineEditPre2->text().toStdString();

                int first = travel->getGraph()->firstVertex();
                int last = travel->getGraph()->lastVertex();

                travel->getGraph()->insertVertex(last+1, flight);

                for (int i = first; i <= last; i++) {
                    if(travel->getGraph()->getVertexValue(i)->getId() == pre1ID) {
                        travel->getGraph()->insertEdge(i,last+1);
                    }
                }

                for (int i = first; i <= last; i++) {
                    if(travel->getGraph()->getVertexValue(i)->getId() == pre2ID) {
                        travel->getGraph()->insertEdge(i,last+1);
                    }
                }

            } else {
                QMessageBox::information(this, "Fehler", "Es gibt keine Reise mit dieser ID");
            }

        } else if (ui->radioButtonNeueReise->isChecked()) {
            long customerID = ui->spinBoxKundenID->value();
            std::shared_ptr<Customer> customer = travelagency->findCustomer(customerID);

            if (customer) {
                long newtravelID = travelagency->getAllTravels().size() + 1;
                std::shared_ptr<Travel> newTravel(new Travel(newtravelID, customerID));
                customer->addTravel(newTravel);
                travelagency->addTravel(newTravel);
                std::shared_ptr<FlightBooking> flight(new FlightBooking(id, price, fromDate, toDate, fromDestination, toDestination, airline, bookingClass, fromDestLat, fromDestLong, toDestLat, toDestLong, newtravelID));

                travelagency->addBooking(flight);
                newTravel->addBooking(flight);

                shared_ptr<Graph<shared_ptr<Booking>, 15>> graph(new Graph<shared_ptr<Booking>, 15>);
                newTravel->setGraph(graph);
                newTravel->getGraph()->insertVertex(1, flight);
            } else {
                QMessageBox::information(this, "Fehler", "Es gibt keinen Kunden mit dieser ID");
            }
        }


    } else if (ui->radioButtonCar->isChecked()) {
        QUuid uuid = QUuid::createUuid();

        std::string id = uuid.toString().toStdString();
        double price = ui->doubleSpinBoxPreis_2->value();
        std::string fromDate = ui->dateEditAnkunft_2->date().toString("yyyyMMdd").toStdString();
        std::string toDate = ui->dateEditAbreise_2->date().toString("yyyyMMdd").toStdString();

        std::string pickupLocation = ui->lineEditAbholort->text().toStdString();
        std::string returnLocation = ui->lineEditRueckgabeort->text().toStdString();
        std::string company = ui->lineEditFirma->text().toStdString();
        std::string vehicleClass = ui->lineEditFahrzeugklasse->text().toStdString();
        std::string pickupLocationLat{};
        std::string pickupLocationLong{};
        std::string returnLocationLat{};
        std::string returnLocationLong{};

        if (ui->radioButtonBestehendeReise->isChecked()) {
            long travelID =ui->spinBoxReiseID->value();
            std::shared_ptr<Travel> travel = travelagency->findTravel(travelID);

            if (travel) {
                std::shared_ptr<RentalCarReservation> car(new RentalCarReservation(id, price, fromDate, toDate, pickupLocation, returnLocation, company, vehicleClass, pickupLocationLat, pickupLocationLong, returnLocationLat, returnLocationLong, travelID));
                travelagency->addBooking(car);
                travel->addBooking(car);

                std::string pre1ID = ui->lineEditPre1->text().toStdString();
                std::string pre2ID = ui->lineEditPre2->text().toStdString();

                int first = travel->getGraph()->firstVertex();
                int last = travel->getGraph()->lastVertex();

                travel->getGraph()->insertVertex(last+1, car);

                for (int i = first; i <= last; i++) {
                    if(travel->getGraph()->getVertexValue(i)->getId() == pre1ID) {
                        travel->getGraph()->insertEdge(i,last+1);
                    }
                }

                for (int i = first; i <= last; i++) {
                    if(travel->getGraph()->getVertexValue(i)->getId() == pre2ID) {
                        travel->getGraph()->insertEdge(i,last+1);
                    }
                }
            } else {
                QMessageBox::information(this, "Fehler", "Es gibt keine Reise mit dieser ID");
            }

        } else if (ui->radioButtonNeueReise->isChecked()) {
            long customerID = ui->spinBoxKundenID->value();
            std::shared_ptr<Customer> customer = travelagency->findCustomer(customerID);

            if (customer) {
                long newtravelID = travelagency->getAllTravels().size() + 1;
                std::shared_ptr<Travel> newTravel(new Travel(newtravelID, customerID));
                customer->addTravel(newTravel);
                travelagency->addTravel(newTravel);
                std::shared_ptr<RentalCarReservation> car(new RentalCarReservation(id, price, fromDate, toDate, pickupLocation, returnLocation, company, vehicleClass, pickupLocationLat, pickupLocationLong, returnLocationLat, returnLocationLong, newtravelID));

                travelagency->addBooking(car);
                newTravel->addBooking(car);

                newTravel->getGraph()->insertVertex(1, car);
            } else {
                QMessageBox::information(this, "Fehler", "Es gibt keinen Kunden mit dieser ID");
            }
        }

    } else if (ui->radioButtonHotel->isChecked()) {
        QUuid uuid = QUuid::createUuid();

        std::string id = uuid.toString().toStdString();
        double price = ui->doubleSpinBoxPreis_3->value();
        std::string fromDate = ui->dateEditAnkunft_3->date().toString("yyyyMMdd").toStdString();
        std::string toDate = ui->dateEditAbreise_3->date().toString("yyyyMMdd").toStdString();

        std::string hotel = ui->lineEditHotel->text().toStdString();
        std::string town = ui->lineEditStadt->text().toStdString();
        std::string roomType = ui->lineEditZimmer->text().toStdString();
        std::string hotelLat{};
        std::string hotelLong{};


        if (ui->radioButtonBestehendeReise->isChecked()) {
            long travelID =ui->spinBoxReiseID->value();
            std::shared_ptr<Travel> travel = travelagency->findTravel(travelID);

            if (travel) {
                std::shared_ptr<HotelBooking> room(new HotelBooking(id, price, fromDate, toDate, hotel, town, roomType, hotelLat, hotelLong, travelID));
                travelagency->addBooking(room);
                travel->addBooking(room);

                std::string pre1ID = ui->lineEditPre1->text().toStdString();
                std::string pre2ID = ui->lineEditPre2->text().toStdString();

                int first = travel->getGraph()->firstVertex();
                int last = travel->getGraph()->lastVertex();

                travel->getGraph()->insertVertex(last+1, room);

                for (int i = first; i <= last; i++) {
                    if(travel->getGraph()->getVertexValue(i)->getId() == pre1ID) {
                        travel->getGraph()->insertEdge(i,last+1);
                    }
                }

                for (int i = first; i <= last; i++) {
                    if(travel->getGraph()->getVertexValue(i)->getId() == pre2ID) {
                        travel->getGraph()->insertEdge(i,last+1);
                    }
                }
            } else {
                QMessageBox::information(this, "Fehler", "Es gibt keine Reise mit dieser ID");
            }

        } else if (ui->radioButtonNeueReise->isChecked()) {
            long customerID = ui->spinBoxKundenID->value();
            std::shared_ptr<Customer> customer = travelagency->findCustomer(customerID);

            if (customer) {
                long newtravelID = travelagency->getAllTravels().size() + 1;
                std::shared_ptr<Travel> newTravel(new Travel(newtravelID, customerID));
                customer->addTravel(newTravel);
                travelagency->addTravel(newTravel);
                std::shared_ptr<HotelBooking> room(new HotelBooking(id, price, fromDate, toDate, hotel, town, roomType, hotelLat, hotelLong, newtravelID));

                travelagency->addBooking(room);
                newTravel->addBooking(room);

                newTravel->getGraph()->insertVertex(1, room);
            } else {
                QMessageBox::information(this, "Fehler", "Es gibt keinen Kunden mit dieser ID");
            }
        }
    }
}


void AddBookingDialog::on_radioButtonNeueReise_clicked()
{
    ui->tabWidget_2->setTabEnabled(0, false);
    ui->tabWidget_2->setTabEnabled(1, true);

    ui->tabWidget_2->setCurrentIndex(1);

    ui->groupBox_3->setDisabled(true);
}


void AddBookingDialog::on_radioButtonBestehendeReise_clicked()
{
    ui->tabWidget_2->setTabEnabled(0, true);
    ui->tabWidget_2->setTabEnabled(1, false);

    ui->tabWidget_2->setCurrentIndex(0);

    ui->groupBox_3->setDisabled(false);
}

