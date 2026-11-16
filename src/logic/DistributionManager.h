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

    void addUniversity(const University& uni);
    const QVector<University>& getUniversities() const;

    // изменение приоритета
    void moveUniversityUp(int index);
    void moveUniversityDown(int index);

    QVector<QPair<QString, QString>> runDistribution();

private:
    QVector<Applicant> m_applicants;
    QVector<University> m_universities;
};