
    <div class="section">
        <button onclick="stopAnimation()">
            Stop Animation
        </button>
    </div>

    <hr/>

    <div>
        <h1>Animations</h1>
        
        <div class="responseMessages">
            ${responseMessages}
        </div>
        
        <form action="upload" method="POST" enctype="multipart/form-data">
            <label for="animation">Upload an animation</label>
            <input name="animation" type="file"/>
            
            <input type="submit" class="settingsSaveButton" value="Upload"/>
        </form>
    </div>

    <hr>
    
    <div>
        <c:forEach items="${animationNames}" var="name">
            <button onclick="displayAnimation('${name}')" >
                <img src="<%= request.getContextPath() %>/files/animations/${name}" />
                ${name}
            </button>            
            
            <br/>
            <br/>
        </c:forEach>    
    </div>
