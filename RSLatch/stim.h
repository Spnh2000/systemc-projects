#ifndef STIM_H
#define STIM_H

#include <systemc.h>

SC_MODULE(stim)
{
    sc_out<bool> S;
    sc_out<bool> R;

    SC_CTOR(stim)
    {
        SC_THREAD(StimGen);
    }

    void StimGen()
    {
        // Reset state
        S.write(false);
        R.write(true);
        wait(10, SC_NS);

        // Set
        S.write(true);
        R.write(false);
        wait(10, SC_NS);

        // Reset
        S.write(false);
        R.write(true);
        wait(10, SC_NS);

        // Invalid state
        S.write(true);
        R.write(true);
        wait(10, SC_NS);

        sc_stop();
    }
};

#endif