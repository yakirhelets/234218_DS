//
// Created by Yakir on 07/05/2017.
//

#include "school.h"
class DeleteStudent {
public:
    void operator() (Student* s) {
        delete s;
    };
};
class DeleteTeam {
public:
    void operator() (Team* t) {
        delete t;
    };
};

School::School() : teamsById(), studentsById(), studentsByPower(),
                   numOfStudents(0), numOfTeams(0), strongestStudent(NULL) {}

School::~School() {
    teamsById.postorder(DeleteTeam());
    studentsById.postorder(DeleteStudent());
}

void School::addStudent(int studentId, int grade, int power) {
    Student* newStudent = new Student(NULL, studentId, grade, power);
    try {
        studentsById.insert(newStudent, studentId);
    } catch (AVL<Student*,int>::KeyAlreadyExists& e){
        delete newStudent;
        throw Failure();
    }
    studentsByPower.insert(newStudent,studentPowerKey(studentId,power));
    //update the most dangerous Student
    if (strongestStudent!=NULL) {
        if (studentPowerKey(*getStrongestStudent()) < studentPowerKey(*newStudent)) {
            strongestStudent=newStudent;
        }
    } else {
        strongestStudent=newStudent;
    }
    numOfStudents++;
}

void School::addTeam(int TeamId) {
    Team* newTeam = new Team(TeamId);
    try {
        this->teamsById.insert(newTeam, TeamId);
    } catch (AVL<Team*,int>::KeyAlreadyExists& e){
        delete newTeam;
        throw Failure();
    }
    numOfTeams++;
}

void School::moveStudentToTeam(int studentId, int TeamId) {
    Student* student;
    Team* team;
    try {
        student = studentsById.find(studentId);
        team = teamsById.find(TeamId);
    }catch (AVL<Student*,int>::KeyDoesNotExist& error) {
        throw Failure();
    }catch (AVL<Team*,int>::KeyDoesNotExist& error) {
        throw Failure();
    }
    if(student->getTeam()){
		if (student->getTeam()->getTeamId() == TeamId){
			return;
		}
    }
    team->addStudentToTeam(student, studentPowerKey(*student));
    if (team->getMostPowerfulStudentInTeam()) {
        if(studentPowerKey(*team->getMostPowerfulStudentInTeam())
           < studentPowerKey(*student)) {
            team->setMostPowerFulStudentInTeam(student);
        }
    } else {
        team->setMostPowerFulStudentInTeam(student);
    }
    if (student->getTeam()) {
        Team* oldTeam = student->getTeam();
        oldTeam->removeStudentFromTeam(studentPowerKey(*student));
        if ( oldTeam->getStudentbyPowerTree()->getRoot() ) {
            oldTeam->setMostPowerFulStudentInTeam
                    (oldTeam->getStudentbyPowerTree()->getMax());

        } else {
            oldTeam->setMostPowerFulStudentInTeam(NULL);
        }
    }
    student->setTeam(team);
}

void School::getMostPowerful(int TeamId, int* studentId) {
    if (TeamId<0) {
//        if (numOfStudents==0) {
        if (!strongestStudent) {
            *studentId=-1;
            return;
        } else {
            *studentId=strongestStudent->getID();
            return;
        }
    } else {
        Team* team;
        try {
            team = teamsById.find(TeamId);
        }catch (AVL<Team*,int>::KeyDoesNotExist& error) {
            throw Failure();
        }
//        if (team->getNumOfStudentsInTeam()==0) {
        if (!team->getMostPowerfulStudentInTeam()) {
            *studentId=-1;
            return;
        }
        *studentId=team->getMostPowerfulStudentInTeam()->getID();
    }
}

