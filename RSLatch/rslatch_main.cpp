#include <systemc.h>

#include "stim.h"
#include "mon.h"
#include "rslatch.h"

int sc_main(int, char**)
{
    sc_signal<bool> sigS, sigR;
    sc_signal<bool> sigQ, sigN;

    // stimulus generator
    stim Stim1("Stimulus");
    Stim1.S(sigS);
    Stim1.R(sigR);

    // device under test
    rslatch DUT("rslatch");
    DUT.S(sigS);
    DUT.R(sigR);
    DUT.Q(sigQ);
    DUT.N(sigN);

    // monitor
    Monitor mon("Monitor");
    mon.S(sigS);
    mon.R(sigR);
    mon.Q(sigQ);
    mon.N(sigN);

    std::cout << "\nT\t\tS\tR\tQ\tN\n";

    sc_start();

    return 0;
}