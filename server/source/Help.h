#ifndef HELP_H
#define HELP_H

struct Help;

struct Help * Help_construct();

void Help_destruct(struct Help * this);

void Help_printCommandLineManual(struct Help * this);

void Help_printStatus(struct Help * this, int port, int connectionLimit, int bufferLength, int threadNumber);

#endif
