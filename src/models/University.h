#pragma once

#include <QString>

class University {
public:
    // Конструктор
    University(const QString& name, int passingScore, int seats);

    // Геттеры
    QString getName() const;
    int getPassingScore() const;
    int getSeats() const;
    int getEnrolled() const; // Сколько уже зачислено

    // Бизнес-методы (вся логика проверки инкапсулирована здесь)
    bool isPassing(int applicantScore) const; // Хватает ли балла?
    bool hasSpace() const;                    // Есть ли свободные места?
    
    // Действия
    void enrollStudent(); // Увеличивает счетчик зачисленных на 1
    void reset();         // Сбрасывает счетчик (нужно перед новым распределением)

private:
    QString m_name;
    int m_passingScore;
    int m_seats;
    int m_enrolled = 0; // По умолчанию зачислено 0 человек
};