
package org.onebeartoe.quatro.engrave.filesystem;

import java.io.IOException;
import java.util.List;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * This servlet handles requests to creates directories under the file listing 
 * base directory.
 */
@WebServlet(urlPatterns = {"/filesystem/create-directory"})
public class CreateDirectoryServlet extends HttpServlet
{
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException 
    {
        
        
        List fileNames = null;
        request.setAttribute("animationNames", fileNames);

        ServletContext c = getServletContext();
        RequestDispatcher rd = c.getRequestDispatcher("/controls/index.jsp");
        rd.forward(request, response);
    }
}
