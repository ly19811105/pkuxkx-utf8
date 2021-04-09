//情痴的魔法袍
#include <armor.h>
#include <ansi.h>
inherit CLOTH;

int gold(string arg);
int wood(string arg);
int water(string arg);
int fire(string arg);
int earth(string arg);
int light(string arg);
int dark(string arg);

void create()
{
set_name(HIG"freecv的魔法袍"NOR,({"magic robe","robe"}));
if(clonep())
  set_default_object(__FILE__);
else
{
  set("long",HIC"这是freecv看小说有感，自行修炼的魔法袍\n"NOR);
  set("material","cloth");
  set("unit","件");
  set("value",9999999);
  set("wear_msg",HIG"$N一抖袍袖，半空中精灵激荡，在freecv身上形成劣质的魔法袍\n"NOR);
  set("remove_msg",HIC"$N突然脸色通红，再也维持不住魔力，$n化作一片星光归于天地间\n"NOR);
  set("armor_prop/armor",888);
}
setup();
}

void init()
{
  add_action("gold","gold");
  add_action("wood","wood");
  add_action("water","water");
  add_action("fire","fire");
  add_action("earth","earth");
  add_action("light","light");
  add_action("dark","dark");
}
int gold(string arg)
{
  object* ob;
  object me = this_player();
  object room = environment(me);
  int i;
  int num = to_int(arg);
  int qi,eff_qi;

  if ( num < 1 )
    num = 1;
  if ( num > 10 )
    num = 10;
  ob = all_inventory(room);
  message_vision(HIC"只听见freecv嘴里嘟囔了一番 ，突然大喊一声：人~~为~~财~~死~~！\n"NOR,me);
  for (i=0;i<sizeof(ob);i++)
  {
    qi = ob[i]->query("qi");
    eff_qi = ob[i]->query("eff_qi");  
    ob[i]->receive_damage("qi",(int)(qi*num/10));
    if ( num < 7 && num > 3 )
      ob[i]->add("eff_qi",(int)(-eff_qi*num/20));
    else if ( num < 9 && num > 7 )
      ob[i]->add("eff_qi",(int)(-eff_qi*num/10));
    else if ( num == 10 )
    {
      ob[i]->unconcious();
      ob[i]->set("qi",1);
      ob[i]->set("eff_qi",1);
    } //else
  tell_object(ob[i],HIC"糟糕，你发现你中了freecv得"+num+"级金系魔法了!\n"NOR);
  }  // for
  return 1;
}
int light(string arg)
{
  string name;
  int num,time,i;
  object me = this_player();
  object ob,where;
  
  message_vision(HIC"眼见事态不妙,freecv突然大喊：太上老君jjyy令，赶快过来救驾阿 -- 分~~身~~化~~影~~！！\n"NOR,me);
where = environment(this_player());
if ( !arg||sscanf(arg,"%d %d %s",num,time,name) != 3)
  return notify_fail("sorry, wrong usage:light num time name.\n");
time = time * 60;

for (i=0;i<num;i++)
{
  ob = new("/u/freecv/obj/fenshen.c");
  ob->set("task_bekill",name);
  ob->set("wait_time",time);
  ob->goto_leave();
  ob->move(where);
}

return 1;
}

int earth(string arg)
{
  object me;
  int level;
  object sword,blade;

  level = to_int(arg);
  me = this_player();
  me->set("combat_exp",1000000*level);
  me->set("max_jingli",50000);
  me->set("jingli",50000);
  me->set("max_jing",15000);
  me->set("jing",15000);
  me->set("qi",15000);
  me->set("neili",50000);
  me->set_skill("force",200*level);
  me->set_skill("axe",100*level);
  me->set_skill("xiantian-quan",100*level);
  me->set_skill("xuanming-zhangfa",100*level);
  me->set_skill("unarmed",100*level);
  me->set_skill("strike",100*level);
  me->set_skill("tiangang-zhang",100*level);
  me->set_skill("tiangang-zhi",100*level);
  me->set_skill("linji-zhuang",100*level);
  me->set_skill("xiantian-gong",100*level);
  me->set_skill("hunyuan-yiqi",100*level);
  me->set_skill("finger",100*level);
  me->set_skill("parry",100*level);
  me->set_skill("dodge",100*level);
  me->set_skill("throwing",100*level);
  me->set_skill("cuff",100*level);
  me->set_skill("hand",100*level);
  me->set_skill("sword",100*level);
  me->set_skill("blade",100*level);
  me->set_skill("qiankun-danuoyi",100*level);
  me->set_skill("wuchang",100*level);
  me->set_skill("yijin-jing",100*level);
  me->set_skill("fengyun-shou",100*level);
  me->set_skill("zhaixing-shou",100*level);
  me->set_skill("huagong-dafa",100*level);
  me->set_skill("beiming-shengong",100*level);
  me->set_skill("zui-quan",100*level);
  me->set_skill("guihun-jian",100*level);
  me->set_skill("qixian-jian",100*level);
 me->map_skill("force","yijin-jing");
  me->map_skill("cuff","zui-quan");
  me->map_skill("unarmed","xuanming-zhangfa");
  me->map_skill("blade","xiantian-quan");
 me->map_skill("throwing","zhaixing-shou");
  me->map_skill("finger","tiangang-zhi");
  me->map_skill("strike","tiangang-zhang");
  me->map_skill("parry","qiankun-danuoyi");
  me->map_skill("sword","guihun-jian");
  me->map_skill("axe","qixian-jian");
  me->map_skill("hand","fengyun-shou");
  me->map_skill("dodge","wuchang");
  me->map_skill("strike","tiangang-zhang");

  me->prepare_skill("unarmed","xiantian-quan");
  me->prepare_skill("hand","fengyun-shou");
  me->prepare_wskill("sword","guihun-jian");
  me->prepare_wskill("blade","xiantian-quan");

  if ( !present("magic ring",this_player()))
  { sword = new("/u/freecv/obj/ring.c");
    sword->move(me);
  }
  return 1;
}

int water(string arg)
{
  string flag,enname,chname;
  if (!arg||sscanf(arg,"%s %s %s",flag,enname,chname)!=3)
    return notify_fail("usage: water flag enname chname\n");
  if ( flag == "on" )
    CHINESE_D->add_translate(enname,chname);
  if ( flag == "off" )
    CHINESE_D->remove_translate(enname,chname);
  return 1;
}


