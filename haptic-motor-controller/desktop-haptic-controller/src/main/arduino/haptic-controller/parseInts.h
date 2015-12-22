
const int PARSE_INTS_MAX_ARGS = 5;

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
  char charBuffer[16];
  
  while (idx != -1)
  {
      arg = command.substring(beginIdx, idx);
      arg.toCharArray(charBuffer, 16);
  
      // add error handling for atoi:
      parseIntsArray[numArgs++] = atoi(charBuffer);

      parseIntsArrayLength++;
      
      beginIdx = idx + 1;
      idx = command.indexOf(",", beginIdx);
  }

  arg = command.substring(beginIdx);
  arg.toCharArray(charBuffer, 16);
  parseIntsArray[numArgs] = atoi(charBuffer);
  parseIntsArrayLength++;
//  data[numArgs++] = command.substring(beginIdx);  
}

