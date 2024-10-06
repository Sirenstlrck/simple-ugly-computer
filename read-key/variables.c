#include "read_key.h"

struct termios lastSavedTermios;
int lastSavedTermios_echoMode;
int lastSavedTermios_signalValue;