#include "../include/Relationship.hpp"

Relationship::Relationship(int l, int r) : love{l}, respect{r} {}

Relationship::Relationship(Stats* thisStats, Traits* thisTraits, Stats* otherStats)
{
    this->love = std::max((20 - abs(thisStats->age - otherStats->age)), 0) + otherStats->happiness/5 + otherStats->wealth/5 + thisTraits->extrovertedness/10 + thisTraits->agreeableness/10 + std::max(20 - thisTraits->neuroticism, 0);
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
