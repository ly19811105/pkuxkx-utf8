#include <ansi.h>
inherit ROOM;
int do_zhangsan(string user);
int do_getout(string user);

void create()
{
	set("short", HIY"云之遥的家"NOR);
	set("long", HIG"这里是云之遥的家，到处乱七八糟的，各种工具丢得到处都是，大概只有\n它的主人才知道各种东西放在哪里。\n"NOR);
	set("exits", ([
		"out" : "/d/city/guangchang",
        "tqt" : "/d/wizard/zine/safari",
        "beijing":"/d/beijing/zhengyangmen",
		"jiangzhou":"/d/jiangzhou/guangchang",
	]));
    set("no_die",1);
	set("valid_startroom", 1);
	set("no_clean_up", 1);
	set("no_reset",1);
	setup();
}

void init()
{
	add_action("do_zhangsan","zhangsan");
	add_action("do_getout","getout");
}

int do_getout(string user)
{
	object ob;
	object me = this_player();
	object *inv;
	int i;
	if (me->query("id")!="lordstar")
		return notify_fail("你又不是房间的主人，还是不要乱动房间里的东西。\n");
	ob = present(user, this_object());
	if (!objectp(ob) || !ob->is_character())
		return notify_fail("房间里没有 "+user+" 这个人。\n");
	ob->start_busy(2);
	message_vision(HIC"$N大叫一声：来人！给朕把"+ob->query("name")+ HIC"推出去重打一百大板！\n"NOR, me);
	message_vision(HIR"只见一群大汉一拥而上，把$n摁在地上扒了个精光，在"HIW"雪白的屁股"HIR"上噼里啪啦地打了一顿板子！\n"NOR, me, ob);
	inv = all_inventory(ob);
	for(i=0; i<sizeof(inv); i++)
	{
		if ((string)inv[i]->query("equipped")=="worn" )
			inv[i]->unequip();
	}
	ob->move("/d/city/guangchang");
	ob->delete("env/invisibility");
	message_vision(HIW"\n只听啪唧一声脆响，$N被人从屋子里扔了出来，以恶狗吃屎之势摔了个大马趴。\n\n"NOR, ob);
	message_vision(HIW"好了，这会儿耳根清静了！\n"NOR, me);
	return 1;
}

int do_zhangsan(string user)
{
	object ob, zs;
	object me = this_player();
	if (me->query("id")!="lordstar" && me->query("id")!="caijue")
		return notify_fail("你又不是房间的主人，还是不要乱动房间里的东西。\n");
	if (!objectp(ob=find_player(user)))
		return notify_fail("没有这个玩家在线。\n");
	if (ob->query("xkdling"))
		return notify_fail("人家已经去过侠客岛了，你就别操那个闲心了。\n");
	zs = new("/d/xiakedao/npc/zhangsan.c");
	zs->move(this_object());
	zs->set("count", 0);
	ob->set_temp("marks/bihua",1);
	message_vision(HIC"$N按动了一个按钮，叮的一声响，一位大汉推开门走了进来。\n"NOR, me);
	message_vision(HIW"$N"HIW"躬身行礼道：主人请吩咐！\n"NOR, zs);
	message_vision(HIW"$N向$n"HIW"耳语了两句，$n躬身领命出门去了。\n",me, zs);
	zs->FaLingToUser(ob->query("id"));
	return 1;
}

int new_sp(string user)
{
	object ob;
	object me = this_player();
	if (me->query("id")!="lordstar")
		return notify_fail("你又不是房间的主人，还是不要乱动房间里的东西。\n");
	if (!objectp(ob=find_player(user)))
		return notify_fail("没有这个人。\n");
	if (!ob->query("relationship/target_name"))
		ob->set("relationship/target_name", "云之遥");
	ob->set_temp("relative/changespecial", 1);
	ob->delete("relationship/freesp");
	return 1;
}

int delete_sp(string user)
{
	object ob;
	object me = this_player();
	if (me->query("id")!="lordstar")
		return notify_fail("你又不是房间的主人，还是不要乱动房间里的东西。\n");
	if (!objectp(ob=find_player(user)))
		return notify_fail("没有这个人。\n");
	ob->delete("relationship");
	return 1;
}

