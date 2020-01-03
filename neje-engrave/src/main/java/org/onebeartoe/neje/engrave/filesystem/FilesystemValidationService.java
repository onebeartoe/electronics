
package org.onebeartoe.neje.engrave.filesystem;

import java.io.File;
import java.util.logging.Logger;

/**
 * This class validates filesystem requests.
 */
public class FilesystemValidationService
{
    private Logger logger;
    
    public FilesystemValidationService()
    {
        String className = getClass().getName();
        
        logger = Logger.getLogger(className);
    }

    /**
     * This validation method only allows the following characters:
     *  
     *      alphanumeric, '-', '_', '/' and '.'
     * 
     * @param baseDirectory
     * @param path 
     */
    public boolean validatePath(File baseDirectory, String path)
    {
        String baseAbsolute = baseDirectory.getAbsolutePath();
        
        File suspectPath = new File(baseDirectory, path);

        String suspectAbsolute = suspectPath.getAbsolutePath();
        
        boolean valid = true;
        
        if( !suspectAbsolute.startsWith(baseAbsolute) )
        {
            valid = false;
            
            String message = String.format("the suspect path (%s) does not start with base (%s)", suspectAbsolute, baseAbsolute)            ;
            logger.info(message);
        }

        if (!path.matches("[/a-zA-Z0-9-_.]++")
                || path.contains("../")
                || path.contains("./"))
        {
            valid = false;
            
            logger.info("path does not match: " + path);
        }
        
        return valid;
    }
}
