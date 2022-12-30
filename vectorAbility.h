//
// Created by 97252 on 11/20/2022.
//

#ifndef WET1_VECTORSCORE_H
#define WET1_VECTORSCORE_H
#include <cmath>


class vectorAbility {
    int m_ability;
    int m_key;

public:
    vectorAbility() {
        m_ability=-1;
    m_key=-1;
    };

    vectorAbility(int ability, int key){
        m_ability=ability;
        m_key=key;
    }

    vectorAbility(const vectorAbility& vector)=default;

    vectorAbility& operator=(const vectorAbility& vector)=default;

    ~vectorAbility()=default;


    void updateAbility(const int change);

    int getAbility() const;

    int getID() const;

    bool operator<(const vectorAbility& vAbility) const;

    bool operator==(const vectorAbility& vAbility)const;

    bool operator>(const vectorAbility& vAbility) const;

};


#endif //WET1_VECTORSCORE_H
