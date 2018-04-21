
package org.onebeartoe.quatro.engrave;

import java.io.File;
import org.onebeartoe.quatro.engrave.filesystem.FilesystemValidationService;

/**
 * This class is stored in the servlet context and holds properties of the application.
 */
public class ApplicationProfile
{
    private NejeEngraver engraver;
    
    private File baseDirectory;
    
    private FilesystemValidationService filesystemValidationService;

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

    public FilesystemValidationService getFilesystemValidationService()
    {
        return filesystemValidationService;
    }

    public void setFilesystemValidationService(FilesystemValidationService filesystemValidationService)
    {
        this.filesystemValidationService = filesystemValidationService;
    }
    
    

    public void setBaseDirectory(File baseDirectory)
    {
        this.baseDirectory = baseDirectory;
    }
}
