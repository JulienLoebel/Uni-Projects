#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include "travelagency.h"

namespace Ui {
class SortDialog;
}

class SortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SortDialog(std::shared_ptr<TravelAgency> pTravelAgency, QWidget *parent = nullptr);
    ~SortDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SortDialog *ui;
    std::shared_ptr<TravelAgency> travelagency;

};

#endif // SORTDIALOG_H
