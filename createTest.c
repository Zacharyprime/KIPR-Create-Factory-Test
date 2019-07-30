#include <kipr/botball.h>
#include <time.h>
/*
	CREATE FACTORY TEST
    by: Zachary Sasser
    
    This program tests all the botball functionality of your iRobot Create. 
    This is mainly for KIPR use to quality control Creates.

*/
int frameDelay = 0;


//Displays a green graphic to show the test has been successful.
void success(){
    graphics_open(600,600);
    graphics_fill(0,255,0);
    graphics_update();
    msleep(1000);
    graphics_close();
}

//Tests to see if the bumpers are working properly
void testBumpers(){
    //LEFT BUMPER
    printf("Test the LEFT bumper... \n");
    while(!get_create_lbump()){
    	msleep(10);
    }
    
    printf("Left Bumper works!");
    msleep(frameDelay);
    console_clear();
    success();
    
    
    //RIGHT BUMPER
    printf("Test the RIGHT bumper... \n");
    while(!get_create_rbump()){
    	msleep(10);
    }
    
    printf("Right Bumper works!");
    msleep(frameDelay);
    console_clear();
    success();
}

//Tests to see if the cliff sensors are working.
void testCliffs(){
    //LEFT CLIFF SENSOR
	printf("Tilt the LEFT side of the Create... \n");
    while(!get_create_lcliff()){
    	msleep(10);
    }
    
    printf("Left Cliff Sensor works!");
    msleep(frameDelay);
    console_clear();
    success();
    
    //RIGHT CLIFF SENSOR
    printf("Tilt the RIGHT side of the Create... \n");
    while(!get_create_rcliff()){
    	msleep(10);
    }
    
    printf("Right Cliff Sensor works!");
    msleep(frameDelay);
    console_clear();
    success();
    
    //FRONT-LEFT CLIFF SENSOR
    printf("Tilt the LEFT side of the Create from the front... \n");
    while(!get_create_lfcliff()){
    	msleep(10);
    }
    
    printf("Front-Left Cliff Sensor works!");
    msleep(frameDelay);
    console_clear();
    success();
    
    //FRONT-RIGHT CLIFF SENSOR
    printf("Tilt the RIGHT side of the Create from the front... \n");
    while(!get_create_rfcliff()){
    	msleep(10);
    }
    
    printf("Front-Right Cliff Sensor works!");
    msleep(frameDelay);
    console_clear();
    success();
}

//Tests the light touch sensors (detect walls)
void testLightTouch(){
    //LEFT LIGHT TOUCH SENSOR
 	printf("Put your hand in front of the LEFT light touch sensor to simulate a wall... \n");
    while(!get_create_lclightbump()){
    	msleep(10);
    }
    
    printf("Left Light Touch Sensor works!");
    msleep(frameDelay);
    console_clear();
    success();
    
    //RIGHT LIGHT TOUCH SENSOR
    printf("Put your hand in front of the RIGHT light touch sensor to simulate a wall... \n");
    while(!get_create_rclightbump()){
    	msleep(10);
    }
    
    printf("Right Light Touch Sensor works!");
    msleep(frameDelay);
    console_clear();
    success();
    
    //FRONT-LEFT LIGHT TOUCH SENSOR
    printf("Put your hand in front of the FRONT-LEFT light touch sensor to simulate a wall... \n");
    while(!get_create_lflightbump()){
    	msleep(10);
    }
    
    printf("Front-Left Light Touch Sensor works!");
    msleep(frameDelay);
    console_clear();
    success();
    
    //FRONT-RIGHT LIGHT TOUCH SENSOR
    printf("Put your hand in front of the FRONT-RIGHT light touch sensor to simulate a wall... \n");
    while(!get_create_rflightbump()){
    	msleep(10);
    }
    
    printf("Front-Right Light Touch Sensor works!");
    msleep(frameDelay);
    console_clear();
    success();
}

void testWheelDrop(){
    //LEFT WHEEL DROP
    printf("Let the LEFT wheel drop (should hear a click)... \n");
    while(!get_create_lwdrop()){
    	msleep(10);
    }
    
    printf("Left drop sensor works!");
    msleep(frameDelay);
    console_clear();
    success();
    
    //RIGHT WHEEL DROP
    printf("Let the RIGHT wheel drop (should hear a click)... \n");
    while(!get_create_rwdrop()){
    	msleep(10);
    }
    
    printf("Right drop sensor works!");
    msleep(frameDelay);
    console_clear();
    success();
}
void testWheels(){
 	printf("Testing wheels...\n");
    set_create_distance(0); //Set encoder readings to 0
    int time = 0;
    
    //Try to drive the motors for 500mm but if it takes too long, the wheels have failed.
    while(get_create_distance()<500 && time<5000){
    	create_drive_straight(500);
        msleep(100);
        time+=100;
    }
    
    create_drive_direct(0,0);
    
    //Display message that wheels have failed and exit program
    if(time>=5000){
        console_clear();
     	printf("Wheel Failure...");
        msleep(frameDelay);
        console_clear();
        return 0;
    }
    
    //Display message if wheels are functional
    else{
        console_clear();
        printf("Wheels are working!");
        msleep(frameDelay);
        console_clear();
        success();
    }
}

