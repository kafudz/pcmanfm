static void _update_primary_bar_visibility(FmTabPage *page)
{
    FmTabPagePane *pane;

    if (!page->panes || page->panes->len == 0)
        return;
    pane = g_ptr_array_index(page->panes, 0);
    gtk_widget_set_visible(pane->loc_box, TRUE);
}
