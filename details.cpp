#include "details.h"
#include "ui_details.h"

Details::Details(const ExtendedTeams *teamA, const ExtendedTeams *teamB, QWidget *parent)
    : QDialog(parent), ui(new Ui::Details),
      dA_team(teamA),
      dB_team(teamB)
{
    ui->setupUi(this);
    if (!dA_team)
        return;

    ui->details_ListWidget_A->clear();

    ui->details_ListWidget_A->addItem("Drużyna: " + dA_team->getName());
    ui->details_ListWidget_A->addItem("Mecze rozegrane: " + QString::number(dA_team->matches().size()));
    ui->details_ListWidget_A->addItem("Łącznie goli: " + QString::number(dA_team->getGoalsFor()));
    ui->details_ListWidget_A->addItem("Średnia goli na mecz: " +
                                      QString::number(dA_team->goalsPerMatch(), 'f', 2));
    ui->details_ListWidget_A->addItem("Celność strzałów: " +
                                      QString::number(dA_team->shootingAccuracy(), 'f', 1) + "%");
    ui->details_ListWidget_A->addItem("Przewidywalność xG: " +
                                      QString::number(dA_team->expectedGoalsAccuracy(), 'f', 1) + "%");
    ui->details_ListWidget_A->addItem("Najlepszy strzelec: " + dA_team->topScorer());

    ui->details_ListWidget_A->addItem("Średnia ilość rzutów rożnych: " + QString::number(dA_team->averageCorners()));

    ui->details_ListWidget_A->addItem("Średnia ilość podań: " + QString::number(dA_team->averagePasses()));

    ui->details_ListWidget_A->addItem("Średnie posiadanie piłki " + QString::number(dA_team->averagePosession()) + " %");

    ui->details_ListWidget_A->addItem(" ");
    ui->details_ListWidget_A->addItem("Ostatnie mecze:");

    const QVector<MatchStats> &matchesA = dA_team->matches();
    for (int i = 0; i < matchesA.size(); ++i)
    {
        const MatchStats &m = matchesA[i];

        QString summary;
        if (m.ustawienia_zaawansowane)
        {
            summary = QString("• [%1]  %2:%3  |  xG=%4  Celne=%5/%6  RR=%7  Podania=%8  Posiadanie=%9%%")
                          .arg(m.date.toString("dd.MM"))
                          .arg(m.goalsFor)
                          .arg(m.goalsAg)
                          .arg(m.expectedG)
                          .arg(m.shotsOnTgt)
                          .arg(m.shotsTot)
                          .arg(m.corners)
                          .arg(m.passes)
                          .arg(m.possesion);
        }
        else
        {
            summary = QString("• [%1]  %2:%3  (brak danych zaawansowanych)")
                          .arg(m.date.toString("dd.MM"))
                          .arg(m.goalsFor)
                          .arg(m.goalsAg);
        }

        ui->details_ListWidget_A->addItem(summary);
    }

    if (!dB_team)
        return;

    ui->details_ListWidget_B->clear();

    ui->details_ListWidget_B->addItem("Drużyna: " + dB_team->getName());
    ui->details_ListWidget_B->addItem("Mecze rozegrane: " + QString::number(dB_team->matches().size()));
    ui->details_ListWidget_B->addItem("Łącznie goli: " + QString::number(dB_team->getGoalsFor()));
    ui->details_ListWidget_B->addItem("Średnia goli na mecz: " +
                                      QString::number(dB_team->goalsPerMatch(), 'f', 2));
    ui->details_ListWidget_B->addItem("Celność strzałów: " +
                                      QString::number(dB_team->shootingAccuracy(), 'f', 1) + "%");
    ui->details_ListWidget_B->addItem("Przewidywalność xG: " +
                                      QString::number(dB_team->expectedGoalsAccuracy(), 'f', 1) + "%");
    ui->details_ListWidget_B->addItem("Najlepszy strzelec: " + dB_team->topScorer());

    ui->details_ListWidget_B->addItem("Średnia ilość rzutów rożnych: " + QString::number(dB_team->averageCorners()));

    ui->details_ListWidget_B->addItem("Średnia ilość podań: " + QString::number(dB_team->averagePasses()));

    ui->details_ListWidget_B->addItem("Średnie posiadanie piłki " + QString::number(dB_team->averagePosession()) + " %");

    ui->details_ListWidget_B->addItem(" ");
    ui->details_ListWidget_B->addItem("Ostatnie mecze:");

    const QVector<MatchStats> &matchesB = dB_team->matches();
    for (int i = 0; i < matchesB.size(); ++i)
    {
        const MatchStats &m = matchesB[i];

        QString summary;
        if (m.ustawienia_zaawansowane)
        {
            summary = QString("• [%1]  %2:%3  |  xG=%4  Celne=%5/%6  RR=%7  Podania=%8  Posiadanie=%9%%")
                          .arg(m.date.toString("dd.MM"))
                          .arg(m.goalsFor)
                          .arg(m.goalsAg)
                          .arg(m.expectedG)
                          .arg(m.shotsOnTgt)
                          .arg(m.shotsTot)
                          .arg(m.corners)
                          .arg(m.passes)
                          .arg(m.possesion);
        }
        else
        {
            summary = QString("• [%1]  %2:%3  (brak danych zaawansowanych)")
                          .arg(m.date.toString("dd.MM"))
                          .arg(m.goalsFor)
                          .arg(m.goalsAg);
        }

        ui->details_ListWidget_B->addItem(summary);
    }
}

Details::~Details()
{
    delete ui;
}