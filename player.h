//
// Created by 97252 on 11/18/2022.
//

#ifndef WORLDCUP_PLAYER_H
#define WORLDCUP_PLAYER_H
#include <memory>
#include "wet2util.h"

class Team;

class Player {
private:
    int m_id;
    permutation_t m_partialSpirit;
    int m_ability;
    int m_cards;
    bool m_isGoalKeeper;
    int m_numberOfGames;
    int m_gamesDidntPlayed;
    std::shared_ptr<Player> m_father;
    std::shared_ptr<Team> m_team;

public:
    Player(int id, int cards, int games, int gamesDidntPlayed, bool goalKeeper, int ability,
           std::shared_ptr<Team> team, std::shared_ptr<Player> parent, permutation_t spiritUntil);//

    Player(const Player &player)=default;

    ~Player() {
        if(m_ranking!= nullptr && (m_ranking->getLeft()!= nullptr || m_ranking->getRight()!= nullptr)) {
            delete m_ranking;
        }
        m_ranking= nullptr;
    };

    int getPlayerId() const;

    void updateStats(int goals, int cards, int games);

    vectorScore getVScore() const;

    vectorScore getPlayerScoreVector() const;

    int getPlayerNumOfGames() const;//

    void addCards(int cards);

    int getCards();

    permutation_t getPartialSpirit();

    void updateGames(int game);

    //be aware that goal keeping can not be changed
    bool isGoalKeeper() const;

    int getPlayerScore() const;

    std::shared_ptr<Team> getTeam();

    void setAfter(const Player& player);

    void setBefore(const Player& player);

    void setRanking(NodeList* node);

    void removeFromList();

    int closetPlayer() const;

    NodeList* getRanking();
};



#endif //WORLDCUP_PLAYER_H