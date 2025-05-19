#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "BusinessLogic/teamsmodel.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_add_team_clicked()
{
    const QString name = ui->lineEdit_druzyna->text().trimmed();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Nazwa drużyny nie może być pusta.");
        return;
    }
    for (int i = 0; i < m_teams.size(); ++i) {                       // const Teams&
        if (m_teams[i].getName() == name) {     // Case-Insensitive
            QMessageBox::warning(this, "Błąd",
                                 "Taka drużyna już istnieje.");
            return;
        }
    }

    m_teams.append(Teams(name));
    refreshCombos();
    ui->lineEdit_druzyna->clear();
}

void MainWindow::refreshCombos()
{
    ui->select_A->clear();
    ui->select_B->clear();
    for (int i = 0; i < m_teams.size(); ++i)
    {
        ui->select_A->addItem(m_teams[i].getName());
        ui->select_B->addItem(m_teams[i].getName());
    }

}


void MainWindow::on_testButton_clicked()
{
    QList<Teams> teamsList;

    Teams team1("Team A");
    team1.addMatch(15, 4);
    Teams team2("Team B");
    team2.addMatch(453,123);
    team2.addMatch(4,1);

    teamsList.append(team1);
    teamsList.append(team2);

    TeamsModel* model = new TeamsModel(this);
    model->setTeams(teamsList);
    ui->scoresTable->setModel(model);
}

