

    <div class="copyspace">
        
        
        <div class="featuredProject">
            <h3>
                Neje Print
            
                <button onclick="resetEngraver('reset')" >Reset</button>
            </h3>
        </div>
        
        <div class="featuredProject">
            <h3>Current File</h3>
            
            <p>		
                File: ${currentFile}
                
                
            </p>
            
            <button onclick="resetEngraver('reset')" >Start</button>

            <button onclick="resetEngraver('reset')" >Pause</button>
        </div>
            
        <div class="featuredProject">
            <h3>Filesystem</h3>
            
            <p>		
                 &nbsp;
            </p>
            
            <script type="text/javascript" src="<%= request.getContextPath() %>/controls/controls.js"></script>

            
            <button onclick="resetEngraver('reset')" >Upload Image</button>

            <button onclick="resetEngraver('reset')" >Create Directory</button>
            
            
            <div id="logs" class="logs" style="">
        </div>
            
        <br class="clearingBreak">
    </div>
