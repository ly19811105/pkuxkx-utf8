//wuguan_liangong.c Zine
#include <ansi.h>
inherit ROOM;
void create()
{
set("short", "练功场");
set("long", @LONG
这里是太乙武馆的练功场，地面上放着几个石锁(shisuo)，几个年轻弟子正
在用石锁练习着臂力。
LONG );
set("exits",  ([
        "east"   : __DIR__"wuguan_dating",
      ]));
set("item_desc", ([
   	"shisuo":"一副石锁，恐怕至少有百八斤的份量。你可以举(ju)起来练习臂力。\n",
   ]) );set("objects",([
	       __DIR__"npc/dizi.c":2,
           __DIR__"obj/suo":2,

	]));
    
    set("lingwu_family", "百姓");
    setup();
}

int valid_leave(object me,string dir)//不许带走石锁
{
    int i;
    object *all_ob=deep_inventory(me);
    for (i=0;i<sizeof(all_ob);i++)
    {
        if (all_ob[i]->query("is_shisuo"))
        {
            return notify_fail("你想把武馆的石锁带去哪里？\n");
        }
    }
    return ::valid_leave(me,dir);
}

void init()
{
    add_action("do_get","get");
}

int do_get(string arg)
{
    object me=this_player();
    int i;
    object *all_ob=deep_inventory(me);
    if (arg=="all")
    {
        tell_object(me,"东西要一样一样的拿！\n");
        return 1;
    }
    if (arg=="shi suo"||arg=="suo")
    {
        for (i=0;i<sizeof(all_ob);i++)
        {
            if (all_ob[i]->query("is_shisuo"))
            {
                tell_object(me,"你想身上不是已经有一副石锁了吗？\n");
                return 1;
            }
        }
    }
}