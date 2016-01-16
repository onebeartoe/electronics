
use <../../../../3D-Modeling/OpenSCAD/shapes/open-cylinder/open-cylinder.scad>

slipRingAttachment();

/**
 * If an arithmatic operation is specified for a property, then the left operand if what the 
 * data sheet says and the right operand is the offset for the attchment.
 */
module slipRingAttachment(baseHeight = 9 - 2,
                          baseInnerRadius = 3,    
                          baseOuterDiameter = 7.8 + 0.4,
                          channelLength = 50,
                          channelWidth = 5)
{
    union()
    {
//        xDelta = -baseOuterDiameter / 2.0;
//        yDelta = -channelWidth;
//        zDelta = (baseHeight * 2) -0.002;        
//        color("red")
//        translate([xDelta, yDelta, zDelta])
//        plexiglassHolder(width = baseOuterDiameter,
//                         channelLength = channelLength,
//                         baseHeight = baseHeight);
        
        xLength = channelLength; 
        xTranslate = -channelLength / 2.0;
        yTranslate = baseOuterDiameter / 2.0;
        zTranslate = baseHeight - 0.001;
        wiresCutoutRadius = baseInnerRadius - 2;
        color("blue")    
        translate([xTranslate, -yTranslate, baseHeight])
        slipRingLedChannel(channelLength = xLength,
                           yLength = baseOuterDiameter,
                           baseHeight = 3,
                           wiresCutoutRadius = wiresCutoutRadius);

        outerRadius = baseOuterDiameter / 2.0;
        slipRingBase(baseHeight = baseHeight,
                     baseInnerRadius = baseInnerRadius,
                     baseOuterRadius = outerRadius);        
    }
}

module plexiglassHolder(width,
                        baseHeight,
                        channelLength)
{    
    cube([channelLength,
          width,
          baseHeight
    ]);    
}

module slipRingLedChannel(channelLength,
                          yLength,
                          baseHeight,
                          wiresCutoutRadius)
{
    difference()
    {
        // whole block
        cube([channelLength,
              yLength,
              baseHeight]);

        // cutout for the LED stick              
        channelCutoutLengthX = channelLength + 5 + 0.001; 
        channelCutoutLengthY = yLength / 2.0;
        channelCutoutLengthZ = (baseHeight / 2.0) + 0.001; 
        channelCutoutOffsetY = channelCutoutLengthY / 2.0;
        channelCutoutOffsetZ = (baseHeight - channelCutoutLengthZ) + 0.001;
        translate([-1.001, 
                   channelCutoutOffsetY, 
                   channelCutoutOffsetZ]) 
        cube([channelCutoutLengthX,
              channelCutoutLengthY,
              channelCutoutLengthZ]);

        // cutout for the wires
        wireCutoutLengthZ = baseHeight + channelCutoutLengthZ + 0.001;
        wireCutoutOffsetX = channelLength / 2.0; 
        wireCutoutOffsetY = yLength / 2.0;
        wireCutoutOffsetZ = -0.001; 
        translate([wireCutoutOffsetX,
                   wireCutoutOffsetY,
                   wireCutoutOffsetZ])
        cylinder(r = wiresCutoutRadius,
                 h = wireCutoutLengthZ,
                 $fn = 30);
    }
}

module slipRingBase(baseHeight,
                    baseInnerRadius,    
                    baseOuterRadius)
{    
    openCylinder(height = baseHeight,                 
                 innerRadius = baseInnerRadius,
                 outerRadius = baseOuterRadius);
}
