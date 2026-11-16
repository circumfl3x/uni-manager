#include "University.h"

University::University(const QString& name, int passingScore, int seats)
    : m_name(name), m_passingScore(passingScore), m_seats(seats) {
}

QString University::getName() const {
    return m_name;
}

int University::getPassingScore() const {
    return m_passingScore;
}

int University::getSeats() const {
    return m_seats;
}

int University::getEnrolled() const {
    return m_enrolled;
}

bool University::isPassing(int applicantScore) const {
    return applicantScore >= m_passingScore;
}

bool University::hasSpace() const {
    return m_enrolled < m_seats;
}

void University::enrollStudent() {
    if (hasSpace()) {
        m_enrolled++;
    }
}

void University::reset() {
    m_enrolled = 0;
}