#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "BusinessLogic/teamsmodel.h"
#include "BusinessLogic/file-handling.h"
#include "BusinessLogic/extended-teams.h"
#include <QDebug>
#include <QFileDialog>
#include <QCheckBox>
#include <QInputDialog>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new TeamsModel();
    ui->scoresTable->setModel(model); // dzięki temu tabela zawsze będzie mieć kolumny, nawet zanim dodamy zespoły
    ui->scoresTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // dzięki temu kolumny tabeli skalują się do okna

    ui->formWidget_A->setEnabled(false); //formWidget_A - lewe zaawansowane ustawienia standardowo sa ukryte
    ui->formWidget_B->setEnabled(false); //....... prawe ukryte
    ui->Zaawansowane_CheckBox->setChecked(false); //standardowo zaawansowane nie jest zaznaczony

    currentTourName = QInputDialog::getText(this, "Podaj nazwe turnieju", "Nazwa:", QLineEdit::Normal, "");
    tournaments[currentTourName] = m_teams;
    refreshCombos();
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

ExtendedTeams* MainWindow::getOrCreateExt(const QString& name)
{
    for (int i = 0; i < m_advTeams.size(); ++i)     //QVector<ExtendedTeams*>  m_advTeams - jest w definicji mainwindow.h
    {
        if (m_advTeams[i]->getName() == name)       //szukamy czy juz istnieje taka druzyne w extended klasie
            return m_advTeams[i];
    }

    ExtendedTeams* t = new ExtendedTeams(name);     //jak nie tworzymy nowa
    m_advTeams.append(t);
    return t;
}

void MainWindow::refreshCombos()
{
    for(auto it = tournaments.begin(); it!=tournaments.end(); ++it)
    {
        if(ui->tournamentList->findText(it.key()) == -1)
        {
            ui->tournamentList->addItem(it.key());
        }
    }
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

    if (ui->Zaawansowane_CheckBox->isChecked()) //if zaawansowane jest zaznaczone
    {
        MatchStats msA; //tworzymy nowy obiekt struktury; naglowki ida tak: match-specify.h ->extended-teams.h->mainwindow.h
        msA.date        = QDate::currentDate();
        msA.goalsFor    = goalsA;
        msA.goalsAg     = goalsB;
        msA.shotsOnTgt  = ui->StrzNBr_A->text().toInt();
        msA.shotsTot    = ui->StrzL_A->text().toInt();
        msA.expectedG   = ui->OczGol_A->text().toInt();
        msA.scorers     = ui->Strzelcy_A->text().split(",", Qt::SkipEmptyParts);

        getOrCreateExt(teamAName)->addMatch(msA);

        /* ten nowo utowrzony, badz znaleziony obiekt wskazujemy na metode addMatch,
         * ktora jak widzisz w parametrach bierze obiekt struktury, ten obiekt z wszystkimi jego wartosciami
         * zostanie dodany do wektora w prywatnym polu ExtendedTeams - czyli bedziemy mieli log z wszystkimi
         * meczami (w ktorych zaznaczyles zaawansowane)dla tej druzyny. Jak zobaczysz w implementacje addMatch,
         *  to zauwazysz ze pelni ona niejako
         * role konstruktora sparametryzowanego

        */

        MatchStats msB;
        msB.date        = QDate::currentDate();
        msB.goalsFor    = goalsB;
        msB.goalsAg     = goalsA;
        msB.shotsOnTgt  = ui->StrzNBr_B->text().toInt();
        msB.shotsTot    = ui->StrzL_B->text().toInt();
        msB.expectedG   = ui->OczGol_B->text().toInt();
        msB.scorers     = ui->Strzelcy_B->text().split(",", Qt::SkipEmptyParts);

        getOrCreateExt(teamBName)->addMatch(msB);


    }

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
        "",                             //const QString &dir = QString(),
        "Pliki tekstowe (*.txt)"            //const QString &filter = QString(), taki format mam osobiscie na windowsie
        );

    if (path.isEmpty()) return;

    qDebug() << path;

    QVector<Teams> loaded = FileOp::loadFromFile(path);
    if (loaded.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Nie udało się wczytać danych.");
        return;
    }

    m_teams = loaded;
    refreshCombos();
    model->setTeams(m_teams);
}


void MainWindow::on_Save_Button_clicked()
{
    QString path = QFileDialog::getSaveFileName(
        this,
        "Zapisz dane drużyn",
        "",
        "Pliki tekstowe (*.txt);;Wszystkie pliki (*)"
        );

    if (path.isEmpty()) //czyli user zamknal okno, anulowal
        return;

    qDebug() << path;


    bool zapisano = FileOp::saveToFile(m_teams, path);


    if (zapisano) {
        QMessageBox::information(this, "Sukces", "Zapisano dane do pliku.");
    } else {
        QMessageBox::critical(this, "Błąd", "Nie udało się zapisać danych do pliku.");
    }
}

void MainWindow::on_Zaawansowane_CheckBox_stateChanged(int arg1)
{
    bool zaznaczony = (arg1 == Qt::Checked);
    ui->formWidget_A->setEnabled(zaznaczony); //uzylem setEnabled zamiast setVisible żeby layout zawsze byl ten sam
    ui->formWidget_B->setEnabled(zaznaczony);   //setEnabled(false) == zaciemnione komorki
}


