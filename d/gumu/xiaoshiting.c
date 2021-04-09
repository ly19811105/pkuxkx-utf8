// Room: /d/gumu/xiaoshiting.c
 
inherit ROOM; 
 
void create() 
{ 
        set("short", "小石厅");
        set("long", @LONG
       这是一间小石厅，布置得很整齐。靠北有一个小石椅，
椅上坐着位少女，正在教旁边的几个少女吹箫

LONG
        );
        set("no_sleep_room", 1);
       
  set("exits", ([ 
    "east"  : __DIR__"mudao6",
]));

  set("objects",([CLASS_D("gumu")+"/xiaohong":1,__DIR__"npc/xiao":4,__DIR__"npc/girl":3,]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
 
