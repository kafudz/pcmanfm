#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "pcmanfm.h"

#if GTK_CHECK_VERSION(3, 0, 0)
/* Each rule set gets its own provider, so one that a future GTK refuses to
 * parse cannot take the others down with it. */
static void add_screen_css(GdkScreen *screen, const char *css)
{
    GtkCssProvider *provider = gtk_css_provider_new();

    if (gtk_css_provider_load_from_data(provider, css, -1, NULL))
        gtk_style_context_add_provider_for_screen(
            screen, GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION + 2);
    g_object_unref(provider);
}
#endif

/* Compact, theme-adaptive styling for the main file-manager surfaces. */
void pcmanfm_modern_ui_init(void)
{
#if GTK_CHECK_VERSION(3, 0, 0)
    GdkScreen *screen = gdk_screen_get_default();

    if (!screen)
        return;

    /* Keep the interface compact and flat while inheriting the active GTK
     * theme's colours. This avoids baking in a light/dark palette. */
    add_screen_css(screen,
                   ".toolbar-row {\n"
                   "    background-color: transparent;\n"
                   "    background-image: none;\n"
                   "    border-bottom: 1px solid #30343b;\n"
                   "    box-shadow: none;\n"
                   "}\n"
                   "toolbar {\n"
                   "    padding: 3px 6px;\n"
                   "    border-style: none;\n"
                   "    background-color: transparent;\n"
                   "    background-image: none;\n"
                   "    box-shadow: none;\n"
                   "}\n"
                   "toolbar button {\n"
                   "    min-width: 26px;\n"
                   "    min-height: 26px;\n"
                   "    margin: 0 1px;\n"
                   "    padding: 3px 6px;\n"
                   "    border: 1px solid transparent;\n"
                   "    border-radius: 5px;\n"
                   "    background-color: transparent;\n"
                   "    background-image: none;\n"
                   "    box-shadow: none;\n"
                   "}\n"
                   "toolbar button:hover {\n"
                   "    background-color: alpha(@theme_fg_color, 0.08);\n"
                   "}\n"
                   "toolbar button:active {\n"
                   "    background-color: alpha(@theme_fg_color, 0.14);\n"
                   "}\n"
                   "notebook { border-width: 0; }\n"
                   "notebook header {\n"
                   "    border-style: none;\n"
                   "    background-color: @theme_bg_color;\n"
                   "}\n"
                   "notebook tab { padding: 4px 10px; }\n"
                   "statusbar {\n"
                   "    padding: 2px 6px;\n"
                   "    border-top: 1px solid #30343b;\n"
                   "}\n"
                   "statusbar label { padding: 1px 3px; }\n"
                   "treeview.view {\n"
                   "    -GtkTreeView-vertical-separator: 4;\n"
                   "    -GtkTreeView-horizontal-separator: 8;\n"
                   "}\n");

    /* Highlight the exact folder that can receive a drop. GtkIconView draws
     * its DROP_INTO target with gtk_render_focus(), so its outline properties
     * control that item's feedback without tinting the whole file view. */
    add_screen_css(screen,
                   "iconview.view {\n"
                   "    outline-color: @theme_selected_bg_color;\n"
                   "    outline-style: solid;\n"
                   "    outline-width: 2px;\n"
                   "    outline-offset: 2px;\n"
                   "    -gtk-outline-radius: 5px;\n"
                   "}\n");

#if GTK_CHECK_VERSION(3, 20, 0)
    /* GtkTreeView marks a folder drop target with DROP_ACTIVE and the 'into'
     * style class. Keep before/after insertion feedback unchanged. */
    add_screen_css(screen,
                   "treeview.view:drop(active).into {\n"
                   "    border-color: @theme_selected_bg_color;\n"
                   "    border-style: solid;\n"
                   "    border-width: 2px;\n"
                   "    border-radius: 5px;\n"
                   "}\n");
#endif

    /* Keep the side-pane divider visible but quiet. It should not disappear
     * when a theme supplies its own shadow or border treatment. */
    add_screen_css(screen,
                   ".side-pane {\n"
                   "    border-right: 1px solid #30343b;\n"
                   "    box-shadow: none;\n"
                   "}\n"
                   ".pane-locbox {\n"
                   "    padding-left: 6px;\n"
                   "    border-bottom: none;\n"
                   "    box-shadow: none;\n"
                   "}\n"
                   ".pane-box { box-shadow: none; }\n"
                   "paned > separator { box-shadow: none; }\n");

    /* The full-width location bar above the side pane has no extra inset. */
    add_screen_css(screen,
                   ".pane-locbox.locbar-docked { padding: 0; }\n");

    /* Strip inconsistent theme gradients while retaining a visible keyboard
     * focus ring that follows the user's selected GTK accent colour. */
    add_screen_css(screen,
                   ".pane-locbox entry, .pane-locbox entry:hover,\n"
                   ".pane-locbox entry:focus, .pane-locbox entry:active {\n"
                   "    border-image: none;\n"
                   "    background-image: none;\n"
                   "    box-shadow: none;\n"
                   "}\n"
                   ".pane-locbox entry:focus {\n"
                   "    border-color: alpha(@theme_selected_bg_color, 0.75);\n"
                   "}\n"
                   ".pane-locbox button, .pane-locbox button:hover,\n"
                   ".pane-locbox button:checked, .pane-locbox button:active,\n"
                   ".pane-locbox button:focus {\n"
                   "    border-image: none;\n"
                   "    background-image: none;\n"
                   "    box-shadow: none;\n"
                   "}\n"
                   ".pane-locbox button:focus {\n"
                   "    border-color: alpha(@theme_selected_bg_color, 0.75);\n"
                   "    background-color: alpha(@theme_selected_bg_color, 0.10);\n"
                   "}\n"
                   ".pane-locbox button:checked {\n"
                   "    background-color: alpha(@theme_fg_color, 0.10);\n"
                   "}\n");

    /* Compact side-pane rows with enough icon/label separation for scanning. */
    add_screen_css(screen,
                   ".side-pane treeview.view {\n"
                   "    -GtkTreeView-vertical-separator: 6;\n"
                   "    -GtkTreeView-horizontal-separator: 8;\n"
                   "}\n");
#endif
}
