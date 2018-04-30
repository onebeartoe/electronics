
function logEvent(message, divId)
{
    var e = document.getElementById(divId);
    
    var logs = message + "<br/>" + e.innerHTML;
    
    e.innerHTML = logs;
}

function logServerResponse(xmlhttp, divId)
{
    if (xmlhttp.readyState==4 && xmlhttp.status==200)      
    {
        var s = xmlhttp.responseText;
        logEvent(s, divId);
    }
}

function pauseEngraver()
{
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange=function()
    {
        var divId = "logs";
        logServerResponse(xmlhttp, divId);
    }
    var url = "../engraver/pause";    

    xmlhttp.open("POST", url, true);
    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
    xmlhttp.send("&p=3");
}

function resetEngraver()
{
    var r = confirm("Confirm engraver reset, please.");
    
    if (r == true) 
    {
        var xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange=function()
        {
            var divId = "logs";
            logServerResponse(xmlhttp, divId);
        }
        var url = "../engraver/reset";    

        xmlhttp.open("POST", url, true);
        xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
        xmlhttp.send("&p=3");
    }
}

function startEngraving()
{
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange=function()
    {
        var divId = "logs";
        logServerResponse(xmlhttp, divId);
    }
    var url = "../engraver/start";
    xmlhttp.open("POST", url, true);
    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
    xmlhttp.send("&p=3");    
}

function uploadImageToEngraver(imagePath)
{
    var currentFile = document.getElementById("currentFile");
    currentFile.innerHTML = "File: " + imagePath;
    
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange=function()
    {
        divId = "logs";
        logServerResponse(xmlhttp, divId);
    }
    var url = "../engraver/upload-image" + "/" + imagePath;
    xmlhttp.open("POST", url, true);
    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
    xmlhttp.send("&p=3");
}