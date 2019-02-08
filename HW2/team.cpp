/*
 * team.cpp
 *
 *  Created on: 5 ���� 2017
 *      Author: Tal
 */

#include "team.h"

Team::Team(int ID) {
	TeamID=ID;
	studentTreeByPower = new RankTree<Student*, studentPowerKey>();
	numOfStudents=0;
	winCount=0;
	mostPowerfulStudent=NULL;
};
//		: TeamID(ID), studentTreeByPower(), numOfStudents(0),
//					 winCount(0), mostPowerfulStudent(NULL){};

Team::~Team() {
//    studentTreeByPower->postorder(DeleteStudent());
//    if (studentTreeByPower) {
        delete studentTreeByPower;
//    }
}

void Team::addStudentToTeam(Student* student, studentPowerKey key){
	studentTreeByPower->insert(student,key, student->getPower());
	numOfStudents++;
}

void Team::removeStudentFromTeam(studentPowerKey key){
	studentTreeByPower->remove(key);
	numOfStudents--;
}

int Team::getTeamId() const{
	return TeamID;
}

RankTree<Student*,studentPowerKey>* Team::getStudentbyPowerTree(){
	return studentTreeByPower;
}

void Team::setStudentByPowerTree(RankTree<Student*,studentPowerKey>* tree){
	studentTreeByPower = tree;
}

int Team::getNumOfStudentsInTeam() const{
	return numOfStudents;
}

void Team::setNumOfStudentsInTeam(int num){
	numOfStudents = num;
}

int Team::getWinCount() const {
	return winCount;
}

void Team::setWinCount(int winCount) {
	Team::winCount = winCount;
}

Student* Team::getMostPowerfulStudentInTeam() const{
	return mostPowerfulStudent;
}

void Team::setMostPowerFulStudentInTeam(Student* student){
	mostPowerfulStudent = student;
}
