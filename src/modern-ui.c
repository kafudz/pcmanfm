#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "pcmanfm.h"

#if GTK_CHECK_VERSION(3, 0, 0)

/* Load the modern stylesheet for the whole application.
 *
 * This must run after gtk_init(): the default GdkScreen does not exist before
 * that, so loading the stylesheet from a constructor would silently drop it. */
void pcmanfm_modern_ui_init(void)
{
    static gboolean installed = FALSE;
    GtkCssProvider *provider;
    GdkScreen *screen;
    GError *error = NULL;
    char *css_path;

    if (installed)
        return;

    screen = gdk_screen_get_default();
    if (!screen)
    {
        g_warning("No default screen, PCManFM modern UI stylesheet not loaded");
        return;
    }

    provider = gtk_css_provider_new();
    css_path = g_build_filename(PACKAGE_DATA_DIR, "pcmanfm.css", NULL);

    if (gtk_css_provider_load_from_path(provider, css_path, &error))
    {
        gtk_style_context_add_provider_for_screen(
            screen,
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        installed = TRUE;
    }
    else
    {
        g_warning("Could not load PCManFM modern UI stylesheet %s: %s",
                  css_path, error ? error->message : "unknown error");
        g_clear_error(&error);
    }

    g_free(css_path);
    g_object_unref(provider);
}

#else /* GTK2: the stylesheet is GTK3-only, nothing to do. */

void pcmanfm_modern_ui_init(void)
{
}

#endif
