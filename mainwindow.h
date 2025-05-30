#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BusinessLogic/teams.h"
#include <QVector>
#include "BusinessLogic/teamsmodel.h"
#include "BusinessLogic/extended-teams.h"
#include "details.h"
#include <QRandomGenerator>
#include "edytuj.h"
         // include z biblioteki

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_add_team_clicked();
    
    void on_add_match_clicked();

    void on_Load_Button_clicked();

    void on_Save_Button_clicked();

    void on_Zaawansowane_CheckBox_stateChanged(int arg1);

    void on_details_clicked();

    void on_DEMO_clicked();

    void on_edytuj_A_clicked();

    void on_edytuj_B_clicked();

private:
    void refreshCombos();
    ExtendedTeams* getOrCreateExt(const QString& name);

    Ui::MainWindow *ui;
    QVector<Teams>  m_teams;
    TeamsModel * model = nullptr;
    QVector<ExtendedTeams*>  m_advTeams;
};

#endif // MAINWINDOW_H
