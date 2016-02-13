
use <../../../../3D-Modeling/OpenSCAD/shapes/open-cylinder/open-cylinder.scad>

// the is the height of the slipring's attachment point
slipringBaseHeight = 9;

// used a caliper!
plexiglassWidth = 5.4;

baseInnerRadius = (7.8 / 2.0);

slipRingAttachment();

//plexiglass();

module plexiglass()
{
    // simulate the two glass panes
    width = plexiglassWidth * 2;
    
    translateY = -width / 2.0;
    translateZ = slipringBaseHeight;
    translate([0, translateY, translateZ])
    cube([10, width, 20]);
}

/**
 * If an arithmatic operation is specified for a property, then the left operand if what the 
 * data sheet says and the right operand is the offset for the attchment.
 */
module slipRingAttachment(baseHeight = slipringBaseHeight - 2,
                          baseInnerRadius = baseInnerRadius +
                          0.3,   
                          baseOuterDiameter = baseInnerRadius * 2 + 4,
                          channelLength = 50,
                          channelWidth = 5)
{
    union()
    {
        yLength = baseOuterDiameter + 5;
        xTranslate = -channelLength / 2.0;
        yTranslate = yLength / 2.0;
        zTranslate = baseHeight - 0.001;
        wiresCutoutRadius = baseInnerRadius - 1;
        color("blue")    
        translate([xTranslate, -yTranslate, baseHeight])
        ledWireChannel(channelLength = channelLength,
                           yLength = yLength,
                           baseHeight = 3,
                           wiresCutoutRadius = wiresCutoutRadius);

        outerRadius = baseOuterDiameter / 2.0;
        innerRadius = baseInnerRadius;
        slipRingBase(baseHeight = baseHeight,
                     baseInnerRadius = innerRadius,
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

module ledWireChannel(channelLength,
                          yLength,
                          baseHeight,
                          wiresCutoutRadius)
{
    difference()
    {
        // whole block
        cube([channelLength,
              yLength,
              baseHeight+2]);

        // channel for the slip ring wires             
        slipRingWiresChannelLengthX = channelLength + 5 + 0.001; 
        slipRingWiresChannelLengthY = wiresCutoutRadius * 2.0;        
        slipRingWiresChannelLengthZ = (baseHeight / 2.0) + 0.001; 
        channelCutoutOffsetY = (yLength / 2.0) - (slipRingWiresChannelLengthY / 2.0);
        channelCutoutOffsetZ = (baseHeight - slipRingWiresChannelLengthZ) + 0.001;
        translate([-.001, 
                   channelCutoutOffsetY, 
                   channelCutoutOffsetZ]) 
        cube([slipRingWiresChannelLengthX,
              slipRingWiresChannelLengthY,
              slipRingWiresChannelLengthZ]);

        // channel for the LED strip
        stripLengthX = channelLength + 0.002; 
        stripLengthY = 9;
        stripTranslateX = -0.001;        
        stripTranslateY = (yLength / 2.0) - (stripLengthY / 2.0);
        stripTranslateZ = slipRingWiresChannelLengthZ + channelCutoutOffsetZ - 0.001;
        translate([stripTranslateX, stripTranslateY, stripTranslateZ])
        cube([stripLengthX, stripLengthY, 3]);

        // cylinder for the slip ring wires
        wireCutoutLengthZ = baseHeight + slipRingWiresChannelLengthZ + 0.001;
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
