/*
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
| Entry point of the program designated to orchestrate    |
| the overall control flow including starting and         |
| stopping the program.                                   |
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/

int main(int argc, char *argv[]) {
	/*
	responsible for parsing command-line arguments (start, 
	stop, input file for paragraph text). initialize and 
	manage program lifecycle. calls start_logger() and 
	stop_logger() functions to control the logging session.
	will need special commands for starting and stopping the 
	program. all available commands will be displayed to 
	the user- followed by "press XXXXX to start".
	*/
}

void start_logger() {
	/*
	capture the current time the program was started. signal 
	the Keystroke Capture Module to start recording events.
	initialize the display_text module to load and display 
	the paragraph text & subsequently display what the users 
	types so that they can match it with the provided text.
	ensures all other modules are properly initialized:
	Timing, Data Storage, etc...
	*/
}

void stop_logger() {
	/*
	capture the current time the program was ended, then 
	calculate the total duration. this may need some 
	playing with- but it might be best to actually 
	calculate the duration by simply calculating the timing 
	distance from the first key pressed to the last key 
	released- excluding command stroke. this will also 
	signal the Keystroke Capture Module to stop recording.
	call the Data Storage Module to save and export captured 
	data. clean up resources and ensures proper termination.
	*/
}

