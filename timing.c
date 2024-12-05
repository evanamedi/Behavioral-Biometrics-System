/*
Perhaps we only need just the logic for get_timestamp()
We can keep run_timing_tests() as part of the initialization sequence
*/


int run_timing_tests() {
    // run tests to make sure utilities and APIs are working
    // return 0 for success
}

long long get_timestamp() {
    // returns the current timestamp in nanoseconds
    // uses mach_absolute_time for high-res timing
    // return current time
}


//
//
// - - - - - - - - - - MAY NOT NEED - - - - - - - - - -
//
//

int initialize_timing() {
    // initialize the timing utilities using OS specific APIs
    // call run_timing_tests()

    // return 0 for success
}

void cleanup_timing() {
}
