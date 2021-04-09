// Room: /d/quanzhou/hole.c
//玄铁泛滥，将拿到剑的概率降低到1/3
//edit by binlang
//zt3 advent，2/5和1/3是不一样的
inherit ROOM;
int do_pick(string arg);
void create()
{
        set("short", "山洞");
        set("long", @LONG
   这是独孤求败埋剑之所。地板上有三把剑,一把木剑，已经腐烂。
   一把紫葳软剑，但已经不在了。另外一把玄铁剑（sword)，
   旁边刻着“玄铁重剑，无锋不工”。
LONG
        );
    set("item_desc", ([
                "sword": "看起来你需要运足内力（pick）这把剑。\n",
                "剑": "看起来你需要运足内力（pick）这把剑。\n",
               ]));
        setup();
}
void init()
{
 add_action("do_pick","pick");
  add_action("do_swim","swim");
 }
int do_pick(string arg)
{
        object me,sword;
        me=this_player();
        if(!arg||arg!="sword") return notify_fail("你要拾什么?\n");
        if(query_temp("mark/been_get")) return notify_fail("剑已被拿走了。\n");
        if (random(10)<4) 
{
          message_vision( "\n剑已被拿走了。\n",this_player());
                         set_temp("mark/been_get",1);
                        return 1;
}
        if((arg == "sword"||arg == "玄铁剑") && me->query_str()>27 && me->query(
"neili")>500)
 {
          message_vision( "\n$N运起内力将玄铁剑拿了起来。\n",this_player());
                        sword=new(__DIR__"obj/xuantiejian.c");
                        sword->set("weapon_prop/damage",150);
                        sword->move(me);
                            set_temp("mark/been_get",1);
                        return 1;
                        return 1;
                }
        message_vision( "\n$N运足内力,可是玄铁剑稳丝不动。\n",this_player());
      return 1;
}
int do_swim(string arj)
{this_player()->move(__DIR__"hutiaoxia");
  return 1;
}
void reset()
{
    ::reset();
        delete_temp("mark/been_get");
}
