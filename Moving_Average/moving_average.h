#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H

#include <systemc.h>

SC_MODULE(MovingAverage){
    sc_in<unsigned int> xn;
    sc_in<bool> clk, reset;
    sc_out<unsigned int> yn;


    sc_signal<unsigned int> x0, x1, x2;

    SC_CTOR(MovingAverage):xn("xn"), clk("clk"), reset("reset"), yn("yn"), x0("x0"), x1("x1"), x2("x2")
    {
        SC_METHOD(shift);
        sensitive << clk.pos() << reset;

        SC_METHOD(add);
        sensitive << xn << x0 << x1 << x2;
    
    }

    void shift(){
        if(reset){
            x0.write(0);
            x1.write(0);
            x2.write(0);
        } else if (clk.posedge()){
            x0.write(xn.read());
            x1.write(x0.read());
            x2.write(x1.read());
        }

    }


    void add(){
        yn.write((x0.read()+x1.read()+x2.read()+xn.read())/4); 
    }

};

#endif // MOVING_AVERAGE_H
