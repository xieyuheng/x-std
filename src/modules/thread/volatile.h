#pragma once

// The volatile keyword informs the compiler that
// a variable's value may change in ways
// not directly controlled by the program.

// This prevents the compiler from performing certain optimizations,
// ensuring that the program always reads
// the most up-to-date value of the variable.

#define volatile_load(pointer) atomic_load_explicit(pointer, memory_order_relaxed)
#define volatile_store(pointer, value) atomic_store_explicit(pointer, value, memory_order_relaxed)
