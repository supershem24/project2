/**
 * @file IOpenable.h
 * @author Shawn_Porto
 *
 * Allows cam to connect to box and sparty
 */
 
#ifndef IOPENABLE_H
#define IOPENABLE_H

/**
 * Allows cam to connect to box and sparty
 */
class IOpenable {
private:

public:
    /**
     * Open the openable
     */
    virtual void Open() = 0;
};


#endif //IOPENABLE_H
