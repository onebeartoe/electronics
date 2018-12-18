
package org.onebeartoe.neje.engrave.filesystem;

import java.io.File;
import org.testng.annotations.Test;

/**
 * @author Roberto Marquez
 */
public class FilesystemValidationServiceSpecification
{
    private FilesystemValidationService implementation;
    
    public FilesystemValidationServiceSpecification()
    {
        implementation = new FilesystemValidationService();
    }
    
    @Test
    public void validateAndSanitize()
    {
        File parent = new File("bin");
        String subpath = "ls";
        
        implementation.validateAndSanitize(parent, subpath);
    }
    
    @Test
    public void validateAndSanitize_containsExtension()
    {
        File parent = new File("photos");
        String subpath = "mom.jpg";
        
        implementation.validateAndSanitize(parent, subpath);
    }
    
    @Test(expectedExceptions = IllegalArgumentException.class)
    public void validateAndSanitize_fail_pathModifier()
    {
        File parent = new File("bin");
        
        String subpath = "../secret/names.text";
        
        implementation.validateAndSanitize(parent, subpath);
    }    
}
