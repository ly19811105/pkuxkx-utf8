#include <ansi.h>
inherit ROOM;

void create()
{ 
       set("short",HIC"石室"NOR);
       set("long", @LONG
室中也无特异之处，你抬头仰望，但见室顶密密麻麻的写满了字迹符号，
你看了一会，但觉奥妙难解。室顶西南角绘著一幅图，似与武功无关，凝神细
看，倒像是幅地图。石室右下方好象可以往下(down)走。
LONG
     );
        set("item_desc", ([
             "down": HIB"黑乎乎的，看不真切。\n"NOR,
        ]));
        set("exits", ([
              "up" : __DIR__"shiguan",                 
        ]));
        setup();
}

void init()
{
        add_action("do_look", "look"); 
        add_action("do_look", "kan");
        add_action("do_walk", "walk");
        add_action("do_study", "yandu");
}

int do_look(string arg)
{
        object me=this_player();
        if ( arg =="map") {
            write(HIY"你凝望著那幅图，心中不由大喜，原来那绘的正是出墓的秘道。\n"NOR);
            me->set_temp("map", 1);
            me->start_busy(1);
            return 1;         
        }
        if ( arg =="ceiling") {
            write(HIY"你看着室顶，满满的都是密密麻麻的小字。\n"NOR);
            me->set_temp("ceiling", 1);
            me->start_busy(1);
            return 1;         
        }
        if ( arg =="zi") {
            write(HIY"你望著那些小字，似乎都是一些武功要诀。\n"NOR);
            if( !me->query_temp("ceiling")
             || me->query("combat_exp", 1) < 1000000 ){
               tell_object(me,HIY"不过上面写的艰深难懂，你看了一会就放弃了。\n"NOR);
               return 1;
            }
            if(( random(me->query_kar()) > 22
             && me->query("jiuyin/gumufail") < 3 
               && random(me->query_int()) > 25)
             || me->query("jiuyin/gumu")){
              write(HIW"你陡然一瞥间，看到几个小字“九阴真经内功要诀”，你兴奋极了。\n"NOR);
              write(HIW"你研究了一下，发现应该能研读(yandu)些大伏魔拳法(dafumo-quan)、\n"NOR);
              write(HIW"九阴真功(jiuyin-zhengong)以及九阴身法(jiuyin-shenfa)的皮毛。\n"NOR);
              if( !me->query("jiuyin/gumu"))
              log_file("quest/jiuyin",sprintf("%s %s(%s)失败%s次后，在古墓石壁上得到九阴真经。\n",
                  ctime(time())[4..19], me->name(1),capitalize(getuid(me)),chinese_number(me->query("jiuyin/gumufail")) ));
              me->set("jiuyin/gumu", 1);
            }
            else {
              if( me->query("jiuyin/gumufail") <= 3 )
              me->add("jiuyin/gumufail", 1);
              if ( me->query("jiuyin/gumufail") < 3 )
              log_file("quest/jiuyin",sprintf("%s %s(%s)错过%s次，没有发现古墓石壁上的九阴真经。\n",
                      ctime(time())[4..19], me->name(1),capitalize(getuid(me)),chinese_number(me->query("jiuyin/gumufail")) )); 
              if( me->query("jiuyin/gumufail") == 3)
              log_file("quest/jiuyin",sprintf("%s %s(%s)错过三次，无法再发现古墓石壁上的九阴真经。\n",
                      ctime(time())[4..19], me->name(1),capitalize(getuid(me)))); 
              write(HIY"不过上面写的艰深难懂，你看了一会就放弃了。\n"NOR);
            }
            me->delete_temp("ceiling");
            return 1;         
        }
        return notify_fail("你要看什么？\n");
}

