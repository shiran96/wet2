//
// Created by Shiran on 17/11/2022.
//

#ifndef WET1_TEAM_H
#define WET1_TEAM_H

#include "AVLTree.h"
#include <memory>
#include "player.h"
#include "vectorAbility.h"

class Team {
public:
    int m_id;
    int m_points;
    int m_numberOfPlayers;
    int m_hasGoalKeeper;
    int m_gamePlayed;
    permutation_t m_spirit;
    int m_ability;
    int m_score;
    std::shared_ptr<Team> m_parentTeam;
    std::shared_ptr<Player> m_firstPlayer;
    bool m_isBought;
    int m_numOfTeamInCom;
    vectorAbility m_VA;

    Team(int id, int numOfTeam);//

    ~Team();//

    Team(const Team& team)=default;

    int getTeamId();

    int getTeamPoints();//

    permutation_t getTeamSpirit();//

    void setTeamPoints(int points);

    int getTeamNumberOfPlayers();

    void getBestPlayersArr(int* const output);

    void toInt(vectorScore* input, int* output, int size);

    int getScore()const;

    AVLTree<Player,int>* getPlayerTreeID();
    //void setGoalKeeper()

    int getBestPlayer() const;

    int getNumberOfGames() const;

    void setNumberOfGames(int num);
    //function to use in world cup
    //log(n)
    void add_player(std::shared_ptr<Player> newPlayer);

    void remove_player(int playerId);

    void updatePlayer(int playerID, int goals, int cards, int games);


    bool isPlayable();
    //team is not nullptr
    void uniteTeam(std::shared_ptr<Team> team1, std::shared_ptr<Team> team2);
};

void playMatch(Team &firstTeam, Team &secondTeam)
#endif //WET1_TEAM_H
