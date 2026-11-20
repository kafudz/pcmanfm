#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "pcmanfm.h"

/* Keep the location bars in side-by-side panes visually consistent. The
 * pane widget has a more specific rule that removes the leading padding from
 * the first pane, so this higher-priority rule restores the same inset on
 * both sides. */
void pcmanfm_modern_ui_init(void)
{
#if GTK_CHECK_VERSION(3, 0, 0)
    GdkScreen *screen = gdk_screen_get_default();
    GtkCssProvider *provider;

    if (!screen)
        return;

    provider = gtk_css_provider_new();
    if (gtk_css_provider_load_from_data(provider,
                                        ".pane-locbox { padding-left: 6px; }\n",
                                        -1, NULL))
        gtk_style_context_add_provider_for_screen(
            screen, GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION + 2);
    g_object_unref(provider);
#endif
}
