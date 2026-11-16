#pragma once

#include <QString>

class Applicant {
public:
    
    Applicant() = default;
    Applicant(const QString& name, const QString& country, int score);

    
    QString getName() const;
    QString getCountry() const;
    int getScore() const;

    void setName(const QString& name);
    void setCountry(const QString& country);
    void setScore(int score);

private:
    QString m_name;
    QString m_country;
    int m_score = 0;
};