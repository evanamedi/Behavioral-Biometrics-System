/* 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
| Manages in-memory storage of captured keystroke data    |
| Formats and exports data to a CSV file                  |
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
*/


void initialize_storage(int paragraph_byte_size) {
	/*  
	allocates memory for storing keystroke events & 
	prepares any necessary data structures. we will have 
	two main types of memory for temp storing:

	
	- - - - - - - - - - -
	| key stroke events |
	- - - - - - - - - - - 
	this will be a fixed memory size for storing all key 
	strokes. once stop_logger() is called we will then 
	store the data into a persistent storage method. each 
	key stroke recorded is defined by either a 
	'key-press' or 'key-release'. each event will 
	record onto a single line to be stored in CSV format:

	| key code | event type | timestamp     |
	  65         p            1623456789012

	we will calculate the fixed-memory size to be the 
	average byte size of a single line multiplied by the 
	amount of chars provided in the given paragraph plus 
	an additional 10% of that total size (may change).

	a key thing to keep in mind here is that speed matters 
	most than format. so collecting the data and storing 
	it in memory as fast as possible is all that matters. 
	then once we are finished logging, we can then parse 
	the data to format it correctly. 

	however, this might be overkill and that kind of 
	optimization may not be necessary.
	
	this may use a stack data structure, where each item 
	in the stack is a tuple of the 3 data fields being 
	collected. biggest priority here is fast insertions. 

	we could also look at a way of just combining the 
	entire 3 fields into one field. the divider would 
	be the event type which is (at least thus far) either 
	a 'p' or 'r' (press or release). then we parse this 
	after the program ends. just depends on how much we 
	want to optimize- which is not important right now. 



	- - - - - - - - - - -
	| user input buffer |
	- - - - - - - - - - - 
	this will be a buffer and output display separate 
	from logging key stroke events. in this buffer we 
	will collect what the user is typing and display it 
	back to them. this way they can understand where 
	they are in completing the text. 

	however, this buffer does not simply collect 
	everything the user inputs and just append it to the 
	buffer. it will have to take into consideration back 
	spaces and other special characters that should not 
	be displayed.

	one idea may be to keep all characters typed in a 
	stack. as a character is typed we display it to the 
	user, then add it to the top of the stack. we can 
	have a filter before going to the stack or display 
	that ensures the current key stroke meets the 
	criteria for an acceptable char. if it does not- 
	then we simply ignore it (this will still get key 
	logged, but ignored for the purpose of user input 
	buffer). this also includes the space bar. in the
	case that a user uses the backspace to fix a typo 
	(or any other reason) we remove the last item on 
	the stack & buffer per each instance.
	*/
}

void store_log_event(int key_code, char event_type, long long timestamp) {
	/*
	logs each captured keystroke event into our 
	pre-initialized in-memory data structure. using 
	a stack we can ensure events are stored sequentially.
	*/

}


void export_to_csv(const char *csv_file_name) {
	/*
	this function will be called once stop_logger() is 
	called. it will be in charge of collecting all the 
	items from the 'key stroke event' stack and exporting 
	it to the current sessions CSV file. this may include 
	parsing all of the data so that it fits the proper CSV 
	structure. a format check and sequential ordering check 
	will apply as well.
	*/
}

char create_csv_file() {
	/*
	we will have a folder where all CSV files shall live. 
	each CSV file represents a single typing session. this 
	function triggers when the program starts, but before 
	start_keylogger() is run. part of the initialization set 
	up. the folder name will be included in the config file 
	& initialized with main(). each session will yield a new 
	CSV file name to go with each new file. for now we may do:
	key_log_data_<MM_DD_YYY_HH_MM>.csv
	*/
}

void cleanup_storage() {
	/*
	frees all allocated memory including both the 
	'key stroke event' stack, and 'user input buffer' / stack.
	this should be called inside of stop_keylogger() as a last 
	called function.
	/*
}