int new_drug(string arg)
{
	string filename;
	object drug;
	object me=this_player();
	if (me->query("id")!="lordstar")
		return notify_fail("你又不是房间的主人，还是不要乱动房间里的东西。\n");
	if (!arg) arg="xiandou";
	if (arg=="xiandou") filename="/d/wizard/obj/xiandou";
	else if (arg=="qingxin san") filename="/d/xingxiu/obj/xxqingxi";

	else if (arg=="long dan") filename="/d/ludingshan/obj/special/dan1";
	else if (arg=="huolong" || arg=="huolong dan") filename="/d/ludingshan/obj/special/dan2";
	else if (arg=="qiannian" || arg=="qiannian dan") filename="/d/ludingshan/obj/special/dan3";
	else if (arg=="baicao" || arg=="baicao dan") filename="/d/ludingshan/obj/special/dan4";

	else if (arg=="ningyuan" || arg=="ningyuan wan") filename="/obj/vein/dan1";
	else if (arg=="ningzhen" || arg=="ningzhen dan") filename="/obj/vein/dan2";
	else if (arg=="juqi" || arg=="juqi san") filename="/obj/vein/dan3";
	else if (arg=="heqi" || arg=="heqi san") filename="/obj/vein/dan4";
	else if (arg=="jiqi" || arg=="jiqi san") filename="/obj/vein/dan5";
	else if (arg=="binglong" || arg=="binglong san") filename="/obj/vein/dan6";
	else if (arg=="tianyu" || arg=="tianyu wan") filename="/obj/vein/dan7";
	else if (arg=="bingling" || arg=="bingling dan") filename="/obj/vein/dan8";
	else if (arg=="jujing" || arg=="jujing ji") filename="/obj/vein/dan9";
	else if (arg=="mugu" || arg=="mugu cha") filename="/obj/vein/dan10";
	else if (arg=="shuangling1" || arg=="shuangling dan") filename="/obj/vein/dan11";
	else if (arg=="shuangling2" || arg=="shuangling wan") filename="/obj/vein/dan12";
	else if (arg=="huolong" || arg=="huolong san") filename="/obj/vein/dan13";
	else if (arg=="yuze" || arg=="yuze wan") filename="/obj/vein/dan14";
	
	else return notify_fail("没有这样的丹药。\n");
	
	drug=new(filename);
	if (objectp(drug)) drug->move(me);
	return 1;
}

int new_armor(string arg)
{
	object ob;
	int type;
	object me=this_player();
	if (me->query("id")!="lordstar")
		return notify_fail("你又不是房间的主人，还是不要乱动房间里的东西。\n");
	ob=new("/obj/gem/armor.c");
	if (!objectp(ob)) return notify_fail("创造物品失败。\n");
	if (!arg) arg="armor";
	if (arg=="boots") type=2;
	else if (arg=="cloth") type=3;
	else if (arg=="hands") type=4;
	else if (arg=="head") type=5;
	else if (arg=="shield") type=6;
	else if (arg=="surcoat") type=7;
	else if (arg=="waist") type=8;
	else if (arg=="wrists") type=9;
	else type=1;
	ob->set("type",type);
	ob->gen_armor(type, 10000, 10000);
	ob->set("forge/max", 3);
	ob->move(me);
	return 1;
}

int new_ring(string arg)
{
	object ob;
	int type;
	object me=this_player();
	if (me->query("id")!="lordstar")
		return notify_fail("你又不是房间的主人，还是不要乱动房间里的东西。\n");
	ob=new("/obj/gem/ring.c");
	if (!objectp(ob)) return notify_fail("创造物品失败。\n");
	if (!arg) arg="ring";
	if (arg=="ring") type=1;
	else type=2;
	ob->set("type",type);
	ob->gen_armor(type, 10000, 10000);
	ob->set("forge/max",2);
	ob->move(me);
	return 1;
}

int new_baoshi(string arg)
{
	object item;
	object me=this_player();
	if (me->query("id")!="lordstar")
		return notify_fail("你又不是房间的主人，还是不要乱动房间里的东西。\n");
	item = new("/obj/gem/gem");
	if (objectp(item))
	{
		if (!arg) arg="ri";
		if (arg == "yan" || arg == "mu" || arg == "sui" || arg == "jin" || arg == "bing" || arg == "gu" || arg == "yu" || arg == "jiao" || arg == "jia")
			item->set_level(10000, 10000, arg);
		item->move(me);
	}
	return 1;
}
