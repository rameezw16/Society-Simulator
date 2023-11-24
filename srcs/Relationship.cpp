#include "../include/Relationship.hpp"

Relationship::Relationship(int l, int r) : love{l}, respect{r} {}

Relationship::Relationship(Stats* thisStats, Traits* thisTraits, Stats* otherStats)
{
    // love more if similar in age + if other is happy + if other is wealthy + if I am extroverted + if I am agreeable + if other is of opposite gender - if other I am neurotic
    this->love = std::max((20 - abs(thisStats->age - otherStats->age)), 0) + otherStats->happiness/5 + otherStats->wealth/5 + thisTraits->extrovertedness/10 + thisTraits->agreeableness/10 + 10*(thisStats->gender ^ otherStats->gender) + std::max(10 - thisTraits->neuroticism, 0);
    
    // respect if other is older + if other is wealthier + if I am conscientious + if I am agreeable
    this->respect = std::max(otherStats->age - thisStats->age, 0)/3 + std::max(10 + otherStats->wealth - thisStats->wealth, 0)/5  + thisTraits->conscientiousness/4 + thisTraits->agreeableness/5;
    
    // this->professionalism = otherStats->wealth;
}

Relationship Relationship::operator +(Relationship& other)
{
    Relationship RelationshipSum = {0, 0};
    RelationshipSum.love = this->love + other.love;
    RelationshipSum.respect = this->respect + other.respect;
    // RelationshipSum.professionalism = this->professionalism + other.professionalism;
    return RelationshipSum;
}
