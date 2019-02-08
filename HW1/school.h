#ifndef WET1_DATASYSTEM_H
#define WET1_DATASYSTEM_H

#include "AVL.h"
#include "team.h"
#include "student.h"

class School {
    AVL<Team*,int> teamsById;
    AVL<Student*,int> studentsById;
    AVL<Student*,studentPowerKey> studentsByPower;
    int numOfStudents;
    int numOfTeams;
    Student* strongestStudent;
public:
    School();
    ~School();
    void addStudent(int studentId, int grade, int power);
    void addTeam(int TeamId);
    void moveStudentToTeam(int studentId, int teamId);
    void getMostPowerful(int TeamId, int* StudentId);
    void removeStudent(int StudentId);
    void getAllStudentsByPower(int TeamId, int** Students, int* numOfStudents);
    void increaseLevel(int grade, int powerIncrease);
    Student* getStrongestStudent() const;
    const AVL<Team*, int> &getTeamsById() const;
    /*
     * exception classes
     */
    class Failure {};
    class AllocationError {};
    class InvalidInput {};
};


#endif //WET1_DATASYSTEM_H
