
    <script type="text/javascript" src="<%= request.getContextPath() %>/controls/controls.js"></script>

    <script type="text/javascript" src="<%= request.getContextPath() %>/controls/filesystem.js"></script>
    
    <div class="copyspace">                
        <div class="featuredProject">            
            <div class ="sideBySide">
                <div class="sideBySideLeft" style="width: 45%;">
                    <h3>
                        Neje Print
                                                
                        <button onclick="resetEngraver()" >Reset</button>
                    </h3>
                </div>

                <div class="sideBySideRight" style="width: 45%;">
                    <div id="resetLog" class="logs">
                    </div>                        
                </div>
            </div>
        </div>
        
        <div class="featuredProject">
            <h3>Current File</h3>
                <p id="currentFile">		
                    File: ${currentFile}                
                </p>  
            
            	<div class ="sideBySide">
                    <div class="sideBySideLeft" style="width: 45%;">
                        <button onclick="startEngraving()" >Start</button>

                        <button onclick="pauseEngraver()" >Pause</button>                                    
                    </div>
                    
                    <div class="sideBySideRight" style="width: 45%;">
                        <img src=http://192.168.1.113:8081/ border=0 width=75%>
                        
                        <div id="logs" class="logs">
                        </div>                        
                    </div>
                </div>          
        </div>
           
        <br class="clearingBreak">
            
        <div class="featuredProject">
            <h3>Filesystem ${subpath}</h3>
            
            <div id="filesystem" 
                 class="logs" 
                 style="">This is the default text for the filesystem div.</div>

            <br/>
            <br/>

            <div class="filesystemButtons">
            
                <button id="uploadButton">Upload to Filesystem</button>

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

                <button id="createDirButton" >Create Directory</button>

                <div id="createDirModal" class="modal">
                    <!-- Modal content -->
                    <div class="modal-content">
                        <span id="createDirSpan" class="close">&times;</span>

                        <p>Create a directory:</p>

                        <form action="../filesystem/create-directory" method="POST">

                            <input id="path" name="path" type="text"/>

                            <br/>
                            <br/>

                            <input type="submit" class="" value="Create"/>
                        </form>
                    </div>
                </div>
                
                
            </div>
                
            <div id="filesystemLogs" class="logs">
                ${filesystemLog}
            </div>

            <br class="clearingBreak">
        </div>

    </div>
            
<script type="text/javascript">
//  alert("hi message");
    updateFilesystem("/");
                
    // Get the modal
    var modal = document.getElementById('uploadModal');

    // Get the button that opens the modal
    var btn = document.getElementById("uploadButton");

    // When the user clicks on the button, open the modal 
    btn.onclick = function() {
        modal.style.display = "block";
    }

    // Get the <span> element that closes the modal
    var span = document.getElementsByClassName("close")[0];

    // When the user clicks on <span> (x), close the modal
    span.onclick = function() {
        modal.style.display = "none";
    }

    // setup the create directory modal
    var createDirModal = document.getElementById('createDirModal');
    var createDirButton = document.getElementById('createDirButton');
    var createDirSpan = document.getElementById('createDirSpan');
    
    createDirButton.onclick = function()
    {
        createDirModal.style.display = "block";
    }

    createDirSpan.onclick = function()
    {
        createDirModal.style.display = "none";
    }

    // When the user clicks anywhere outside of the modal, close it
    window.onclick = function(event) 
    {
        if (event.target == modal) 
        {
            modal.style.display = "none";
        }
        
        if(event.target == createDirModal)
        {
            createDirModal.style.display = "none";
        }
    }                
</script>