void School::removeStudent(int studentId) {
    Student* toRemove;
    try{
        toRemove = studentsById.find(studentId);
    } catch (AVL<Student*,int>::KeyDoesNotExist& error){
        throw Failure();
    }
    Team* toRemoveTeam = toRemove->getTeam();
    if (toRemoveTeam) {
        toRemoveTeam->removeStudentFromTeam( studentPowerKey(*toRemove) );
        if ( toRemoveTeam->getStudentbyPowerTree()->getRoot() ) {
            toRemoveTeam->setMostPowerFulStudentInTeam
                    (toRemoveTeam->getStudentbyPowerTree()->getMax());
        } else {
            toRemoveTeam->setMostPowerFulStudentInTeam(NULL);
        }
    }
    studentsById.remove(studentId);
    studentsByPower.remove( studentPowerKey(*toRemove) );
    delete toRemove;
    if ((studentsByPower.getRoot())) {
        strongestStudent = studentsByPower.getMax();
    } else {
        strongestStudent = NULL;
    }
    numOfStudents--;
}

/*
 * functor for getAllStudentsByPower
 */

class fillArrayBackwards {
    int **students;
public:
    fillArrayBackwards(int **students) :
            students(students) {};

    void operator()(Student *s) {
        (**students) = s->getID();
        (*students)--;
    }
};
/*
 * ***************************************
 */

void School::getAllStudentsByPower(int TeamId, int** Students,
                                   int* numOfStudents) {
    Team* team;
    if (TeamId < 0) {
        *numOfStudents=this->numOfStudents;
        if (this->numOfStudents==0) {
            *Students=NULL;
            return;
        } else {
            *Students = (int*)malloc((this->numOfStudents)*sizeof(int));
            int* endptr= (*Students)+(*numOfStudents)-1;
            studentsByPower.inorder(fillArrayBackwards(&endptr));
            return;
        }
    }
    if (TeamId > 0) {
        try {
            team = this->teamsById.find(TeamId);
        } catch (AVL<Team*, int>::KeyDoesNotExist& error) {
            throw Failure();
        }
        *numOfStudents=team->getNumOfStudentsInTeam();
        if (team->getNumOfStudentsInTeam()==0) {
            *Students=NULL;
            return;
        }
        *Students = (int*)malloc((*numOfStudents)*sizeof(int));
        int* endptr = (*Students)+(*numOfStudents)-1;
        team->getStudentbyPowerTree()->inorder(fillArrayBackwards(&endptr));
        return;
    }
}

/*
 *
 */
class FillStudentsInArray {
    Student** array;
public:
    FillStudentsInArray(Student** array) : array(array){};
    void operator()(Student* s) {
        (*array) = s;
        (array)++;
    }
};

class FillTeamsInArray {
    Team** array;
public:
    FillTeamsInArray(Team** array) : array(array){};
    void operator()(Team* t) {
        (*array) = t;
        (array)++;
    }
};

class CountGrades {
    int grade;
    int* count;
public:
    CountGrades(int grade, int* count) : grade(grade), count(count){};
    void operator()(Student* s) {
        if (s->getGrade()==grade) {
            (*count)++;
        }
    }
};

/*
 *
 */

/*
 * splits  the StudentArray "A" into two arrays, B and C by the Students' grade.
 * the function asserts that the arrays are allocated properly.
 */
static void splitStudentArrayByGrade(Student** A, int aSize, Student** B,
                                     Student** C, int grade) {
    int j = 0;
    int k = 0;
    for (int i=0 ; i<aSize ; i++) {
        if (A[i]->getGrade() == grade) {
            B[j] = A[i];
            j++;
        } else {
            C[k] = A[i];
            k++;
        }
    }
}
/*
 * merges  the StudentArrays "B" and "C" to a sorted array, "A".
 * the function asserts that the arrays are allocated properly.
 */
