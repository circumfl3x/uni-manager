#pragma once

#include <QString>

class University {
public:

    University(const QString& name, int passingScore, int seats);

    
    QString getName() const;
    int getPassingScore() const;
    int getSeats() const;
    int getEnrolled() const; 

    bool isPassing(int applicantScore) const; 
    bool hasSpace() const;
    
    void enrollStudent(); 
    void reset();

private:
    QString m_name;
    int m_passingScore;
    int m_seats;
    int m_enrolled = 0;
};