
function updateFilesystem(path)
{    
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange=function()
    {
        if (xmlhttp.readyState==4 && xmlhttp.status==200)      
        {
            var response = xmlhttp.responseText;
            
            var e = document.getElementById("filesystem");

            e.innerHTML = response;
        }
    }
    
    var url = "../filesystem" + path;

    xmlhttp.open("POST", url, true);
    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
    xmlhttp.send("&p=3");
}
