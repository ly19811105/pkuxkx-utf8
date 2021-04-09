// yang.c 杨老板 
#include <command.h>
inherit NPC;
//inherit F_VENDOR;
inherit F_DEALER;
int ask_huo();
string ask_ling();
void create()
{
	set_name("杨永福", ({ "yang yongfu", "yang" }));
	set("title", "杂货铺老板");
	set("shen_type", 1);
    set("start_room","/d/city/zahuopu");

	set("gender", "男性");
	set("age", 45);
	set("long",
		"杨老板是土生土长的扬州人，做了几十年的小买卖。\n");
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_temp("apply/damage", 15);

	set("combat_exp", 40000);
	set("attitude", "friendly");
	set("vendor_goods", ({
        "/d/murong/obj/yuer",
                "/d/murong/obj/yugou",
          "/d/city/obj/guide",
            "/d/xiangyang/npc/obj/shuming.c",
		__DIR__"obj/beixin",
            
                __DIR__"obj/zhuhu",
                __DIR__"obj/chazhong",
            "/d/taishan/obj/pot",
            "/d/xingxiu/npc/obj/case",
            "/clone/obj/anqidai",
//			"/clone/book/bingcan", // 冰蚕毒掌临时技能书，提供测试。
			//"/clone/armor/cloth_testpoison",
//                "/d/xiakedao/obj/false-ling",
//value过大会导致MONEY_D溢出，比如价值一万两黄金的ling，buy ling 3就会发现身上多了很多silver……
//                "/clone/gift/baozhu.c",
//                "/clone/gift/baozhu2.c",
//                __DIR__"obj/yuer",
//                __DIR__"obj/yugan",
	}));
	set("inquiry",([
                "火石" : (:ask_huo:),
                "赏善罚恶令" : (:ask_ling:),
	]) );	
	setup();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
int ask_huo()
{
	object me=this_player();
	if( !me->query_temp("got_msg") ) return 0;
	command("whisper "+me->query("id")+" 我这里有火石卖, 你可不能告诉别人, 就一两黄金一个火石, 不二价.");
	me->set_temp("have_asked",1);
	return 1;
}
string ask_ling()
{
        object me = this_player();
        object ob = this_object();
        command("kesou");
        command("hehe");
        command("whisper "+me->query("id")+" 你要么？要的话给你打个折，一千两黄金！");
        me->set_temp("ask_for_false_ling", 1);
        return "嗯，小店确实出售赏善罚恶令。";
}
int accept_object(object me,object ob)
{
	object obj;
/*
	if(!me->query_temp("have_asked")) return 0;
	if(!(ob->query("money_id")&&ob->value()>=10000)	)
		return notify_fail("我说过一两黄金不二价.\n");
	obj=new("/u/xuan/obj/huoshi");
	obj->move(me);
	tell_object(me,"嘿嘿, 一两黄金买个火石你傻不傻呀.\n");
*/
        if(!me->query_temp("ask_for_false_ling")) return 0;
        if(!(ob->query("money_id")&&ob->value()>=10000000) )
                return notify_fail("我说过一千两黄金，不二价！\n");
        obj = new("/d/xiakedao/obj/false-ling");
        obj->move(me);
        command(":D");
        CHANNEL_D->do_channel(this_object(), "bd", "praise "+me->query("id"), 1);
	return 1;
}
	
