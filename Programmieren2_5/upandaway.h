#ifndef UPANDAWAY_H
#define UPANDAWAY_H

#include "travelagency.h"
#include <QMainWindow>
#include <QListWidget>
#include <memory>


QT_BEGIN_NAMESPACE
namespace Ui { class UpAndAway; }
QT_END_NAMESPACE

class UpAndAway : public QMainWindow
{
    Q_OBJECT

public:
    UpAndAway(std::shared_ptr<TravelAgency> pTravelAgency, QWidget *parent = nullptr);
    ~UpAndAway();

private slots:
    void on_actionEinlesen_triggered();


    void on_pushButtonSuche_clicked();

    void on_tableWidgetKunde_cellDoubleClicked(int row);

    void on_tableWidgetReise_cellDoubleClicked(int row);

    void on_doubleSpinBoxPreis_valueChanged(double arg1);

    void on_dateEditAnkunft_dateChanged(const QDate &date);

    void on_dateEditAbreise_dateChanged(const QDate &date);

    void on_dateEditAnkunft_2_dateChanged(const QDate &date);

    void on_dateEditAbreise_2_dateChanged(const QDate &date);

    void on_doubleSpinBoxPreis_2_valueChanged(double arg1);

    void on_dateEditAnkunft_3_dateChanged(const QDate &date);

    void on_dateEditAbreise_3_dateChanged(const QDate &date);

    void on_doubleSpinBoxPreis_3_valueChanged(double arg1);

    void on_lineEditHotel_textChanged(const QString &arg1);

    void on_lineEditStadt_textEdited(const QString &arg1);

    void on_lineEditAbholort_textChanged(const QString &arg1);

    void on_lineEditRueckgabeort_textChanged(const QString &arg1);

    void on_lineEditFirma_textChanged(const QString &arg1);

    void on_lineEditFahrzeugklasse_textChanged(const QString &arg1);

    void on_lineEditAbflugort_textChanged(const QString &arg1);

    void on_lineEditAnkunftsort_textChanged(const QString &arg1);

    void on_lineEditAirline_textChanged(const QString &arg1);

    void on_lineEditFlugklasse_textEdited(const QString &arg1);

    void on_lineEditZimmer_textEdited(const QString &arg1);

    void on_pushButtonFlugbuchung_clicked();

    void on_pushButtonMietwagenreservierung_clicked();

    void on_pushButtonHotelreservierung_clicked();

    void on_actionKunde_triggered();

    void on_actionBuchung_triggered();

    void on_actionSpeichern_triggered();

    void on_actionChecks_triggered();

    void on_actionABC_Analyse_triggered();

private:
    Ui::UpAndAway *ui;

    std::shared_ptr<TravelAgency> travelagency;

};
#endif // UPANDAWAY_H
