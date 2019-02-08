#include "library1.h"
#include "school.h"

void* Init() {
    School* school = new School();
    return (void*)school;
}

StatusType AddStudent(void *DS, int StudentID, int Grade, int Power) {
    if(!DS || StudentID <=0 || Power <= 0 || Grade < 0){
        return INVALID_INPUT;
    }
    try{
        ((School*)DS)->addStudent(StudentID, Grade, Power);
    }catch (School::Failure& e){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType AddTeam(void *DS, int TeamID) {
    if (!DS || TeamID <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((School*)DS)->addTeam(TeamID);
    }catch (School::Failure& error){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType MoveStudentToTeam(void *DS, int StudentID, int TeamID) {
    if (!DS || TeamID <= 0 || StudentID <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((School*)DS)->moveStudentToTeam(StudentID, TeamID);
    }catch (School::Failure& error){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetMostPowerful(void *DS, int TeamID, int *StudentID) {
    if (!DS || TeamID == 0 || !StudentID) {
        return INVALID_INPUT;
    }
    try {
        ((School*)DS)->getMostPowerful(TeamID, StudentID);
    }catch (School::Failure& error){
        return FAILURE;
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
    }
    return SUCCESS;
}

StatusType GetAllStudentsByPower(void *DS, int TeamID, int **Students, int *numOfStudents) {
    if(!DS || TeamID == 0 || !Students || !numOfStudents){
        return INVALID_INPUT;
    }
    try{
        ((School*)DS)->getAllStudentsByPower(TeamID, Students, numOfStudents);
    }catch (School::Failure& e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType IncreaseLevel(void *DS, int Grade, int PowerIncrease) {
    if(!DS || Grade < 0 || PowerIncrease <= 0){
        return INVALID_INPUT;
    }
    try{
        ((School*)DS)->increaseLevel(Grade, PowerIncrease);
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void Quit(void** DS) {
    delete (*((School**)DS));
    *DS=NULL;
}
