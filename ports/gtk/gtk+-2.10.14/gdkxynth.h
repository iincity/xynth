
#include <config.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <xynth.h>

#include "gdk.h"
#include "gdkwindow.h"

#include "gdkregion-generic.h"

#include "gdkinternals.h"
#include "gdkalias.h"

#define XYNTH_DEBUG 98

#if XYNTH_DEBUG != 0
#define DEBUG(fmt...) {\
	printf(fmt);\
	printf(" [%s (%s:%d)]\n", __FUNCTION__, __FILE__, __LINE__);\
}
#else
#define DEBUG(fmt...) do { } while (0)
#endif

#if XYNTH_DEBUG == 99
#define ENTER() DEBUG("Enter");
#define LEAVE() DEBUG("Leave");
#else
#define ENTER() do { } while (0)
#define LEAVE() do { } while (0)
#endif

#define NIY()   {\
	DEBUG("Not Implemented Yet");\
}

#define ASSERT() {\
	DEBUG("This should not happen");\
	assert(0);\
}

#define ERROR(fmt...) {\
	DEBUG("ERROR" fmt); \
	ASSERT(); \
}

G_BEGIN_DECLS

/* gdkcursor-xynth */

typedef struct _GdkCursorXYNTH GdkCursorXYNTH;

struct _GdkCursorXYNTH {
	GdkCursor cursor;
	gint hot_x;
	gint hot_y;
	s_surface_t *surface;
};

/* gdkdisplay-xynth.c */

typedef struct _GdkDisplayXYNTH           GdkDisplayXYNTH;
typedef struct _GdkDisplayXYNTHClass      GdkDisplayXYNTHClass;

#define GDK_TYPE_DISPLAY_XYNTH            (gdk_display_xynth_get_type())
#define GDK_DISPLAY_XYNTH(object)         (G_TYPE_CHECK_INSTANCE_CAST((object), GDK_TYPE_DISPLAY_XYNTH, GdkDisplayXYNTH))
#define GDK_DISPLAY_XYNTH_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),     GDK_TYPE_DISPLAY_XYNTH, GdkDisplayXYNTHClass))
#define GDK_IS_DISPLAY_XYNTH(object)      (G_TYPE_CHECK_INSTANCE_TYPE((object), GDK_TYPE_DISPLAY_XYNTH))
#define GDK_IS_DISPLAY_XYNTH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),     GDK_TYPE_DISPLAY_XYNTH))
#define GDK_DISPLAY_XYNTH_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj),     GDK_TYPE_DISPLAY_XYNTH, GdkDisplayXYNTHClass))

struct _GdkDisplayXYNTH {
	GdkDisplay parent;
	s_window_t *xynth;
};

struct _GdkDisplayXYNTHClass {
	GdkDisplayClass parent;
};

GType gdk_display_xynth_get_type (void);
s_surface_t * gdk_display_xynth_create_surface (GdkDisplayXYNTH *display, int bpp, int width, int height);

/* gdkdrawable-xynth.c */

typedef struct _GdkDrawableImplXYNTH      GdkDrawableImplXYNTH;
typedef struct _GdkDrawableImplXYNTHClass GdkDrawableImplXYNTHClass;

#define GDK_TYPE_DRAWABLE_IMPL_XYNTH       (gdk_drawable_impl_xynth_get_type())
#define GDK_DRAWABLE_IMPL_XYNTH(object)    (G_TYPE_CHECK_INSTANCE_CAST((object), GDK_TYPE_DRAWABLE_IMPL_XYNTH, GdkDrawableImplXYNTH))
#define GDK_IS_DRAWABLE_IMPL_XYNTH(object) (G_TYPE_CHECK_INSTANCE_TYPE((object), GDK_TYPE_DRAWABLE_IMPL_XYNTH))

struct _GdkDrawableImplXYNTH {
	GdkDrawable           parent_object;
	GdkDrawable           *wrapper;
	gboolean              buffered;
	GdkRegion             *paint_region;
	gint                  paint_depth;
	gint                  width;
	gint                  height;
	gint                  abs_x;
	gint                  abs_y;
	GdkColor              color;
	GdkColormap           *colormap;
	s_surface_t           *surface;
	cairo_surface_t       *cairo_surface;
};

struct _GdkDrawableImplXYNTHClass {
	GdkDrawableClass parent_class;
};

GType gdk_drawable_impl_xynth_get_type (void);

/* gdppixmap-xynth.c */

typedef struct _GdkPixmapImplXYNTH           GdkPixmapImplXYNTH;
typedef struct _GdkPixmapImplXYNTHClass      GdkPixmapImplXYNTHClass;

struct _GdkPixmapImplXYNTH {
	GdkDrawableImplXYNTH parent_instance;
};

struct _GdkPixmapImplXYNTHClass {
	GdkDrawableImplXYNTHClass parent_class;
};

GType gdk_pixmap_impl_xynth_get_type (void);

/* gdkevents-xynth.c */

void _gdk_events_init (void);
guint32 gdk_xynth_get_time (void);
GdkWindow * gdk_xynth_child_at (GdkWindow *window, gint *winx, gint *winy);
void gdk_xynth_event_windows_add (GdkWindow *window);

/* gdkwndow-xynth.c */

