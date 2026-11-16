#include "DistributionManager.h"
#include <algorithm>

DistributionManager::DistributionManager() {
    m_universities.append(University("ИТМО", 85, 2));
    m_universities.append(University("ЛЭТИ", 75, 3));
    m_universities.append(University("СПбГУ", 65, 4));
}

void DistributionManager::addApplicant(const Applicant& app) {
    m_applicants.append(app);
}

void DistributionManager::clearApplicants() {
    m_applicants.clear();
}

const QVector<Applicant>& DistributionManager::getApplicants() const {
    return m_applicants;
}

const QVector<University>& DistributionManager::getUniversities() const {
    return m_universities;
}

QVector<QPair<QString, QString>> DistributionManager::runDistribution() {
    for (auto& uni : m_universities) {
        uni.reset();
    }

    QVector<Applicant> sortedApplicants = m_applicants;
    std::sort(sortedApplicants.begin(), sortedApplicants.end(), 
        [](const Applicant& a, const Applicant& b) {
            return a.getScore() > b.getScore();
        }
    );

    QVector<QPair<QString, QString>> results;

    for (const auto& app : sortedApplicants) {
        bool isEnrolled = false;

        for (auto& uni : m_universities) {
            if (uni.isPassing(app.getScore()) && uni.hasSpace()) {
                uni.enrollStudent();
                results.append({app.getName(), uni.getName()});
                isEnrolled = true;
                break;
            }
        }

        if (!isEnrolled) {
            results.append({app.getName(), "Не зачислен"});
        }
    }

    return results;
}