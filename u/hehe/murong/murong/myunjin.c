//myunjin.c
//by hehe
//2003.3.5

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "云锦阁");
    set("long", @LONG
小楼檐下一块匾额，写着"云锦楼"三个墨绿篆字，楼下前后左右
种的都是茶花。但这些茶花在大理都不过是三四流货色，和这
精致的楼阁亭榭相比，未免不衬。
LONG
    );

    set("exits", ([
		"north" : __DIR__"mroad5",
		"west" : __DIR__"mneishi",
		"south" : __DIR__"mlhfd",
    ]));
    
	set("objects",([
		__DIR__"npc/wang" : 1,
		__DIR__"npc/yahuan" : 2,
        ]));
	set("no_fight",1);
	set("no_steal",1);
	set("no_get",1);
    set("outdoors", "murong");
    setup();

}
void init()
{
	object me=this_player();

	if(!(present("hua",me))
		&& !(me->query_temp("murong/zhonghua"))
		&& (me->query("gender")!="女性"
		|| me->query("family/family_name")=="姑苏慕容"))
	{
		message_vision("王夫人喝道：“$N你是什么东西？出去！\n",me);
        call_out("kickout", 0, me);
	}
}
int kickout(object me)
{
	if (!present(me,find_object("/d/murong/myunjin.c"))) 
	{
		return 1;
    }
    message_vision("王夫人喝道：“来啊，把他关起来。\n",me);
    message_vision("突然出来几个婢女用绳子把$N捆了起来。\n",me);
    message_vision("$N感到后脑勺受到重重一击，$N昏了过去。\n",me);
    message_vision("昏昏沉沉中$N感觉被人丢到一个地方，$N重重的摔在地上。\n",me);
	me->set("eff_qi",10);
	me->set("qi",0);
	me->start_busy(60);
    me->move("/d/murong/mshishi");
    return 1;
}
int valid_leave(object me,string dir)
{
	me=this_player();
	if(dir=="south" && !(me->query_temp("murong/langhuan")))
		return notify_fail("没有王夫人的同意你就想乱闯!\n");
	me->delete_temp("murong/langhuan");
	return ::valid_leave(me,dir);
}
