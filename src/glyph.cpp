#include "glyph.h"

Glyph::Glyph(std::string glyph, std::string description) :
    fglyph(glyph), fdescription(description)
{ }

std::string Glyph::getGlyph() const {
    return fglyph;
}

std::string Glyph::getDescription() const {
    return fdescription;
}
