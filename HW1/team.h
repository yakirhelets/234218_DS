/*
 * team.h
 *
 *  Created on: 4 ���� 2017
 *      Author: Tal
 */

#ifndef TEAM_H_
#define TEAM_H_

#include "student.h"
#include "AVL.h"

class Team{
private:
	int TeamID;
	AVL<Student*, studentPowerKey> studentTreeByPower;
	int numOfStudents;
	Student* mostPowerfulStudent;
public:
	Team(int ID);
	void addStudentToTeam(Student* student, studentPowerKey key);
	void removeStudentFromTeam(studentPowerKey key);
	int getTeamId() const;
	AVL<Student*,studentPowerKey>* getStudentbyPowerTree();
	void setStudentByPowerTree(AVL<Student*,studentPowerKey>* tree);
	Student* getMostPowerfulStudentInTeam() const;
	int getNumOfStudentsInTeam() const;
	void setNumOfStudentsInTeam(int num);
	void setMostPowerFulStudentInTeam(Student* student);
};

#endif /* TEAM_H_ */
