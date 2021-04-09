#ifndef __BEIJING_DEFS_H__
#define __BEIJING_DEFS_H__

#define HELPER "/d/beijing/helper.c"	// chu's helper functions
#define HELPER2 "/d/beijing/helper2.c"	// ssy's helper functions
#define TRAVERSER "/clone/obj/traverser.c"

#define IS_SHIWEI(player) (player->query("class") == "officer")
#define PIN(player) (player->query("pin"))
#define day_event() (NATURE_D->outdoor_room_event())

#endif
