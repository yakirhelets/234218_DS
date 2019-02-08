/*
 * student.cpp
 *
 *  Created on: 4.5.2017
 *      Author: Tal
 */

#include "student.h"

//Implementation of student.h

Student::Student(Team* team, int studentID,  int grade, int power):
	team(team), studentID(studentID), grade(grade), power(power){}

int Student::getID() const{
	return studentID;
}

Team* Student::getTeam() const{
	return team;
}

int Student::getPower() const{
	return power;
}

int Student::getGrade() const{
	return grade;
}

void Student::setID(int ID){
	studentID = ID;
}

void Student::setTeam(Team* t){
	team = t;
}

void Student::setPower(int pow){
	power = pow;
}

void Student::setGrade(int GR){
	grade = GR;
}


//Implementation of compare class for sorting by power

bool operator==(const studentPowerKey& s1,const studentPowerKey& s2){
	return (s1.ID == s2.ID) && (s1.power == s2.power);
}

bool operator<(const studentPowerKey& s1,const studentPowerKey& s2){
	if (s1.power == s2.power){
		return s1.ID > s2.ID;
	}
	return s1.power < s2.power;
}

bool operator>(const studentPowerKey& s1,const studentPowerKey& s2){
	return (!(s1<s2) && !(s1==s2));
}





