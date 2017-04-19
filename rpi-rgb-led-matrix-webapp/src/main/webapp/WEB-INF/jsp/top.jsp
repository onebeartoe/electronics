
<!DOCTYPE html>

<html>
    <head>
        <title><%= title %></title>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/layout.css" />
    </head>
    
    <body>
        <script type="text/javascript" src="<%= request.getContextPath() %>/led-matrix.js"></script>

        <div class="navigation" style="">
            <a href="<%= request.getContextPath() %>/">About</a>
            |
            <a href="<%= request.getContextPath() %>/still-images/">Still Images</a>
            |
            <a href="<%= request.getContextPath() %>/animations/">Animations</a>
            |
            <a href="<%= request.getContextPath() %>/scrolling-text/">Scrolling Text</a>
            |
            <a href="<%= request.getContextPath() %>/settings/">Settings</a>
        </div>
        
        <h3>Raspberry Pi RGB LED Matrix</h3>
