#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "pcmanfm.h"

/* Keep the location bars consistent and remove custom borders and shadows
 * where the side-pane divider meets the left location bar. */
void pcmanfm_modern_ui_init(void)
{
#if GTK_CHECK_VERSION(3, 0, 0)
    GdkScreen *screen = gdk_screen_get_default();
    GtkCssProvider *provider;

    if (!screen)
        return;

    provider = gtk_css_provider_new();
    if (gtk_css_provider_load_from_data(provider,
                                        ".pane-locbox { padding-left: 6px; border-bottom: none; box-shadow: none; }\n"
                                        ".pane-box { box-shadow: none; }\n"
                                        ".side-pane { border-right: none; box-shadow: none; }\n"
                                        "paned > separator { box-shadow: none; }\n",
                                        -1, NULL))
        gtk_style_context_add_provider_for_screen(
            screen, GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION + 2);
    g_object_unref(provider);
#endif
}
