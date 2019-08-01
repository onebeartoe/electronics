
#ifndef onebeartoe_TextDisplableWing_cpp
#define onebeartoe_TextDisplableWing_cpp

#include "TextDisplableWing.h"

TextDisplableWing::TextDisplableWing()
{
    interval = 5 * 1000;
}

void TextDisplableWing::oneLoop()
{
    Serial.println("do nothing in TextDisplableWing::oneLoop() ");   
}

void TextDisplableWing::setText(String text)
{
    this->text = text;
}

void TextDisplableWing::setTextMode(TextWingModes mode)
{
    this->mode = mode;
}

#endif
