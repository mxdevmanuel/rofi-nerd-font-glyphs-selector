
#include <algorithm>
#include <vector>

#include <rofi/mode.h>
#include <rofi/helper.h>
#include <rofi/mode-private.h>

#include "glyph.h"
#include "utils.h"

extern "C" {

typedef struct {
    std::vector<Glyph*> glyphs;
} RNFPrivateData;

void rofi_view_hide();

/**
 * @param mode The mode to initialize
 *
 * Initialize mode
 *
 * @returns FALSE if there was a failure, TRUE if successful
 */
static int rnf_mode_init(Mode *sw) {
    if(mode_get_private_data(sw) == NULL) {
        RNFPrivateData *pd = new RNFPrivateData();
        mode_set_private_data(sw, pd);

        // get base database path
        std::filesystem::path basepath = std::filesystem::path("/") / "usr" / "lib" / "nerd-fonts-complete";

        // find all db files
        std::list<std::filesystem::path> files;
        std::filesystem::directory_iterator d_iter(basepath);
        std::copy_if(std::filesystem::begin(d_iter), std::filesystem::end(d_iter),
                     std::back_inserter(files), check_rnf_db_file_filter);

        // get glyphs from files
        for(std::filesystem::path path : files) {
            std::list<Glyph*> glyphs = get_glyphs_from_file(path);
            std::copy(glyphs.begin(), glyphs.end(), std::back_inserter(pd->glyphs));
        }
    }
    return TRUE;
}

/**
 * @param mode The mode to query
 *
 * Get the number of entries in the mode.
 *
 * @returns an unsigned in with the number of entries.
 */
static unsigned int rnf_mode_get_num_entries(const Mode *sw) {
    RNFPrivateData *pd = (RNFPrivateData*) mode_get_private_data(sw);
    if(pd != NULL)
        return pd->glyphs.size();
    return 0;
}

/**
 * @param mode The mode to query
 * @param menu_retv The menu return value.
 * @param input Pointer to the user input string. [in][out]
 * @param selected_line the line selected by the user.
 *
 * Acts on the user interaction.
 *
 * @returns the next #ModeMode.
 */
static ModeMode rnf_mode_result(Mode *sw, int mretvm, char **input, unsigned int selected_line) {
    ModeMode rval = MODE_EXIT;
    RNFPrivateData *pd = (RNFPrivateData*) mode_get_private_data(sw);
    if(pd != NULL) {
        
        if(mretvm & MENU_NEXT)
            rval = NEXT_DIALOG;
        if(mretvm & MENU_PREVIOUS)
            rval = PREVIOUS_DIALOG;
        if(mretvm & MENU_QUICK_SWITCH)
            rval = (ModeMode) (mretvm & MENU_LOWER_MASK);

        if(mretvm & MENU_OK) {
            bool result;
            if((mretvm & MENU_CUSTOM_ACTION) == MENU_CUSTOM_ACTION) {
                // alt action, aka 'Shift+Enter'
                // copy to clipboard with xsel

                result = action_copy_to_clipboard({pd->glyphs[selected_line]});
            } else {
                // action, aka 'Enter'
                // paste to previous active window with xdotool
                
                rofi_view_hide(); // hide rofi window first
                result = action_paste_to_active_window({pd->glyphs[selected_line]});
            }

            rval = RELOAD_DIALOG;
            if(result)
                rval = MODE_EXIT;
        }

    }
    return rval;
}


/**
 * @param mode The mode to destroy
 *
 * Destroy the mode
 */
static void rnf_mode_destroy(Mode *sw) {
    RNFPrivateData *pd = (RNFPrivateData*) mode_get_private_data(sw);
    if(pd != NULL) {
        delete pd;
        mode_set_private_data(sw, NULL);
    }
}

/**
 * @param sw The mode object.
 * @param tokens The tokens to match against.
 * @param index  The index in this plugin to match against.
 *
 * Match the entry.
 *
 * @param returns try when a match.
 */
static int rnf_token_match(const Mode *sw, rofi_int_matcher **tokens, unsigned int index) {
    RNFPrivateData *pd = (RNFPrivateData*) mode_get_private_data(sw);
    if(pd != NULL)
        return helper_token_match(tokens, pd->glyphs[index]->getDescription().c_str());
    return -1;
}

/**
 * @param mode The mode to query
 * @param selected_line The entry to query
 * @param state The state of the entry [out]
 * @param attribute_list List of extra (pango) attribute to apply when displaying. [out][null]
 * @param get_entry If the should be returned.
 *
 * Returns the string as it should be displayed for the entry and the state of how it should be displayed.
 *
 * @returns allocated new string and state when get_entry is TRUE otherwise just the state.
 */
static char *rnf_get_display_value(const Mode *sw, unsigned int selected_line, G_GNUC_UNUSED int *state, G_GNUC_UNUSED GList **attr_list, int get_entry) {
    RNFPrivateData *pd = (RNFPrivateData*) mode_get_private_data(sw);
    if(pd != NULL) {
        Glyph* selected = pd->glyphs[selected_line];
        std::string display = selected->getGlyph() + " " + selected->getDescription();
        return strdup(display.c_str());
    }
    return NULL;
}

Mode mode = {
  .abi_version        = ABI_VERSION,
  .name               = "rnf",
  //.cfg_name_key       = "rnf",
  ._init              = rnf_mode_init,
  ._destroy           = rnf_mode_destroy,
  ._get_num_entries   = rnf_mode_get_num_entries,
  ._result            = rnf_mode_result,
  ._token_match       = rnf_token_match,
  ._get_display_value = rnf_get_display_value,
  ._get_completion    = NULL,
  ._preprocess_input  = NULL,
  ._get_message       = NULL,
  .private_data       = NULL,
  .free               = NULL,
};

}
