#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BusinessLogic/teams.h"
#include <QVector>
#include "BusinessLogic/teamsmodel.h"
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

private:
    void refreshCombos();

    Ui::MainWindow *ui;
    QVector<Teams>  m_teams;
    TeamsModel * model = nullptr;
};

#endif // MAINWINDOW_H
