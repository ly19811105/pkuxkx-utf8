// longsword.c 长剑

#include <ansi.h>
#include <weapon.h>
inherit SWORD;
int change(string arg);

void create()
{
       set_name(HIY"freecv的魔法戒指"NOR, ({ "gu qin","magic ring", "ring" }));
        set_weight(1);
	if (clonep())
		set_default_object(__FILE__);
	else {
                set("unit", "枚");
		set("long", "这是一柄普通的精钢剑，一般的剑客都配带此剑。\n");
                set("value", 0);
		set("material", "steel");
                set("wield_msg", HIC"$N小心翼翼的从口袋里掏出一枚蓝色的邪恶戒指戴上\n"NOR);
                set("unwield_msg", HIG"$N恋恋不舍的将戒指放回到口袋中\n"NOR);
	}
	init_sword(25);
	setup();
}

void init()
{
  add_action("change","pfm");
}

int change(string arg)
{
  string tmp,perform_file;
  string kind,action,target;
  int sizes;
  object * sz;
  object me = this_player();
  object target_ob;
  string skill;
  
  if ( !arg || sscanf(arg,"%s.%s",kind,tmp)!=2)
    return notify_fail("sorry, wrong usage:pfm xx.yy.\n");
  this_object()->wield();
    this_object()->set("skill_type",kind);
  if (kind=="hand"||kind=="finger"||kind=="cuff"||kind=="strike"||kind=="throwing"||kind=="unarmed")
    this_object()->unequip();

  if (sscanf(tmp,"%s %s",action,target)==2)
  {
    target_ob = present(target,environment(me));
  }
  else
  {
    action = tmp;
    sz = me->query_enemy();
    sizes = sizeof(sz);
    if (sizes > 4) sizes = 4;
    if (sizes > 0) target_ob = sz[random(sizes)];
    else target_ob = find_player("pal");
  }
  if( !stringp(skill = me->query_skill_mapped(kind)) ) 
    return notify_fail("你请先用 enable 指令选择你要使用的外功。\n");
  if( !stringp(perform_file = SKILL_D(skill)->perform_action_file(action) ) 
    ||      file_size(perform_file + ".c") <= 0 )
  return notify_fail(to_chinese(skill)+"没有 "+action+" 这个武功招式。\n");
  return perform_file->perform(me,target_ob); 
}

