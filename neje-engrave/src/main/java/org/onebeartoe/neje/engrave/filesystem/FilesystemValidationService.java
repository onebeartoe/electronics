
package org.onebeartoe.neje.engrave.filesystem;

import java.io.File;

/**
 * This class validates filesystem requests.
 */
public class FilesystemValidationService
{
    /**
     * This validation method only allows the following characters:
     *  
     *      alphanumeric, '-', '_', and '.'
     * 
     * @param baseDirectory
     * @param path 
     */
    public void validatePath(File baseDirectory, String path)
    {
        String baseAbsolute = baseDirectory.getAbsolutePath();
        
        File suspectPath = new File(baseDirectory, path);
        String suspectAbsolute = suspectPath.getAbsolutePath();
        
        if( !suspectAbsolute.startsWith(baseAbsolute) )
        {
            throw new IllegalArgumentException("bad filesystem path: " + suspectAbsolute);
        }

        if (!path.matches("[a-zA-Z0-9-_.]++"))
        {
            throw new IllegalArgumentException("Invalid input was ound found: " + path);
        }
    }    

    public String validateAndSanitize(File baseDirectory, String subpath)
    {
        validatePath(baseDirectory, subpath);
        
        return subpath;
    }
}
