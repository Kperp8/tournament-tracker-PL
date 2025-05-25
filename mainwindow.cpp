#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "BusinessLogic/teamsmodel.h"
#include "BusinessLogic/file-handling.h"
#include <QDebug>
#include <QFileDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new TeamsModel();
    ui->scoresTable->setModel(model); // dzięki temu tabela zawsze będzie mieć kolumny, nawet zanim dodamy zespoły
    ui->scoresTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // dzięki temu kolumny tabeli skalują się do okna
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


    if(m_teams.append(Teams(name)); true)
    {
        qDebug() << "dodano" << name;
        for(int i = 0; i < m_teams.size(); ++i)
        {
            qDebug() << i << m_teams[i].getName();
        }

    }
    refreshCombos();
    ui->lineEdit_druzyna->clear();

    if(model == nullptr)
        model = new TeamsModel();
    model->setTeams(m_teams); // potencjalnie nieoptymalnie
    ui->scoresTable->setModel(model);
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

void MainWindow::on_add_match_clicked()
{
    QString teamAName = ui->select_A->currentText();
    QString teamBName = ui->select_B->currentText();
    int goalsA = ui->spinBox_A->value();
    int goalsB = ui->spinBox_B->value();

    int indexA = -1, indexB = -1;
    for (int i = 0; i < m_teams.size(); ++i) {
        if (m_teams[i].getName() == teamAName) indexA = i;
        if (m_teams[i].getName() == teamBName) indexB = i;
    }

    if (indexA == -1 || indexB == -1) {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono jednej z drużyn.");
        return;
    }

    if (indexA == indexB) {
        QMessageBox::warning(this, "Błąd", "Nie można rozegrać meczu przeciwko sobie.");
        return;
    }

    m_teams[indexA].addMatch(goalsA, goalsB);
    m_teams[indexB].addMatch(goalsB, goalsA);

    qDebug() << "Mecz dodany:" << teamAName << goalsA << "-" << goalsB << teamBName;

    for(int i = 0; i < m_teams.size(); ++i)
    {
        m_teams[i].displayData();
    }

    if(model == nullptr)
        model = new TeamsModel();
    model->setTeams(m_teams); // potencjalnie nieoptymalnie
    ui->scoresTable->setModel(model);
}


void MainWindow::on_Load_Button_clicked()
{
    QString path = QFileDialog::getOpenFileName(
        this,                       //QWidget *parent, to jakbys potrzebowal i chcial cos zmienic
        "Wczytaj dane drużyn",          //const QString &caption,
        "tabela-ligowa",                             //const QString &dir = QString(),
        "Pliki tekstowe (*.txt)"            //const QString &filter = QString(), taki format mam osobiscie na windowsie
        );

    if (path.isEmpty()) return;

    QVector<Teams> loaded = FileOp::loadFromFile(path);
    if (loaded.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Nie udało się wczytać danych.");
        return;
    }

    m_teams = loaded;
    refreshCombos();
    model->setTeams(m_teams);
}

