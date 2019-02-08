
#include "library2.h"
#include "test_utils.h"
#include "school.h"

static bool InitAddStudentGetTeamLeaderQuitTest(){

	School* technion = (School*)Init(10);
	ASSERT_TEST(technion != NULL);
	int leader;

	//checks getTeamLeader Invalid_Input
	ASSERT_TEST(GetStudentTeamLeader(NULL,1,&leader) == INVALID_INPUT);
	ASSERT_TEST(GetStudentTeamLeader(technion,-1,&leader) == INVALID_INPUT);
	ASSERT_TEST(GetStudentTeamLeader(technion,0,&leader) == INVALID_INPUT);
	ASSERT_TEST(GetStudentTeamLeader(technion,1,NULL) == INVALID_INPUT);

	//checks  getTeamLeader failure
	ASSERT_TEST(GetStudentTeamLeader(technion,1,&leader) == FAILURE);

	//checks addStudent Invalid_Input
	ASSERT_TEST(AddStudent(NULL,1,1,1) == INVALID_INPUT);
	ASSERT_TEST(AddStudent(technion,-1,1,1) == INVALID_INPUT);
	ASSERT_TEST(AddStudent(technion,0,1,1) == INVALID_INPUT);
	ASSERT_TEST(AddStudent(technion,1,-1,1) == INVALID_INPUT);
	ASSERT_TEST(AddStudent(technion,1,0,1) == INVALID_INPUT);
	ASSERT_TEST(AddStudent(technion,1,11,1) == INVALID_INPUT);
	ASSERT_TEST(AddStudent(technion,1,1,-1) == INVALID_INPUT);
	ASSERT_TEST(AddStudent(technion,1,1,0) == INVALID_INPUT);

	//inserting 2 students to team 1 and 10 with id = 1,2 and power = 1.
	ASSERT_TEST(AddStudent(technion,1,1,1) == SUCCESS);
	ASSERT_TEST(AddStudent(technion,2,10,1) == SUCCESS);

	//checking FAILURE
	ASSERT_TEST(AddStudent(technion,1,3,1) == FAILURE);

	//getLeader correctness
	ASSERT_TEST(GetStudentTeamLeader(technion,1,&leader) == SUCCESS);
	ASSERT_TEST(leader == 1);

	//adding team1 another stud with power=1 and id=3 -> id=1 is leader in team1
	ASSERT_TEST(AddStudent(technion,3,1,1) == SUCCESS);
	ASSERT_TEST(GetStudentTeamLeader(technion,3,&leader) == SUCCESS);
	ASSERT_TEST(leader == 1);

	//adding team10 another stud with power=2 and id=4 -> id=14 is leader in team10
	ASSERT_TEST(AddStudent(technion,4,10,2) == SUCCESS);
	ASSERT_TEST(GetStudentTeamLeader(technion,2,&leader) == SUCCESS);
	ASSERT_TEST(leader == 4);

//	Quit(NULL);//this may cause seg-fault if no checking 4 null-arg
	Quit((void**)&technion);
	ASSERT_TEST(technion == NULL);

	return true;
}

