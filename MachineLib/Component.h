/**
 * @file Component.h
 * @author Shawn_Porto
 *
 * Component of Machine
 */
 
#ifndef COMPONENT_H
#define COMPONENT_H


/**
 * Component of Machine
 */
class Component
{
private:
    ///Position of the component
    wxPoint mPosition;
public:
    Component(){}

    virtual ~Component() = default;
    /** Copy constructor disabled */
    Component(const Component &) = delete;
    /** Assignment operator disabled */
    void operator=(const Component &) = delete;

    /**
     * Draw this component
     * @param graphics graphics component
     * @param x the x position of the object
     * @param y the y position of the object
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) = 0;

    /**
     * Draws the components' last part
     * @param graphics the graphics component
     * @param x the x position of the object
     * @param y the y position of the object
     */
    virtual void DrawLast(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) {};

    /**
     * Update the component
     * @param time time the machine is currently on
     */
    virtual void Update(double time){}

    /**
     * Advances the component by delta
     * @param delta the amount of time to advance the component by
     */
    virtual void Advance(double delta){}

    /**
     * Resets the components to when time = 0
     */
    virtual void Reset(){}

    /**
     * Get the current component position
     * @return position the component is at
     */
    virtual wxPoint GetPosition() {return mPosition;}

    /**
    * Set the current component position
    * @param position position the component is at
    */
    virtual void SetPosition(wxPoint position) {mPosition = position;}
};



#endif //COMPONENT_H
