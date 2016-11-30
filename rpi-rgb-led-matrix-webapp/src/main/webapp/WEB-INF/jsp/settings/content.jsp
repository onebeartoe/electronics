
    <div class="copyspace">
        <h3>Settings</h3>
        
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
            
            <input type="submit" class="settingsSaveButton" value="Save"/>
        </div>
        </form>
            
        <br class="clearingBreak">
    </div>

