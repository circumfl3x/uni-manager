#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QGroupBox>
#include <QFormLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
    updateUniversitiesTable(); 
}

void MainWindow::setupUi() {
    setWindowTitle("Распределение абитуриентов");
    resize(1100, 700); 

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // left
    QVBoxLayout *leftLayout = new QVBoxLayout();

    QGroupBox *inputGroup = new QGroupBox("Добавить абитуриента");
    QFormLayout *formLayout = new QFormLayout(inputGroup);
    
    m_nameEdit = new QLineEdit();
    m_countryEdit = new QLineEdit();
    m_scoreEdit = new QLineEdit();
    
    formLayout->addRow("ФИО:", m_nameEdit);
    formLayout->addRow("Страна:", m_countryEdit);
    formLayout->addRow("Балл:", m_scoreEdit);

    m_addButton = new QPushButton("Добавить в список");
    m_addButton->setStyleSheet("background-color: #4CAF50; color: white; font-weight: bold;");
    formLayout->addRow(m_addButton);

    leftLayout->addWidget(inputGroup);

    leftLayout->addWidget(new QLabel("Список абитуриентов:"));
    m_applicantsTable = new QTableWidget(0, 3);
    m_applicantsTable->setHorizontalHeaderLabels({"ФИО", "Страна", "Балл"});
    m_applicantsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_applicantsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    leftLayout->addWidget(m_applicantsTable);

    m_clearButton = new QPushButton("Очистить список");
    leftLayout->addWidget(m_clearButton);

    QVBoxLayout *rightLayout = new QVBoxLayout();

    QGroupBox *uniInputGroup = new QGroupBox("Добавить университет");
    QFormLayout *uniFormLayout = new QFormLayout(uniInputGroup);
    
    m_uniNameEdit = new QLineEdit();
    m_uniScoreEdit = new QLineEdit();
    m_uniSeatsEdit = new QLineEdit();
    
    uniFormLayout->addRow("Название:", m_uniNameEdit);
    uniFormLayout->addRow("Проходной балл:", m_uniScoreEdit);
    uniFormLayout->addRow("Кол-во мест:", m_uniSeatsEdit);
    
    m_addUniButton = new QPushButton("Добавить вуз"); // Сначала создаем кнопку
    m_addUniButton->setStyleSheet("background-color: #FF9800; color: white; font-weight: bold;");
    uniFormLayout->addRow(m_addUniButton);

    rightLayout->addWidget(uniInputGroup); // Добавляем форму в правую колонку

    rightLayout->addWidget(new QLabel("Университеты (в порядке приоритета):"));
    m_universitiesTable = new QTableWidget(0, 4);
    m_universitiesTable->setHorizontalHeaderLabels({"Приоритет", "Вуз", "Проходной балл", "Мест"});
    m_universitiesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_universitiesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    rightLayout->addWidget(m_universitiesTable);

    // кнопки изменения приоритета
    QHBoxLayout *prioButtonsLayout = new QHBoxLayout();
    m_upButton = new QPushButton("Приоритет выше");
    m_downButton = new QPushButton("Приоритет ниже");
    prioButtonsLayout->addWidget(m_upButton);
    prioButtonsLayout->addWidget(m_downButton);
    rightLayout->addLayout(prioButtonsLayout);

    m_distributeButton = new QPushButton("РАСПРЕДЕЛИТЬ СТУДЕНТОВ");
    m_distributeButton->setStyleSheet("background-color: #2196F3; color: white; font-weight: bold; padding: 10px; font-size: 14px;");
    rightLayout->addWidget(m_distributeButton);

    rightLayout->addWidget(new QLabel("Результаты распределения:"));
    m_resultsTable = new QTableWidget(0, 2);
    m_resultsTable->setHorizontalHeaderLabels({"Абитуриент", "Куда зачислен"});
    m_resultsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_resultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    rightLayout->addWidget(m_resultsTable);

    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 1);

    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::onAddApplicantClicked);
    connect(m_clearButton, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(m_distributeButton, &QPushButton::clicked, this, &MainWindow::onDistributeClicked);
    connect(m_addUniButton, &QPushButton::clicked, this, &MainWindow::onAddUniversityClicked);
    connect(m_upButton, &QPushButton::clicked, this, &MainWindow::onMoveUpClicked);
    connect(m_downButton, &QPushButton::clicked, this, &MainWindow::onMoveDownClicked);
}

