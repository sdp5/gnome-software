/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 * vi:set noexpandtab tabstop=8 shiftwidth=8:
 *
 * Copyright (C) 2012-2016 Richard Hughes <richard@hughsie.com>
 * Copyright (C) 2020 Kalev Lember <klember@redhat.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#pragma once

#include <glib-object.h>
#include <gmodule.h>
#include <gio/gio.h>
#include <libsoup/soup.h>

#include "gs-app.h"
#include "gs-app-list.h"
#include "gs-category.h"
#include "gs-plugin-event.h"
#include "gs-plugin-types.h"

G_BEGIN_DECLS

#define GS_TYPE_PLUGIN (gs_plugin_get_type ())

G_DECLARE_DERIVABLE_TYPE (GsPlugin, gs_plugin, GS, PLUGIN, GObject)

struct _GsPluginClass
{
	GObjectClass		 parent_class;
	void			(*updates_changed)	(GsPlugin	*plugin);
	void			(*status_changed)	(GsPlugin	*plugin,
							 GsApp		*app,
							 guint		 status);
	void			(*reload)		(GsPlugin	*plugin);
	void			(*report_event)		(GsPlugin	*plugin,
							 GsPluginEvent	*event);
	void			(*allow_updates)	(GsPlugin	*plugin,
							 gboolean	 allow_updates);
	void			(*basic_auth_start)	(GsPlugin	*plugin,
							 const gchar	*remote,
							 const gchar	*realm,
							 GCallback	 callback,
							 gpointer	 user_data);
	void			(*repository_changed)	(GsPlugin	*plugin,
							 GsApp		*repository);
	gboolean		(*ask_user_accepts)	(GsPlugin	*plugin,
							 const gchar	*title,
							 const gchar	*msg,
							 const gchar	*details,
							 const gchar	*accept_label);
	gpointer		 padding[23];
};

typedef struct	GsPluginData	GsPluginData;

/* helpers */
#define	GS_PLUGIN_ERROR					gs_plugin_error_quark ()

GQuark		 gs_plugin_error_quark			(void);

/* public getters and setters */
GsPluginData	*gs_plugin_alloc_data			(GsPlugin	*plugin,
							 gsize		 sz);
GsPluginData	*gs_plugin_get_data			(GsPlugin	*plugin);
const gchar	*gs_plugin_get_name			(GsPlugin	*plugin);
const gchar	*gs_plugin_get_appstream_id		(GsPlugin	*plugin);
void		 gs_plugin_set_appstream_id		(GsPlugin	*plugin,
							 const gchar	*appstream_id);
gboolean	 gs_plugin_get_enabled			(GsPlugin	*plugin);
void		 gs_plugin_set_enabled			(GsPlugin	*plugin,
							 gboolean	 enabled);
gboolean	 gs_plugin_has_flags			(GsPlugin	*plugin,
							 GsPluginFlags	 flags);
void		 gs_plugin_add_flags			(GsPlugin	*plugin,
							 GsPluginFlags	 flags);
void		 gs_plugin_remove_flags			(GsPlugin	*plugin,
							 GsPluginFlags	 flags);
guint		 gs_plugin_get_scale			(GsPlugin	*plugin);
const gchar	*gs_plugin_get_language			(GsPlugin	*plugin);
SoupSession	*gs_plugin_get_soup_session		(GsPlugin	*plugin);
void		 gs_plugin_set_soup_session		(GsPlugin	*plugin,
							 SoupSession	*soup_session);
void		 gs_plugin_add_rule			(GsPlugin	*plugin,
							 GsPluginRule	 rule,
							 const gchar	*name);

/* helpers */
GBytes		*gs_plugin_download_data		(GsPlugin	*plugin,
							 GsApp		*app,
							 const gchar	*uri,
							 GCancellable	*cancellable,
							 GError		**error);
gboolean	 gs_plugin_download_file		(GsPlugin	*plugin,
							 GsApp		*app,
							 const gchar	*uri,
							 const gchar	*filename,
							 GCancellable	*cancellable,
							 GError		**error);
gchar		*gs_plugin_download_rewrite_resource	(GsPlugin	*plugin,
							 GsApp		*app,
							 const gchar	*resource,
							 GCancellable	*cancellable,
							 GError		**error);

gboolean	 gs_plugin_check_distro_id		(GsPlugin	*plugin,
							 const gchar	*distro_id);
GsApp		*gs_plugin_cache_lookup			(GsPlugin	*plugin,
							 const gchar	*key);
void		 gs_plugin_cache_lookup_by_state	(GsPlugin	*plugin,
							 GsAppList	*list,
							 GsAppState	 state);
void		 gs_plugin_cache_add			(GsPlugin	*plugin,
							 const gchar	*key,
							 GsApp		*app);
void		 gs_plugin_cache_remove			(GsPlugin	*plugin,
							 const gchar	*key);
void		 gs_plugin_cache_invalidate		(GsPlugin	*plugin);
void		 gs_plugin_status_update		(GsPlugin	*plugin,
							 GsApp		*app,
							 GsPluginStatus	 status);
gboolean	 gs_plugin_app_launch			(GsPlugin	*plugin,
							 GsApp		*app,
							 GError		**error);
void		 gs_plugin_updates_changed		(GsPlugin	*plugin);
void		 gs_plugin_reload			(GsPlugin	*plugin);
const gchar	*gs_plugin_status_to_string		(GsPluginStatus	 status);
void		 gs_plugin_report_event			(GsPlugin	*plugin,
							 GsPluginEvent	*event);
void		 gs_plugin_set_allow_updates		(GsPlugin	*plugin,
							 gboolean	 allow_updates);
gboolean	 gs_plugin_get_network_available	(GsPlugin	*plugin);
void		 gs_plugin_basic_auth_start		(GsPlugin	*plugin,
							 const gchar	*remote,
							 const gchar	*realm,
							 GCallback	 callback,
							 gpointer	 user_data);
void		gs_plugin_repository_changed		(GsPlugin	*plugin,
							 GsApp		*repository);
void		gs_plugin_update_cache_state_for_repository
							(GsPlugin *plugin,
							 GsApp *repository);
gboolean	gs_plugin_get_action_supported		(GsPlugin	*plugin,
							 GsPluginAction	 action);
gboolean	gs_plugin_ask_user_accepts		(GsPlugin	*plugin,
							 const gchar	*title,
							 const gchar	*msg,
							 const gchar	*details,
							 const gchar	*accept_label);

G_END_DECLS
