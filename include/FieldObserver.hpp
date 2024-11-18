#ifndef FIELDOBSERVER_HPP  // FIELDOBSERVER_HPP
#define FIELDOBSERVER_HPP

class FieldObserver {
public:
    virtual void onShipDestroyed() = 0;

    virtual ~FieldObserver() {}
};

#endif  // FIELDOBSERVER_HPP
