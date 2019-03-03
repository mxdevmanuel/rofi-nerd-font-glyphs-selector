#ifndef GLYPH_H_
#define GLYPH_H_

#include <string>

class Glyph {
private:
    std::string fglyph;
    std::string fdescription;

public:
    Glyph(std::string glyph, std::string description);
    Glyph(Glyph &) = default;
    Glyph(Glyph &&) = default;
    ~Glyph() = default;

    std::string getGlyph() const;
    std::string getDescription() const;

};

#endif // GLYPH_H
