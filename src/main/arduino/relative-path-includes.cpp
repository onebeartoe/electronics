
// TODO: REMOVE THIS
int keyboardShortcutssss = 5;

// TODO: MOVE THIS TO AND USE THE VERSION IN A CLASS!
uint8_t NO_MODIFIER = 0;





//-------------------------------------------------
// Arduino #include relative paths; pound include baby!
//
// TODO: upvote this answer on stackexchange
//
// https://arduino.stackexchange.com/a/9575/25692
//
// Be sure to define the  project's root folder in client .h files:
//#define PROJECT_ROOT C:\home\owner\versioning\github\electronics\src\main\arduino\

//Define a relative-to-absolute macro 'transformation' :
#define TO_STRING(s) #s
#define ABSOLUTE_PATH(root, relative_path) TO_STRING(root\relative_path)
#define RELATIVE_PATH(library) ABSOLUTE_PATH(PROJECT_ROOT, library)

// Include your files using the relative path :
//#include RELATIVE_PATH(keyboard-shortcuts\keyboard-shortcuts\KeyboardShortcuts.h)
//#include RELATIVE_PATH(another\file\relative\path.h)
//-------------------------------------------------
