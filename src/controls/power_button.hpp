#include <stdint.h>

class PowerButton
{
public:
    PowerButton();
    void init();
    bool getState();

private:
    const uint8_t PB_PIN;
};