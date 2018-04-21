
    <script type="text/javascript" src="<%= request.getContextPath() %>/controls/controls.js"></script>

    <script type="text/javascript" src="<%= request.getContextPath() %>/controls/filesystem.js"></script>

    <script type="text/javascript" src="<%= request.getContextPath() %>/controls/modal.js"></script>

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
            
            <div id="filesystem" class="logs" style="">This is the default text for the filesystem div.</div>
            
            <br/>
            <br/>
            
            
            
<!-- Trigger/Open The Modal -->
<button id="uploadButton">Upload Image</button>

<!-- The Modal -->
<div id="uploadModal" class="modal">

  <!-- Modal content -->
  <div class="modal-content">
    <span class="close">&times;</span>
    
    <p>Upload an image to engrave:</p>
    
        <form action="../filesystem/upload" method="POST" enctype="multipart/form-data">
            
            <input name="upload" type="file"/>
            
            <br/>
            <br/>
            
            <input type="submit" class="uploadButton" value="Upload"/>
        </form>    
    
  </div>

</div>            

            <button onclick="resetEngraver('reset')" >Create Directory</button>
            
            
            <div id="logs" class="logs" style=""/>
        </div>
            
        <br class="clearingBreak">
    </div>

            
<script type="text/javascript">
//  alert("hi message");
    updateFilesystem("/");
                
    // Get the modal
    var modal = document.getElementById('uploadModal');

    // Get the button that opens the modal
    var btn = document.getElementById("uploadButton");

    // Get the <span> element that closes the modal
    var span = document.getElementsByClassName("close")[0];

    // When the user clicks on the button, open the modal 
    btn.onclick = function() {
        modal.style.display = "block";
    }

    // When the user clicks on <span> (x), close the modal
    span.onclick = function() {
        modal.style.display = "none";
    }

    // When the user clicks anywhere outside of the modal, close it
    window.onclick = function(event) 
    {
        if (event.target == modal) 
        {
            modal.style.display = "none";
        }
    }                
</script>