static void mergeStudentArrayByGrade(Student** A, Student** B, int bSize,
                                     Student** C, int cSize) {
    int i=0;
    int j=0;
    int k=0;
    while (i < bSize && j < cSize) {
        if ( studentPowerKey(*(B[i])) < studentPowerKey(*(C[j])) ) {
            A[k] = B[i];
            i++;
        } else {
            A[k] = C[j];
            j++;
        }
        k++;
    }
    if (i < bSize) {
        for (; i < bSize; i++) {
            A[k] = B[i];
            k++;
        }
    } else {
        for (; j < cSize; j++) {
            A[k] = C[j];
            k++;
        }
    }
}
void School::increaseLevel(int grade, int powerIncrease) {
    Team** teamArray = new Team*[numOfTeams];
    teamsById.inorder(FillTeamsInArray(teamArray));
    int numOfStudentsFromGrade=0;
    int totalNumOfStudents;
    for (int i = 0 ; i < numOfTeams ; i++) {
        totalNumOfStudents = teamArray[i]->getNumOfStudentsInTeam();
        if (totalNumOfStudents==0) {
            continue;
        }
        Student** studentsArray = new Student*[totalNumOfStudents];
        teamArray[i]->getStudentbyPowerTree()->
                inorder(FillStudentsInArray(studentsArray));
        teamArray[i]->getStudentbyPowerTree()->
                inorder(CountGrades(grade, &numOfStudentsFromGrade));
        if (numOfStudentsFromGrade==0) {
            delete[] studentsArray;
            continue;
        }
        Student** studentsFromGrade = new Student*[numOfStudentsFromGrade];
        Student** studentsNotFromGrade =
                new Student*[totalNumOfStudents-numOfStudentsFromGrade];
        splitStudentArrayByGrade(studentsArray, totalNumOfStudents,
                                 studentsFromGrade, studentsNotFromGrade, grade);
        for (int j=0 ; j<numOfStudentsFromGrade ; j++) {
            studentsFromGrade[j]->setPower(studentsFromGrade[j]->getPower()+powerIncrease);
        }
        mergeStudentArrayByGrade(studentsArray,studentsFromGrade,
                                 numOfStudentsFromGrade,studentsNotFromGrade,
                                 (totalNumOfStudents-numOfStudentsFromGrade));
        studentPowerKey* powerArray = new studentPowerKey[totalNumOfStudents];
        for (int j=0 ; j<totalNumOfStudents ; j++) {
            powerArray[j]=studentPowerKey( *(studentsArray[j]) );
        }
        teamArray[i]->getStudentbyPowerTree()->inorderWrite(studentsArray, powerArray);

        for (int j=0 ; j<numOfStudentsFromGrade ; j++) {
            studentsFromGrade[j]->setPower(studentsFromGrade[j]->getPower()-powerIncrease);
        }
        teamArray[i]->setMostPowerFulStudentInTeam(studentsArray[totalNumOfStudents-1]);
        numOfStudentsFromGrade=0;
        delete[] studentsArray;
        delete[] studentsFromGrade;
        delete[] studentsNotFromGrade;
        delete[] powerArray;
    }
    delete[] teamArray;
    if (numOfStudents==0) {
        return;
    }
    Student** studentsArray = new Student*[numOfStudents];
    studentsByPower.inorder(FillStudentsInArray(studentsArray));
    studentsByPower.inorder(CountGrades(grade, &numOfStudentsFromGrade));
    if (numOfStudentsFromGrade==0) {
        delete[] studentsArray;
        return;
    }
    Student** studentsFromGrade = new Student*[numOfStudentsFromGrade];
    Student** studentsNotFromGrade =
            new Student*[numOfStudents-numOfStudentsFromGrade];
    splitStudentArrayByGrade(studentsArray, numOfStudents, studentsFromGrade,
                             studentsNotFromGrade, grade);
    for (int j=0 ; j<numOfStudentsFromGrade ; j++) {
        studentsFromGrade[j]->setPower(studentsFromGrade[j]->getPower()+powerIncrease);
    }
    mergeStudentArrayByGrade(studentsArray,studentsFromGrade,
                             numOfStudentsFromGrade,studentsNotFromGrade,
                             (numOfStudents-numOfStudentsFromGrade));
    studentPowerKey* powerArray = new studentPowerKey[numOfStudents];
    for (int j=0 ; j<numOfStudents ; j++) {
        powerArray[j]=studentPowerKey( *(studentsArray[j]) );
    }
    studentsByPower.inorderWrite(studentsArray, powerArray);
    strongestStudent=studentsArray[numOfStudents-1];
    delete[] studentsArray;
    delete[] studentsFromGrade;
    delete[] studentsNotFromGrade;
    delete[] powerArray;
}

Student* School::getStrongestStudent() const {
    return strongestStudent;
}

const AVL<Team*, int> &School::getTeamsById() const {
    return teamsById;
}

