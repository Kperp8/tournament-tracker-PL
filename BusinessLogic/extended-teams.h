#ifndef EXTENDED_TEAMS_H
#define EXTENDED_TEAMS_H
#include <QStringList>
#include "teams.h"

class BUSINESSLOGIC_EXPORT ExtendedTeams : public Teams
{
private:
    QStringList strzelcy;
    int podania = 0;
    int posesja = 0;
    int rzuty_r = 0;
    int strzaly_c = 0;
    int oczekiwane_g = 0;
    int laczne_s = 0;
public:

    ExtendedTeams(const QString &name = "");

    void setStrzelcy(const QStringList& s);
    void setZaawansowane(int podania, int posesja, int rzuty_r, int strzaly_c, int oczekiwane_g, int laczne_s);

    QStringList getStrzelcy() const;
    int getPodania() const;
    int getPosesja() const;
    int getRzuty_r() const;
    int getStrzaly_c() const;
    int getOczekiwane_g() const;
    int getLaczne_s() const;

    void displayData() const override;





};

#endif // EXTENDED_TEAMS_H
