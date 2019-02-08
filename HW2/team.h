/*
 * team.h
 *
 *  Created on: 4 ���� 2017
 *      Author: Tal
 */

#ifndef TEAM_H_
#define TEAM_H_

#include "student.h"
#include "RankTree.h"

class Team{
private:
	int TeamID;
	RankTree<Student*, studentPowerKey>* studentTreeByPower;
	int numOfStudents;
	int winCount;
	Student* mostPowerfulStudent;
public:
	Team(int ID);
	~Team();
	void addStudentToTeam(Student* student, studentPowerKey key);
	void removeStudentFromTeam(studentPowerKey key);
	int getTeamId() const;
	RankTree<Student*,studentPowerKey>* getStudentbyPowerTree();
	void setStudentByPowerTree(RankTree<Student*,studentPowerKey>* tree);
	Student* getMostPowerfulStudentInTeam() const;
	int getNumOfStudentsInTeam() const;
	void setNumOfStudentsInTeam(int num);
	void setMostPowerFulStudentInTeam(Student* student);
	int getWinCount() const;
	void setWinCount(int winCount);
};

#endif /* TEAM_H_ */
