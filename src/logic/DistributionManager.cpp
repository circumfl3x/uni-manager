#include "DistributionManager.h"
#include <algorithm>

DistributionManager::DistributionManager() {
    m_universities.append(University("ИТМО", 297, 2));
    m_universities.append(University("ЛЭТИ", 271, 3));
    m_universities.append(University("СПбГУ", 289, 4));

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

// реализация изменения приоритета кнопками
void DistributionManager::moveUniversityUp(int index) {
    if (index > 0 && index < m_universities.size()) {
        std::swap(m_universities[index], m_universities[index - 1]);
    }
}

void DistributionManager::moveUniversityDown(int index) {
    if (index >= 0 && index < m_universities.size() - 1) {
        std::swap(m_universities[index], m_universities[index + 1]);
    }
}

void DistributionManager::insertUniversity(int index, const University& uni) {
    // Если приоритет больше, чем всего вузов, ставим в конец
    if (index > m_universities.size()) {
        index = m_universities.size();
    }
    // Если меньше нуля, ставим в начало
    if (index < 0) {
        index = 0;
    }
    m_universities.insert(index, uni);
}