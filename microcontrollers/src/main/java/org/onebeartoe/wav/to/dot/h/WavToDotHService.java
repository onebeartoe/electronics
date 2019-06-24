/*
 */
package org.onebeartoe.wav.to.dot.h;

import org.onebeartoe.wav.to.dot.h.exception.NullWavFileException;
import org.onebeartoe.wav.to.dot.h.exception.WavFileTooBigException;
import org.onebeartoe.wav.to.dot.h.exception.WavFileDoesNotExistException;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import org.onebeartoe.application.AppletService;
import org.onebeartoe.application.RunProfile;

/**
 *
 * @author Roberto Marquez
 */
public class WavToDotHService extends AppletService
{
    public void serviceRequest(RunProfile runProfile) throws WavFileTooBigException, IOException, NullWavFileException, WavFileDoesNotExistException
    {
        WavToDotHRunProfile rp = (WavToDotHRunProfile) runProfile;
        
        File wavFile = rp.getWavFile();

        if(wavFile == null)
        {
            throw new NullWavFileException();
        }

        if( !wavFile.exists() )
        {
            throw new WavFileDoesNotExistException();
        }
        
        int TOO_BIG = 1000 * 1000; // about a Megabyte is too big for a .h file to fit 
                                   // on a microctrontroller (at least in 2019)
        
        if(wavFile.length() > TOO_BIG)
        {
            throw new WavFileTooBigException();
        }
        
        Path wavPath = wavFile.toPath();
        
        byte [] waveBytes = Files.readAllBytes(wavPath);
        
        StringBuffer dotFileContents = new StringBuffer();
        
        for(int i = 0; i < waveBytes.length; i++)
        {
            dotFileContents.append("'");
            String b = String.format("%02X", waveBytes[i]);
            dotFileContents.append(b);
            dotFileContents.append("'");
        }
        
        byte [] dotHBytes = dotFileContents.toString()
                                           .getBytes();
  
        String outfileName = wavFile.getName() + ".h";
        File pwd = new File(".");
        File parent = pwd;
        File cononicalOutfile = new File(parent, outfileName);
        
        String cononicalPath = cononicalOutfile.getCanonicalPath();
        
        System.out.println("outfile: " + cononicalPath );
        
        File outfile = new File(cononicalPath);
        
        Path outfilePath = outfile.toPath();
//        Files.write(outfilePath, dotHBytes);
    }
}
