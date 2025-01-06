/**
 * @file MachineFactories.h
 * @author Shawn_Porto
 *
 * Machine Factories all in one class file
 */
 
#ifndef MACHINEFACTORIES_H
#define MACHINEFACTORIES_H

class Machine;

/**
 * Creates Machine 1
 */
class Machine1Factory
{
private:
    /// directory to find images
    std::wstring mResourcesDir;
public:
    /** Default constructor disabled */
    Machine1Factory() = delete;
    /** Copy constructor disabled */
    Machine1Factory(const Machine1Factory &) = delete;
    /** Assignment operator disabled */
    void operator=(const Machine1Factory &) = delete;

    Machine1Factory(std::wstring resourcesDir);
    std::shared_ptr<Machine> CreateMachine(wxPoint location);
};

/**
 * Creates Machine 2
 */
class Machine2Factory
{
private:
    /// directory to find images
    std::wstring mResourcesDir;
public:
    /** Default constructor disabled */
    Machine2Factory() = delete;
    /** Copy constructor disabled */
    Machine2Factory(const Machine2Factory &) = delete;
    /** Assignment operator disabled */
    void operator=(const Machine2Factory &) = delete;

    Machine2Factory(std::wstring resourcesDir);
    std::shared_ptr<Machine> CreateMachine(wxPoint location);
};



#endif //MACHINEFACTORIES_H
