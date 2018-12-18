
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
        
        boolean valid = implementation.validatePath(parent, subpath);
        
        assert(valid == true);
    }
    
    @Test
    public void validateAndSanitize_containsExtension()
    {
        File parent = new File("photos");
        String subpath = "mom.jpg";
        
        boolean valid = implementation.validatePath(parent, subpath);
        
        assert(valid == true);
    }
    
    @Test()
    public void validateAndSanitize_fail_pathModifier()
    {
        File parent = new File("bin");
        
        String subpath = "../secret/names.text";
        
        boolean valid = implementation.validatePath(parent, subpath);
        
        assert(valid == false);
    }    
}
