
package org.onebeartoe.neje.engrave;

import java.io.File;
import org.onebeartoe.neje.engrave.filesystem.FilesystemValidationService;

/**
 * This class is stored in the servlet context and holds properties of the application.
 */
public class ApplicationProfile
{
    
    public static final String  BASE_SUB_DIRECTORY = "/.config/neje-graver/uploads/";    
    
    public static final String CONFIGURATION_FILENAME = "neje-engrver.properties";    
    
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
