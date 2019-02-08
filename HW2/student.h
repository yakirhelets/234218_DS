/*
 * student.h
 *
 *  Created on: Apr 30, 2017
 *      Author: Tal Tzafrir
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <stdlib.h>

class Student {
private:
    int studentID;
    int teamID;
    int power;
public:
    Student(): studentID(-1), teamID(-1), power(-1) {};
    Student(int studentID, int teamID, int power);
    int getTeam() const;
    int getID() const;
    int getPower() const;
    void setTeam(int team);
    void setID(int ID);
    void setPower(int power);

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
