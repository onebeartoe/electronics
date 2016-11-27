
    <div class="section">
        <button onclick="stopAnimation()">
            Stop Animation
        </button>
    </div>

    <hr/>

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
