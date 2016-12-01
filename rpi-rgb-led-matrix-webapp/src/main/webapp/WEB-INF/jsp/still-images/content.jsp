
    <div>
        <h3>Still Images</h3>
        
        <div class="responseMessages">
            ${responseMessages}
        </div>
        
        <form action="upload" method="POST" enctype="multipart/form-data">
            <label for="still-image">Upload a still image</label>
            <input name="still-image" type="file"/>
            
            <input type="submit" class="settingsSaveButton" value="Upload"/>
        </form>
    </div>

    <hr>
        
    <div>
        <c:forEach items="${stillImageNames}" var="name">
            <button onclick="displayStillImage('${name}')" 
                    style="margin-left: auto; margin-right: auto;">
                <img src="<%= request.getContextPath() %>/files/still-images/${name}" />
                ${name}
            </button>            
            
            <br/>
            <br/>
        </c:forEach>    
    </div>
