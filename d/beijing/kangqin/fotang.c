// Room: /d/beijing/kangqin/fotang.c
#include <ansi.h>
inherit ROOM;
int do_tao(string arg);
int do_qiao(string arg);
int do_unlock(string arg);
void create()
{
	set("short", HIC"佛堂"NOR);
	set("long",
MAG"这是一间佛堂，墙和地板都是砖(brick)砌的。里供着一尊如来佛像(foxiang)，
佛像前是一张供桌。桌上点着盏油灯。屋里有些昏暗。\n"NOR
	);
	set("exits", ([ /* sizeof() == 2 */
//  	"down" : __DIR__"mishi",
  	"west" : __DIR__"garden2",
]));

	set("objects",([
                "/d/beijing/npc/puren.c":1,
                "/d/beijing/npc/obj/desk.c":1,
        ]));
        set("item_desc", ([

                "foxiang" :"这是一尊铜像，栩栩如生，宛若真人,正笑眯眯地望着你。\n",

                "brick" : "很普通的石砖，一块一块嵌得很平整。\n",

        ]) );
	set("getkey",0);

	set("getbook",0);

	setup();

}
void init()

{

  add_action("do_qiao", "wa");

  add_action("do_qiao", "qiao");

  add_action("do_tao", "tao");

  add_action("do_unlock", "open");

  add_action("do_unlock", "unlock");

  add_action("do_unlock", "pull");

  add_action("do_unlock", "insert");
}





int do_tao(string arg)

{

	object me, ob;

	me = this_player();



	if( !arg || arg!="foxiang" )

		return notify_fail("你要掏什么？\n");

        if (!me->query_temp("book42_asked") )
        return notify_fail("你没事掏什么掏啊？\n");
	if (me->query_temp("marks/爬") )

	{

		message_vision("$N伸手在佛像耳朵里掏了掏。\n", me);

        if ( query("get_key" ) > 0 )

		{

			me->receive_damage("qi",50);

			return notify_fail("你掏了半天，什么也没有，看来是被人取走了。\n");

		}

		switch(random(5))

		{

			case 0:

				message_vision("$N掏了一会儿，取出一件小小物事来。\n", me);

				message_vision("$N跃下地来，对着火光一看，却是一枚小钥匙。\n",me);

				ob=new("/d/beijing/npc/obj/jinyaos");

				add("get_key", 1);

 			    	ob->move(me);

				break;

			default:

				message_vision("$N伸手掏了一会儿，什么也没掏到。\n",me);

 				break;

		}

		return 1;

	}

	return notify_fail("佛像太高，你够不着。\n");

}



int do_qiao(string arg)

{

        object me, weapon;

	me = this_player();



	if( !arg || arg!="brick" )

		return notify_fail("你要撬什么？\n");

        if (!me->query_temp("book42_asked") )
        return notify_fail("你没事撬什么撬啊？\n");
	if (me->query_temp("marks/移") )

	{

		if (!objectp(weapon = me->query_temp("weapon")))

			return notify_fail("不用家伙恐怕不行吧！\n");

		message_vision("$N拔出" + weapon->name() + "，将一块方砖撬起。\n",me);

		message("vision","登时露出一块铁板来，板上有个拉环，环下有个锁孔(lock)。\n", environment(me));

		me->set_temp("marks/撬",1);

		return 1;

	}

	else

		tell_object(me, "地板被供桌挡住了。\n");

	return 1;

}



int do_unlock(string arg)

{

	object ob;



	if (!arg || arg != "lock" )

		return notify_fail("你要开什么？\n");

	if(!this_player()->query_temp("marks/撬")) return notify_fail("锁在哪儿啊？\n");

	if (!(ob = present("jin yaoshi", this_player())))

	{

		message_vision(

	"\n$N猛地一拉铁环，蓦听的飕的一声，一枝机弩从下面射了出来，正中$N胸口。\n", this_player());
        this_player()->receive_damage("qi", 0, "拉铁环触发机关");
		this_player()->die();

		return 1;

	}

	message_vision("$N将金钥匙轻轻插下，只听喀的一声，锁已打开。\n",this_player());

	if(query("getbook"))

		return notify_fail("你失望地发现书已经被人取走了.\n");

	message_vision("$N伸手进去，摸出一包事物，却是个包袱，打开一看，\n"+

	"正是一部《四十二章经》。$N忍不住叫了一声。\n",this_player());

	destruct(ob);

	ob=new("/d/beijing/npc/obj/book42_6");

	add("getbook",1);

	ob->move(this_player());

        this_player()->delete_temp("book42_asked");
	return 1;

}



int valid_leave(object me, string dir)

{

        me->delete_temp("marks/爬");

        me->delete_temp("marks/移");

        me->delete_temp("marks/撬");

        return ::valid_leave(me, dir);

}