void MainWindow::on_details_clicked()
{
    const QString nameA = ui->select_A->currentText();
    const QString nameB = ui->select_B->currentText();

    int indexA = -1;
    int indexB = -1;

    // Szukamy drużyny rozszerzonej po nazwie
    for (int i = 0; i < m_advTeams.size(); ++i)
    {
        if (m_advTeams[i]->getName() == nameA) indexA = i;
        if (m_advTeams[i]->getName() == nameB) indexB = i;
    }

    if (indexA == -1 || indexB == -1)
    {
        QMessageBox::information(this,
                                 "Brak danych",
                                 "Przynajmniej jedna z drużyn nie posiada danych zaawansowanych.");
    }

    Details dlg(m_advTeams[indexA],m_advTeams[indexB], this); //idz do konstruktora w details.cpp
    dlg.exec();
    return;
}


void MainWindow::on_DEMO_clicked()
{
    QStringList nazwiska = {
        "Lewandowski", "Messi", "Haaland", "Mbappe",
        "Benzema", "Salah", "Kane", "Foden"
    };

    auto losujStrzelcow = [&](int liczbaGoli) -> QStringList {
        QStringList lista;
        for (int i = 0; i < liczbaGoli; ++i) {
            int idx = QRandomGenerator::global()->bounded(nazwiska.size());
            lista << nazwiska[idx];
        }
        return lista;
    };

    // --- LOSOWANIE DANYCH DLA DRUŻYNY A -------------------------
    int RzutRA      = QRandomGenerator::global()->bounded(0,10);
    int LiczbPA     = QRandomGenerator::global()->bounded(211,390);
    int PosesjaA    = QRandomGenerator::global()->bounded(0,100);
    int goalsA      = QRandomGenerator::global()->bounded(0, 5);   // 0–4 gole
    int shotsA      = QRandomGenerator::global()->bounded(5, 16);  // 5–15 strzałów
    int onTargetA   = QRandomGenerator::global()->bounded(2, qMin(shotsA, 9) + 1); // max celnych = shotsA
    int xGA         = QRandomGenerator::global()->bounded(qMax(goalsA - 1, 0), goalsA + 2); // około gola ±1
    QStringList scorersA = losujStrzelcow(goalsA);

    // --- LOSOWANIE DLA DRUŻYNY B -------------------------------
    int RzutRB      = QRandomGenerator::global()->bounded(0,10);
    int LiczbPB      = QRandomGenerator::global()->bounded(211,390);
    int PosesjaB   = QRandomGenerator::global()->bounded(PosesjaA,100);
    int goalsB      = QRandomGenerator::global()->bounded(0, 5);
    int shotsB      = QRandomGenerator::global()->bounded(5, 16);
    int onTargetB   = QRandomGenerator::global()->bounded(2, qMin(shotsB, 9) + 1);
    int xGB         = QRandomGenerator::global()->bounded(qMax(goalsB - 1, 0), goalsB + 2);
    QStringList scorersB = losujStrzelcow(goalsB);

    // --- WYPEŁNIANIE UI ----------------------------------------
    ui->spinBox_A->setValue(goalsA);
    ui->spinBox_B->setValue(goalsB);


    ui->Lp_A->setText(QString::number(LiczbPA));
    ui->RzutR_A->setText(QString::number(RzutRA));
    ui->PosP_A->setText(QString::number(PosesjaA));
    ui->StrzL_A->setText(QString::number(shotsA));
    ui->StrzNBr_A->setText(QString::number(onTargetA));
    ui->OczGol_A->setText(QString::number(xGA));
    ui->Strzelcy_A->setText(scorersA.join(", "));


    ui->Lp_B->setText(QString::number(LiczbPB));
    ui->RzutR_B->setText(QString::number(RzutRB));
    ui->PosP_B->setText(QString::number(PosesjaB));
    ui->StrzL_B->setText(QString::number(shotsB));
    ui->StrzNBr_B->setText(QString::number(onTargetB));
    ui->OczGol_B->setText(QString::number(xGB));
    ui->Strzelcy_B->setText(scorersB.join(", "));


    // --- DOMYŚLNE DANE ----------------------------------------

}


void MainWindow::on_edytuj_A_clicked()
{
    QString name = ui->select_A->currentText();

    if (name.isEmpty())
        return;

    Edytuj dlg(name, this);
    if(dlg.exec() == QDialog::Accepted)
    {
        QString NewName = dlg.GetNewName();

        if(NewName.isEmpty() || NewName == name) return;

        for (Teams& t: m_teams)
            if(t.getName() == name)
                t.setName(NewName);

        for (ExtendedTeams* ex: m_advTeams)
            if(ex->getName() == name)
                ex->setName(NewName);

        refreshCombos();
        model->setTeams(m_teams);

    }
}

void MainWindow::on_actionDodaj_turniej_triggered()
{
    QString name = QInputDialog::getText(this, "Dodawanie turnieju", "Nazwa nowego turnieju:", QLineEdit::Normal, "");
    tournaments[name] = QList<Teams>();
    refreshCombos();
}


void MainWindow::on_tournamentList_currentTextChanged(const QString &arg1)
{
    tournaments[currentTourName] = m_teams;
    currentTourName = arg1;
    m_teams = tournaments[currentTourName];
    if(model == nullptr)
        model = new TeamsModel();
    model->setTeams(m_teams); // potencjalnie nieoptymalnie
    ui->scoresTable->setModel(model);
    refreshCombos();
}

