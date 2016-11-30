
    <div>
        <h3>Still Images</h3>
        
        <form
    </div>

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
