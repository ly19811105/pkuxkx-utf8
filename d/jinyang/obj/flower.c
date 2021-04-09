#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit NECK;

#include "message.h"

void create()
{       
	switch (random(9)){
		case 0: set_name(HIC "野菊花" NOR, ({ "ye juhua", "flower"})); set("unique", 1);break; 
		case 1: set_name(HIY "黄鹤翎" NOR, ({ "huang heling", "flower"})); break; 
		case 2: set_name(HIW "白菊花" NOR, ({ "bai juhua", "flower"})); break; 
		case 3: set_name(HIR "美人红" NOR, ({ "meiren hong", "flower"})); break;
		case 4: set_name(HIC "野菊花" NOR, ({ "ye juhua", "flower"})); set("unique", 1);break; 
		case 5: set_name(YEL "金孔雀" NOR, ({ "jin kongque", "flower"})); break; 
		case 6: set_name(HIY "莺羽黄" NOR, ({ "yin yuhuang", "flower"})); break; 
		case 7: set_name(WHT "玉楼春" NOR, ({ "yu louchun", "flower"})); break; 
		case 8: set_name(HIC "野菊花" NOR, ({ "ye juhua", "flower"})); set("unique", 1);break; 
		case 9: set_name(HIM "桃花菊" NOR, ({ "tao hongju", "flower"})); break; 
	}
	set_weight(100);
	set("long","一朵清新淡丽的小"+query("name")+"，散发着一丝丝清香。\n");
	set("material", "flower");
	set("unit", "朵");
	set("armor_prop/armor", 1);
	set("armor_prop/personality", 1);
	setup();
}

int init ()
{
	add_action ("do_wear", "wear");
	add_action ("do_wear", "dai");
	add_action ("do_remove", "remove");
	add_action ("do_smell", "smell");
	add_action ("do_smell", "wen");
	call_out("need_water", 10+random(10), environment(this_object()));
	return 1;
}

int do_wear (string arg)
{
	object flower = this_object();
	string name = flower->query("name");
	string msg;

	if (arg != "flower" && arg != "ju hua")
		return 0;
	msg = "$N戴上一朵"+name+"，小脸蛋顿时涨的通红。\n"; 
	flower->set("wear_msg",msg);
	return 0;
}

int do_remove (string arg)
{
	object flower = this_object();
	string name = flower->query("name");
	string msg;

	if (arg != "flower" && arg != "ju hua")
		return 0;

	msg = "$N将"+name+"轻轻地摘下来……\n"; 
	flower->set("unequip_msg",msg);
	return 0;
}

int do_smell (string arg)
{
	object me = this_player();
	object flower = this_object();
	string name = flower->query("name");
	string msg;

	if (arg != "flower" &&  arg != "ju hua")
		return 0;

	msg = "$N将"+name+"捧起闻了闻，又惦记起昨天的故人。\n"; 
	message_vision (msg,me);
	return 1;
}
