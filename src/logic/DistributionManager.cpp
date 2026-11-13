#include "DistributionManager.h"
#include <algorithm>

DistributionManager::DistributionManager() {
    // Заполняем фиксированный список вузов.
    // Порядок добавления = порядок приоритета!
    // (Название, Проходной балл, Кол-во мест)
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
    // 1. Сбрасываем счетчики зачисленных в вузах (на случай повторного запуска)
    for (auto& uni : m_universities) {
        uni.reset();
    }

    // 2. Делаем копию абитуриентов и сортируем по убыванию балла
    QVector<Applicant> sortedApplicants = m_applicants;
    std::sort(sortedApplicants.begin(), sortedApplicants.end(), 
        [](const Applicant& a, const Applicant& b) {
            return a.getScore() > b.getScore(); // По убыванию
        }
    );

    QVector<QPair<QString, QString>> results;

    // 3. Идем по отсортированному списку и распределяем
    for (const auto& app : sortedApplicants) {
        bool isEnrolled = false;

        // Идем по вузам в порядке приоритета (как они лежат в m_universities)
        for (auto& uni : m_universities) {
            // Если балл проходит и есть места — зачисляем
            if (uni.isPassing(app.getScore()) && uni.hasSpace()) {
                uni.enrollStudent();
                results.append({app.getName(), uni.getName()});
                isEnrolled = true;
                break; // Зачислили — переходим к следующему абитуриенту
            }
        }

        // Если ни в один вуз не прошёл
        if (!isEnrolled) {
            results.append({app.getName(), "Не зачислен"});
        }
    }

    return results;
}