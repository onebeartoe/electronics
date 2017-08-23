
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

void erase_img(File imgFile);
void draw_img(File imgFile);
void *get_wif_path();
void open_cwd();
void reset_wif();

//TODO: is any of this function used by the image_brower app?  Or is it all
//      unused carry over from Album.ino
void display()
{
  erase_img(wif); // wif is still the old file
// had this commented while working after the refactor  
  wif.close();    // keep close and open calls in the same spot
  
  get_wif_path(); // store new wif name in path
  wif = SD.open(path); 
  draw_img(wif); // draw new wif
}

void draw_img(File imageFile)
{    
    Serial.print("bmp path: ");
    Serial.println(path);

    
    bmpDraw(path, 0,0);
    tft.setCursor(5,5);
    tft.print(path);

//TODO: are these still needed?    
  reset_wif();
  reset_wif();  
}

void erase_img(File imgFile)
{
//TODO: are these still needed?    
  reset_wif();
  reset_wif();
}

/*
  store current working directory int path
 */
char * get_cwd_path()
{
    int n = strlen(ROOT_DIR);
    for(int i=0; i < n; i++)
    {
      path[i] = ROOT_DIR[i];
    }

    path[n - 1] = '/';
    path[n] = 'A' + current_dir;
    path[n+1] = '/';
    path[n+2] = 0;
  
   Serial.print("get_cwd_path path:");
   Serial.println(path);
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

    strcat(path, ".bmp");
//  strcat(path, ".WIF");
  if(!SD.exists(path))
  {
    char *msg = "FILE NOT FOUND";
    
//TODO: display the message on the TFT display

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

int countWifs(File dir)
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

void next_dir()
{
  current_dir++;
  current_dir %= n_dir;
  open_cwd();
  
  current_wif = 0;
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
//TODO: can the call to SD.begin() be moved back to the setup() function, since the ePaper display is not used in this project?  
  SD.begin(SD_CS); // hack to wake SD up after detach.  returns false but seems to work.
  
  get_cwd_path(); // copy current dir path to path
  cwd.close();
  cwd = SD.open(path);
  n_wif = countWifs(cwd);
}

void prev_dir()
{
  current_dir--;
  if(current_dir < 0){
    current_dir = n_dir - 1;
  }
  open_cwd();

  current_wif = 0;
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

void setupSdCard()
{
  int n = strlen(ROOT_DIR);
  bool done = false;

  root = SD.open(ROOT_DIR);
  if(!root)
  {
    Serial.print("Root not found:\n    ");
    Serial.println(ROOT_DIR);
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
}