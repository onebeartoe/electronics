
const int PARSE_INTS_MAX_ARGS = 5;

/**
  * this represents teh number of decimal coluns the id can have.  in this case it the IDs are 1-117, so the number of columns is 3
  */
const int INT_COLUMNS_COUNT = 3;

const int MAX_COMMA_COUNT = PARSE_INTS_MAX_ARGS - 1;

// This is the maximum size of a command string.
const int CHAR_BUFFER_SIZE = (PARSE_INTS_MAX_ARGS * INT_COLUMNS_COUNT) + MAX_COMMA_COUNT;

int parseIntsArray[PARSE_INTS_MAX_ARGS];

int parseIntsArrayLength;

void parseInts(String command)
{
  // given: String command

  parseIntsArrayLength = 0;
  
  int numArgs = 0;
  
  int beginIdx = 0;
  int idx = command.indexOf(",");
  
  String arg;
  char charBuffer[CHAR_BUFFER_SIZE];
  
  while (idx != -1)
  {
      arg = command.substring(beginIdx, idx);
      arg.toCharArray(charBuffer, CHAR_BUFFER_SIZE);
  
      // add error handling for atoi:
      parseIntsArray[numArgs++] = atoi(charBuffer);

      parseIntsArrayLength++;
      
      beginIdx = idx + 1;
      idx = command.indexOf(",", beginIdx);
  }

  arg = command.substring(beginIdx);
  arg.toCharArray(charBuffer, CHAR_BUFFER_SIZE);
  parseIntsArray[numArgs] = atoi(charBuffer);
  parseIntsArrayLength++;
//  data[numArgs++] = command.substring(beginIdx);  
}

