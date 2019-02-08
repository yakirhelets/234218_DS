//
// Created by Yakir on 07/06/2017.
//

#include "school.h"
#include "stdio.h"
class DeleteStudent {
public:
    void operator() (Student* s) {
        delete s;
    };
};

class FillStudentsInArray {
    Student** array;
public:
    FillStudentsInArray(Student** array) : array(array){};
    void operator()(Student* s) {
        (*array) = s;
        (array)++;
    }
};

static void mergeStudentArrayByPower(Student** M, Student** A, int aSize, Student** B, int bSize) {
    int i=0;
    int j=0;
    int k=0;
    while (i < aSize && j < bSize) {
        if ( studentPowerKey(*(A[i])) < studentPowerKey(*(B[j])) ) {
            M[k] = A[i];
            i++;
        } else {
            M[k] = B[j];
            j++;
        }
        k++;
    }
    if (i < aSize) {
        for (; i < aSize; i++) {
            M[k] = A[i];
            k++;
        }
    } else {
        for (; j < bSize; j++) {
            M[k] = B[j];
            k++;
        }
    }
}

static void mergePowerKeyArray(studentPowerKey* M, studentPowerKey* A, int aSize, studentPowerKey* B, int bSize) {
    int i=0;
    int j=0;
    int k=0;
    while (i < aSize && j < bSize) {
        if ( (A[i]) < (B[j]) ) {
            M[k] = A[i];
            i++;
        } else {
            M[k] = B[j];
            j++;
        }
        k++;
    }
    if (i < aSize) {
        for (; i < aSize; i++) {
            M[k] = A[i];
            k++;
        }
    } else {
        for (; j < bSize; j++) {
            M[k] = B[j];
            k++;
        }
    }
}


School::School(int numOfTeams) {
    Team** teamsArr = new Team*[numOfTeams];
    for (int i=0 ; i<numOfTeams ; ++i) {
        teamsArr[i] = new Team(i);
    }
    teams = new UnionFind<Team*>(numOfTeams, teamsArr);
    this->numOfTeams=numOfTeams;
    studentsArr = new HashTable<Student*>();
}

School::~School() {
    studentsArr->forEach(DeleteStudent());
    delete studentsArr;
    delete teams;
}

void School::addStudent(int studentId, int teamId, int power) {
    if (studentsArr->doesExist(studentId)) {
        throw Failure();
        return;
    }
    Student* newStudent = new Student(studentId,teamId,power);
    studentsArr->insert(newStudent, studentId);
    Team* team = teams->dataFind(teamId);
    team->addStudentToTeam(newStudent, studentPowerKey(studentId,power));
    //update the most dangerous Student
    if (team->getMostPowerfulStudentInTeam()!=NULL) {
        if (studentPowerKey(*(team->getMostPowerfulStudentInTeam())) < studentPowerKey(*newStudent)) {
            team->setMostPowerFulStudentInTeam(newStudent);
        }
    } else {
        team->setMostPowerFulStudentInTeam(newStudent);
    }
}

void School::removeStudent(int studentId) {
    Student* toRemove;
    try{
        toRemove = studentsArr->get((studentId));
    } catch (HashTable<Student*>::KeyDoesNotExist& error){
        throw Failure();
    }
    Team* toRemoveTeam = teams->dataFind( toRemove->getTeam() );
    //remove from team
    toRemoveTeam->removeStudentFromTeam( studentPowerKey(*toRemove) );
    if ( toRemoveTeam->getStudentbyPowerTree()->getRoot() ) {
        toRemoveTeam->setMostPowerFulStudentInTeam
                (toRemoveTeam->getStudentbyPowerTree()->getMax());
    } else {
        toRemoveTeam->setMostPowerFulStudentInTeam(NULL);
    }
    //remove from hash
    studentsArr->remove(studentId);
    delete toRemove;

}

