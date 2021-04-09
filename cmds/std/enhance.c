// enhance.c
// by pretty

#include <ansi.h>
inherit F_DBASE;

int main(object me, string arg)
{
	object ob;
	string file, str;
	int dam;
        string* autoloads;
        int i;
        int mine;


	seteuid(ROOT_UID);

	if( !arg || !objectp(ob = present(arg, me)) )
		return notify_fail("你想增强什么武器？\n");

	if( !(dam = ob->query("weapon_prop/damage")) )
		return notify_fail(ob->name() + "并不是一件武器！\n");

	if( !ob->query("auto_load") )
		return notify_fail("只有订做的武器才可以增强。\n");

         mine = 0;
        if ( arrayp(autoloads = me->query("auto_load")) )
        {
              for ( i = 0; i < sizeof(autoloads); i++)
                        if ( autoloads[i] == base_name(ob) + ".c" )
                                mine = 1;
         }
          if ( mine == 0 ) 
                return notify_fail ("这不是你的兵器！\n");



        if( (int)ob->query("weapon_prop/damage") >= 180 )
                return notify_fail("你的武器已经足够强大了。\n");
        if( (int)ob->query("weapon_prop/damage") >= 150 && !me->query("reborn/all"))
                return notify_fail("你的武器已经足够强大了。\n");
        if( (int)ob->query("weapon_prop/damage") >= 120 && !me->query("ludingshan"))
                return notify_fail("你的武器已经足够强大了。\n");

//	if( me->query("jingli") < me->query("max_jingli")
	if(( me->query("jingli") < me->query("max_jingli") && me->query("jingli") < 15*me->query_skill("force",1))
	|| me->query("max_jingli") < (int)ob->query("weapon_prop/damage") * 30 )
		return notify_fail("你的精力不够。\n");

	file = base_name(ob) + ".c";
	str = read_file(file);
	str = replace_string(str, "(" + dam + ")", "(" + (dam + 1) + ")");
	rm(file);
	write_file(file, str);
	do {
		destruct(ob);
	} while (ob = find_object(file));
	if( (ob = new(file)) ) ob->move(me);
	else write("请退出游戏一次以使修改生效。\n");
	me->set("jingli", 0);
        me->add("max_jingli",-((int)ob->query("weapon_prop/damage")/2));
	me->save();
        write(HIR + "你闭目屏息，突然将一口鲜血喷在" + ob->query("name") + HIR + "上。" + ob->query("name") + HIR +"的杀伤力增强了！\n" + NOR);       
	return 1;
}
int help(object me)
{
        write(@HELP
指令格式：enhance [<兵器名称>]

这个指令用于增强订作的兵器的杀伤力，但相应要减少使用者最大
精力。每使用一次此命令兵器的杀伤力就增加一，而使用者的最大
精力也减少使用后兵器杀伤力数值的一半。使用时要求精力是满的而
且最大精力不小于当前兵器杀伤力*30。兵器的杀伤力最多可以提
升到120，如果解开了鹿鼎山的秘密，则最高可以到150；出师以后可
以升到180.


例子：
  enhance myweapon
如果使用前myweapon杀伤力为25，则能enhance的条件是使用者精力
满而且最大精力不小于750。使用后myweapon杀伤力变为26，而使用
者的最大精力减少13。
  

see also : 订兵器。到扬州兵器铺里打"ding"就可以知道指令格式。
订一件兵器需要黄金二百两。
HELP
        );
        return 1;
}

