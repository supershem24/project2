/**
* @file SarahFactory.h
 * @author Shawn_Porto
 *
 * Factory class that builds the Sarah character
 */

#ifndef SARAHFACTORY_H
#define SARAHFACTORY_H

class Actor;

/**
 * Factory class that builds the Sarah character
 */
class SarahFactory
{
private:

public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};



#endif //SARAHFACTORY_H
