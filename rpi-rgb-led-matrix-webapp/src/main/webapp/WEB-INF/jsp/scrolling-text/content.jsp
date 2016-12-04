
    <div class="copyspace">
        <h1>Scrolling Text</h1>
        
        <div class="saveMessages">
            ${responseMessages}
        </div>
        
        <form action="update" method="POST">
        <div class="featuredProject">
            <h3>text:</h3>
            
            <p>		
                <input name="text" type="text" value="${ledMatrix.scrollingText}" size="60"/>
            </p>
            
            <input type="submit" class="settingsSaveButton" value="Save"/>
        </div>
            
        </form>
            
        <br class="clearingBreak">
    </div>

