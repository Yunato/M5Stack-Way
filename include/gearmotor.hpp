#ifndef GEARMOTOR_H_
#define GEARMOTOR_H_

#include <M5Stack.h>

class GearMotor {
private:
    int rin_port;
    int fin_port;

public:
    explicit GearMotor(int rin_port, int fin_port);
    virtual ~GearMotor(void);
    void rotate();
    void stop();
};

#endif
