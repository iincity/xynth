/***************************************************************************
    begin                : Wed Mar 9 2005
    copyright            : (C) 2005 - 2006 by Alper Akcan
    email                : distchx@yahoo.com
  ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "xynth_.h"

typedef struct main_data_s {
	s_object_t *objectp;
	s_object_t *objectc[4];
	s_object_t *objectcc[4];
} main_data_t;

static void handler0_p (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
        main_data_t *mdata = (main_data_t *) window->client->user_data;
	s_putbox(window->surface, 10, 50, mdata->objectp->surface->width, mdata->objectp->surface->height, mdata->objectp->surface->vbuf);
}

static void handler1_p (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	int i;
	int j;
        main_data_t *mdata = (main_data_t *) window->client->user_data;

	for (i = 0; i < 4; i++) {
		s_object_move(mdata->objectc[i], ((unsigned) rand()) % mdata->objectc[i]->parent->surface->width,
		                                 ((unsigned) rand()) % mdata->objectc[i]->parent->surface->height,
		                                 ((unsigned) rand()) % mdata->objectc[i]->parent->surface->width,
		                                 ((unsigned) rand()) % mdata->objectc[i]->parent->surface->height
		                                 );
		if (i == 0) {
			for (j = 0; j < 4; j++) {
				s_object_move(mdata->objectcc[j], ((unsigned) rand()) % mdata->objectcc[j]->parent->surface->width,
			        	                          ((unsigned) rand()) % mdata->objectcc[j]->parent->surface->height,
			                		 	  ((unsigned) rand()) % mdata->objectcc[j]->parent->surface->width,
				                                  ((unsigned) rand()) % mdata->objectcc[j]->parent->surface->height
				                                  );
			}
		}
	}

	handler0_p(window, event, handler);
}

static void handler2_p (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	int i;
        main_data_t *mdata = (main_data_t *) window->client->user_data;

        i = rand() % 4;
	s_object_show(mdata->objectc[i]);
	s_object_show(mdata->objectcc[i]);

	handler0_p(window, event, handler);
}

static void handler3_p (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
        main_data_t *mdata = (main_data_t *) window->client->user_data;

	s_thread_mutex_lock(mdata->objectc[0]->mut);
	s_fillbox(mdata->objectc[0]->surface, 10,
	                                      10,
	                                      mdata->objectc[0]->surface->width - 20,
	                                      mdata->objectc[0]->surface->height - 20,
	                                      s_rgbcolor(mdata->objectc[0]->surface, rand() % 255, rand() % 255, rand() % 255));
	s_object_update(mdata->objectc[0], &mdata->objectc[0]->surface->win);
	s_thread_mutex_unlock(mdata->objectc[0]->mut);
	handler0_p(window, event, handler);
}

int main (int argc, char *argv[])
{
        int c = 0;
        int i = 0;
        int j = 0;
	int x = 60;
	int y = 60;
	int w = 400;
	int h = 300;
	int mw = 1000;
	int mh = 1000;
	s_handler_t *hndl;
	s_window_t *window;
	main_data_t *mdata;

	srand(time(NULL));

	s_client_init(&window);

	s_window_new(window, WINDOW_MAIN, NULL);
	mw = window->surface->width;
	mh = window->surface->height;

	s_window_set_title(window, "Demo - %s", argv[0]);
	s_window_set_coor(window, 0, x, y, MIN(mw, w), MIN(mh, h));

	s_fillbox(window->surface, 0, 0, 20, 20, s_rgbcolor(window->surface, 222, 222, 222));
	s_fillbox(window->surface, 2, 2, 16, 16, s_rgbcolor(window->surface, 255, 0, 0));
	s_handler_init(&hndl);
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = 0;
	hndl->mouse.y = 0;
	hndl->mouse.w = 20;
	hndl->mouse.h = 20;
	hndl->mouse.p = handler0_p;
	hndl->mouse.button = MOUSE_LEFTBUTTON;
	s_handler_add(window, hndl);

	s_fillbox(window->surface, 20, 0, 20, 20, s_rgbcolor(window->surface, 222, 222, 222));
	s_fillbox(window->surface, 22, 2, 16, 16, s_rgbcolor(window->surface, 255, 0, 0));
	s_handler_init(&hndl);
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = 20;
	hndl->mouse.y = 0;
	hndl->mouse.w = 20;
	hndl->mouse.h = 20;
	hndl->mouse.p = handler1_p;
	hndl->mouse.button = MOUSE_LEFTBUTTON;
	s_handler_add(window, hndl);

	s_fillbox(window->surface, 40, 0, 20, 20, s_rgbcolor(window->surface, 222, 222, 222));
	s_fillbox(window->surface, 42, 2, 16, 16, s_rgbcolor(window->surface, 255, 0, 0));
	s_handler_init(&hndl);
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = 40;
	hndl->mouse.y = 0;
	hndl->mouse.w = 20;
	hndl->mouse.h = 20;
	hndl->mouse.p = handler2_p;
	hndl->mouse.button = MOUSE_LEFTBUTTON;
	s_handler_add(window, hndl);

	s_fillbox(window->surface, 60, 0, 20, 20, s_rgbcolor(window->surface, 222, 222, 222));
	s_fillbox(window->surface, 62, 2, 16, 16, s_rgbcolor(window->surface, 255, 0, 0));
	s_handler_init(&hndl);
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = 60;
	hndl->mouse.y = 0;
	hndl->mouse.w = 20;
	hndl->mouse.h = 20;
	hndl->mouse.p = handler3_p;
	hndl->mouse.button = MOUSE_LEFTBUTTON;
	s_handler_add(window, hndl);

	mdata = (main_data_t *) s_malloc(sizeof(main_data_t));
	window->client->user_data = (void *) mdata;
	
	s_object_init(window, &(mdata->objectp), 500, 500, NULL);
	for (i = 0; i < 4; i++) {
		s_object_init(window, &(mdata->objectc[i]), 100, 100, mdata->objectp);
		switch (i) {
			case 0: c = s_rgbcolor(mdata->objectc[i]->surface, 255, 0, 0); break;
			case 1: c = s_rgbcolor(mdata->objectc[i]->surface, 0, 255, 0); break;
			case 2: c = s_rgbcolor(mdata->objectc[i]->surface, 0, 0, 255); break;
			case 3: c = s_rgbcolor(mdata->objectc[i]->surface, 255, 255, 255); break;
		}
		s_fillbox(mdata->objectc[i]->surface, 0, 0, mdata->objectc[i]->surface->width, mdata->objectc[i]->surface->height, c);

		if (i == 0) {
			for (j = 0; j < 4; j++) {
				s_object_init(window, &(mdata->objectcc[j]), 20, 20, mdata->objectc[i]);
				switch (j) {
					case 0: c = s_rgbcolor(mdata->objectcc[j]->surface, 0, 0, 0); break;
					case 1: c = s_rgbcolor(mdata->objectcc[j]->surface, 0, 255, 0); break;
					case 2: c = s_rgbcolor(mdata->objectcc[j]->surface, 0, 0, 255); break;
					case 3: c = s_rgbcolor(mdata->objectcc[j]->surface, 255, 255, 255); break;
				}
				s_fillbox(mdata->objectcc[j]->surface, 0, 0, mdata->objectcc[j]->surface->width, mdata->objectcc[j]->surface->height, c);
			}
		}
	}

	s_window_set_coor(window, WINDOW_NOFORM, window->surface->buf.x, window->surface->buf.y,
	                                         mdata->objectp->surface->width + 20, mdata->objectp->surface->height + 60);
        s_fillbox(window->surface, 0, 40, mdata->objectp->surface->width + 20, mdata->objectp->surface->height + 20, s_rgbcolor(window->surface, 222, 222, 222));

	s_window_show(window);
	s_client_main(window);

	s_object_uninit(mdata->objectp);
	s_free(mdata);

	return 0;
}

#if defined(SINGLE_APP)
s_single_app_t single_object = {
	object_main,
	1,
	{"object"}
};
#endif