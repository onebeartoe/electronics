/*
 */
package org.onebeartoe.wav.to.dot.h;

import java.io.File;
import org.onebeartoe.application.RunProfile;

/**
 *
 * @author Roberto Marquez
 */
class WavToDotHRunProfile extends RunProfile
{
    private File wavFile;

    public void setWavFile(File wavFile)
    {
        this.wavFile = wavFile;
    }
    
    

    public File getWavFile()
    {
        return wavFile;
    }
    
}
