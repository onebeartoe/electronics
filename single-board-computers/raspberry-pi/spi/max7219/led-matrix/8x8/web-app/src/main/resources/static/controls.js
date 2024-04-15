
function updateMode(mode)
{
    var textfield = document.getElementById("userText");
    
    if(mode === "USER_TEXT")
    {
        
        
        var isVisible = textfield.checkVisibility();

        if(isVisible)
        {
            // the call came from the button

            sendRequest(mode, textfield);
        }
        else
        {
            displayUserText(true);
        }
    }
    else
    {
        displayUserText(false);

        sendRequest(mode, textfield);
    }
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

function sendRequest(mode, textfield)
{
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange=function()
    {
        logServerResponse(xmlhttp);
    }

    var queryString = "?mode=" + mode + "&userText=" + textfield.value;
    

    var url = "/api/mode/" + mode + queryString;
    
//TODO: make this a post!!    
    xmlhttp.open("GET", url, true);
//    xmlhttp.open("POST", url, true);

    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
    
    xmlhttp.send("");    
}
