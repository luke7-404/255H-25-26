#include "menu.hpp" // Include header file

using namespace std; // Using standard for iostream

// Static member variable initializations
bool LCD_Menu::isBlue = false; // Tracks if blue auton screen is active
bool LCD_Menu::isDeconstructed = false; // Tracks if menu system is destroyed

uint8_t LCD_Menu::viewing = 0; // Tracks screen being viewed
lv_obj_t* LCD_Menu::tabBar = nullptr; // Main tab bar container
lv_obj_t* LCD_Menu::redAuton = nullptr; // Red auton screen container
lv_obj_t* LCD_Menu::blueAuton = nullptr; // Blue auton screen container
lv_obj_t* LCD_Menu::systemScreen = nullptr; // System info screen container
lv_obj_t* LCD_Menu::selectedAutonLabel = nullptr; // Label for displaying selected autonomous routine
lv_obj_t* LCD_Menu::telemetryLabel = nullptr; // Label object for printing diagnostics
lv_timer_t* LCD_Menu::screenTimer = nullptr; // Timer for updating system screen
std::vector<lv_obj_t*> LCD_Menu::autonButton(6, nullptr); // Vector of auton selection buttons


// Constructor - Initializes the LCD menu system
LCD_Menu::LCD_Menu() {
  cout << "LCD Menu Object was created" << endl;
  lv_init(); // Initialize LVGL
}

// Destructor - Cleans up LCD menu system
LCD_Menu::~LCD_Menu(){
  cout << "LCD Menu Object was destroyed" << endl;
  lv_obj_clean(lv_scr_act()); // Remove all objects from screen
  lv_deinit(); // Deinitialize LVGL
  isDeconstructed = true; // Signal menu system destruction
}

// -------------------------------- SCREEN UTIL -------------------------------- //

void LCD_Menu::init() {
  // Create the main tab bar and buttons
  this->makeButtons();
  screenTimer = lv_timer_create(timerHandler_STATIC, 200, nullptr); // Create a timer to update the screen
  lv_event_send(redAuton, LV_EVENT_CLICKED, NULL); // Send a click event to the red auton tab
}

void LCD_Menu::makeButtons() {
    
  LV_IMG_DECLARE(bg); // declare the file that holds the background image
  // Create a tab view with tabs at the top and a height of 26 pixels
  tabBar = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 26);
  // Set the background color of the tab view to blue
  lv_obj_set_style_bg_img_src(tabBar, &bg, LV_PART_MAIN);
  
  // Get the tab buttons container (btnm)
  lv_obj_t* btnm = lv_tabview_get_tab_btns(tabBar);
  
  // Style the tab buttons container
  lv_obj_set_style_bg_color(btnm, BLACK, LV_PART_MAIN);
  lv_obj_set_style_bg_color(btnm, BLACK, LV_PART_ITEMS);
  lv_obj_set_style_text_color(btnm, lv_color_white(), LV_PART_MAIN);

  // Add tabs to the tab view
  redAuton = lv_tabview_add_tab(tabBar, "RED Auton");
  blueAuton = lv_tabview_add_tab(tabBar, "BLUE Auton");
  systemScreen = lv_tabview_add_tab(tabBar, "System");

  // Add an event callback to the tab bar to handle tab clicks
  lv_obj_add_event_cb(tabBar, tabHandler_STATIC, LV_EVENT_CLICKED, nullptr);

  // Add event callbacks to each tab to handle tab-specific clicks
  lv_obj_add_event_cb(redAuton, redAuton_eventHandler_STATIC, LV_EVENT_CLICKED, nullptr);
  lv_obj_add_event_cb(blueAuton, blueAuton_eventHandler_STATIC, LV_EVENT_CLICKED, nullptr);
  lv_obj_add_event_cb(systemScreen, system_eventHandler_STATIC, LV_EVENT_CLICKED, nullptr);

  // Set the active tab to the last viewed tab without animation
  lv_tabview_set_act(tabBar, viewing, LV_ANIM_OFF);
}

void LCD_Menu::screenClear() {
  viewing = lv_tabview_get_tab_act(tabBar); // Save the index of viewed tab
  
    
  // Loop through the auton buttons
  for (uint8_t i = 0; i < autonButton.size(); i++) { 
    if(autonButton[i] != nullptr) { // If the button exists
      //lv_obj_clean(autonButton[i]); // Delete the button
      lv_obj_del(autonButton[i]); // Remove the button from the screen
      autonButton[i] = nullptr; // Set the button pointer to null
    }
  }

  if(selectedAutonLabel != nullptr) {
    lv_obj_del(selectedAutonLabel);
    selectedAutonLabel = nullptr;
  }

  if(telemetryLabel != nullptr) {
    lv_obj_del(telemetryLabel);
    telemetryLabel = nullptr;
  }
}

