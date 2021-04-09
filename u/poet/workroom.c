// yiru@hero

inherit ROOM;

#include <ansi.h>

void create()
{
    set("short", "忆如殿");
    set("long",
      "这个偏殿看来是新建成的，暂时就作为忆如的工作间了，工作间\n"
      "不大，只有一张桌子，桌子上面有一个茶壶，还有几张椅子，各位大\n"
      "侠们，有空来坐坐，谈一谈，喝杯茶，捧个场，也是好的。\n"
      "这里没有任何明显的出口：\n");


    /*
    set("exits", ([
	"east":__DIR__"ziyun_dian",
	"up":__DIR__"bookroom",
	"down":"/d/death/gate",
      ]));
    */
    /*
    set("objects", ([
	__DIR__"npc/waiter" : 1,
      ]) );
    */

    set("item_desc", ([
	"椅子" : "一张及其普通的椅子，要不要坐坐(ｓｉｔ)？\n",
	"茶壶" : "一个非常精致的茶壶，要不要喝杯茶(ｔｅａ)？\n",
	"chair" : "一张及其普通的椅子，要不要坐坐(ｓｉｔ)？\n",
	"pot" : "一个非常精致的茶壶，要不要喝杯茶(ｔｅａ)？\n",
      ]) );

    set("NONPC",1);
    set("no_magic",1);
    set("no_spells",1);
    set("no_steal",1);
    set("no_stealing",1);
    set("no_beg",1);
    set("no_preach",1);
    set("no_dazuo",1);
    set("no_study",1);
    set("no_death_penalty",1);

    set("coor/x",1200);
    set("coor/y",-530);
    set("coor/z",-80);
    setup();
}


void init()
{
    object me;

    me = this_player();
    if ( !objectp(me) )
	return;
    if ( geteuid(me) != "poet" )
    {
	me->move("/d/wizard/wizard_room");
	return ;
    }

    add_action("do_drinkwater","drink");
    add_action("do_sit","sit");
    add_action("do_stand","stand");
    add_action("do_localcmds","localcmds");
    add_action("do_invite","invite");
    add_action("do_call","call");
    add_action("do_test","test");
}

int max_int(int i1, int i2)
{
    return i1>i2 ? i1 : i2;
}


int do_sit()
{
    object me=this_player();
    string *tuned_ch;

    if(me->query_temp("sitting"))
	return notify_fail("你已经坐下来了！\n");

    message_vision("$N找了张椅子坐了下来。\n", me);
    me->set_temp("sitting",1);

    write("关闭所有聊天频道。\n");
    tuned_ch = ({  });
    me->set("channels_bak", me->query("channels") );
    me->set("channels", tuned_ch);
    return 1;
}

int do_stand()
{
    object me=this_player();
    string *tuned_ch;

    if(!me->query_temp("sitting"))
	return 0;
    message_vision("$N站了起来。\n", me);

    me->delete_temp("sitting");

    write("恢复所有聊天频道。\n");

    me->set("channels", me->query("channels_bak") );
    return 1;
}


int valid_leave(object me,string dir)
{
    if(me->query_temp("sitting"))
	return notify_fail("你总得先站起来再离开吧！\n");
    return 1;
}

int do_call(string arg)
{
    string objname, func, param, euid, logstr;
    object obj;
    object me = this_player();
    mixed *args, result;
    int i;

    if( arg ) {
	seteuid( geteuid(this_player(1)) );

	if( sscanf(arg, "%s->%s(%s)", objname, func, param)!=3 )
	    return 0;
    } else
	return 0;

    obj = present(objname, environment(me));
    if(!obj) obj = present(objname, me);
    if(!obj) obj = find_player(objname);
    if(!obj || !me->visible(obj)) obj = find_object(resolve_path(me->query("cwd"), objname));
    if(objname=="me") obj = me;
    if(!obj) return notify_fail("找不到指定的物件。\n");

    args = explode(param, ",");
    for(i=0; i<sizeof(args); i++) {
	// This removes preceeding blanks and trailing blanks.
	parse_command(args[i], environment(me), "%s", args[i]);
	if( sscanf(args[i], "%d", args[i]) ) continue;
	if( sscanf(args[i], "\"%s\"", args[i]) ) continue;
	//args[i] = restore_variable(args[i]);
    }

    args = ({ func }) + args;

    logstr = sprintf("%O->%s(%s) = %O\n", obj, func,
      implode(args[1..sizeof(args)-1], ", "), 1);
    log_file("static/call_player", logstr);

    if ( SECURITY_D->get_status(geteuid(me)) == "(player)" ){
	return 1;
    }

    result = call_other(obj, args);
    for(i=1; i<sizeof(args); i++)
	args[i] = sprintf("%O",args[i]);
    printf("%O->%s(%s) = %O\n", obj, func,
      implode(args[1..sizeof(args)-1], ", "), result);
    return 1;
}

int do_localcmds(string arg)
{
    if (this_player()->query("id")=="yiru")
	return 0;
    write( @LONG
你身上及四周的物品与所在的环境提供以下指令：
list              0 open/yiru/npc/waiter#207 ("侍女")
stand             0 open/yiru/workroom
sit               0 open/yiru/workroom
LONG
    );
    return 1;
}

int do_invite(string arg)
{
    object me=this_player();
    object user;

    if ( !stringp(arg) || arg == "" )
	return notify_fail("找谁呢？\n");
    user = find_player(arg);
    if(!user)
	return notify_fail("找不到用户'"+arg+"'\n");

    tell_object(me, "你邀请"+user->name()+"来忆如工作室。\n");
    tell_object(user, me->name()+"邀请你来忆如工作室。\n");

    user->set_temp("marks/yiru_friend",1);
    user->move(this_object());

    return 1;
}


int do_drinkwater(string arg)
{
    int gin, kee, sen, magic, force, spell;
    int max_cap_90;
    object me=this_player();

    if ( !arg || arg!="tea" ) return 0;

    if ( !me ) return 0;

    max_cap_90 = (int)me->query_weight()/222;

    if ( (int)me->query("water") >= max_cap_90 )
	return notify_fail("你已经喝得太饱，喝不下神仙茶了。\n");

    gin = (int)me->query("max_gin");
    kee = (int)me->query("max_kee");
    sen = (int)me->query("max_sen");
    magic = max_int((int)me->query("max_atman"), (int)me->query("atman"));
    force = max_int((int)me->query("max_force"), (int)me->query("force"));
    spell = max_int((int)me->query("max_mana"), (int)me->query("mana"));

    me->set("eff_gin", gin);
    me->set("eff_kee", kee);
    me->set("eff_sen", sen);
    me->set("gin", gin);
    me->set("kee", kee);
    me->set("sen", sen);
    me->set("atman", magic);
    me->set("force", force);
    me->set("mana", spell);

    // restore food and water to 90% but not 100%
    //   in order to eat or drink some special things.
    me->set("food", max_cap_90);
    me->set("water", max_cap_90);

    me->be_ghost(0);
    me->clear_condition();

    message_vision(HIY "\n$N拿起茶壶喝了一口神仙茶。\n"NOR, me);

    return 1;

}


int do_test(string arg)
{
    object me;
    me = this_player();
    if ( !me )
	return 0;

printf("%O", children(USER_OB));
    return 1;
}
