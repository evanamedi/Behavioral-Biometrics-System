/*
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
| Hook onto macOs keyboard events to capture key presses  |
| and releases. Sends captured data to the Data Storage   |
| Module (key code, event type, timestamp, etc...).       |
| Character keys will be recorded in ASCII                |
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
*/

void initialize_capture() {
	/*
	sets up the Quartz Event Taps API for capturing keyboard 
	events. ensures that all necessary permissions are in 
	place. prepares the event tap to monitor:

	key press   : kCGEventKeyDown
	key release : kCGEventKeyUp
	*/
}

/*
depending on how the QET API works, we may have two options 
to capturing events. 

the first option as laid out below includes two functions- 
one to start the capture and one to stop the capture. this 
method works by creating a (press) event on start_capture() 
with the relevant information about it, then a (release) 
event on stop_capture() with its relevant information. this 
method would include keeping track of when a key has been 
pressed, and not yet released. in the meantime keeping track 
of other additional press events as well. the implication 
is that a user could continue holding down 'a' while 
simultaneously pressing 'b' and 'c'. thus requiring a data
structure to contain a binary representation of either 
'pressing' or 'released'. having said that, this may be 
overkill for our intent and purpose. generally the 'shift' 
key will be the most common case of a user holding down a 
key while simultaneously pressing other keys. but i feel 
this small detail is relevant to capture due to the 
variability of how different people would go about using 
the 'shift' key. one person may hold down 'shift' as they 
type a word in full caps- but others may press and release
'shift' as they type each letter.

a second option may include only one function. where the 
function is called when a user presses a key, and its 
first action is recording the time it was called to 
indicate the time the key was pressed, then the function 
only returns once the key as been released. but just before 
returning- it records the time stamp to indicate when it 
was released. this could provide savings in storage and 
time by reusing all the keys information, excluding time 
stamps. additionally this may provide a more accurate 
time stamp. the benefits may not be noticeable- but this 
would reduce code complexity if it worked.

i do not want to spend much time pre-optimizing. however, 
there is something to be said about providing the most 
accurate timing possible. the more precise we get with 
recording time stamp data, the more likely the detection 
model can accurately predict. 
*/

void start_capture() {
	/*
	activates the event tap to begin monitoring keyboard 
	input & starts an asynchronous loop to process key 
	events as they occur
	*/
}

void stop_capture() {
	/*
	deactivates and releases the event tap & ensures that 
	no residual hooks remain active
	*/
}

CGEventRef event_callback(CGEventTapProxy proxy, 
						  CGEventType type, 
						  CGEventRef event, 
						  void *userInfo) {
	/*
	callback function triggered by the Quartz Event Taps 
	API for every key event. extracts key code and event 
	type. gets timestamp using the Timing Module. passes 
	the data to the Data Storage Module
	*/
}