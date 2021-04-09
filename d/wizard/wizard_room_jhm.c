#include <ansi.h>;

inherit ROOM;

void create()
{
set("short", HIR"随风工作室"NOR);
        set("long", @LONG
LONG NOR);

        set("exits", ([
                "south" : "/d/city/guangchang",
                "southeast" : "/d/city/biwuchang",
        "west" : __DIR__"dream_room" ,
        "southwest" : "/d/city/mingren" ,


             "north" : "/d/wizard/wizard_room_whuan",

        ]));
        set("objects", ([
        ]));

        set("valid_startroom", 1);

        setup();
}

void init()
{
        object me = this_player();
        add_action("do_search","search");
        if(me->query("id") == "ztpal")
        {
                me->move("/d/city/guangchang");
                me->delete("env/immortal");
                me->delete("invisibility");
                me->die();
                message("channel:rumor",HIM"【谣言】听说"+me->query("name")+HIM"从"HIY"香蕉树"HIM"上掉到中央广场摔死了！\n"NOR,users());
        }
        return;
}

int do_search()
{
        object me = this_player();
        object obj = random(20)<14 ? new("/clone/story/obj/lingzhi.c") : new("/d/xiangyang/npc/obj/shanlw.c");
        message_vision("$N在树洞里四下搜寻着，找到一颗"+obj->query("name")+"！\n", me);
        message_vision("只可惜一股强大的内力袭来，$N不得不将它丢掉。\n", me);
        destruct(obj);

        return 1;
}
void alternative_die (object me)
{
         object ob;
          ob = me->get_damage_origin_object();
          if (! ob)
            return;  
          
          if(!userp(ob)){
                destruct (ob);
                return ;
                }
          if(!userp(me)){
                destruct (me);
                return ;
                }
}
