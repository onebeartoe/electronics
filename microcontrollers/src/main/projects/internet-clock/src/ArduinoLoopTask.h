
#ifndef onebeartoe_ArduinoLoopTask_h
#define onebeartoe_ArduinoLoopTask_h

class ArduinoLoopTask
{
    public:
  
        long previousMillis;
        
        /**
         * This is the execution delay in milliseconds.
         */
        long interval = 10 * 1000; // ten seconds
        
        virtual void oneLoop();
 
//        virtual void loop();
        
        /**
         * Call this method in the Arduino's sketch's loop() function.
         */
// this was just added
virtual      
        void loop()
        {
            unsigned long currentMillis = millis();
 
            if(currentMillis - previousMillis > interval) 
            {
                // save the last time you blinked the LED 
                previousMillis = currentMillis;
                
                oneLoop();
            }
        }
};

#endif
