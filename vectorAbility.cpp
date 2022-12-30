//
// Created by 97252 on 11/20/2022.
//

#include "vectorAbility.h"


//(1)
void vectorAbility::updateAbility(const int change) {
    m_ability+=change;
}
//(1)
bool vectorAbility::operator<(const vectorAbility& vAbility) const{
    bool lowerAbility = (m_ability < vAbility.m_ability);
    bool key= (m_ability == vAbility.m_ability) && (m_key < vAbility.m_key);
    return lowerAbility||key;
}
//(1)
bool vectorAbility::operator==(const vectorAbility& vAbility)const{
    bool equalAll = (m_ability == vAbility.m_ability) && (m_key == vAbility.m_key);
    return equalAll;
}
//(1)
bool vectorAbility::operator>(const vectorAbility& vAbility) const{
    bool equalOrLower = (*this < vAbility) || (*this == vAbility);
    return !equalOrLower;
}
//(1)
int vectorAbility::getAbility() const {
    return m_ability;
}

int vectorAbility::getID() const {
    return m_key;
}
