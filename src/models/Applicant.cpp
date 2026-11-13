#include "Applicant.h"

Applicant::Applicant(const QString& name, const QString& country, int score)
    : m_name(name), m_country(country), m_score(score) {
}

QString Applicant::getName() const {
    return m_name;
}

QString Applicant::getCountry() const {
    return m_country;
}

int Applicant::getScore() const {
    return m_score;
}

void Applicant::setName(const QString& name) {
    m_name = name;
}

void Applicant::setCountry(const QString& country) {
    m_country = country;
}

void Applicant::setScore(int score) {
    m_score = score;
}