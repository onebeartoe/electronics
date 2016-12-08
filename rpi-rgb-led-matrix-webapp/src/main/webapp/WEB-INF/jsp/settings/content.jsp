
    <div class="copyspace">
        <h1>Settings</h1>
        
        <div class="saveMessages">
            ${saveMessages}
        </div>
        
        <form action="save" method="POST">
        <div class="featuredProject">
            <h3>Animations Directory:</h3>
            <p>		
                <input name="animationsDirectory" type="text" value="${ledMatrix.animationsPath}" size="60"/>
            </p>
        </div>
            
        <div class="featuredProject">
            <h3 class="settingsSaveButton">Still Images Directory:</h3>
            
            <p>		
                <input name="stillImagesDirectory" type="text" value="${ledMatrix.stillImagesPath}" size="60"/>
            </p>
        </div>
            
        <div>
            <h3 class="settingsSaveButton">rpi-rgb-led-matrix Home:</h3>
            
            <p>		
                <input name="rpiRgbLedMatrixHome" type="text" value="${ledMatrix.rpiRgbLedMatrixHome}" size="60"/>
            </p>
        </div>
            
        <div>
            <h3>Command Line Flags</h3>
            
            <p>
                <input name="commandLineFlags" type="text" value="${commandLineFlags}" class="jkljj"/>
            </p>
            
            <input type="submit" class="settingsSaveButton" value="Save"/>
        </div>
        </form>
            
        <br class="clearingBreak">
    </div>

