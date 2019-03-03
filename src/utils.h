#ifndef UTILS_H_
#define UTILS_H_

#include <filesystem>
#include <list>
#include <string>

class Glyph;

namespace fs = std::filesystem;

/*
 * Filter nerd font db file by filename
 */
bool check_rnf_db_file_filter(const fs::path& path);

/*
 * Try to parse string and return glyph
 * String must be in nerd font string database format
 *
 * @param description string to parse
 * @return glyph or nullptr
 */
Glyph* get_glyph_from_string(const std::string& description);

/*
 * Try to parse file and return all glyph it contains
 *
 * @param filepath path to filename
 * @return glyphs found in file or empty
 */
std::list<Glyph*> get_glyphs_from_file(const fs::path& filepath);

/*
 * Action to copy glyphs to clipboard
 * 
 * @param selected list of glyphs to copy to clipboard
 */
bool action_copy_to_clipboard(std::list<Glyph*> selected);

/*
 * Action to paste glyphs in current active window
 *
 * @parama selected list of glyphs to paste
 */
bool action_paste_to_active_window(std::list<Glyph*> selected);


#endif // UTILS_H_
