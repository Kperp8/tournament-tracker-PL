#include "details.h"
#include "ui_details.h"

Details::Details(const ExtendedTeams* teamA, const ExtendedTeams* teamB, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Details),
    dA_team(teamA),
    dB_team(teamB)
{
    ui->setupUi(this);
    if (!dA_team)
        return;

    ui->details_ListWidget_A->clear();  // czyść na wszelki wypadek

    ui->details_ListWidget_A->addItem("Drużyna: " + dA_team->getName());
    ui->details_ListWidget_A->addItem("Mecze rozegrane: " + QString::number(dA_team->matchCount()));
    ui->details_ListWidget_A->addItem("Łącznie goli: " + QString::number(dA_team->getGoalsFor()));
    ui->details_ListWidget_A->addItem("Średnia goli na mecz: " +
                            QString::number(dA_team->goalsPerMatch(), 'f', 2));
    ui->details_ListWidget_A->addItem("Celność strzałów: " +
                            QString::number(dA_team->shootingAccuracy(), 'f', 1) + "%");
    ui->details_ListWidget_A->addItem("Przewidywalność xG: " +
                            QString::number(dA_team->expectedGoalsAccuracy(), 'f', 1) + "%");
    ui->details_ListWidget_A->addItem("Najlepszy strzelec: " + dA_team->topScorer());

    ui->details_ListWidget_A->addItem(" ");  // odstęp
    ui->details_ListWidget_A->addItem("Ostatnie mecze:");

    const QVector<MatchStats>& matchesA = dA_team->matches();
    for (int i = 0; i < matchesA.size(); ++i)
    {
        const MatchStats& m = matchesA[i];
        QString summary = QString("• [%1] %2:%3, xG=%4, Celne=%5/%6")
                              .arg(m.date.toString("dd.MM"))
                              .arg(m.goalsFor)
                              .arg(m.goalsAg)
                              .arg(m.expectedG)
                              .arg(m.shotsOnTgt)
                              .arg(m.shotsTot);

        ui->details_ListWidget_A->addItem(summary);
    }


    if (!dB_team)
        return;

    ui->details_ListWidget_B->clear();  // czyść na wszelki wypadek

    ui->details_ListWidget_B->addItem("Drużyna: " + dB_team->getName());
    ui->details_ListWidget_B->addItem("Mecze rozegrane: " + QString::number(dB_team->matchCount()));
    ui->details_ListWidget_B->addItem("Łącznie goli: " + QString::number(dB_team->getGoalsFor()));
    ui->details_ListWidget_B->addItem("Średnia goli na mecz: " +
                                      QString::number(dB_team->goalsPerMatch(), 'f', 2));
    ui->details_ListWidget_B->addItem("Celność strzałów: " +
                                      QString::number(dB_team->shootingAccuracy(), 'f', 1) + "%");
    ui->details_ListWidget_B->addItem("Przewidywalność xG: " +
                                      QString::number(dB_team->expectedGoalsAccuracy(), 'f', 1) + "%");
    ui->details_ListWidget_B->addItem("Najlepszy strzelec: " + dB_team->topScorer());

    ui->details_ListWidget_B->addItem(" ");  // odstęp
    ui->details_ListWidget_B->addItem("Ostatnie mecze:");

    const QVector<MatchStats>& matchesB = dB_team->matches();
    for (int i = 0; i < matchesB.size(); ++i)
    {
        const MatchStats& m = matchesB[i];
        QString summary = QString("• [%1] %2:%3, xG=%4, Celne=%5/%6")
                              .arg(m.date.toString("dd.MM"))
                              .arg(m.goalsFor)
                              .arg(m.goalsAg)
                              .arg(m.expectedG)
                              .arg(m.shotsOnTgt)
                              .arg(m.shotsTot);

        ui->details_ListWidget_B->addItem(summary);
    }
}


Details::~Details()
{
    delete ui;
}
