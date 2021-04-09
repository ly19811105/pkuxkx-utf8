// wangtiejiang.c
//
// Modified by pretty (09/16/98)
//   -- add "ding" action

#include <ansi.h>

inherit NPC;
inherit F_DEALER;
inherit F_MASTER;

string *weapons = ({
	"axe", "blade", "club", "dagger", "fork", "halberd", "hammer",
	"pestle", "spear", "staff", "sword", "whip", "xie",
});

int do_ding(string arg);

void create()
{
        set_name("王铁匠", ({ "wang tiejiang", "wang" }));
        set("title", "打铁铺");
        set("shen_type", 1);
        set("gender", "男性");
        set("age", 45);
        set("long",
                "王铁匠是外地人，刚刚在此开了个打铁铺，买卖倒也红火。\n");
        set_skill("unarmed", 10);
        set_skill("dodge", 10);
        set_temp("apply/damage", 15);
        set("combat_exp", 1000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/city/obj/gangdao",
                "/d/city/obj/tiejia",
                "/d/city/obj/changjian",
                "/d/city/obj/duanjian",
                "/clone/weapon/dart",
                "/d/xingxiu/npc/obj/tiegun",
                "/d/village/npc/obj/hammer",	
           }));
        setup();
}
void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_ding", "ding");
}

int do_ding(string arg)
{
	string cat, color, name, id
;
	object me, ob, gold;
	string file, fname;

	me = this_player();
	if ( !arg || sscanf(arg, "%s %s %s %s", cat, color, name, id) != 4)
		return notify_fail("指令格式：ding <种类> <颜色> <中文名> <英文名>\n");

	if ( !objectp(gold = present("gold_money", me)) )
		return notify_fail("你身上没有金子。\n");

	if ( gold->query_amount() < 1000 )
		return notify_fail("你身上没带够一千两金子。\n");

	if ( member_array( cat, weapons ) == -1 )
		return notify_fail("这里没有你想要的兵器。\n");

	if ( !LOGIN_D->check_legal_name(name) )
		return notify_fail("这个中文名字不合法，请重新输入。\n");

	if ( !LOGIN_D->check_legal_id(id) )
		return notify_fail("这个英文名字不合法，请重新输入。\n");

        if ( me->is_busy() )
                return notify_fail("你现在正忙着呢！\n");

	if ( sizeof(me->query("auto_load")) > 1 )
		return notify_fail("你已经有了两件自造物品了！\n");

	if ( !(file = read_file("/clone/stdweapon/" + cat + ".c")) )
		return notify_fail("读文件出错。\n");

        if (color == "$BLK$") file = replace_string(file, "color", "BLK");
        else
        if (color == "$RED$") file = replace_string(file, "color", "RED");
        else
        if (color == "$GRN$") file = replace_string(file, "color", "GRN");
        else
        if (color == "$YEL$") file = replace_string(file, "color", "YEL");
        else
        if (color == "$BLU$") file = replace_string(file, "color", "BLU");
        else
        if (color == "$MAG$") file = replace_string(file, "color", "MAG");
        else
        if (color == "$CYN$") file = replace_string(file, "color", "CYN");
        else
        if (color == "$WHT$") file = replace_string(file, "color", "WHT");
        else
        if (color == "$HIR$") file = replace_string(file, "color", "HIR");
        else
        if (color == "$HIG$") file = replace_string(file, "color", "HIG");
        else
        if (color == "$HIY$") file = replace_string(file, "color", "HIY");
        else
        if (color == "$HIB$") file = replace_string(file, "color", "HIB");
        else
        if (color == "$HIM$") file = replace_string(file, "color", "HIM");
        else
        if (color == "$HIC$") file = replace_string(file, "color", "HIC");
        else
        if (color == "$HIW$") file = replace_string(file, "color", "HIW");
        else
        if (color == "$NOR$") file = replace_string(file, "color", "NOR");
        else return notify_fail("没有你想要的颜色！\n");

	file = replace_string(file, "名字", name);
	file = replace_string(file, "ＩＤ", id);
      file = replace_string(file, "(dam)", "(30)");

	seteuid(ROOT_UID);
        fname = PRIVATE_DIR + me->query("id")[0..0] + "/" + me->query("id") + time() + ".c";
message_vision(fname,this_object());
	if (!write_file(fname, file))
		return notify_fail("无法写入文件。\n");
	if ( !objectp(ob = new(fname)) || !ob->move(me))
		return notify_fail("无法创建文件。\n");
	message_vision("$N叮叮铛铛的敲了一阵后说道：好了！\n", this_object());
	message_vision("$N交给$n一" + ob->query("unit") + ob->name() + "。\n", this_object(), me);
	me->add("auto_load", ({ base_name(ob) + ".c" }) );
	gold->add_amount(-1000);
	me->save();
	return 1;
}

