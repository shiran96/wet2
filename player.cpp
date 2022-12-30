//
// Created by 97252 on 11/18/2022.
//

#include "player.h"
#include "team.h"

Player::Player(int id, int cards, int games, int gamesDidntPlayed, bool goalKeeper,int ability,
               std::shared_ptr<Team> team, std::shared_ptr<Player> parent,permutation_t spiritUntil) {
    m_id=id;
    m_cards=cards;
    m_numberOfGames=games;
    m_gamesDidntPlayed=gamesDidntPlayed;
    m_isGoalKeeper=goalKeeper;
    m_ability=ability;
    m_team=team;
    m_father=parent;
    m_partialSpirit=spiritUntil;
}
//(1)
int Player::getPlayerId() const{
    return m_id;
}

void Player::updateStats(int goals, int cards, int games) {
    m_vScore.updateGoals(goals);
    m_vScore.updateCards(cards);
    m_numberOfGames+=games;
}
//(1)
vectorScore Player::getPlayerScoreVector() const{
    return m_vScore;
}
//(1)
int Player::getPlayerNumOfGames() const{
    if(m_father== nullptr){
        return m_numberOfGames-m_gamesDidntPlayed+m_team->getNumberOfGames();
    }
    else {
        std::shared_ptr<Player> temp = m_father;
        while (temp->m_father != nullptr) {
            temp = temp->m_father;
        }

        //Making the players closer to each other.
        std::shared_ptr<Player> toCloser= this;
        std::shared_ptr<Player> temp2=this;
        while(toCloser->m_father!=temp){
            toCloser=toCloser->m_father;
            temp2->m_father=temp;
            temp2=toCloser;
        }


        return m_numberOfGames-m_gamesDidntPlayed+temp->m_team->getNumberOfGames();
    }
}

void Player::addCards(int cards) {
    m_cards=m_cards+cards;
    std::shared_ptr<Player> temp = m_father;
    while (temp->m_father != nullptr) {
        temp = temp->m_father;
    }

    //Making the players closer to each other.
    std::shared_ptr<Player> toCloser= this;
    std::shared_ptr<Player> temp2=this;
    while(toCloser->m_father!=temp){
        toCloser=toCloser->m_father;
        temp2->m_father=temp;
        temp2=toCloser;
    }
}

int Player::getCards() {
    return m_cards;
}

permutation_t Player::getPartialSpirit() {
    if (m_team->m_isBought) {
        return m_partialSpirit * m_team->m_spirit;
    } else {
        return m_partialSpirit;
    }
}

//(1)
bool Player::isGoalKeeper() const{
    return m_isGoalKeeper;
}
//(1)
void Player::updateGames(const int game) {
    m_numberOfGames+=game;
}
//(1)
int Player::getPlayerScore() const{
    return m_vScore.getFullScore();
}

std::shared_ptr<Team> Player::getTeam(){
    return m_team;
}

//(1)
vectorScore Player::getVScore() const {
    return m_vScore;
}
//(1)
void Player::setAfter(const Player &player) {
    if(player.m_ranking->getRight() != nullptr){
        NodeList* node = player.m_ranking->getRight();
        player.m_ranking->setRight(m_ranking);
        m_ranking->setLeft(player.m_ranking);
        m_ranking->setRight( node);
        node->setLeft(m_ranking);
        return;
    }
    player.m_ranking->setRight(m_ranking);
    m_ranking->setLeft(player.m_ranking);
}
//(1)
void Player::setBefore(const Player &player) {
    if(player.m_ranking->getLeft() != nullptr){
        NodeList* node = player.m_ranking->getLeft();
        player.m_ranking->setLeft(m_ranking);
        m_ranking->setRight(player.m_ranking);
        m_ranking->setLeft( node);
        node->setRight(m_ranking);
        return;
    }
    player.m_ranking->setLeft(m_ranking);
    m_ranking->setRight(player.m_ranking);
}

void Player::setRanking(NodeList *node) {
    m_ranking=node;
}

void Player::removeFromList() {
    if(m_ranking) {
        if(m_ranking->getRight()!= nullptr){
            m_ranking->getRight()->setLeft(m_ranking->getLeft());
        }
        if(m_ranking->getLeft()!= nullptr){
            m_ranking->getLeft()->setRight(m_ranking->getRight());
        }
    }
}
//(1)
int Player::closetPlayer() const {
    if(m_ranking->getLeft()== nullptr && m_ranking->getRight()== nullptr){
        return -1;
    }
    if(m_ranking->getLeft()== nullptr){
        return m_ranking->getRight()->getVScore().getID();
    }
    if (m_ranking->getRight()== nullptr){
        return m_ranking->getLeft()->getVScore().getID();
    }
    return m_vScore.closest(m_ranking->getLeft()->getVScore(),m_ranking->getRight()->getVScore());
}

NodeList* Player::getRanking() {
    return m_ranking;
}




