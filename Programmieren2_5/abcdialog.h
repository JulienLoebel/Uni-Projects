#ifndef ABCDIALOG_H
#define ABCDIALOG_H
#include "travelagency.h"

#include <QDialog>

namespace Ui {
class abcDialog;
}

class ABCDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ABCDialog(std::shared_ptr<TravelAgency> pTravelAgency, QWidget *parent = nullptr);
    ~ABCDialog();

    void showABCAnalyse();

private:
    Ui::abcDialog *ui;
     std::shared_ptr<TravelAgency> travelagency;
};

#endif // ABCDIALOG_H
