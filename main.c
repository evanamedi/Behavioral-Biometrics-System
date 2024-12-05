
int main(int argc, char *argv[]) {
    // call start_initialization()

    // run infinite loop waiting for commands
    // - - - - - POSSIBLE COMMANDS - - - - -
    // help
    // start
    // exit
}

void start_logger() {
    // call initialize_capture()

    // call display_provided_text()

    // call run_session()
}

void stop_logger() {
}

int start_initialization() {
    // ensure CSV folder exists

    // print: program name, version #, author

    // provide introductory display and list of available commands

    // returns integer indicating successful initialization
}

int start_deinitialization() {
    // call cleanup_display()

    // call cleanup_storage()

    // call cleanup_timing()
}

void run_session() {
    // call start_countdown()

    // call start_logger()

    // call start_capture()
}
