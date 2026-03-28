#include <systemc.h>
#include "simple_fifo.h"

int sc_main(int __attribute__((unused)) argc,
            char __attribute__((unused)) *argv[])
{
    PRODUCER producer("producer");
    CONSUMER consumer("consumer");

    SimpleFifo<int> channel(4);

    producer.master.bind(channel);
    consumer.slave.bind(channel);
    sc_start(30, SC_NS);

    return 0;
}
