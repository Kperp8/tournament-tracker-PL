#ifndef DETAILS_H
#define DETAILS_H
#include "BusinessLogic/extended-teams.h"
#include <QDialog>

namespace Ui {
class Details;
}

class Details : public QDialog
{
    Q_OBJECT

public:
    explicit Details(const ExtendedTeams* teamA, const ExtendedTeams* teamB, QWidget *parent = nullptr);
    ~Details();

private:
    Ui::Details *ui;
    const ExtendedTeams* dA_team = nullptr;
    const ExtendedTeams* dB_team = nullptr;
};

#endif // DETAILS_H
