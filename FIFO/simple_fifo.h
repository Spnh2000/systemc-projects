#ifndef SIMPLE_FIFO_H
#define SIMPLE_FIFO_H

#include <systemc.h>
#include <queue>
#include <iostream>


using namespace std;


template <class T>
// Interface for the FIFO
class SimpleFIFOInterface : public sc_interface {
    public:
    virtual T read() = 0;
    virtual void write(T) = 0;
};




template <class T>
// FIFO implementation (Channel)
class SimpleFifo : public SimpleFIFOInterface<T> {
    private:
    queue<T> fifo;
    sc_event writtenEvent;
    sc_event readEvent;  //for unblock the consumer and producer 
    u_int64_t maxSize;

    public:
    SimpleFifo(u_int64_t size = 16) : maxSize(size) {}

    T read() {
        if(fifo.empty()== true){
            wait(writtenEvent);
        }
        T val = fifo.front();
        fifo.pop();
        readEvent.notify(SC_ZERO_TIME);
        return val;
    }

    void write(T val) {
        if(fifo.size()== maxSize){
            wait(readEvent);
        }
        fifo.push(val);
        writtenEvent.notify(SC_ZERO_TIME);
    }
};

// Producer module
SC_MODULE(PRODUCER) {
    sc_port<SimpleFIFOInterface<int>> master;

    SC_CTOR(PRODUCER){
        SC_THREAD(process);
    }

    void process(){
        unsigned int counter = 0;
        
        while(true){
            wait(1,SC_NS);
            master->write(counter++);
            cout << "@" << sc_time_stamp() << "P: " << counter << endl;
        }
    }
};

// Consumer module
SC_MODULE(CONSUMER) {
    sc_port<SimpleFIFOInterface<int>> slave;

    SC_CTOR(CONSUMER){
        SC_THREAD(process);
    }

    void process(){
        while(true){
            wait(4,SC_NS);
            cout << "@" << sc_time_stamp() << "C: " << slave->read() << endl;
        }
    }
};


#endif // SIMPLE_FIFO_H