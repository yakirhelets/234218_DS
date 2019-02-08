/*
 * team.cpp
 *
 *  Created on: 5 ���� 2017
 *      Author: Tal
 */

#include "team.h"


Team::Team(int ID) : TeamID(ID), studentTreeByPower(), numOfStudents(0), mostPowerfulStudent(NULL){};

void Team::addStudentToTeam(Student* student, studentPowerKey key){
	studentTreeByPower.insert(student,key);
	numOfStudents++;
}

void Team::removeStudentFromTeam(studentPowerKey key){
	studentTreeByPower.remove(key);
	numOfStudents--;
}

int Team::getTeamId() const{
	return TeamID;
}

AVL<Student*,studentPowerKey>* Team::getStudentbyPowerTree(){
	return &studentTreeByPower;
}

void Team::setStudentByPowerTree(AVL<Student*,studentPowerKey>* tree){
	studentTreeByPower = *tree;
}

Student* Team::getMostPowerfulStudentInTeam() const{
	return mostPowerfulStudent;
}

int Team::getNumOfStudentsInTeam() const{
	return numOfStudents;
}

void Team::setNumOfStudentsInTeam(int num){
	numOfStudents = num;
}

void Team::setMostPowerFulStudentInTeam(Student* student){
	mostPowerfulStudent = student;
}