void MainWindow::onAddApplicantClicked() {
    QString name = m_nameEdit->text().trimmed();
    QString country = m_countryEdit->text().trimmed();
    QString scoreStr = m_scoreEdit->text().trimmed();

    if (name.isEmpty() || country.isEmpty() || scoreStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля!");
        return;
    }

    bool ok;
    int score = scoreStr.toInt(&ok);
    if (!ok || score < 0 || score > 300) { // макс балл 300
        QMessageBox::warning(this, "Ошибка", "Балл должен быть числом от 0 до 300!");
        return;
    }

    m_manager.addApplicant(Applicant(name, country, score));
    
    m_nameEdit->clear();
    m_countryEdit->clear();
    m_scoreEdit->clear();

    updateApplicantsTable();
}

void MainWindow::updateApplicantsTable() {
    const auto& apps = m_manager.getApplicants();
    m_applicantsTable->setRowCount(apps.size());

    for (int i = 0; i < apps.size(); ++i) {
        m_applicantsTable->setItem(i, 0, new QTableWidgetItem(apps[i].getName()));
        m_applicantsTable->setItem(i, 1, new QTableWidgetItem(apps[i].getCountry()));
        m_applicantsTable->setItem(i, 2, new QTableWidgetItem(QString::number(apps[i].getScore())));
    }
}

void MainWindow::updateUniversitiesTable() {
    const auto& unis = m_manager.getUniversities();
    m_universitiesTable->setRowCount(unis.size());

    for (int i = 0; i < unis.size(); ++i) {
        m_universitiesTable->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        m_universitiesTable->setItem(i, 1, new QTableWidgetItem(unis[i].getName()));
        m_universitiesTable->setItem(i, 2, new QTableWidgetItem(QString::number(unis[i].getPassingScore())));
        m_universitiesTable->setItem(i, 3, new QTableWidgetItem(QString::number(unis[i].getSeats())));
    }
}

void MainWindow::onClearClicked() {
    m_manager.clearApplicants();
    updateApplicantsTable();
    m_resultsTable->setRowCount(0);
}

void MainWindow::onDistributeClicked() {
    if (m_manager.getApplicants().isEmpty()) {
        QMessageBox::information(this, "Пусто", "Добавьте хотя бы одного абитуриента.");
        return;
    }

    auto results = m_manager.runDistribution();

    m_resultsTable->setRowCount(results.size());
    for (int i = 0; i < results.size(); ++i) {
        m_resultsTable->setItem(i, 0, new QTableWidgetItem(results[i].first));
        
        QTableWidgetItem *resultItem = new QTableWidgetItem(results[i].second);

        if (results[i].second == "Не зачислен") {
            resultItem->setForeground(QBrush(Qt::red));
        } else {
            resultItem->setForeground(QBrush(Qt::darkGreen));
        }
        m_resultsTable->setItem(i, 1, resultItem);
    }
}

void MainWindow::onAddUniversityClicked() {
    QString name = m_uniNameEdit->text().trimmed();
    QString scoreStr = m_uniScoreEdit->text().trimmed();
    QString seatsStr = m_uniSeatsEdit->text().trimmed();

    if (name.isEmpty() || scoreStr.isEmpty() || seatsStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Необходимо заполнить все поля");
        return;
    }

    bool okScore, okSeats;
    int score = scoreStr.toInt(&okScore);
    int seats = seatsStr.toInt(&okSeats);

    if (!okScore || score < 0 || score > 300) {
        QMessageBox::warning(this, "Ошибка", "Проходной балл должен быть числом от 0 до 300");
        return;
    }
    
    if (!okSeats || seats <= 0) {
        QMessageBox::warning(this, "Ошибка", "Количество мест должно быть больше нуля");
        return;
    }

    m_manager.addUniversity(University(name, score, seats));
    
    m_uniNameEdit->clear();
    m_uniScoreEdit->clear();
    m_uniSeatsEdit->clear();
    
    updateUniversitiesTable();
}

void MainWindow::onMoveUpClicked() {
    int currentRow = m_universitiesTable->currentRow();
    if (currentRow <= 0) {
        QMessageBox::information(this, "Внимание", "Выбран вуз с самым высоким приоритетом");
        return;
    }
    
    m_manager.moveUniversityUp(currentRow);
    updateUniversitiesTable();
    
    // Возвращаем выделение на ту же строку, чтобы можно было нажимать дальше
    m_universitiesTable->selectRow(currentRow - 1); 
}

void MainWindow::onMoveDownClicked() {
    int currentRow = m_universitiesTable->currentRow();
    // Проверяем, что выбрана не последняя строка и вообще что-то выбрано
    if (currentRow < 0 || currentRow >= m_manager.getUniversities().size() - 1) {
        QMessageBox::information(this, "Внимание", "Выбран вуз с самым низким приоритетом");
        return;
    }
    
    m_manager.moveUniversityDown(currentRow);
    updateUniversitiesTable();
    
    m_universitiesTable->selectRow(currentRow + 1);
}