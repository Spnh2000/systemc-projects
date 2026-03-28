#include <systemc.h>
#include "moving_average.h"



#include <systemc.h>
#include "moving_average.h"

SC_MODULE(Testbench)
{
    sc_signal<unsigned int> xn_sig;
    sc_signal<unsigned int> yn_sig;
    sc_signal<bool> reset_sig;
    sc_clock clk_sig;

    MovingAverage dut;

    SC_CTOR(Testbench)
        : clk_sig("clk_sig", 10, SC_NS),
          dut("moving_average")
    {
        dut.xn(xn_sig);
        dut.clk(clk_sig);
        dut.reset(reset_sig);
        dut.yn(yn_sig);

        SC_THREAD(stimulus);
        SC_METHOD(monitor);
        sensitive << xn_sig << yn_sig << reset_sig;
        dont_initialize();
    }

    void stimulus()
    {
        reset_sig.write(true);
        xn_sig.write(0);
        wait(12, SC_NS);

        reset_sig.write(false);

        xn_sig.write(4);
        wait(10, SC_NS);

        xn_sig.write(8);
        wait(10, SC_NS);

        xn_sig.write(12);
        wait(10, SC_NS);

        xn_sig.write(16);
        wait(10, SC_NS);

        xn_sig.write(20);
        wait(10, SC_NS);

        sc_stop();
    }

    void monitor()
    {
        std::cout << "t=" << sc_time_stamp()
                  << " reset=" << reset_sig.read()
                  << " xn=" << xn_sig.read()
                  << " yn=" << yn_sig.read()
                  << std::endl;
    }
};

int sc_main(int, char**)
{
    Testbench tb("tb");
    sc_start();
    return 0;
}

