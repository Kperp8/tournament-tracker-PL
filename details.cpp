#include "details.h"
#include "ui_details.h"

Details::Details(const ExtendedTeams* team, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Details),
    dm_team(team)
{
    ui->setupUi(this);
    if (!dm_team)
        return;

    ui->details_ListWidget->clear();  // czyść na wszelki wypadek

    ui->details_ListWidget->addItem("Drużyna: " + dm_team->getName());
    ui->details_ListWidget->addItem("Mecze rozegrane: " + QString::number(dm_team->matchCount()));
    ui->details_ListWidget->addItem("Łącznie goli: " + QString::number(dm_team->getGoalsFor()));
    ui->details_ListWidget->addItem("Średnia goli na mecz: " +
                            QString::number(dm_team->goalsPerMatch(), 'f', 2));
    ui->details_ListWidget->addItem("Celność strzałów: " +
                            QString::number(dm_team->shootingAccuracy(), 'f', 1) + "%");
    ui->details_ListWidget->addItem("Przewidywalność xG: " +
                            QString::number(dm_team->expectedGoalsAccuracy(), 'f', 1) + "%");
    ui->details_ListWidget->addItem("Najlepszy strzelec: " + dm_team->topScorer());

    ui->details_ListWidget->addItem(" ");  // odstęp
    ui->details_ListWidget->addItem("Ostatnie mecze:");

    const QVector<MatchStats>& matches = dm_team->matches();
    for (int i = 0; i < matches.size(); ++i)
    {
        const MatchStats& m = matches[i];
        QString summary = QString("• [%1] %2:%3, xG=%4, Celne=%5/%6")
                              .arg(m.date.toString("dd.MM"))
                              .arg(m.goalsFor)
                              .arg(m.goalsAg)
                              .arg(m.expectedG)
                              .arg(m.shotsOnTgt)
                              .arg(m.shotsTot);

        ui->details_ListWidget->addItem(summary);
    }
}


Details::~Details()
{
    delete ui;
}