static bool RemoveStudentTeamFightNumOfWinsTest(){

	School* technion = (School*)Init(10);
	ASSERT_TEST(technion != NULL);
	int leader, num_wins;

	//checks NumOfWins Invalid_Input
	ASSERT_TEST(GetNumOfWins(NULL,1,&num_wins) == INVALID_INPUT);
	ASSERT_TEST(GetNumOfWins(technion,-1,&num_wins) == INVALID_INPUT);
	ASSERT_TEST(GetNumOfWins(technion,0,&num_wins) == INVALID_INPUT);
	ASSERT_TEST(GetNumOfWins(technion,11,&num_wins) == INVALID_INPUT);
	ASSERT_TEST(GetNumOfWins(technion,1,NULL) == INVALID_INPUT);

	//checks team_wins initiated to 0
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 0);

	//checks TeamFight Invalid_Input
	ASSERT_TEST(TeamFight(NULL,1,2,1) == INVALID_INPUT);
	ASSERT_TEST(TeamFight(technion,-1,2,1) == INVALID_INPUT);
	ASSERT_TEST(TeamFight(technion,0,2,1) == INVALID_INPUT);
	ASSERT_TEST(TeamFight(technion,11,2,1) == INVALID_INPUT);
	ASSERT_TEST(TeamFight(technion,1,-1,1) == INVALID_INPUT);
	ASSERT_TEST(TeamFight(technion,1,0,1) == INVALID_INPUT);
	ASSERT_TEST(TeamFight(technion,1,11,1) == INVALID_INPUT);
	ASSERT_TEST(TeamFight(technion,1,2,-1) == INVALID_INPUT);
	ASSERT_TEST(TeamFight(technion,1,2,0) == INVALID_INPUT);

	//checks TeamFight SUCCSESS with initial draw.
	ASSERT_TEST(TeamFight(technion,1,2,1) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 0);

	//cheks TeamFight with-in the same team
	ASSERT_TEST(TeamFight(technion,1,1,1) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 0);

	//checks removeStudent Invalid_Input
	ASSERT_TEST(RemoveStudent(NULL,1) == INVALID_INPUT);
	ASSERT_TEST(RemoveStudent(technion,-1) == INVALID_INPUT);
	ASSERT_TEST(RemoveStudent(technion,0) == INVALID_INPUT);

	///checks removeStudent Failure
	ASSERT_TEST(RemoveStudent(technion,1) == FAILURE);


	//inserting 5 stud to team1. id1 with power 9. id's 2-5 with power 1.
			ASSERT_TEST(AddStudent(technion,1,1,9) == SUCCESS);
			ASSERT_TEST(AddStudent(technion,2,1,1) == SUCCESS);
			ASSERT_TEST(AddStudent(technion,3,1,1) == SUCCESS);
			ASSERT_TEST(AddStudent(technion,4,1,1) == SUCCESS);
			ASSERT_TEST(AddStudent(technion,5,1,1) == SUCCESS);
	ASSERT_TEST(GetStudentTeamLeader(technion,5,&leader) == SUCCESS);
	ASSERT_TEST(leader == 1);

	//inserting 5 stud to team2. id's 6-10: all with power 43.
	for(int i=6; i<=10; ++i){
		ASSERT_TEST(AddStudent(technion,i,2,3) == SUCCESS);
	}

	ASSERT_TEST(GetStudentTeamLeader(technion,10,&leader) == SUCCESS);
	ASSERT_TEST(leader == 6);

	//with num_of_fighters < 4 :team 1 is stronger
	//with num_of_fighters == 4 :draw
	//with num_of_fighters > 4 :team 2 is stronger

	//1 fighter
	ASSERT_TEST(TeamFight(technion,1,2,1) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 1);
	ASSERT_TEST(GetNumOfWins(technion,2,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 0);

	//2 fighters
	ASSERT_TEST(TeamFight(technion,1,2,2) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 2);
	ASSERT_TEST(GetNumOfWins(technion,2,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 0);

	//3 fighters
	ASSERT_TEST(TeamFight(technion,1,2,3) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 3);
	ASSERT_TEST(GetNumOfWins(technion,2,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 0);

	//4 fighters
	ASSERT_TEST(TeamFight(technion,1,2,4) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 3);
	ASSERT_TEST(GetNumOfWins(technion,2,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 0);

	//5 fighters
	ASSERT_TEST(TeamFight(technion,1,2,5) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 3);
	ASSERT_TEST(GetNumOfWins(technion,2,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 1);

	//remove id6.
	ASSERT_TEST(RemoveStudent(technion,6) == SUCCESS);
	ASSERT_TEST(GetStudentTeamLeader(technion,6,&leader) == FAILURE);
	ASSERT_TEST(GetStudentTeamLeader(technion,10,&leader) == SUCCESS);
	ASSERT_TEST(leader == 7);

	//5 fighters while team2 has 4 stud.
	ASSERT_TEST(TeamFight(technion,1,2,5) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 4);
	ASSERT_TEST(GetNumOfWins(technion,2,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 1);

	//removes another stud from team2. total power=9.
	ASSERT_TEST(RemoveStudent(technion,9) == SUCCESS);
	// removing students from team1. the order of removal is id5,4,...
	//last student gets a draw in the fight
	ASSERT_TEST(TeamFight(technion,1,2,5) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 5);

	ASSERT_TEST(RemoveStudent(technion,5) == SUCCESS);
	ASSERT_TEST(TeamFight(technion,1,2,5) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 6);

	ASSERT_TEST(RemoveStudent(technion,4) == SUCCESS);
	ASSERT_TEST(TeamFight(technion,1,2,5) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 7);

	ASSERT_TEST(RemoveStudent(technion,3) == SUCCESS);
	ASSERT_TEST(TeamFight(technion,1,2,5) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 8);

	ASSERT_TEST(RemoveStudent(technion,2) == SUCCESS);//draw
	ASSERT_TEST(TeamFight(technion,1,2,5) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 8);

	ASSERT_TEST(RemoveStudent(technion,1) == SUCCESS);
	ASSERT_TEST(TeamFight(technion,1,2,5) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 8);
	ASSERT_TEST(GetNumOfWins(technion,2,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 2);

	Quit((void**)&technion);
	ASSERT_TEST(technion == NULL);

	return true;
}

static bool JoinTeamsFightTest(){

	School* technion = (School*)Init(10);
	ASSERT_TEST(technion != NULL);
	int leader, num_wins;

	//checks joinTeames Invalid_Input
	ASSERT_TEST(JoinTeams(NULL,1,2) == INVALID_INPUT);
	ASSERT_TEST(JoinTeams(technion,-1,2) == INVALID_INPUT);
	ASSERT_TEST(JoinTeams(technion,0,2) == INVALID_INPUT);
	ASSERT_TEST(JoinTeams(technion,1,-1) == INVALID_INPUT);
	ASSERT_TEST(JoinTeams(technion,1,0) == INVALID_INPUT);


	//after insertion team1\2_total_power = 20.
	for(int i = 1; i<=20; ++i){
		num_wins = 0;
		if(i%2 == 1){
			ASSERT_TEST(AddStudent(technion,i,1,i%4) == SUCCESS);
		} else {
			ASSERT_TEST(AddStudent(technion,i,2,i%4 + 1) == SUCCESS);
		}

		if(i%4 == 0){
			ASSERT_TEST(TeamFight(technion,1,2,10) == SUCCESS);
			ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
			ASSERT_TEST(num_wins == i/2);
		}
		if(i%4 == 1){
			ASSERT_TEST(TeamFight(technion,1,2,10) == SUCCESS);
			ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
			ASSERT_TEST(num_wins == i/2+1);
		}
		if(i%4 == 2){
			ASSERT_TEST(TeamFight(technion,1,2,10) == SUCCESS);
			ASSERT_TEST(GetNumOfWins(technion,2,&num_wins) == SUCCESS);
			ASSERT_TEST(num_wins == i/4+1);
		}
		if(i%4 == 3){
			ASSERT_TEST(TeamFight(technion,1,2,10) == SUCCESS);
			ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
			ASSERT_TEST(num_wins == i/2 + 1);
		}
	}


	ASSERT_TEST(GetStudentTeamLeader(technion,2,&leader) == SUCCESS);
	ASSERT_TEST(leader == 2);


	//join teams 3-10 with no students - "BIG_TEAM"
	for(int i=3;i<=10;++i){
		if(i==10) break;
		ASSERT_TEST(JoinTeams(technion,i,i+1) == SUCCESS);
	}

	//inserting to mixed 3-10 teams 20 stud with power 2
	for(int i=21;i<=40;++i){
		ASSERT_TEST(AddStudent(technion,i,i%7+3,2) == SUCCESS);
	}

	//BIG_TEAM is stronger right now. after joining team1,2 will be a draw.
	ASSERT_TEST(TeamFight(technion,1,3,20) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,4,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 1);

	ASSERT_TEST(TeamFight(technion,2,10,20) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,4,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 2);

	//joining team-to-itself- nothing happens.
	ASSERT_TEST(JoinTeams(technion,1,1) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 10);

	//joining team 1 and 2
	ASSERT_TEST(JoinTeams(technion,1,2) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 15);
	ASSERT_TEST(GetStudentTeamLeader(technion,20,&leader) == SUCCESS);
	ASSERT_TEST(leader == 2);

	//joining team to itself 1,2
	ASSERT_TEST(JoinTeams(technion,1,2) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 15);

	//self fight
	ASSERT_TEST(TeamFight(technion,1,2,20) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 15);

	//BIG_TEAM vs Team1,2 == draw
	ASSERT_TEST(TeamFight(technion,1,3,20) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins== 15);

	//id20 is the weakest in TEAM1,2 with power 1.
	//in 19 fighters team1,2 is stronger
	ASSERT_TEST(TeamFight(technion,1,3,19) == SUCCESS);
	ASSERT_TEST(GetNumOfWins(technion,1,&num_wins) == SUCCESS);
	ASSERT_TEST(num_wins == 16);

	Quit((void**)&technion);
	ASSERT_TEST(technion == NULL);


	return true;
}

int main(){

	RUN_TEST(InitAddStudentGetTeamLeaderQuitTest);
	RUN_TEST(RemoveStudentTeamFightNumOfWinsTest);
	RUN_TEST(JoinTeamsFightTest);

	return 0;
}
