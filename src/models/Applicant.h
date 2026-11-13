#pragma once

#include <QString>

class Applicant {
public:
    // Конструкторы
    Applicant() = default;
    Applicant(const QString& name, const QString& country, int score);

    // Геттеры (const означает, что метод не меняет объект)
    QString getName() const;
    QString getCountry() const;
    int getScore() const;

    // Сеттеры (позволят нам менять данные, например, если страна поменялась)
    void setName(const QString& name);
    void setCountry(const QString& country);
    void setScore(int score);

private:
    QString m_name;
    QString m_country;
    int m_score = 0;
};