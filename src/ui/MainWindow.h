#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include "logic/DistributionManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT 

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onAddApplicantClicked();
    void onClearClicked();
    void onDistributeClicked();
    void onAddUniversityClicked();
    void onMoveUpClicked();
    void onMoveDownClicked();

private:
    void setupUi();
    void updateApplicantsTable();
    void updateUniversitiesTable();

    DistributionManager m_manager;

    QLineEdit *m_nameEdit;
    QLineEdit *m_countryEdit;
    QLineEdit *m_scoreEdit;
    
    QPushButton *m_addButton;
    QPushButton *m_clearButton;
    QPushButton *m_distributeButton;

    QTableWidget *m_applicantsTable;
    QTableWidget *m_universitiesTable;
    QTableWidget *m_resultsTable;

    QLineEdit *m_uniNameEdit;
    QLineEdit *m_uniScoreEdit;
    QLineEdit *m_uniSeatsEdit;
    QPushButton *m_addUniButton;

    QPushButton *m_upButton;
    QPushButton *m_downButton;
};