/* 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
| Handles the loading and display of the text to be typed |
| Manages a modifiable buffer for user input              |
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
*/

void load_text(const char *file_name) {
	/*
	reads the initial paragraph from the provided text file
	then loads that text into a buffer. we may have a count
	down function that is triggered when the user runs the
	start command. the function will take the text out of
	the buffer to be displayed, print it to the screen,
	start a quick count down for the user, then call
	start_logger() once the count down is complete. in the
	meantime as the count down is going- we can remove the
	text from the buffer as it is no longer needed in 
	memory.

	it may be that we combine the functions load_text(),
	start_countdown(), and start_logger() into one function
	depending on the complexity. it may increase readability
	at little cost to separation of concerns. TBD.
	*/
}

void update_display(char key) {
	/*
	this will first check that the current argument matches 
	an acceptable displayable key code. anything that passes 
	the check, excluding 'backspace', should be added to the 
	user input buffer stack & displayed back to the user. when 
	a 'backspace' is encountered we pop the last item added to 
	the stack, and adjust the users display accordingly.
	*/
}

// optional function should we want to separate the updating 
// & rendering of the stack into two separate concerns.
void render_display() {
	/*
	refreshes the terminal with the current state of the 
	display buffer- ensuring the displayed text matches the 
	users input in the stack.
	*/
}

void cleanup_display() {
	/*
	this should free all resources related to the display 
	buffer. we currently have cleanup_storage() handling 
	cleaning up data structures held in memory. this cleanup 
	function is concerned with just clearing the display buffer. 
	Perhaps it makes more sense to have all clean up functionality 
	consolidated into one function. we could also explore creating 
	a single data structure for the purpose of handling any calls 
	for allocating memory. then this main data structure and its 
	accompanying logic will handle management of all resources.
	*/
}