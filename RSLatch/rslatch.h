#ifndef RSLATCH_H
#define RSLATCH_H

#include <systemc.h>

SC_MODULE(rslatch){
    public:
    sc_in<bool> S, R;
    sc_out<bool> Q, N;

    SC_CTOR(rslatch): S("S"), R("R"), Q("Q"), N("N")
    {
       SC_METHOD(process);
       sensitive << S << R << Q << N; 
    }

    private: 
    void process(){
        Q.write(!(R.read()||N.read()));
        N.write(!(S.read()||Q.read()));
    }

};
#endif //RSLATCH_H