void LCD_Menu::tabHandler_STATIC(lv_event_t* e) {
  // Get the tab view object from the event
  lv_obj_t* tabview = lv_event_get_current_target(e);
  // Get the index of the currently active tab
  uint16_t activeTab = lv_tabview_get_tab_act(tabview);

  // Handle the event based on the active tab
  switch(activeTab) {
    case 0:
        // Send a click event to the redAuton tab
        lv_event_send(redAuton, LV_EVENT_CLICKED, NULL);
      break;
    case 1:
        // Send a click event to the blueAuton tab
        lv_event_send(blueAuton, LV_EVENT_CLICKED, NULL);
      break;
    case 2:
        // Send a click event to the systemScreen tab
        lv_event_send(systemScreen, LV_EVENT_CLICKED, NULL);
      break;
  }
}

// -------------------------------- AUTON FUNC -------------------------------- //

// Prints out buttons for auton selection
void LCD_Menu::printAuton(lv_color_t color) {
  screenClear(); // Clear the screen

  uint16_t start_X1, start_Y1, start_X2, start_Y2;

  start_X1 = 16; // Top Left corner X coordinate
  start_Y1 = 32; // Top Left corner Y coordinate
  start_X2 = 130; // Bottom Right corner X coordinate
  start_Y2 = 93.75; // Bottom Right corner Y coordinate
  lv_obj_t* btnLabel; // Button label object

  // Loop to create 6 buttons
  for(uint8_t i = 1; i <= 6; i++) {
    // Adjust the position for even-numbered buttons
    if (i % 2 == 0) {
      start_X1 += 121;
      start_X2 += 121;
    } 
    // Adjust the position for odd-numbered buttons (except the first one)
    else if ((i % 2 > 0) && i != 1) {
      start_X1 -= 121;
      start_X2 -= 121;
      start_Y1 += 69;
      start_Y2 += 69;
    }
    
    // Create a button
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn, start_X2 - start_X1, start_Y2 - start_Y1);
    // Set button background color to black
    lv_obj_set_style_bg_color(btn, BLACK, 0);
    // Align the button to the top-left corner with the specified offsets
    lv_obj_align(btn, LV_ALIGN_TOP_LEFT, start_X1, start_Y1);

    // Add an event callback to the button to handle clicks
    lv_obj_add_event_cb(btn, auton_eventHandler_STATIC, LV_EVENT_CLICKED, nullptr);
    
    // Create a label for the button
    btnLabel = lv_label_create(btn);
    if(i == 1){
      lv_label_set_text(btnLabel, "Skills");
      lv_obj_set_style_text_color(btnLabel, SKILLS_GREEN, 0);
    } 
    else if(i == 2) lv_label_set_text(btnLabel, "AWP1");
    else if(i == 3) lv_label_set_text(btnLabel, "AWP2");
    else if(i == 4) lv_label_set_text(btnLabel, "1");
    else if(i == 5) lv_label_set_text(btnLabel, "2");
    else if(i == 6) lv_label_set_text(btnLabel, "3");

    if (i != 1) lv_obj_set_style_text_color(btnLabel, color, 0);
    lv_obj_align(btnLabel, LV_ALIGN_CENTER, 0, 0);
    
    // Store the button in the autonButton array
    autonButton[i-1] = btn;
  }
}

void LCD_Menu::redAuton_eventHandler_STATIC(lv_event_t* e) {
  // Clear the screen
  screenClear();
  // Display the red autonomous routine
  printAuton(AUTON_RED);
  // Set the flag indicating the current tab is not blue
  isBlue = false;
}

void LCD_Menu::blueAuton_eventHandler_STATIC(lv_event_t* e) {
  // Clear the screen
  screenClear();
  // Display the blue autonomous routine with options
  printAuton(AUTON_BLUE);
  // Set the flag indicating the current tab is blue
  isBlue = true;
}

// Helper variable that holds values for the auton ID
char checkout;

// Function to get the current autonomous ID
char LCD_Menu::getAutonID() {
  return checkout;
}

// Helper variable that holds the name of the current autonomous routine
string checkoutName;

// Function to get the name of the current autonomous routine
std::string LCD_Menu::getAutonName() {
  return checkoutName;
}

