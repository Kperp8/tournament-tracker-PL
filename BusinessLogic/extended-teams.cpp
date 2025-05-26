#include "teams.h"
#include "extended-teams.h"
#include <QDebug>

ExtendedTeams::ExtendedTeams(const QString& name) : Teams(name)
{}

void ExtendedTeams::setStrzelcy(const QStringList& s) { strzelcy = s; }


void ExtendedTeams::setZaawansowane(int podania, int posesja, int rzuty_r, int strzaly_c, int oczekiwane_g, int laczne_s)
{
    this->podania = podania;
    this->posesja = posesja;
    this->rzuty_r = rzuty_r;
    this->strzaly_c = strzaly_c;
    this->oczekiwane_g = oczekiwane_g;
    this->laczne_s = laczne_s;
}

QStringList ExtendedTeams::getStrzelcy() const { return strzelcy; }
int ExtendedTeams::getPodania() const {return podania;}
int ExtendedTeams::getPosesja() const {return posesja;}
int ExtendedTeams::getRzuty_r() const {return rzuty_r;}
int ExtendedTeams::getOczekiwane_g() const {return oczekiwane_g;}
int ExtendedTeams::getStrzaly_c() const {return strzaly_c;}
int ExtendedTeams::getLaczne_s() const {return laczne_s;}

void ExtendedTeams::displayData() const
{
    Teams::displayData();
    qDebug() << ">> Strzelcy:" << strzelcy.join(", ")
           << ">> Podania" << podania
           << ">> Posiadanie:" << posesja << "%"
           << ">> Rzuty rożne:" << rzuty_r
           << ">> Strzały celne:" << strzaly_c
           << ">> Oczekiwane gole:" << oczekiwane_g
           << ">> Strzały łącznie:" << laczne_s;
}

