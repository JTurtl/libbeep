#include "beep.h"
#include <stdio.h>
/* pow() */
#include <math.h>

enum Value {
    REST,
    C, D, E, F, G, A, B,
    CS, DS,  FS, GS, AS,
};

struct Note {
    enum Value val;
    int octave;
    int length;
};

int note_to_freq(struct Note n) {
    /* 4th octave frequency */
    int f;
    switch (n.val) {
        case C:  f = 261; break;
        case CS: f = 277; break;
        case D:  f = 293; break;
        case DS: f = 311; break;
        case E:  f = 330; break;
        case F:  f = 350; break;
        case FS: f = 370; break;
        case G:  f = 392; break;
        case GS: f = 415; break;
        case A:  f = 440; break;
        case AS: f = 466; break;
        case B:  f = 494; break;

        case REST: return 0; break;
    }

    double realf = f * pow(2, n.octave - 4);
    return (int)realf;
}

#define C3(len) (struct Note){.val=C,.octave=3,.length=len}
#define D3(len) (struct Note){.val=D,.octave=3,.length=len}
#define E3(len) (struct Note){.val=E,.octave=3,.length=len}
#define F3(len) (struct Note){.val=F,.octave=3,.length=len}
#define G3(len) (struct Note){.val=G,.octave=3,.length=len}
#define A3(len) (struct Note){.val=A,.octave=3,.length=len}
#define B3(len) (struct Note){.val=B,.octave=3,.length=len}
#define CS3(len) (struct Note){.val=CS,.octave=3,.length=len}
#define DS3(len) (struct Note){.val=DS,.octave=3,.length=len}
#define FS3(len) (struct Note){.val=FS,.octave=3,.length=len}
#define GS3(len) (struct Note){.val=GS,.octave=3,.length=len}
#define AS3(len) (struct Note){.val=AS,.octave=3,.length=len}

#define C4(len) (struct Note){.val=C,.octave=4,.length=len}
#define D4(len) (struct Note){.val=D,.octave=4,.length=len}
#define E4(len) (struct Note){.val=E,.octave=4,.length=len}
#define F4(len) (struct Note){.val=F,.octave=4,.length=len}
#define G4(len) (struct Note){.val=G,.octave=4,.length=len}
#define A4(len) (struct Note){.val=A,.octave=4,.length=len}
#define B4(len) (struct Note){.val=B,.octave=4,.length=len}
#define CS4(len) (struct Note){.val=CS,.octave=4,.length=len}
#define DS4(len) (struct Note){.val=DS,.octave=4,.length=len}
#define FS4(len) (struct Note){.val=FS,.octave=4,.length=len}
#define GS4(len) (struct Note){.val=GS,.octave=4,.length=len}
#define AS4(len) (struct Note){.val=AS,.octave=4,.length=len}

#define C5(len) (struct Note){.val=C,.octave=5,.length=len}
#define D5(len) (struct Note){.val=D,.octave=5,.length=len}
#define E5(len) (struct Note){.val=E,.octave=5,.length=len}
#define F5(len) (struct Note){.val=F,.octave=5,.length=len}
#define G5(len) (struct Note){.val=G,.octave=5,.length=len}
#define A5(len) (struct Note){.val=A,.octave=5,.length=len}
#define B5(len) (struct Note){.val=B,.octave=5,.length=len}
#define CS5(len) (struct Note){.val=CS,.octave=5,.length=len}
#define DS5(len) (struct Note){.val=DS,.octave=5,.length=len}
#define FS5(len) (struct Note){.val=FS,.octave=5,.length=len}
#define GS5(len) (struct Note){.val=GS,.octave=5,.length=len}
#define AS5(len) (struct Note){.val=AS,.octave=5,.length=len}

#define C6(len) (struct Note){.val=C,.octave=6,.length=len}
#define D6(len) (struct Note){.val=D,.octave=6,.length=len}
#define E6(len) (struct Note){.val=E,.octave=6,.length=len}
#define F6(len) (struct Note){.val=F,.octave=6,.length=len}
#define G6(len) (struct Note){.val=G,.octave=6,.length=len}
#define A6(len) (struct Note){.val=A,.octave=6,.length=len}
#define B6(len) (struct Note){.val=B,.octave=6,.length=len}
#define CS6(len) (struct Note){.val=CS,.octave=6,.length=len}
#define DS6(len) (struct Note){.val=DS,.octave=6,.length=len}
#define FS6(len) (struct Note){.val=FS,.octave=6,.length=len}
#define GS6(len) (struct Note){.val=GS,.octave=6,.length=len}
#define AS6(len) (struct Note){.val=AS,.octave=6,.length=len}

#define R(len) (struct Note){.val=REST,.length=len}

void play(struct BeepInstance *instance, struct Note n) {
    if (n.val != REST) printf("%d\n", note_to_freq(n));
    else puts("...");

    int ms_per_beat = 1000.0/(95.0 / 60.0);
    beep_play(instance, note_to_freq(n), (n.length * ms_per_beat) / 4);
}

struct Note symphony[] = {
    C4(1), R(3),
    C6(2), DS6(2), F6(2), FS6(2), F6(2), DS6(2), C6(2), R(4),

    AS5(1), D6(1), C6(2), R(4),

    G3(1), R(1), C4(1), R(3),