//Display current battery percentage
void testBattery(){
    console_clear();
    printf("The Battery is charged to: %f %% \n", (double)get_create_battery_charge()/get_create_battery_capacity()*100);
    
    msleep(frameDelay);
    console_clear();
}

//Plays the six flag theme song instrumental version to match the rainbow colors
void playSong(){
	system("aplay /party.wav");
}

//Run a congratulations animation and song
void finishTest(){

    printf("Congratulations! Your create is (probably) functional!");
    msleep(frameDelay);
    console_clear();
    //Coordinates to split the screen into 7 rectangles
    int x1 = 0;
    int x2 = 67;
    int x3 = 135;
    int x4 = 202;
    int x5 = 270;
    int x6 = 337;
    int x7 = 405;
    int x8 = 472;
    
    //Defining all the colors (note that the colors on each array change as the program runs)
    int COLOR1[3] = {255,0,0}; //RED
    int COLOR2[3] = {255,165,0}; //ORANGE
    int COLOR3[3] = {255,215,0}; //YELLOW
    int COLOR4[3] = {0,255,0}; //GREEN
    int COLOR5[3] = {0,0,255}; //BLUE
    int COLOR6[3] = {75,0,130}; //INDIGO
    int COLOR7[3] = {128,0,128}; //VIOLET
    
    
    
    create_disconnect();
    printf("Disconnection Successful! \n");
    msleep(frameDelay);
    
    
    
    graphics_open(472,248);
    
    //Open a seperate thread to play the party song so the animation will still run
    thread playStart = thread_create(playSong);
    thread_start(playStart);
    
    //Run the animation for 10 seconds 
    int time = 0;
    while(time<10000){
        
        //Make colored rectangles on the screen in a rainbow fashion
        graphics_rectangle_fill(x1,0,x2,248,COLOR1[0],COLOR1[1],COLOR1[2]); //RED
        graphics_rectangle_fill(x2,0,x3,248,COLOR2[0],COLOR2[1],COLOR2[2]); //ORANGE
        graphics_rectangle_fill(x3,0,x4,248,COLOR3[0],COLOR3[1],COLOR3[2]); //YELLOW
        graphics_rectangle_fill(x4,0,x5,248,COLOR4[0],COLOR4[1],COLOR4[2]); //GREEN
        graphics_rectangle_fill(x5,0,x6,248,COLOR5[0],COLOR5[1],COLOR5[2]); //BLUE
        graphics_rectangle_fill(x6,0,x7,248,COLOR6[0],COLOR6[1],COLOR6[2]); //INDIGO
        graphics_rectangle_fill(x7,0,x8,248,COLOR7[0],COLOR7[1],COLOR7[2]); //VIOLET/PURPLE
        
        //Swap all the Red values of the colors to the next line
        int old = COLOR1[0];
        COLOR1[0] = COLOR2[0];
        COLOR2[0] = COLOR3[0];
        COLOR3[0] = COLOR4[0];
        COLOR4[0] = COLOR5[0];
        COLOR5[0] = COLOR6[0];
        COLOR6[0] = COLOR7[0];
        COLOR7[0] = old;
        
        //Swap all the Green values of the colors to the next line
        old = COLOR1[1];
        COLOR1[1] = COLOR2[1];
        COLOR2[1] = COLOR3[1];
        COLOR3[1] = COLOR4[1];
        COLOR4[1] = COLOR5[1];
        COLOR5[1] = COLOR6[1];
        COLOR6[1] = COLOR7[1];
        COLOR7[1] = old;
        
        //Swap all the Blue values of the colors to the next line
        old = COLOR1[2];
        COLOR1[2] = COLOR2[2];
        COLOR2[2] = COLOR3[2];
        COLOR3[2] = COLOR4[2];
        COLOR4[2] = COLOR5[2];
        COLOR5[2] = COLOR6[2];
        COLOR6[2] = COLOR7[2];
        COLOR7[2] = old;
        
        graphics_update();
        msleep(10);
        time+=100;
    }
    
    //Close everything
    //WARNING: DON'T CLOSE THE PROGRAM BEFORE ANIMATION IS FINISHED.
    thread_destroy(playStart);
    graphics_close();
    
}

int main()
{
    printf("Trying to connect to iRobot Create... \n");
    create_connect();
    
    //Turn on create FULL mode so that the sensors don't lock up the create to protect it from falling
    create_full();
    
    
    console_clear();
    printf("Connection Successful! \n");
    msleep(frameDelay);
    console_clear();
    
    testBattery();
    testBumpers();
    testCliffs();
    testLightTouch();
    testWheelDrop();
    testWheels();
    create_disconnect();
    finishTest();
    
    return 0;
}

