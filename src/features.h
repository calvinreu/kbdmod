#pragma once

#ifndef FEATUREDOUBLETAP
#define FEATUREDOUBLETAP true
#endif
#ifndef FEATURETAPHOLD
#define FEATURETAPHOLD true
#endif

#if FEATUREDOUBLETAP == true
#define DOUBLETAPVAR outputSeq doubletap;
#define DOUBLETAP doubletap
#define DOUBLETAPCONF OutputConfig doubletap;
#define WRITEDOUBLETAP write_sequence(TAPHOLD);
#else
#define DOUBLETAPVAR
#define DOUBLETAP 0
#define DOUBLETAPCONF
#define WRITEDOUBLETAP 0
#endif

#if FEATURETAPHOLD == true
#define TAPHOLDVAR outputSeq taphold;
#define TAPHOLDCONF OutputConfig taphold;
#define TAPHOLD taphold
#define WRITETAPHOLD write_sequence(TAPHOLD)
#else
#define TAPHOLDVAR
#define TAPHOLD 0
#define TAPHOLDCONF
#define WRITETAPHOLD 0
#endif