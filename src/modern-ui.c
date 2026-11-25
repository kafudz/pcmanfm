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

/* Keep the location bars consistent and remove custom borders and shadows
 * where the side-pane divider meets the left location bar. */
void pcmanfm_modern_ui_init(void)
{
#if GTK_CHECK_VERSION(3, 0, 0)
    GdkScreen *screen = gdk_screen_get_default();

    if (!screen)
        return;

    add_screen_css(screen,
                   ".pane-locbox { padding-left: 6px; border-bottom: none; box-shadow: none; }\n"
                   ".pane-box { box-shadow: none; }\n"
                   ".side-pane { border-right: none; box-shadow: none; }\n"
                   "paned > separator { box-shadow: none; }\n");

    /* The full-width bar above the side pane: the same space on both sides,
     * whatever the per-pane rules above say about the left edge. */
    add_screen_css(screen,
                   ".pane-locbox.locbar-docked { padding: 0; }\n");

    /* No coloured focus accent on the location bars. */
    add_screen_css(screen,
                   ".pane-locbox entry, .pane-locbox entry:focus {\n"
                   "    border-color: transparent;\n"
                   "    box-shadow: none;\n"
                   "    outline-style: none;\n"
                   "    outline-width: 0;\n"
                   "}\n"
                   ".pane-locbox button:focus, .pane-locbox button:checked {\n"
                   "    border-color: transparent;\n"
                   "    box-shadow: none;\n"
                   "    outline-style: none;\n"
                   "    outline-width: 0;\n"
                   "}\n");

    /* Side pane rows: compact, but with room between the rows and between
     * each icon and its label. Row spacing in a tree view is only reachable
     * through these style properties; padding on the cells has no effect. */
    add_screen_css(screen,
                   ".side-pane treeview.view {\n"
                   "    -GtkTreeView-vertical-separator: 8;\n"
                   "    -GtkTreeView-horizontal-separator: 10;\n"
                   "}\n");
#endif
}