void School::joinTeams(int team1, int team2) {
	Team* t1 = teams->dataFind(team1);
	Team* t2 = teams->dataFind(team2);

    if (teams->find(team1)==teams->find(team2)) {
        return;
    }

	int size1 = t1->getNumOfStudentsInTeam();
	int size2 = t2->getNumOfStudentsInTeam();

	if (size1 == 0 && size2 == 0){
		teams->unite(team1, team2);
		return;
	}

	Student** studentsArray1 = new Student*[size1];
	t1->getStudentbyPowerTree()->inorder(FillStudentsInArray(studentsArray1));
	Student** studentsArray2 = new Student*[size2];
	t2->getStudentbyPowerTree()->inorder(FillStudentsInArray(studentsArray2));

	studentPowerKey* powerKeyArray1 = new studentPowerKey[size1];
	studentPowerKey* powerKeyArray2 = new studentPowerKey[size2];

	for (int i = 0; i < size1; i++){
		powerKeyArray1[i] = studentPowerKey(*studentsArray1[i]);
	}
	for (int i = 0; i < size2; i++){
		powerKeyArray2[i] = studentPowerKey(*studentsArray2[i]);
	}

	Student** mergedStudentArray = new Student*[size1 + size2];
	studentPowerKey* mergedPowerKeyArray = new studentPowerKey[size1 + size2];
    int* mergedPowers = new int[size1 + size2];

	mergeStudentArrayByPower(mergedStudentArray, studentsArray1, size1, studentsArray2, size2);
	mergePowerKeyArray(mergedPowerKeyArray, powerKeyArray1, size1, powerKeyArray2, size2);

    for (int i =0 ; i < size1+size2 ; i++) {
        mergedPowers[i]=mergedStudentArray[i]->getPower();
    }

	int numOfWins1 = t1->getWinCount();
	int numOfWins2 = t2->getWinCount();

    Team* united = teams->unite(team1, team2);
    RankTree<Student*, studentPowerKey>* mergedTree = t1->getStudentbyPowerTree()->createCompleteEmptyTree(size1 + size2);
    mergedTree->inorderWrite(mergedStudentArray, mergedPowerKeyArray, mergedPowers);
    mergedTree->fixPowers(mergedTree->getRoot());

    if (united->getTeamId()==teams->find(t1->getTeamId())) {
//        t1->getStudentbyPowerTree()->RankDestroy(
//                t1->getStudentbyPowerTree()->getRoot());
        delete t1->getStudentbyPowerTree();
        t1->setStudentByPowerTree(mergedTree);
    } else {
//        t2->getStudentbyPowerTree()->RankDestroy(
//                t2->getStudentbyPowerTree()->getRoot());
        delete t2->getStudentbyPowerTree();
        t2->setStudentByPowerTree(mergedTree);
    }

    t1->setNumOfStudentsInTeam(size1+size2);
    t2->setNumOfStudentsInTeam(size1+size2);

	t1->setWinCount(numOfWins1 + numOfWins2);
	t2->setWinCount(numOfWins1 + numOfWins2);

    t1->setMostPowerFulStudentInTeam(mergedStudentArray[size1+size2-1]);
    t2->setMostPowerFulStudentInTeam(mergedStudentArray[size1+size2-1]);

//    Student* strongest1 = t1->getMostPowerfulStudentInTeam();
//    Student* strongest2 = t2->getMostPowerfulStudentInTeam();
//    if (studentPowerKey(*(strongest1)) > studentPowerKey(*(strongest2))) {
//        t1->setMostPowerFulStudentInTeam(strongest1);
//        t2->setMostPowerFulStudentInTeam(strongest1);
//    } else {
//        t1->setMostPowerFulStudentInTeam(strongest2);
//        t2->setMostPowerFulStudentInTeam(strongest2);
//    }
	delete[] studentsArray1;
	delete[] studentsArray2;
	delete[] powerKeyArray1;
	delete[] powerKeyArray2;
	delete[] mergedStudentArray;
	delete[] mergedPowerKeyArray;
    delete[] mergedPowers;
}

void School::teamFight(int team1, int team2, int numOfFighters) {
	Student* student1;
	Student* student2;

    if (teams->find(team1)==teams->find(team2)) {
        return;
    }

	Team* t1 = teams->dataFind(team1);
	Team* t2 = teams->dataFind(team2);

	int size1 = t1->getNumOfStudentsInTeam();
    int size2 = t2->getNumOfStudentsInTeam();
    if (size1==0 && size2==0) {
        return;
    }
    if (size1==0 && size2!=0) {
        t2->setWinCount(t2->getWinCount()+ 1);
        return;
    }
    if (size2==0 && size1!=0) {
        t1->setWinCount(t1->getWinCount()+ 1);
        return;
    }

	int sumOfPower1 = 0;
	int sumOfPower2 = 0;

    if (numOfFighters == 1) {
        student1 =  t1->getMostPowerfulStudentInTeam();
    } else {
        if (size1 <= numOfFighters) {
            student1 = t1->getStudentbyPowerTree()->select(1);
        } else {
            student1 = t1->getStudentbyPowerTree()->select(
                    size1 - numOfFighters + 1);
        }
    }
    if (numOfFighters == 1) {
        student2 =  t2->getMostPowerfulStudentInTeam();
    } else {
        if (size2 <= numOfFighters) {
            student2 = t2->getStudentbyPowerTree()->select(1);
        } else {
            student2 = t2->getStudentbyPowerTree()->select(
                    size2 - numOfFighters + 1);
        }
    }

	if ( size1 == 1 ){
		sumOfPower1 = student1->getPower();
	} else {
		sumOfPower1 = t1->getStudentbyPowerTree()->sumToRoot(t1->getStudentbyPowerTree()->nodeFind(studentPowerKey(*student1)));
	}
	if ( size2 == 1 ){
		sumOfPower2 = student2->getPower();
	} else {
		sumOfPower2 = t2->getStudentbyPowerTree()->sumToRoot(t2->getStudentbyPowerTree()->nodeFind(studentPowerKey(*student2)));
	}
//	printf("\n%d",sumOfPower1);
//	printf("\n%d\n",sumOfPower2);
    if (sumOfPower1 == sumOfPower2) {
        return;
    } else {
        sumOfPower1 < sumOfPower2 ? t2->setWinCount(t2->getWinCount() + 1)
                                  : t1->setWinCount(t1->getWinCount() + 1);
    }
}



void School::getNumOfWins(int teamId, int* wins) {
    *wins=teams->dataFind(teamId)->getWinCount();
}

void School::getStudentTeamLeader(int studentId, int* leader) {
    int teamNum;
    try {
        teamNum = studentsArr->get(studentId)->getTeam();
    } catch (HashTable<Student*>::KeyDoesNotExist& e){
        throw Failure();
    }
    *leader = teams->dataFind(teamNum)->getMostPowerfulStudentInTeam()->getID();
}

int School::getNumOfTeams(){
	return numOfTeams;
}


