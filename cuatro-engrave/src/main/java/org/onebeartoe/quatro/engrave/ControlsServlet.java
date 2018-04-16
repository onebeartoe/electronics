
package org.onebeartoe.quatro.engrave;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * This servlet manages all the contorls for the engraver.
 */
@WebServlet(name = "ControlsServet", urlPatterns = {"/controls/start"})
public class ControlsServlet extends HttpServlet
{
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        startEngraving();
        
        request.setAttribute("status", "status is all good");
                
        ServletContext c = getServletContext();
        RequestDispatcher rd = c.getRequestDispatcher("/controls/index.jsp");
        rd.forward(request, response);
        
//        response.sendRedirect("/controls");
    }

    private void startEngraving() throws IOException
    {
//        Process commandProcess;
        
        String executable = "/home/roberto/Versioning/group/github/camrein/EzGraver-unix_cli_fixes/EzGraverCli/EzGraverCli";
        
        List<String> command = new ArrayList();
        command.add(executable);
        command.add("s");
        command.add("/dev/ttyUSB0");
        
        String debugList = "";
        for(String s : command)
        {
            debugList += s + " ";
        }
        Logger logger = Logger.getAnonymousLogger();        
        logger.log(Level.INFO, "command list: >" + debugList + "<");        
        
        logger.log(Level.INFO, "staring engraving process");
        ProcessBuilder builder = new ProcessBuilder(command);

        Process commandProcess = builder.start();
    }
}
