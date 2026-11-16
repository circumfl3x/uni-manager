#pragma once

#include <QVector>
#include <QPair>
#include <QString>
#include "models/Applicant.h"
#include "models/University.h"

class DistributionManager {
public:
    DistributionManager();

    void addApplicant(const Applicant& app);
    void clearApplicants();
    const QVector<Applicant>& getApplicants() const;

    const QVector<University>& getUniversities() const;

    QVector<QPair<QString, QString>> runDistribution();

private:
    QVector<Applicant> m_applicants;
    QVector<University> m_universities; // Вектор хранит вузы в порядке приоритета
};