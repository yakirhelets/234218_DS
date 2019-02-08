/*
 * library2.cpp
 *
 *  Created on: 14 ����� 2017
 *      Author: Tal
 */

#include "library2.h"
#include "school.h"

void* Init(int numOfTeams) {
    School* school = new School(numOfTeams);
    return (void*)school;
}

StatusType AddStudent(void *DS, int StudentID, int Team ,int Power){
	if (!DS || StudentID <= 0 || Team <= 0 || Team > ((School*)DS)->getNumOfTeams() || Power <= 0){
		return INVALID_INPUT;
	}
	try{
		((School*)DS)->addStudent(StudentID, Team-1, Power);
	}catch (School::Failure& e){
		return FAILURE;
	}catch (std::bad_alloc& e){
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType RemoveStudent(void *DS, int StudentID) {
    if (!DS || StudentID <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((School*)DS)->removeStudent(StudentID);
    }catch (School::Failure& error){
        return FAILURE;
    }catch (std::bad_alloc& e){
		return ALLOCATION_ERROR;
	}
    return SUCCESS;
}

StatusType JoinTeams(void *DS, int Team1, int Team2){
    if (!DS || (Team1 <= 0 || Team1 > ((School*)DS)->getNumOfTeams())
    		|| (Team2 <= 0 || Team2 > ((School*)DS)->getNumOfTeams())) {
        return INVALID_INPUT;
    }
    if (Team1==Team2) {
        return SUCCESS;
    }
    try {
        ((School*)DS)->joinTeams(Team1-1, Team2-1);
    }catch (std::bad_alloc& e){
		return ALLOCATION_ERROR;
	}
    return SUCCESS;
}

StatusType TeamFight(void *DS, int Team1, int Team2, int NumOfFighters){
    if (!DS || (Team1 <= 0 || Team1 > ((School*)DS)->getNumOfTeams())
    		|| (Team2 <= 0 || Team2 > ((School*)DS)->getNumOfTeams()) || NumOfFighters <= 0) {
        return INVALID_INPUT;
    }
    if (Team1==Team2) {
        return SUCCESS;
    }
    try {
        ((School*)DS)->teamFight(Team1-1, Team2-1, NumOfFighters);
    }catch (std::bad_alloc& e){
		return ALLOCATION_ERROR;
	}
    return SUCCESS;
}

StatusType GetNumOfWins(void *DS, int Team, int* Wins){
    if (!DS || !Wins || (Team <= 0 || Team > ((School*)DS)->getNumOfTeams())) {
        return INVALID_INPUT;
    }
    try {
        ((School*)DS)->getNumOfWins(Team-1, Wins);
    }catch (std::bad_alloc& e){
		return ALLOCATION_ERROR;
	}
    return SUCCESS;
}

StatusType GetStudentTeamLeader(void *DS, int StudentID, int* Leader){
    if (!DS || !Leader || StudentID <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((School*)DS)->getStudentTeamLeader(StudentID, Leader);
    }catch (School::Failure& error){
        return FAILURE;
    }catch (std::bad_alloc& e){
		return ALLOCATION_ERROR;
	}
    return SUCCESS;
}

void Quit(void** DS) {
    if (!DS) {
        return;
    }
    delete (*((School**)DS));
    *DS=NULL;
}










