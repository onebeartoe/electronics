
package org.onebeartoe.quatro.engrave.filesystem;

import java.io.File;

/**
 * This class validates filesystem requests.
 */
public class FilesystemValidationService
{

    void validatePath(File baseDirectory, String path)
    {
        String baseAbsolute = baseDirectory.getAbsolutePath();
        
        File suspectPath = new File(baseDirectory, path);
        String suspectAbsolute = suspectPath.getAbsolutePath();
        
        if( !suspectAbsolute.startsWith(baseAbsolute) )
        {
            throw new IllegalArgumentException("bad filesystem path: " + suspectAbsolute);
        }        
    }
    
}
