<!DOCTYPE html>
<html>
    <head>
        <title>Start Page</title>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="images.css" />
    </head>
    <body>
        <script type="text/javascript" src="led-matrix.js"></script>
        
        <h1>Raspberry Pi RGB LED Matrix Controls</h1>
        
        <div style="margin-left: auto; margin-right: auto; align-content: center">
            <span style="font-size:1.875em;">
                Mode:
            </span>
            
            <select name="mode"
                    id="mode"
                    onchange="modeChanged(this.value);"
                    style="width: 50%; height: 2em; font-size: 3em;">
                
                <option value="animations">Animations</option>
                <option value="still">Still Images</option>
                <option value="text" selected>Scrolling Text</option>
                <option value="clock" >Clock</option>
            </select>
        </div>
        
        <div>
            <button onclick="displayAnimation('animations/', '0anightmare32.png')" 
                    style="margin-left: auto; margin-right: auto;">
                Animation
            </button>
            
            &nbsp;&nbsp;&nbsp;
            
            <button onclick="stopAnimation()" 
                    style="margin-left: auto; margin-right: auto;">
                Stop Animation
            </button>
        </div>
        
        <div id="logs" class="logs" style="">

        </div>        
    </body>
</html>
