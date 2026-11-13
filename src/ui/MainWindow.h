#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include "logic/DistributionManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT // Обязательный макрос для работы сигналов и слотов

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    // Слоты (функции, которые вызываются по клику на кнопки)
    void onAddApplicantClicked();
    void onClearClicked();
    void onDistributeClicked();

private:
    // Вспомогательные методы для настройки интерфейса
    void setupUi();
    void updateApplicantsTable();
    void updateUniversitiesTable();

    // Данные
    DistributionManager m_manager;

    // Элементы интерфейса
    QLineEdit *m_nameEdit;
    QLineEdit *m_countryEdit;
    QLineEdit *m_scoreEdit;
    
    QPushButton *m_addButton;
    QPushButton *m_clearButton;
    QPushButton *m_distributeButton;

    QTableWidget *m_applicantsTable;
    QTableWidget *m_universitiesTable;
    QTableWidget *m_resultsTable;
};