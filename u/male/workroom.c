//mudy/male's workroom

inherit ROOM;

void create()
{
     set("short","千面");
     set("long",@LONG
千面巫师的行宫二。
LONG
);
    set("exits",([
         "ct":"/d/city/guangchang",
         "wz":"/d/wizard/wizard_room",
		 "west":"/u/mudy/workroom.c",
]));
   set("objects",([
   "/u/male/bigexp":10,
]));
        set("valid_startroom", 1);
        set("sleep_room",1);
setup();
}
