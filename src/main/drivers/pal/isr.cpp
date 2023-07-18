#include "isr.hpp"



isr::isr_vectors& isr::get_interrupt_vectors_instance()
{
    static isr_vectors isr_vectors_instance;
    return isr_vectors_instance;
}