void LCD_Menu::auton_eventHandler_STATIC(lv_event_t* e) {
  // Get the button object from the event
  lv_obj_t* btn = lv_event_get_target(e);

  // Get the first child (label) of the button
  lv_obj_t* label = lv_obj_get_child(btn, 0);

  // Get the text from the label
  const char* buttonText = lv_label_get_text(label);

  // If a label for the selected auton already exists, delete it
  if(selectedAutonLabel == nullptr) {
    selectedAutonLabel = lv_label_create(lv_scr_act());
  }
  // Create a new label to display the selected auton
  lv_label_set_text_fmt(selectedAutonLabel, "Selected: %s", buttonText);
  lv_obj_align(selectedAutonLabel, LV_ALIGN_TOP_LEFT, 286, 50);
  
  // Determine which auton was selected based on the label text
  if(strcmp(buttonText, "Skills") == 0) {
    checkout = 1;
    checkoutName = "Skills";
  } else if(strcmp(buttonText, "AWP1") == 0) {
    checkout = 2;
    checkoutName = "AWP1";
  } else if(strcmp(buttonText, "AWP2") == 0) {
    checkout = 3;
    checkoutName = "AWP2";
  } else if(strcmp(buttonText, "1") == 0) {
    checkout = 4;
    checkoutName = "1";
  } else if(strcmp(buttonText, "2") == 0) {
    checkout = 5;
    checkoutName = "2";
  } else if(strcmp(buttonText, "3") == 0) {
    checkout = 6;
    checkoutName = "3";
  } else checkout = 7;
  
  // Return the ASCII representation of the char
  checkout = isBlue ? (checkout + 64) : (checkout + 48);
}

// -------------------------------- SYSTEM FUNC -------------------------------- //

void LCD_Menu::printPose() {
  // Create a text string with the current pose of the drivetrain
  char text[100];
  std::sprintf(text, "X: %.2f\nY: %.2f\nHeading: %.2f", chassis.odom_x_get(), chassis.odom_y_get(), chassis.drive_imu_get());
  // Set the text of the label
  lv_label_set_text(telemetryLabel, text);
  // Align the label to the top-left corner with the specified offsets
  lv_obj_align(telemetryLabel, LV_ALIGN_TOP_LEFT, 286, 70);
  lv_obj_set_style_text_font(telemetryLabel, &lv_font_montserrat_24, 0);
}


// A function that will iterate through an array of type motor and print the motors and multiple attributes of them
void LCD_Menu::listMotors() {

  std::vector<pros::Motor> motors = {};
  /*std::vector<pros::Motor> leftChassis = chassis.left_motors();
  std::vector<pros::Motor> rightChassis = chassis.right_motors();*/
  std::stringstream motorData; // Create a string to store the motor data


  // Iterate through the ports of the motor
  for (short i = 0; i < motors.size(); i++) {
    // Create a string with the individual motor data
    motorData << "Motor " << motors[i].get_port() << ": "
              << motors[i].get_temperature() << ", "
              << motors[i].get_torque() << ", " 
              << motors[i].get_voltage() / 1000.0 << ", "
              << motors[i].get_efficiency() << "\n";
  }

  // Set the text of the label
  lv_label_set_text(telemetryLabel, motorData.str().c_str());
  // Align the label to the top-left corner with the specified offsets
  lv_obj_align(telemetryLabel, LV_ALIGN_TOP_MID, 0, 30);
  lv_obj_set_style_text_font(telemetryLabel, &lv_font_montserrat_16, 0);
}

void LCD_Menu::printSystem() {
  // SD Card is inserted?, file created?, current file number
  // Create a text string with the diagnostics information for the motors
  listMotors();
  /*auto text = listMotors().c_str();
  // Set the text of the label
  lv_label_set_text(telemetryLabel, text);
  // Align the label to the top-left corner with the specified offsets
  lv_obj_align(telemetryLabel, LV_ALIGN_TOP_MID, 0, 70);
  lv_obj_set_style_text_font(telemetryLabel, &lv_font_montserrat_16, 0);*/
}

void LCD_Menu::system_eventHandler_STATIC(lv_event_t* e) {
  // Clear the screen
  screenClear();
}

void LCD_Menu::timerHandler_STATIC(lv_timer_t* timer) {
  if(telemetryLabel == nullptr){
   telemetryLabel = lv_label_create(lv_scr_act());
  }

  if(viewing != 2) {
    printPose();
  } else {
    printSystem();
  }
}