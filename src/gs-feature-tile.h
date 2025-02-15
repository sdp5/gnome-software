/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 * vi:set noexpandtab tabstop=8 shiftwidth=8:
 *
 * Copyright (C) 2013 Matthias Clasen <mclasen@redhat.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "gs-app-tile.h"

G_BEGIN_DECLS

#define GS_TYPE_FEATURE_TILE (gs_feature_tile_get_type ())

G_DECLARE_FINAL_TYPE (GsFeatureTile, gs_feature_tile, GS, FEATURE_TILE, GsAppTile)

GtkWidget	*gs_feature_tile_new			(GsApp		*app);

G_END_DECLS
