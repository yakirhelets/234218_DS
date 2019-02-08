/*
 * student.h
 *
 *  Created on: Apr 30, 2017
 *      Author: Tal Tzafrir
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <stdlib.h>
class Team;

class Student {
private:
    Team* team;
    int studentID;
    int grade;
    int power;
public:
    Student(): team(NULL), studentID(-1), grade(-1), power(-1) {};
    Student(Team* team, int studentID, int grade, int power);
    Team* getTeam() const;
    int getID() const;
    int getPower() const;
    int getGrade() const;
    void setTeam(Team* team);
    void setID(int ID);
    void setPower(int power);
    void setGrade(int grade);

};

class studentPowerKey {
    int ID;
    int power;
public:
    studentPowerKey():ID(-1),power(-1){}; //empty C'tor
    studentPowerKey(int ID,int power):ID(ID),power(power){}
    studentPowerKey(Student& s):ID(s.getID()),power(s.getPower()){};
    bool friend operator==(const studentPowerKey& s1,const studentPowerKey& s2);
    bool friend operator<(const studentPowerKey& s1,const studentPowerKey& s2);
    bool friend operator>(const studentPowerKey& s1,const studentPowerKey& s2);
};



#endif /* STUDENT_H_ */
