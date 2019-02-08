//
// Created by Yakir on 07/06/2017.
//

#ifndef WET2SPRING17_SCHOOL_H
#define WET2SPRING17_SCHOOL_H


#include "GenericUnionFind.h"
#include "GenericHashTable.h"
#include "team.h"
#include "student.h"

class School {
    int numOfTeams;
    HashTable<Student*>* studentsArr;
    UnionFind<Team*>* teams;
public:
    School(int numOfTeams);

    ~School();
    void addStudent(int studentId, int teamId, int power);
    void removeStudent(int studentId);
    void joinTeams(int team1, int team2);
    void teamFight(int team1, int team2, int numOfFighters);
    void getNumOfWins(int teamId, int* wins);
    void getStudentTeamLeader(int studentId, int* leader);
    int getNumOfTeams();
    /*
     * exception classes
     */
    class Failure {};
    class AllocationError {};
    class InvalidInput {};
};


#endif //WET2SPRING17_SCHOOL_H
