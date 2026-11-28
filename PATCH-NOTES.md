# PCManFM 1.4.0 — hardening and compact GTK interface

This patch keeps PCManFM's existing C/GTK/libfm architecture. It does not attempt a language or toolkit rewrite.

## Changes

### IPC and responsiveness (`src/single-inst.c`)

- Keep a per-client line buffer so newline-framed commands remain intact when a Unix-socket read ends mid-record.
- Put accepted client sockets into non-blocking mode and read in 4 KiB chunks, avoiding a slow local client stalling the GTK main loop and avoiding a syscall per byte.
- Reject malformed control bytes and invalid screen numbers without aborting the whole process.
- Bound IPC records to 1 MiB, requests to 16 MiB, and argument count to 4,096.
- Disable GOption's automatic `--help` process exit while parsing IPC requests.
- Parse errors now produce a warning and discard that request; they do not call `g_error()`.

### View and tab lifecycle (`src/main-win.c`)

- Disconnect window callbacks from every folder view in a page, including secondary split panes, when a tab is removed.
- Perform the same signal cleanup explicitly during window teardown before notebook pages are destroyed.
- Release the active view reference during window destruction.
- Guard rename sensitivity when the selected-file snapshot becomes empty during a model update.

### Selection status (`src/tab-page.c`)

- Handle null or empty selected-file snapshots while the folder model is updating.
- Invoke status plugins only when a non-empty snapshot exists.
- Check file-size values and guard aggregate-size accumulation against signed 64-bit overflow.

### GTK 3 presentation (`src/modern-ui.c`)

- Apply compact toolbar buttons, slimmer tabs/status bar, and tighter tree-view spacing.
- Use the active GTK theme's palette rather than forcing a light or dark mode.
- Restore a subtle side-pane divider and retain an accent-colored keyboard focus indicator.
- Keep the styling GTK 3-only so the project's GTK 2 compatibility path is unchanged.

## Verification status

- `bash -n autogen.sh`: passed.
- Whitespace/conflict-marker review of changed lines: passed.
- Source diff reviewed against the uploaded archive.
- A compile and GUI/runtime test could not be performed in this environment: `glib-2.0`, `gio-2.0`, GTK 2/3, and libfm development packages are absent; `intltoolize` is also unavailable, so the project's Autotools bootstrap cannot complete here.

Before merging upstream, build against the target distribution's GTK/libfm versions and test single-instance launches with long paths, split-pane tab close/reopen, status-bar selection updates, and both GTK 2 and GTK 3 configurations.

### Toolbar appearance adjustment

- Removed the toolbar row's solid theme background and made both the shared toolbar/location row and GTK toolbar background transparent.
- Kept the subtle bottom divider and theme-adaptive hover/active feedback on toolbar buttons.

### Toolbar appearance adjustment

- Removed the solid background from the shared toolbar/location row and GTK toolbar; both now use transparent backgrounds.
- Toolbar buttons are transparent at rest, while subtle theme-adaptive hover and active feedback is retained.
- Kept the understated bottom divider so the toolbar remains visually separated without a filled color surface.
