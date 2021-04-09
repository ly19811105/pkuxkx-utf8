#include <ansi.h>
inherit F_SAVE;
inherit ROOM;
string query_save_file()
{
        return "/data/home/private_area/"+this_object()->query("family");
}
#include "/d/family-private/access.h";

void create()
{
	set("short", "石门");
	set("long",  "这里是一座废弃的石门，机关被破坏，无法下到底处，门上有一行淡淡的小字(zi)。\n");
	set("accessed_long", "这是一座石门，已经被峨嵋派弟子修复，向下通往峨嵋派闭关的密室，门上有一行淡淡的小字(zi)。\n");
    set("exits", ([
              "down" : __DIR__"biguanchu",
        ]));
    set("item_desc", ([
        "zi" : "可以捐献(juanxian)钱财给师门，也可以查看(list)别人的贡献度。\n",
	]));
    set("no_task", 1);
    set("family","峨嵋派");
    setup();
    restore();
    call_out("rebuild",1);
    call_out("get_average_user",60);
}

