#include "epr_timer.h"
#include "timer.h"

void initEprTimer() {
    initTimer();
}
void wait(uint32_t us) {

    const int t2 = getTimeStamp() + (us * TICKS_PER_US);

    while (getTimeStamp() < t2) {
        // do nothing
    }
}