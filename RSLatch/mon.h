#ifndef MON_H
#define MON_H

#include <systemc.h>

SC_MODULE(Monitor)
{
    sc_in<bool> S;
    sc_in<bool> R;
    sc_in<bool> Q;
    sc_in<bool> N;

    sc_time currentTime;
    unsigned long long currentDelta;

    SC_CTOR(Monitor)
        : currentTime(SC_ZERO_TIME), currentDelta(0)
    {
        SC_METHOD(monitor);
        sensitive << S << R << Q << N;
    }

    void monitor()
    {
        sc_time time = sc_time_stamp();

        if (time > currentTime)
        {
            currentTime = time;
            currentDelta = sc_delta_count();
        }

        unsigned long long delta = sc_delta_count() - currentDelta;

        std::cout << time << " + " << delta << "δ\t"
                  << S.read() << "\t"
                  << R.read() << "\t"
                  << Q.read() << "\t"
                  << N.read() << std::endl;
    }
};

#endif