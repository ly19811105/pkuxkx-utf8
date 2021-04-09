// Room: /d/sanyen/kitchen.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "厨房");
        set("long", @LONG
一间整理相当干净的厨房, 西北边的角落里砌了两个大灶, 灶里正燃著火, 
灶上分别放著一个大锅(pot) 及一个蒸笼(steampot)。锅子及蒸笼正冒著阵阵的
热气以及香气, 你忍不住想打开来看看。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
        "south" : __DIR__"zhaitang.c",
]));

        set("item_desc", ([
            "pot": "一个冒著腾腾的热气的黑色大铁锅, 里头正煮著小米粥。\n",
            "steampot": "一个竹藤编成的蒸笼, 阵阵的香味使你想打开(open)来瞧一瞧。\n"
]) );
				set("kitchen", 1);
        set("objects", ([
            __DIR__"npc/cook_bonze" : 1 ]) );
	set("no_clean_up", 0);

	setup();
}

void init()
{
    object me=this_player();
   add_action("do_open", ({"open"}) );
   add_action("do_take", ({"take"}) );
   if (me->query_skill("fx-step"))
   {
       me->set_skill("jinyan-gong",me->query_skill("fx-step",1));
       me->delete_skill("fx-step");
       me->set_skill_mapped("dodge","jinyan-gong");
       tell_object(me,HIM+BLINK+"你的飞仙步已经被自动转化成金雁功。\n"NOR);
   }
}

int do_open(string arg)
{
   if (!arg||arg!="steampot")
      return notify_fail("你要打开什么？\n");
   if (!present("cook bonze"))
      {
	message_vision("$N打开蒸笼的盖子, 一股热气冒向$N的脸上。\n"
                      "$N仔细一看, 只见蒸笼里排著一粒粒又白又Ｑ的大馒头(maintal)。\n",this_player());
       return 1;
      }
   else
      {
       message_vision("烧饭道士说:请勿动手动脚, 妨碍我煮饭。\n",
this_player());
       return 1;
      }
}

int do_take(string str)
{
   object ob;
   if (!str||str!="maintal")
       return notify_fail("你要拿什么？\n");
   if (!present("cook bonze"))
      {
       if ((int)query("maintal_trigger")>=5)
          {
           return notify_fail("突然房间里好像传来梦忆柔的声音说拿太多小心吃到噎著哦!!\n");
          }
       else
          {
           message_vision("$N从蒸笼里拿出一粒热乎乎的馒头。\n",this_player());
           ob=new(__DIR__"npc/obj/maintal");
           ob->move(this_player());
           add("maintal_trigger",1);
           return 1;
          }
      }
   else
      {
       message_vision("烧饭道士说: 施主偷东西是不好的行为哦!!!\n",this_player());
       return 1;
      }
}

void reset()
{
        ::reset();
        delete("maintal_trigger");
}
