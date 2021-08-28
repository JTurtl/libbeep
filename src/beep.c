#include "beep.h"

/* struct stat, stat(), S_ISCHR */
#include <sys/stat.h>

/* ioctl() */
#include <sys/ioctl.h>

/* open(), O_WRONLY */
#include <fcntl.h>

/* close() */
#include <unistd.h>

/* EVIOCGSND(), struct input_event */
#include <linux/input.h>

/* struct timespec, nanosleep() */
#include <time.h>

#define DEFAULT_DEVICE_PATH "/dev/input/by-path/platform-pcspkr-event-spkr"
#define BAD_INSTANCE (struct BeepInstance){.device_file_descriptor=-1}

struct BeepInstance beep_init() {
    return beep_init_with(DEFAULT_DEVICE_PATH);
}

struct BeepInstance beep_init_with(const char *device_path) {
    /* Get file attributes */
    struct stat sb;
    if (stat(device_path, &sb) == -1) {
        /* probably doesn't exist lol */
        return BAD_INSTANCE;
    }

    /* Check if it's a "character device" (TODO: a what?) */
    if (!S_ISCHR(sb.st_mode)) {
        return BAD_INSTANCE;
    }

    const int fd = open(device_path, O_WRONLY);
    if (fd == -1) {
        /* TODO: there's a lot of reasons why this might fail
            Maybe more return values or stderr logging */
        return BAD_INSTANCE;
    }

    /* Stat again, I guess 
        TODO: are these next two necessary? */
    if (fstat(fd, &sb) == -1) {
        close(fd);
        return BAD_INSTANCE;
    }

    if (!S_ISCHR(sb.st_mode)) {
        close(fd);
        return BAD_INSTANCE;
    }

    /* wtf */
    if (ioctl(fd, EVIOCGSND(0)) == -1) {
        close(fd);
        return BAD_INSTANCE;
    }

    struct BeepInstance result =  {
        .device_file_descriptor = fd,
    };

    /* in case something was already playing */
    beep_stop(&result);

    return result;
}

void beep_quit(struct BeepInstance *instance) {
    beep_stop(instance);
    close(instance->device_file_descriptor);
}

bool beep_is_ok(struct BeepInstance *instance) {
    return instance->device_file_descriptor != -1;
}

void beep_start(struct BeepInstance *instance, int frequency) {
    const struct input_event e = {
        .code = SND_TONE,
        .time = (struct timeval) {
            .tv_sec = 0, .tv_usec = 0,
        },
        .type = EV_SND,
        .value = frequency,
    };

    const ssize_t bytes_written = write(instance->device_file_descriptor, &e, sizeof(e));
    if (bytes_written != sizeof(struct input_event)) {
        /* Something is funky, not sure what to do about it though */
    }
}

void beep_stop(struct BeepInstance *instance) {
    beep_start(instance, 0);
}

void beep_play(struct BeepInstance *instance, int frequency, uint32_t duration_ms) {
    beep_start(instance, frequency);
    beep_sleep(duration_ms);
    beep_stop(instance);
}

void beep_sleep(uint32_t duration_ms) {
    /* todo: check for nanosleep() duringn compile */
    
    /* todo: make this a single equation */
    long seconds = 0;
    while (duration_ms >= 1000) {
        seconds++;
        duration_ms -= 1000;
    }

    /* nanoseconds are *tiny* */
    long nanosecs = duration_ms * 1000000;

    const struct timespec t = {
        .tv_nsec = nanosecs,
        .tv_sec = seconds,
    };
    nanosleep(&t, NULL);
}
