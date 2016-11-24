
function displayAnimation(imagePath, name)
{
    var mode;
    
    switch(imagePath)
    {
        case "animations/save/":
        {
            mode = "animation/save/";
            break;
        }
        case "animations/":
        {
            mode = "animation/";
            break;
        }
        default:
        {
            // still images
            mode = "still/";
        }
    }
    
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange=function()
    {
        logServerResponse(xmlhttp);
    }
    var url = "animation/" + mode + name;
    xmlhttp.open("POST", url, true);
    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
    xmlhttp.send("&p=3");    
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