    C6(2), DS6(2), F6(2), FS6(2), F6(2), DS6(2), FS6(2), R(6),

    FS6(1), F6(1), DS6(1), FS6(1), F6(1), DS6(1),

};

int main(void) {
    struct BeepInstance instance = beep_init();
    if (!beep_is_ok(&instance)) {
        return 1;
    }

    const int len = sizeof(symphony)/sizeof(struct Note);
    for (int i=0; i<len; i++) {
        play(&instance, symphony[i]);
    }

    beep_quit(&instance);

    puts("⡯⡯⡾⠝⠘⠀ ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢊⠘⡮⣣⠪⠢⡑⡌ \n\
⠟⠝⠈⠀⠀⠀. ⠡⠀⠠⢈⠠⢐⢠⢂⢔⣐⢄⡂⢔⠀⡁⢉⠸⢨⢑⠕⡌  ⠀\n\
⠀ ⡀⠁⠀⠀⠀⡀⢂⠡⠈⡔⣕⢮⣳⢯⣿⣻⣟⣯⣯⢷⣫⣆⡂ ⢐⠑⡌\n\
⢀⠠⠐⠈⠀⢀⢂⠢⡂⠕⡁⣝⢮⣳⢽⡽⣾⣻⣿⣯⡯⣟⣞⢾⢜⢆⠀⡀⠀⠪\n\
⣬⠂⠀⠀⢀⢂⢪⠨⢂⠥⣺⡪⣗⢗⣽⢽⡯⣿⣽⣷⢿⡽⡾⡽⣝⢎⠀⠀⠀⢡\n\
⣿⠀⠀⠀⢂⠢⢂⢥⢱⡹⣪⢞⡵⣻⡪⡯⡯⣟⡾⣿⣻⡽⣯⡻⣪⠧⠑⠀⠁⢐\n\
⣿⠀⠀⠀⠢⢑⠠⠑⠕⡝⡎⡗⡝⡎⣞⢽⡹⣕⢯⢻⠹⡹⢚⠝⡷⡽⡨⠀⠀⢔\n\
⣿⡯⠀⢈⠈⢄⠂⠂⠐⠀⠌⠠⢑⠱⡱⡱⡑⢔⠁⠀⡀⠐⠐⠐⡡⡹⣪⠀⠀⢘\n\
⣿⣽⠀⡀⡊⠀⠐⠨⠈⡁⠂⢈⠠⡱⡽⣷⡑⠁⠠⠑⠀⢉⢇⣤⢘⣪⢽⠀⢌⢎\n\
⣿⢾⠀⢌⠌⠀⡁⠢⠂⠐⡀⠀⢀⢳⢽⣽⡺⣨⢄⣑⢉⢃⢭⡲⣕⡭⣹⠠⢐⢗\n\
⣿⡗⠀⠢⠡⡱⡸⣔⢵⢱⢸⠈⠀⡪⣳⣳⢹⢜⡵⣱⢱⡱⣳⡹⣵⣻⢔⢅⢬⡷\n\
⣷⡇⡂⠡⡑⢕⢕⠕⡑⠡⢂⢊⢐⢕⡝⡮⡧⡳⣝⢴⡐⣁⠃⡫⡒⣕⢏⡮⣷⡟\n\
⣷⣻⣅⠑⢌⠢⠁⢐⠠⠑⡐⠐⠌⡪⠮⡫⠪⡪⡪⣺⢸⠰⠡⠠⠐⢱⠨⡪⡪⡰\n\
⣯⢷⣟⣇⡂⡂⡌⡀⠀⠁⡂⠅⠂⠀⡑⡄⢇⠇⢝⡨⡠⡁⢐⠠⢀⢪⡐⡜⡪⡊\n\
⣿⢽⡾⢹⡄⠕⡅⢇⠂⠑⣴⡬⣬⣬⣆⢮⣦⣷⣵⣷⡗⢃⢮⠱⡸⢰⢱⢸⢨⢌\n\
⣯⢯⣟⠸⣳⡅⠜⠔⡌⡐⠈⠻⠟⣿⢿⣿⣿⠿⡻⣃⠢⣱⡳⡱⡩⢢⠣⡃⠢⠁\n\
⡯⣟⣞⡇⡿⣽⡪⡘⡰⠨⢐⢀⠢⢢⢄⢤⣰⠼⡾⢕⢕⡵⣝⠎⢌⢪⠪⡘⡌⠀\n\
⡯⣳⠯⠚⢊⠡⡂⢂⠨⠊⠔⡑⠬⡸⣘⢬⢪⣪⡺⡼⣕⢯⢞⢕⢝⠎⢻⢼⣀⠀\n\
⠁⡂⠔⡁⡢⠣⢀⠢⠀⠅⠱⡐⡱⡘⡔⡕⡕⣲⡹⣎⡮⡏⡑⢜⢼⡱⢩⣗⣯⣟\n\
⢀⢂⢑⠀⡂⡃⠅⠊⢄⢑⠠⠑⢕⢕⢝⢮⢺⢕⢟⢮⢊⢢⢱⢄⠃⣇⣞⢞⣞⢾\n\
⢀⠢⡑⡀⢂⢊⠠⠁⡂⡐⠀⠅⡈⠪⠪⠪⠣⠫⠑⡁⢔⠕⣜⣜⢦⡰⡎⡯⡾⡽");
}
