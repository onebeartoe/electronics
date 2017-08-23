
class NetbeansIdeShortcuts : public IdeShortcuts //, public OtherExtendedClass
{
    private:

        KeyboardShortcut openResourceShortcut;
        
        void releaseKey()
        {
            // this releases the key (otherwise it is held down!)
            TrinketKeyboard.pressKey(0, 0);
        }

    public:

        KeyboardShortcut gotoLastEdit()
        {
//TODO: add the actual key codes            
            
            return openResourceShortcut;
        }
        
        virtual
        KeyboardShortcut openType()
        {
            KeyboardShortcut openType;

            openType.keys[0] = 7;
            openType.keyCount = 1;

            // alt + shift + o
            TrinketKeyboard.pressKey(KEYCODE_RIGHT_ALT, KEYCODE_RIGHT_SHIFT, KEYCODE_O);
            
            releaseKey();

            return openType;
        }

        virtual KeyboardShortcut openResource()
        {
TrinketKeyboard.print("Hello World!");

            releaseKey();

            return openResourceShortcut;
        }
        
        virtual KeyboardShortcut findInProjects()
        {
TrinketKeyboard.print("key 3");

            // Ctrl + shift + f
//            TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_CONTROL, KEYCODE_MOD_RIGHT_SHIFT, KEYCODE_F);
//            TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_CONTROL, KEYCODE_RIGHT_SHIFT, KEYCODE_F);
//            TrinketKeyboard.pressKey(KEYCODE_LEFT_CONTROL, KEYCODE_RIGHT_SHIFT, KEYCODE_F);
            
            releaseKey();
            
            return openResourceShortcut;
        }
        
        virtual KeyboardShortcut organizeImports()
        {
TrinketKeyboard.print("key 4");            

            releaseKey();

            return openResourceShortcut;
        }
};
