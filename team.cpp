#include "team.h"

Team::Team(int id, int numOfTeam) {
    m_id=id;
    m_numberOfPlayers=0;
    m_score=0;
    m_hasGoalKeeper=0;
    m_gamePlayed=0;
    m_points=0;
    m_ability=0;
    m_firstPlayer= nullptr;
    m_parentTeam= nullptr;
    m_spirit();
    m_numOfTeamInCom=numOfTeam;
    m_VA(0,id);
}

Team::~Team() {
    m_parentTeam= nullptr;
    m_firstPlayer= nullptr;
}

int Team::getTeamId(){
    return m_id;
}

int Team::getTeamPoints(){
    return m_points;
}

permutation_t Team::getTeamSpirit() {
    if(m_parentTeam== nullptr){
        return m_spirit;
    }
    else{
        permutation_t toRes=m_spirit*m_parentTeam->m_spirit;
        std::shared_ptr<Team> temp = m_parentTeam;
        while (temp->m_parentTeam != nullptr) {
            temp = temp->m_father;
            toRes=toRes*temp->m_spirit;
        }

        //Making the players closer to each other.
        std::shared_ptr<Team> toCloser= this;
        std::shared_ptr<Team> temp2=this;
        while(toCloser->m_father!=temp){
            toCloser=toCloser->m_father;
            temp2->m_father=temp;
            temp2=toCloser;
        }
        return toRes;
    }
}

void Team::setTeamPoints(int points){
    m_points += points;
}

int Team::getTeamNumberOfPlayers(){
    return m_numberOfPlayers;
}

void Team::getBestPlayersArr(int* const output){
    vectorScore* input;
    input = new vectorScore[m_numberOfPlayers];
    m_bestPlayerTree.putDataOnArray(input);
    toInt(input, output, m_numberOfPlayers);
    delete[] input;
}

void Team::toInt(vectorScore* input, int* output, int size){
    for (int i = 0; i < size; ++i) {
        output[i]=input[i].getID();
    }
}

int Team::getScore()const{
    return m_score;
}

AVLTree<Player,int>* Team::getPlayerTreeID(){
    return &m_playersTree;
}
//void setGoalKeeper()

int Team::getBestPlayer() const{
    return m_bestPlayerVS->getID();
}

int Team::getNumberOfGames() const{
    if(m_parentTeam!= nullptr){
        return m_gamePlayed+m_parentTeam->getNumberOfGames();
    }
    return m_gamePlayed;
}

void Team::setNumberOfGames(int num){
    m_gamePlayed += num;
}
//function to use in world cup
//log(n)
void Team::add_player(std::shared_ptr<Player> newPlayer){;
    m_numberOfPlayers++;//1
    if(newPlayer->isGoalKeeper()){//1
        m_hasGoalKeeper++;
    }
    m_playersTree.insert( newPlayer, newPlayer->getPlayerId());//log(n)
    m_bestPlayerTree.insert(newPlayer, newPlayer->getVScore());//log(n)
    m_bestPlayerVS= m_bestPlayerTree.getMax();//log(n)
    m_score+=newPlayer->getPlayerScore();//1
}

void Team::remove_player(int playerId){
    std::shared_ptr<Player> pDelPlayer = m_playersTree.find(playerId);//log(n)
    if(pDelPlayer->isGoalKeeper()){
        --m_hasGoalKeeper;
    }
    --m_numberOfPlayers ;
    m_playersTree.remove(playerId);//log(n)
    m_bestPlayerTree.remove(pDelPlayer->getVScore());//log(n)
    if(m_bestPlayerTree.getMax()== nullptr){
        m_bestPlayerVS= nullptr;
    }
    else {
        m_bestPlayerVS = m_bestPlayerTree.getMax();//log(n)
    }
    m_score-=pDelPlayer->getPlayerScore();

}

void Team::updatePlayer(int playerID, int goals, int cards, int games){
    //We checkd before that he is there.
    std::shared_ptr<Player> updPlayer=m_playersTree.find(playerID);
    m_bestPlayerTree.remove(updPlayer->getVScore());
    m_score-=updPlayer->getPlayerScore();
    updPlayer->updateStats(goals, cards, games);
    m_score+=updPlayer->getPlayerScore();
    m_bestPlayerTree.insert(updPlayer, updPlayer->getVScore());
    m_bestPlayerVS=m_bestPlayerTree.getMax();//log(n)
}

bool Team::isPlayable(){
    return ((m_numberOfPlayers>=11) && (m_hasGoalKeeper >0));
}
//team is not nullptr
void Team::uniteTeam(std::shared_ptr<Team> team1, std::shared_ptr<Team> team2){

    int num1=team1->m_numberOfPlayers;
    std::shared_ptr<Player>* arr1;
    arr1= new std::shared_ptr<Player>[num1];
    team1->m_playersTree.putItemsOnArray(arr1);
    for (int i = 0; i < num1; ++i) {
        arr1[i]->updateGames(team1->m_gamePlayed);
    }

    int num2 =team2->m_numberOfPlayers;
    std::shared_ptr<Player>* arr2;
    arr2 = new std::shared_ptr<Player>[num2];
    team2->getPlayerTreeID()->putItemsOnArray(arr2);
    for (int i = 0; i < num2; ++i) {
        arr2[i]->updateGames(team2->m_gamePlayed);
    }

    m_score= team1->m_score+team2->m_score;
    m_hasGoalKeeper = team1->m_hasGoalKeeper+team2->m_hasGoalKeeper;
    m_numberOfPlayers = num1+ num2;

    m_playersTree.combineTrees(&team1->m_playersTree, &team2->m_playersTree);
    m_bestPlayerTree.combineTrees(&team1->m_bestPlayerTree, &team2->m_bestPlayerTree);
    m_bestPlayerVS = m_bestPlayerTree.getMax();
    delete[] arr2;
    delete[] arr1;
}

void playMatch(std::shared_ptr<Team> firstTeam, std::shared_ptr<Team> secondTeam){
    int score1=firstTeam->m_ability+firstTeam->m_points;
    int score2= secondTeam->m_ability+secondTeam->m_points;
    if(score1>score2){
        firstTeam->m_points=firstTeam->m_points+3;
    }
    else if(score1<score2){
        secondTeam->m_points=secondTeam->m_points+3;
    }
    else{
        int str1=firstTeam->m_spirit->strength();
        int str2 = secondTeam->m_spirit->strength();
        if(str1>str2){
            firstTeam->m_points=firstTeam->m_points+3;
        }
        else if(str1<str2){
            secondTeam->m_points=secondTeam->m_points+3;
        }
        else{
            firstTeam->m_points=firstTeam->m_points+1;
            secondTeam->m_points=secondTeam->m_points+1;
        }
    }
    firstTeam->m_gamePlayed++;
    secondTeam->m_gamePlayed++;
}