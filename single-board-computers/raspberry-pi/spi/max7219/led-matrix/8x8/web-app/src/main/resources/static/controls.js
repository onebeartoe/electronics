

function updateMode(mode)
{
    alert ("we got: " + mode);
    
    if(mode === "USER_TEXT")
    {
        var textfield = document.getElementById("userText");
        alert("suer text is selected");
        
        if (textfield.style.display === "none")
        {
          textfield.style.display = "block";
          
          var textButton = document.getElementById("textButton");
          
          textButton.style.display = "block";
        } 
        else 
        {
          x.style.display = "none";
        }
    }
    
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange=function()
    {
        logServerResponse(xmlhttp);
    }
    var url = "/api/mode/" + mode;
//TODO: make this a post!!    
    xmlhttp.open("GET", url, true);
//    xmlhttp.open("POST", url, true);
    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
    xmlhttp.send("?mode=" + mode + "&p=3");    
}

function displayUserText(visible)
{          
    var textButton = document.getElementById("textButton");

    var textfield = document.getElementById("userText");

    if(visible)
    {
        textfield.style.display = "block";
          
        textButton.style.display = "block";
    }
    else
    {
        textfield.style.display = "none";
          
        textButton.style.display = "none";        
    }
}

function logServerResponse(xmlhttp)
{
    if (xmlhttp.readyState==4 && xmlhttp.status==200)      
    {
        var s = xmlhttp.responseText;
        logEvent(s);
    }
}

function logEvent(message)
{
    var e = document.getElementById("logs");
    
    var logs = message + "<br/>" + e.innerHTML;
    
    e.innerHTML = logs;
}
