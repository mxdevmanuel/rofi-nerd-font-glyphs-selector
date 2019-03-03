#include "utils.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <numeric>
#include <regex>
#include <string>

#include "glyph.h"


bool check_rnf_db_file_filter(const fs::path& path) {
    std::string filename = path.filename();
    return (filename != "i_all.sh") &&
           (filename.rfind("i_", 0) == 0); // &&
           //(filename.rfind(".sh", 0) == filename.size() - 1 - 3);
}

Glyph* get_glyph_from_string(const std::string& str) {
    // global static regex, need to create one time
    static std::regex re("i='(.+)'\\s+i_([^=]*)=\\$i");

    std::smatch match;
    if(!std::regex_search(str, match, re))
        return nullptr;

    std::string glyph = match[1];
    std::string description = match[2];
    std::transform(description.begin(), description.end(),
                   description.begin(),
                   [] (char v) { 
                     if (v == '_')
                       return ' ';
                     return v;
                   });

    return new Glyph(glyph, description);
}

std::list<Glyph*> get_glyphs_from_file(const fs::path& filepath) {
    std::list<Glyph*> glyphs;
    std::ifstream is(filepath, std::ifstream::in);
    for(std::string line; std::getline(is, line);) {
        Glyph* glyph = get_glyph_from_string(line);
        if(glyph != nullptr)
            glyphs.push_back(glyph);
    }
    is.close();
    return std::move(glyphs);
}


bool store_in_selection(const std::string& selection, std::string str) {
    std::string args = std::string("xsel --") + selection + std::string(" --input");
    FILE *stream = popen(args.c_str(), "w");
    if(stream == nullptr)
        return false;

    fwrite(str.c_str(), str.size(), 1, stream);
    int status = pclose(stream);
    return status == 0;
}

bool action_copy_to_clipboard(std::list<Glyph*> selected) {
    std::string glyphs = std::accumulate(
            selected.begin(), selected.end(), std::string(""), 
            [](const std::string& in, Glyph* value){
                return in + value->getGlyph();
            });
    
    store_in_selection("clipboard", glyphs);
    return true;
}

bool action_paste_to_active_window(std::list<Glyph*> selected) {
    std::string glyphs = std::accumulate(
            selected.begin(), selected.end(), std::string(""), 
            [](const std::string& in, Glyph* value){
                return in + value->getGlyph();
            });

    store_in_selection("primary", glyphs);

    //
    std::string args = std::string("xdotool key Shift+Insert");
    return system(args.c_str()) == 0;
}
