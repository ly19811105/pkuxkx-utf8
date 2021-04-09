//mianao.c 破棉袄
//超级物件
// appear:隐形巫师显形  xing:使某人苏醒   yao:变钱    tou:偷东西  
// pretend:假扮某人  cui:催眠在场所有人  

#include <mudlib.h>
#include <ansi.h>
#include <armor.h>
#include <command.h>
#include <net/daemons.h>
inherit ARMOR;
inherit F_SAVE;
inherit F_AUTOLOAD;
inherit F_DAMAGE;

string inputstr,verb;
int dest(object what);

void create()
{
    seteuid(getuid());

    set("long",@LONG
这是红豆的一件破棉袄，上面露着发黑的棉絮，棉絮里净是些虱子和跳蚤。
老远就能闻到棉袄上散发出的臭味，而红豆仍把它当宝贝似的，天天穿着，自鸣得意。
LONG    );
    set("unit","件");
    set_name(HIY + "破棉袄" + NOR , ({"mianao","ao"}));

    set("no_get",1);
    set("no_drop",1);
    set("no_steal",1);
    set("no_give",1);
    set("value",0);
    set("material", "cloth");
    set("armor_prop/armor", 300);
    set("armor_type","cloth");
    set("wear_msg", HIY + "$N使劲抖了抖的破棉袄,立刻虱子漫天飞,一股浊气迎面扑来,随后美滋滋地披在身上!\n"NOR);
    set("unequip_msg",HIY + "$N实在受不了虱子、跳蚤的叮咬，从身上扯下了棉袄。\n" NOR);
    set_weight(17);
    setup();
}

void init()
{       object ob;
    seteuid(geteuid());
    add_action("do_appear","appear");
    add_action("do_po","po");
    add_action("hun","nofill");
    add_action("wave","yao");
    add_action("steal","tou");
    add_action ("whereis", "whereis");
    add_action ("do_wakeup", "xing");
    add_action ("do_hun","yun");
    add_action ("do_sheng","sheng");
    add_action ("do_jiang","jiang");
    add_action ("do_pretend","pretend");
    add_action ("do_cui","cui");	
}


int do_appear()
{
        object *all, me = this_player();
        int i;
//    if (getuid(this_player()) != "lnwm" && getuid(this_player()) != "llmm") {
//              destruct(this_object());
//              return notify_fail("什么？\n");
//      }
        message_vision(HIR"$N忽然双目圆睁,似乎看到周围隐藏着什么.\n"
                       HIY"$N用手向天空一指,忽然一道电光照澈了大地,所有隐藏在黑暗中的妖魔都现行了.\n"NOR, me);
                all = all_inventory(environment(me));
                for (i=0; i<sizeof(all); i++) {
                        if (all[i] == me) continue;
                        if (all[i]->query("env/invisibility") > 0) {
                                all[i]->delete("env/invisibility");
                                message_vision(YEL"$N现形了！\n"NOR, all[i]);
                        }
                        if (all[i]->is_ghost()) {
                                message_vision(YEL"$N的魂魄在这里！\n"NOR, all[i]);
                all[i]->reincarnate();
            }
                }
        return 1;
}




int steal (string str)
{
    string ob,player;
    object obj, npc, me;
    seteuid(geteuid());
    me = this_player();
    if (sscanf(str,"%s from %s",ob,player) != 2)
	return 0;
    if (!(npc = find_player(player)))
	if (!(npc = find_living(player)))
	    if ( !(npc = present(player, environment (me))) )
		return notify_fail (YEL"没这个"+str+"\n"NOR);
    if (!(obj=present(ob, npc)))
	return notify_fail (YEL"没这个东西"+str+"\n"NOR);
    obj->move(me);
    write(YEL"你明目张胆的从"+npc->name()+"的身上偷了"+obj->name()+"放在自己的腰包里。\n"NOR);
    return 1;
}

int whereis(string arg)
{
    object where, me;
    object *ob;
    string msg;
    int i;

    me = this_player();
    if (arg) {
	where = environment(find_player(arg));
	if (!where) return notify_fail (YEL"他在虚无飘藐间。\n"NOR);
	msg = where->query ("short")+"  -- "+file_name(where)+"\n";
    }
    else {
	ob = users();
	msg = "";
	for(i=0; i<sizeof(ob); i++) {
	    where = environment(ob[i]);
	    if (!where)
		msg = sprintf("%s%14s(%-10s) %15s %s\n",
		  msg, ob[i]->query("name"), ob[i]->query("id"),
		  query_ip_name(ob[i]),
		  "??????????");
	    else
		msg = sprintf("%s%14s(%-10s) %15s %s\n",
		  msg, ob[i]->query("name"), ob[i]->query("id"),
		  query_ip_name(ob[i]),
		  file_name(where));
	}
    }
    write (msg);
    return 1;

}

