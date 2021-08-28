#ifndef _BEEP_H
#define _BEEP_H

#include <stdint.h>
#include <stdbool.h>

struct BeepInstance {
    int device_file_descriptor;
};

/* Initialize a Beep instance with default device path */
struct BeepInstance beep_init();
/* (try to) Initialize Beep with a given device */
struct BeepInstance beep_init_with(const char *device_path);
void beep_quit(struct BeepInstance*);

/* call after `beep_init[_with]()` to verify init was successful.
    If init fails, device most likely does not support hardware beep. */
bool beep_is_ok(struct BeepInstance*);


/* Begin playing a beep. Will not pause execution.
    Call again while already playing to change frequency */
void beep_start(struct BeepInstance*, int frequency);

/* Stop beeping. Same as beep_start(&instance, 0) */
void beep_stop(struct BeepInstance*);

/* Play a frequency for `duration_ms` milliseconds. Will pause execution. */
void beep_play(struct BeepInstance*, int frequency, uint32_t duration_ms);

void beep_sleep(uint32_t duration_ms);

#endif
