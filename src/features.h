#pragma once

#if DOUBLETAP == ENABLED
#define DOUBLETAPVAR outputSeq doubletap;
#define DOUBLETAP doubletap
#define DOUBLETAPCONF OutputConfig doubletap;
#else
#define DOUBLETAPVAR
#define DOUBLETAP
#define DOUBLETAPCONF
#endif

#if TAPHOLD == ENABLED
#define TAPHOLDVAR outputSeq taphold;
#define TAPHOLDCONF OutputConfig taphold;
#define TAPHOLD taphold
#else
#define TAPHOLDVAR
#define TAPHOLD
#define TAPHOLDCONF
#endif