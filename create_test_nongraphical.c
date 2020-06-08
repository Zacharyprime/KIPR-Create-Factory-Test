/*
KIPR Create Test Utility
Author: Zachary Sasser
Last Updated: 06-08-2020

This is for testing the iRobot Create and it's interaction with the KIPR Wombat and KIPR Wallaby

*/

#include <kipr.h>

int connectionTries = 10; //How many times should we try to connect? (for data)
int connectionMaxFail = 5; //How many tries before a create is considered "bad"
int frameSkip = 20; //Time in milliseconds between frames (adjust for future controllers)

int main(){
	//Connection Test
	printf("CONNECTION TEST: \n");
	printf("Testing connection to Create... \n");
	
	//Retries connection 20 times. A good create should only take ~3 tries.
	int t = 1;
	while(!(create_connect_once()) && t<connectionTries){
		msleep(500);
		t+=1;
	}
	if(t>=connectionMaxFail){
		printf("Bad connection, took too many tries to connect \n");
	}	
	printf("Successful connection established after %d tries. \n", t);

	printf("Testing disconnect function... \n");
	if(!create_disconnect()){
		printf("Disconnection process failure \n");
	}
	else{
		printf("Disconnection successful \n");
	}
	
	
	//Reconnect to Create
	printf("Re-establishing connection to Create... \n");
	t = 1;
	while(!(create_connect_once()) && t<connectionTries){
		msleep(500);
		t+=1;
	}
	if(t>=connectionMaxFail){
		printf("Unacceptable amount of tries to connect, please fix Create before distributing. \n");
	}	
	printf("Successful connection established after %d tries. \n", t);
	
	create_full();
	printf("Set create to full mode. Current Mode #: %d \n", get_create_mode());
	printf("To continue to next test, press any button");
	
	while(!any_button()); //Wait for user input
	while(any_button()); //Debounce button
	
	console_clear();
	//END CONNECTION TEST
	
	
	
	//Bumper/Drop Tests
	printf("Bumper/Drop Sensor Tests: \n");
	while(!any_button()){
		printf("Left Bumper: %d \n", get_create_lbump());
		printf("Right Bumper: %d \n \n", get_create_rbump());
		printf("Left Wheel Drop: %d \n", get_create_lwdrop());
		printf("Center Wheel Drop: %d \n", get_create_cwdrop());
		printf("Right Wheel Drop: %d \n", get_create_rwdrop());
		msleep(frameSkip);
	}
	while(any_button()); //Debounce button
	console_clear();
	//END BUMPER TEST
	
	//Cliff Sensors
	printf("Cliff Sensor Tests: \n");
	while(!any_button()){
		printf("Left Cliff: %d \n", get_create_lcliff());
		printf("Left-Front Cliff: %d \n \n", get_create_lfcliff());
		printf("Right-Front Cliff: %d \n", get_create_rfcliff());
		printf("Right Cliff: %d \n", get_create_rcliff());
		msleep(frameSkip);
	}
	while(any_button()); //Debounce button
	console_clear();
	//END CLIFF TEST
	
	//Light Bump Test
	printf("Light Bump Sensor Tests: \n");
	while(!any_button()){
		printf("Left Light Bump: %d (Digital: %d) \n", get_create_llightbump_amt(),get_create_llightbump());
		printf("Left-Front Light Bump: %d (Digital: %d)  \n \n", get_create_lflightbump_amt(),get_create_lflightbump());
		printf("Left-Center Light Bump: %d (Digital: %d)  \n", get_create_lclightbump_amt(),get_create_lclightbump());
		printf("Right-Center Light Bump: %d (Digital: %d)  \n \n", get_create_rclightbump_amt(),get_create_rclightbump());
		printf("Right-Front Light Bump: %d (Digital: %d)  \n", get_create_rflightbump_amt(),get_create_rflightbump());
		printf("Right Light Bump: %d (Digital: %d)  \n", get_create_rlightbump_amt(),get_create_rlightbump());
		msleep(frameSkip);
	}
	while(any_button()); //Debounce button
	console_clear();
	//END LIGHT BUMP TEST
	
	
	//Battery Readings
	printf("Battery Information: \n");
	while(!any_button()){
		printf("Charging State: %d \n", get_create_battery_charging_state());
		printf("Battery Temp: %d \n \n", get_create_battery_temp());
		printf("Battery Capacity: %d \n", get_create_battery_capacity());
		printf("Battery Voltage (NYI): %d \n", get_create_battery_voltage());
		printf("Battery Current (NYI): %d \n", get_create_battery_current());
		printf("NYI = Not Yet Implemented (as of 06-08-2020)");
		msleep(frameSkip);
	}
	while(any_button()); //Debounce button
	console_clear();
	//END BATTERY TEST
	
	//Wheel Tests (driving functions)
	printf("Wheel + Encoder Testing: \n \n");
	
	
	//Forward Test (low speed)
	printf("Low Speed Encoder Test: \n");
	printf("Please put create in the center of a cleared area of at least 1 meter x 1 meter \n");
	printf("When ready, press any button \n");
	
	while(!any_button()); while(any_button()); //Read button and debounce
	
	
	set_create_distance(0);
	while(get_create_distance()<500){
		printf("Driving forward 0.5 meters (500 millimeters) \n");
		create_drive_direct(500,500);
	}
	printf("Expected Distance: %d millimeters \n", get_create_distance());
	printf("Please measure actual distance traveled to judge accuracy. \n");
	
	printf("Press any button to advance to the next step \n");
	while(!any_button()); while(any_button()); //Read button and debounce
	
	console_clear();
	
	
	//Backward Test (low speed)
	set_create_distance(0);
	while(get_create_distance()>-1000){
		printf("Driving backward 1 meter (1000 millimeters) \n");
		create_drive_direct(-500,-500);
	}
	printf("Expected Distance: %d millimeters \n", get_create_distance());
	printf("Please measure actual distance traveled to judge accuracy. \n");
	
	
	
	printf("Press any button to advance to the next step \n");
	while(!any_button()); while(any_button()); //Read button and debounce
	
	console_clear();
		
	//Forward Test (high speed)
	printf("High Speed Encoder Test: \n");
	printf("Please put create in the center of a cleared area of at least 1 meter x 1 meter \n");
	printf("When ready, press any button \n");
	
	while(!any_button()); while(any_button()); //Read button and debounce
	
	
	set_create_distance(0);
	while(get_create_distance()<500){
		printf("Driving forward 0.5 meters (500 millimeters) \n");
		create_drive_direct(1400,1400);
	}
	printf("Expected Distance: %d millimeters \n", get_create_distance());
	printf("Please measure actual distance traveled to judge accuracy. \n");
	
	printf("Press any button to advance to the next step \n");
	while(!any_button()); while(any_button()); //Read button and debounce
	
	console_clear();
	
	
	//Backward Test (low speed)
	set_create_distance(0);
	while(get_create_distance()>-1000){
		printf("Driving backward 1 meter (1000 millimeters) \n");
		create_drive_direct(-1400,-1400);
	}
	printf("Expected Distance: %d millimeters \n", get_create_distance());
	printf("Please measure actual distance traveled to judge accuracy. \n");
	
	printf("Press any button to advance to the next step \n");
	while(!any_button()); while(any_button()); //Read button and debounce
	
	console_clear();
	
	printf("Create Test Complete! \n");
}
