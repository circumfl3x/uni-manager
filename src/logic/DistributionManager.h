#pragma once

#include <QVector>
#include <QPair>
#include <QString>
#include "models/Applicant.h"
#include "models/University.h"

class DistributionManager {
public:
    DistributionManager();

    // Управление абитуриентами
    void addApplicant(const Applicant& app);
    void clearApplicants();
    const QVector<Applicant>& getApplicants() const;

    // Управление вузами (чтобы интерфейс мог их отобразить)
    const QVector<University>& getUniversities() const;

    // Главный метод распределения.
    // Возвращает список пар: <Имя абитуриента, Куда зачислен (или "Не зачислен")>
    QVector<QPair<QString, QString>> runDistribution();

private:
    QVector<Applicant> m_applicants;
    QVector<University> m_universities; // Вектор хранит вузы в порядке приоритета!
};