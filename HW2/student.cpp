/*
 * student.cpp
 *
 *  Created on: 4.5.2017
 *      Author: Tal
 */

#include "student.h"

//Implementation of student.h

Student::Student(int studentID, int teamID, int power):
	studentID(studentID), teamID(teamID), power(power){}

int Student::getID() const{
	return studentID;
}

int Student::getTeam() const{
	return teamID;
}

int Student::getPower() const{
	return power;
}

void Student::setID(int ID){
	studentID = ID;
}

void Student::setTeam(int t){
	teamID = t;
}

void Student::setPower(int pow){
	power = pow;
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