typedef struct _GdkWindowImplXYNTH      GdkWindowImplXYNTH;
typedef struct _GdkWindowImplXYNTHClass GdkWindowImplXYNTHClass;

#define GDK_TYPE_WINDOW_IMPL_XYNTH         (gdk_window_impl_xynth_get_type())
#define GDK_WINDOW_IMPL_XYNTH(object)      (G_TYPE_CHECK_INSTANCE_CAST((object), GDK_TYPE_WINDOW_IMPL_XYNTH, GdkWindowImplXYNTH))
#define GDK_IS_WINDOW_IMPL_XYNTH(object)   (G_TYPE_CHECK_INSTANCE_TYPE((object), GDK_TYPE_WINDOW_IMPL_XYNTH))
#define GDK_WINDOW_XYNTH_ID(win)           (GDK_WINDOW_IMPL_XYNTH(GDK_WINDOW_OBJECT(win)->impl)->xynth_id)

struct _GdkWindowImplXYNTH {
	GdkDrawableImplXYNTH drawable;
	GdkWindow            *gdkWindow;
	
	s_window_t           *xynth;
	int                  xynth_id;
	int                  input_only;
	
	GdkCursor            *cursor;
	GHashTable           *properties;
	
	GdkWindowTypeHint    type_hint;
};

struct _GdkWindowImplXYNTHClass {
	GdkDrawableImplXYNTHClass parent_class;
};

void _gdk_windowing_window_init (void);

/* gdkdnd-xynth.c */

void _gdk_dnd_init (void);

/* gdkkeys-xynth.c */

void _gdk_xynth_keyboard_init (void);

/* gdkvisual-xynth.c */

void _gdk_visual_init (void);

/* gdkgc-xynth.c */

typedef struct _GdkGCXYNTH      GdkGCXYNTH;
typedef struct _GdkGCXYNTHClass GdkGCXYNTHClass;

#define GDK_TYPE_GC_XYNTH       (gdk_gc_xynth_get_type())
#define GDK_GC_XYNTH(object)    (G_TYPE_CHECK_INSTANCE_CAST((object), GDK_TYPE_GC_XYNTH, GdkGCXYNTH))
#define GDK_IS_GC_XYNTH(object) (G_TYPE_CHECK_INSTANCE_TYPE((object), GDK_TYPE_GC_XYNTH))

struct _GdkGCXYNTH {
	GdkGC           parent_instance;
	GdkRegion       *clip_region;
	GdkGCValuesMask values_mask;
	GdkGCValues     values;
};

struct _GdkGCXYNTHClass {
	GdkGCClass      parent_class;
};

GdkGC * _gdk_xynth_gc_new (GdkDrawable *drawable, GdkGCValues *values, GdkGCValuesMask values_mask);

/* gdkimage-xynth.c */

void _gdk_windowing_image_init (void);
GdkImage * _gdk_xynth_copy_to_image (GdkDrawable *drawable, GdkImage *image, gint src_x, gint src_y, gint dest_x, gint dest_y, gint width, gint height);

/* gdkinput-xynth.c */

struct _GdkDeviceClass {
	GObjectClass parent_class;
};

void _gdk_input_init (void);
void gdk_xynth_mouse_get_info (gint *x, gint *y, GdkModifierType *mask);

/* gdkmain-xynth.c */

GdkWindow * gdk_xynth_other_event_window (GdkWindow *window, GdkEventType type);
GdkWindow * gdk_xynth_keyboard_event_window (GdkWindow *window, GdkEventType type);
GdkWindow * gdk_xynth_pointer_event_window (GdkWindow *window, GdkEventType type);
GdkEvent * gdk_xynth_event_make (GdkWindow *window, GdkEventType type);

/* gdkwindow-xynth.c */

void gdk_xynth_window_id_table_remove (int xynth_id);
void gdk_xynth_window_id_table_insert (int xynth_id, GdkWindow *window);
GdkWindow * gdk_xynth_window_id_table_lookup (int xynth_id);
void _gdk_xynth_calc_abs (GdkWindow *window);
void _gdk_xynth_move_resize_child (GdkWindow *window, gint x, gint y, gint width, gint height);
GdkWindow * gdk_xynth_other_event_window (GdkWindow *window, GdkEventType type);
void gdk_xynth_change_focus (GdkWindow *new_focus_window);

/* gdkglobals-xynth.c */

extern GdkDisplayXYNTH *_gdk_display;
extern GdkScreen       *_gdk_screen;
extern GdkVisual       *system_visual;
extern GdkWindow       *_gdk_parent_root;
extern GdkWindow       *_gdk_xynth_pointer_grab_window;
extern GdkCursor       *_gdk_xynth_pointer_grab_cursor;
extern gboolean         _gdk_xynth_pointer_grab_owner_events;
extern GdkEventMask     _gdk_xynth_pointer_grab_events;
extern GdkWindow       *_gdk_xynth_keyboard_grab_window;
extern gboolean         _gdk_xynth_keyboard_grab_owner_events;
extern GdkEventMask     _gdk_xynth_keyboard_grab_events;

extern int              _gdk_xynth_mouse_x;
extern int              _gdk_xynth_mouse_y;
extern GdkModifierType  _gdk_xynth_modifiers;

G_END_DECLS
