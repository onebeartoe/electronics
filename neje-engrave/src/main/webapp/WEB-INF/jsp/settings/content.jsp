
    <div class="copyspace">
        <h1>Settings</h1>
        
        <div class="saveMessages">
            ${saveMessages}
        </div>
        
        <form action="save" method="POST">
            <div class="featuredProject">
                <h3> Base Directory:</h3>
                <p>		
                    ${baseDir}
                </p>

                <h3 class="settingsSaveButton">EzGraver CLI Executable Path:</h3>

                <p>		
                    <input name="EzGraverCli" type="text" value="${EzGraverCli}" size="80"/>
                </p>

                <input type="submit" class="settingsSaveButton" value="Save"/>
            </div>
        </form>
            
        <br class="clearingBreak">
    </div>

