#include "beep.h"

int main(void) {
    struct BeepInstance instance = beep_init();
    if (!beep_is_ok(&instance)) {
        /* darn */
        return 1;
    }

    /* Play a note for 1 second @ 500hz */
    beep_play(&instance, 500, 1000);

    /* 1 second pause */
    beep_sleep(1000);

    /* ZOOOoooop... */
    for (int i=1000; i>=50; i--) {
        beep_start(&instance, i);
        beep_sleep(10);
    }

    /* ...zoooOOOOP! */
    for (int i=50; i<=1000; i++) {
        beep_start(&instance, i);
        beep_sleep(10);
    }

    /* Mission accomplished */
    beep_quit(&instance);
    
    return 0;
}