int do_walk(string arg)
{ 
        object me=this_player();
        if (me->is_busy() || me->is_fighting())
              return notify_fail("你正忙着哪！\n");
        if ( arg =="down"){ 
//             if(!me->query_temp("map"))
//                   return notify_fail("你伸脚想往下走，但是犹豫再三，又伸回了脚。\n");      
           tell_object(me,HIM"\n你东转西弯，越走越低。同时脚下渐渐潮湿，暗中隐约望去，到处都是岔道。\n"+
                             "再走一会，道路奇陡，竟是笔直向下。下降了约莫半个时辰，这路渐平，只是\n"+
                             "湿气却也渐重，到後来更听到了淙淙水声，路上水没至踝。越走水越高，自腿\n"+
                             "而腹，渐与胸齐。\n"NOR);
           me->delete_temp("map");
           me->move(__DIR__"gmanhe1");
           tell_room(environment(me), me->name() + "从"HIC"石室"NOR"快步走了过来。\n", ({ me }));
           return 1;
        }
        return notify_fail("你在石室里踱来踱去，不知如何是好？\n");
}

int do_study(string arg)
{
      int cost, my_skill;
      object me=this_player();

      if (!arg) return 0;

      if( ! me->query("jiuyin/gumu"))
          return notify_fail("什么？\n");

      if(me->is_busy())
          return notify_fail("你现在正忙着呢。\n");

      if( me->is_fighting() )
          return notify_fail("你无法在战斗中专心下来研读新知！\n");

      if( !me->query_skill("literate", 1) )
          return notify_fail("你是个文盲，先学点文化(literate)吧。\n");

      if((int)me->query("potential") < 1 )
          return notify_fail("你的潜能已经用完了，再怎么读也没用。\n");

      if((int)me->query("combat_exp") < 1000000 )
          return notify_fail("你的实战经验不足，再怎么读也没用。\n");

      if( me->query_int() < 40 )
          return notify_fail("以你目前的领悟能力，还没有办法学这个技能。\n");

      cost = 40 * ( 1 + ( 35 - (int)me->query("int"))/20 );
      if (cost < 20) cost = 20;
      if( me->query("neili") < cost * 2 + 300)
          return notify_fail("你的内力不够，无法领会这个技能。\n");
      me->set_temp("last_damage_from", "研读高深武功，熬尽心机累");

      switch (arg) {
        case "jiuyin-zhengong":
          my_skill = me->query_skill("jiuyin-zhengong", 1);
          if( my_skill >= 150)
              return notify_fail("你觉得这洞壁上所刻已经太浅了，不能学到什么东西。\n");
          if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
              return notify_fail("也许是缺乏实战经验，你对洞壁上所刻总是无法领会。\n");
          else
              write("你研读着有关九阴真功的技巧，似乎有些心得。\n");
          me->improve_skill("jiuyin-zhengong", ((int)me->query_skill("literate", 1)/5 + 1));
          me->receive_damage("jing", cost );
          me->add("neili", -cost * 2);
          me->add("potential", - random(2));
          break;             
        case "jiuyin-shenfa":
          my_skill = me->query_skill("jiuyin-shenfa", 1);
          if( my_skill >= 150)
              return notify_fail("你觉得这洞壁上所刻已经太浅了，不能学到什么东西。\n");
          if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
              return notify_fail("也许是缺乏实战经验，你对洞壁上所刻总是无法领会。\n");
          else
              write("你研读着有关九阴身法的技巧，似乎有些心得。\n");
          me->improve_skill("jiuyin-shenfa", ((int)me->query_skill("literate", 1)/5+1));
          me->receive_damage("jing", cost );
          me->add("neili", -cost * 2);
          me->add("potential", - random(2));
          break;
        case "dafumo-quan":
          my_skill = me->query_skill("dafumo-quan", 1);
          if( my_skill >= 150)
              return notify_fail("你觉得这洞壁上所刻已经太浅了，不能学到什么东西。\n");
          if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
              return notify_fail("也许是缺乏实战经验，你对洞壁上所刻总是无法领会。\n");
          else
              write("你研读着有关大伏魔拳法的技巧，似乎有些心得。\n");
          me->improve_skill("dafumo-quan", ((int)me->query_skill("literate", 1)/5+1));
          me->receive_damage("jing", cost );
          me->add("neili", -cost * 2);
          me->add("potential", - random(2));
          break;
      }
      return 1;
}

