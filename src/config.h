#pragma once

struct OutputConfig {
    bool IgnoreConsumption;//do not consume this key
    bool WaitForRelease;//wait for release to output hold do not

};

struct HoldOutput {
    int  HoldTimer;//keep hold output active until timer runs out
};

struct TapOutput
{
    /* data */
};


struct mapping
{
    const KeyState  state;
    const HoldOutput holdOutput;
    const TapOutput  tapOutpot ;
    void(*actionHold)(const HoldOutput *output);
    void(*actionTap )(const TapOutput  *output);
    //key index is the index in array
};
