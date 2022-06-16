#pragma once

struct OutputAction {
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
    
};
