
/**
 * This is a port of the Wyolum Badger Album sketch from ePaper display to an
 * Adafruit TFT Feather Wing.
 */

#include <SD.h>

/**
 * One day, hopefully, Arduino will support relative filesystem paths.
 */
#include "C:\home\owner\versioning\github\electronics\src\main\arduino\adafruit\feather-wings\ILI9341-tft\swiper\swiper\board-compatibility.h"

const char* ROOT_DIR = "ALBUM/";
char path[20];

long lastWakeTime; //reset with every interaction

int current_dir = -1;
int current_wif = 0;
int n_dir;
int n_wif;

File root;
File cwd;
File wif;

int count_wifs(File dir)
{
  File f;
  int out = 0;

  if(dir.isDirectory()){
    dir.rewindDirectory();
    while(f = dir.openNextFile()){
      // Serial.println(f.name());
      if(isWIF(f)){
	out++;
      }
      f.close();
    }
  }
  return out;
}

//TODO: is any of this function used by the image_brower app?  Or is it all
//      unused carry over from Album.ino
void display()
{
//  digitalWrite(LED_PIN, LOW);
//  ereader.spi_attach();  
  erase_img(wif); // wif is still the old file
//  wif.close();    // keep close and open calls in the same spot
  get_wif_path(); // store new wif name in path
  wif = SD.open(path); 
  draw_img(wif); // draw new wif
//  uint16_t start = millis();
//   ereader.spi_detach(); // this call takes .8 seconds to execute!
   
//  if(true)
//  {
//    for(int ii=0; ii<4; ii++)
//    {
//      digitalWrite(LED_PIN, ii % 2 == 0 );
//      if(ii < 3)
//      {
//	delay(25);
//      }
//    }
//  }
}

void draw_img(File imgFile)
{
  /*
    int temperature = S5813A.read();
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" Celcius");
  */

  //*** maybe need to ensure clock is ok for EPD

  reset_wif();
//  ereader.EPD->frame_cb(0, SD_reader, EPD_inverse);
  reset_wif();
//  ereader.EPD->frame_cb(0, SD_reader, EPD_normal);
//  ereader.EPD->end();   // power down the EPD panel
  
}

void erase_img(File imgFile)
{

  //*** maybe need to ensure clock is ok for EPD

//  ereader.EPD->begin(); // power up the EPD panel
  reset_wif();
//  ereader.EPD->frame_cb(0, SD_reader, EPD_compensate);
  reset_wif();
//  ereader.EPD->frame_cb(0, SD_reader, EPD_white);
}

/*
  store current working directory int path
 */
char *get_cwd_path()
{
  int n = strlen(ROOT_DIR);
  for(int i=0; i < n; i++){
    path[i] = ROOT_DIR[i];
  }
  path[n - 1] = '/';
  path[n] = 'A' + current_dir;
  path[n+1] = '/';
  path[n+2] = 0;
  // Serial.print("get_cwd_path path:");
  // Serial.println(path);
}

/*
  store current wif file into path
 */
void *get_wif_path()
{
  get_cwd_path();
  int n = strlen(path);

  path[n] = 'A' + current_wif;
  path[n + 1] = 0;
  // Serial.print("get_wif_path path:");
  // Serial.println(path);

  strcat(path, ".WIF");
  if(!SD.exists(path))
  {
    char *msg = "FILE NOT FOUND";
    
//TODO: display the message on the TFT display
    
//    ereader.put_ascii(10, 50, msg, true);
//    ereader.put_ascii(20, 50, path, true);
//    ereader.show();

    Serial.println(msg);
  }
}

bool isWIF(File f)
{
  char *name = f.name();
  bool out = false;
  int n = strlen(name);

  if(!f.isDirectory())
  {
    out =  (name[n-4] == '.' &&
	    name[n-3] == 'W' &&
	    name[n-2] == 'I' &&
	    name[n-1] == 'F');
  }
  return out;
}