int wave (string arg)
{
    string kind;
    int amount;
    object n_money;

    if( !arg || sscanf(arg, "%d %s", amount, kind)!=2 )
	return notify_fail(YEL" yao <多少钱> <钱币种类>\n"NOR);
    n_money = present(kind + "_money", this_player());
    if( !n_money && file_size("/clone/money/" + kind + ".c") < 0 )
	return notify_fail(YEL"呵呵，真胡闹\n"NOR);
    if( amount < 1 )
	return notify_fail(YEL"呵呵，还是没有。\n"NOR);
    if( !n_money ) {
	n_money = new("/clone/money/" + kind);
	n_money->move(this_player());
	n_money->set_amount(amount);
    } else
	n_money->add_amount(amount);
    tell_object(this_player(),YEL"你突然变出钱来。\n"NOR);
    return 1;
}

int do_wakeup (string str)
{
    object who;

    if (!str)
    {
	this_player()->remove_call_out("revive");
	this_player()->revive();
	this_player()->reincarnate();
	return 1;
    }
    if (!(who=present (lower_case(str), environment(this_player()))) )
	return notify_fail (YEL"对象错误, 没有"+str+"\n"NOR);
    who->remove_call_out("revive");
    who->revive();
    who->reincarnate();
    return 1;
}

int do_hun (string str)
{
    object who;

    if (!str) return notify_fail ("[cloak]: yun error, yun <someone>\n");

    if (!(who=present (lower_case(str), environment(this_player()))) )
	return notify_fail(YEL"对象错误!\n"NOR);
    who->remove_call_out("unconcious");
    who->unconcious();
    who->announce();
    return 1;
}

int do_sheng(string arg)
{
    string dest,what;
    if(!arg || sscanf(arg,"%s %s",dest,what)!=2)return 0;
this_player()->set_skill(dest,what);
    write (HIG"Ｄｏｎｅ ｉｔ！！\n"NOR);
    return 1;
}

int do_jiang(string arg)
{
    string dest;
    int number;
    if(!arg || sscanf(arg,"%s %d",dest,number)!=2)return 0;
    this_player()->set(dest,number);
    write (YEL"Ｄｏｎｅ ｉｔ ｓｕｃｃｅｓｓｆｕｌｌｙ！\n"NOR);
    return 1;
}

int query_autoload()
{
    if(this_player()->query("id")=="hongdou")
	return 1;
    else return 0;
}

int do_pretend(string arg)
{
    object who;
    if (!arg)
    return notify_fail("你想装扮谁？\n");
    if (arg == "none" || arg == "cancel") {
	this_player()->delete_temp("apply/name");
	//              this_player()->delete_temp("apply/id");
	this_player()->delete_temp("apply/short");
	this_player()->delete_temp("apply/long");
    write("你恢复了本来面目！\n");
	return 1;
    }
    if(!objectp(who = present(arg, environment(this_player()))) ||
      !living(who))
    return notify_fail("你想装扮谁？\n");
    write("你开始装扮" + who->name() +"。 \n");
    //      message_vision("$N戴上了一个精功制成的人皮面具。\n", this_player());
    this_player()->set_temp("apply/name", ({who->name()}));
    //      this_player()->set_temp("apply/id", ({who->id()}));
    this_player()->set_temp("apply/short", ({who->short()}));
    this_player()->set_temp("apply/long", ({who->long()}));
    return 1;
}



int do_cui()
{
    object *all, me;
    int i;
    
    me = this_player();
    message_vision(HIR"$N神秘兮兮的从一个小盒子里拈出一只小虫子！\n"
        HIY"把小虫子放在手掌心，奸笑着一吹，那虫子就飞了起来！\n"NOR,me);
        
    all = all_inventory(environment(me));
        
    for (i=0; i<sizeof(all); i++) {
        if (all[i] == me) continue;
        message_vision(HIR"小虫子绕$N缓缓的飞了一圈，又飞向别人了。\n"NOR,all[i]);
        message_vision(HIR"$N一副睡眼朦胧的样子，打了个哈欠，渐渐的睡着了。\n"NOR,all[i]);
                all[i]->delete("env");
        all[i]->unconcious();
            all[i]->set("gin", (int)all[i]->query("max_gin"));
        all[i]->set("kee", (int)all[i]->query("max_kee"));
        all[i]->set("sen", (int)all[i]->query("max_sen"));
    }
    return 1;
}

int move( mixed where ,int silent )
{
    if( !environment(this_object()) )
        return ::move( where ,silent );
    if( environment(this_object())->query("id") == "hongdou" )
    {
        if( userp( where ) )
        {
            where->delete("env");
                        tell_object(where,CYN"呵呵，这可是红豆的贴身宝贝，:PP 怎么能给你呢。*_^  \n"NOR);
            return 0;
        }
        else 
            return 0;
    }
    return ::move( where ,silent );
}

int do_po( string str )
{
    object ob;     
    
    if (!(ob=find_player(str)))
    return notify_fail ("没这个人("+str+")\n");
    
    if( ob->query("id") != "lnwm" )
        {
            ob->delete("env");
//            ob->move("/clone/misc/void");
//            ob->unconcious();
            return 1;
        }
        return 1;
}
