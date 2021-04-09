//wuguan_xiuxi.c  休息室
//by zoom
//2003.3.30

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", "武馆大门");
set("long", @LONG
这是太乙武馆的大门，用红漆漆得光亮的大门正敞开着，左右各有两个武馆
弟子守门，两边的门柱子上还贴着一副对联(duilian)。
LONG );

set("exits",  ([
        "south"  : __DIR__"wuguan_dating.c",
        "northwest"  :  "/d/xiangyang/xyeast1",
        "northeast"  :  "/d/xiangyang/xyeast2", 
    ]));  
set("item_desc", ([
   	"duilian":"\n          精    身\n          气    心\n          神    意\n          由    是\n          我    谁\n          抟    分\n          为    作\n          一    两\n          处    家\n          ！    ？\n                  ——诸葛不亮手书\n",
   ]) );set("objects",([
	       __DIR__"npc/dizi.c":4,

	]));


        setup();
}