void loop() 
{
    bool update_needed = false;
    
//  int pulse = millis() % (2000 * (2 - ereader.attached));
//  if(pulse  < 50){
//    digitalWrite(LED_PIN, HIGH);
//  }
//  else if(150 < pulse && pulse < 250){
//    digitalWrite(LED_PIN, HIGH);
//  }
//  else{
//    digitalWrite(LED_PIN, LOW);
//  }
    
  long current = millis();
  
//  if ((current - lastWakeTime) > FOCUSTIME && ereader.attached){
//    digitalWrite(LED_PIN, LOW);
//    //ereader.spi_detach(); // this call takes .8 seconds to execute!
//    // Serial.println("ereader detached");
//  }
//  else if ((current - lastWakeTime) > AWAKETIME){
//    //   Serial.println("should sleep");
//    //goToSleep();
//  }

  // ser_interact();
  if(false)//analogRead(MODE_PIN) > 512)
  {
//    Serial.println("Mode");
    prev_wif();
    update_needed = true;
  }
  if(false)//digitalRead(SEL_PIN))
  {
//    Serial.println("Sel");
    next_wif();
    update_needed = true;
  }
  if(false)//digitalRead(UP_PIN))
  {
//    Serial.println("Up");
    prev_dir();
    update_needed = true;
  }
  if(false)//digitalRead(DOWN_PIN))
  {
//     Serial.println("down");
    next_dir();
    update_needed = true;
  }
  
  if(update_needed)
  {
    lastWakeTime = current;
    display();
  }
  else
  {
      
  }
}

void next_dir()
{
  current_dir++;
  current_dir %= n_dir;
  open_cwd();
  // if(current_wif > n_wif - 1){
  current_wif = 0;
  //}
}

/*
  increment image number by one
 */
void next_wif()
{
  current_wif++;
  current_wif %= n_wif;
}

void open_cwd()
{
//TODO: can the call to SD.begin() be mored back to the setup() function, since the ePaper display is not used in this project?  
  SD.begin(SD_CS); // hack to wake SD up after detach.  returns false but seems to work.
  
  get_cwd_path(); // copy current dir path to path
  cwd.close();
  cwd = SD.open(path);
  n_wif = count_wifs(cwd);
}

void prev_dir()
{
  current_dir--;
  if(current_dir < 0){
    current_dir = n_dir - 1;
  }
  open_cwd();
  //if(current_wif > n_wif - 1){
  current_wif = 0;
  //}
}

/*
  decrement image number by one
 */
void prev_wif()
{
  current_wif--;
  if(current_wif < 0){
    current_wif = n_wif - 1;
  }
}

void reset_wif()
{
  wif.seek(0);
  
//TODO: does the width and height need adjusting for the TFT, or is it just the ePaper?
//  my_height = (unsigned short)wif.read();
//  my_height += (unsigned short)wif.read() << 8;
//  my_width = (unsigned short)wif.read();
//  my_width += (unsigned short)wif.read() << 8;
}

void setup() 
{
  int n = strlen(ROOT_DIR);
  bool done = false;

  // Serial.begin(115200);
  // Serial.println("WyoLum, LLC 2013");
  // Serial.println("Buy Open Source Hardware!");
//  ereader.setup(EPD_2_7); // starts SD
//  pinMode(UP_PIN, INPUT);
//  pinMode(DOWN_PIN, INPUT);
//  pinMode(SEL_PIN, INPUT);
//  pinMode(MODE_PIN, INPUT);
//  pinMode(LED_PIN, OUTPUT);
  root = SD.open(ROOT_DIR);
  if(!root)
  {
    Serial.print("Root not found:\n    ");
    Serial.println(ROOT_DIR);
//    ereader.error(SD_ERROR_CODE);
  }
  get_cwd_path();

  n_dir = 0;
  n = strlen(ROOT_DIR); // ROOT_DIR ends with '/'

  for(n_dir=0; !done; n_dir++){
    path[n] = 'A' + n_dir;
    if(SD.exists(path)){
    }
    else{
      done = true;
      n_dir--; // overshot by one
    }
  }
  root.close();
  current_dir = -1;
  next_dir();
  display();

//  for(int ii=0; ii < 3; ii++){
//    digitalWrite(LED_PIN, HIGH);
//    delay(100);
//    digitalWrite(LED_PIN, LOW);
//    delay(100);
//  }
  // ereader.spi_detach();
}