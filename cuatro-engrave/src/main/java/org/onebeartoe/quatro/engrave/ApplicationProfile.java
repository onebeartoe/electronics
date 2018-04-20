
package org.onebeartoe.quatro.engrave;

import java.io.File;

/**
 * This class is stored in the servlet context and holds properties of the application.
 */
public class ApplicationProfile
{
    private NejeEngraver engraver;
    
    private File baseDirectory;

    public NejeEngraver getEngraver()
    {
        return engraver;
    }

    public void setEngraver(NejeEngraver engraver)
    {
        this.engraver = engraver;
    }

    public File getBaseDirectory()
    {
        return baseDirectory;
    }

    public void setBaseDirectory(File baseDirectory)
    {
        this.baseDirectory = baseDirectory;
    }
}
