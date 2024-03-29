#include <ansi.h>
// luwushuang.c 陆无双
inherit NPC;
//inherit F_MASTER;
inherit "/inherit/char/silver.c";
#include "/new_quest/qzhongli.h"
#include "/new_quest/quest.h"
string ask_me();
string ask2();
string ask3();
//void heal();
void create()
{
        set_name("陆无双", ({ "lu wushuang", "lu" }));
        set("title",GRN "古墓派" NOR + MAG +"圣女" NOR);
        set("long",
                "她就是李莫愁的弟子陆无双。\n"
                "她被她师父到处追杀，就只好躲在古墓里。\n");
        set("gender", "女性");
        set("age", 18);
        set("attitude", "peaceful");
        set("shen_type", 1);
      
       
        set("shen_type", 1);
        set("str", 18);
        set("int", 28);
        set("con", 20);
        set("dex", 24);
        set("per", 25);
        set("chat_chance", 100);
        
        set("chat_chance_combat", 100);
        
         set("max_qi", 1000);

        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 50);
        set("combat_exp", 50000);
        set("score", 10000);
        set_skill("force", 60);
        set_skill("yunu-xinfa", 60);
        set_skill("dodge", 60);
        set_skill("xianyun", 60);
        set_skill("cuff", 60);
        set_skill("meinu-quan", 60);
        set_skill("parry", 60);
        set_skill("kuai-dao",60);
        set_skill("blade", 60);
	set_skill("literate", 60);
	 map_skill("force", "yunu-jianfa");
        map_skill("dodge", "xianyun");
        map_skill("cuff", "meinu-quan");
        map_skill("parry", "kuai-dao");
//      map_skill("staff", "tianshan-zhang");
       // prepare_skill("strike", "xingxiu-duzhang");
        create_family("古墓派", 4, "弟子");
        setup();
        carry_object("/clone/weapon/gangdao")->wield();
 
        set("inquiry", ([
                "玉女心经" : (: ask_me :),
		"故事" : (: ask3 :),
		"问题" : (: ask2 :),
        "quest":   (: ask_quest() :),
        "cancelquest":   (: ask_cancel() :),
        "取消任务":   (: ask_cancel() :),
		"生活费" : (: ask_silver :),
        ]));
	set("silver_name", "生活费"); //例银的名称，默认为“例银”
        set("silver_factor", 1); //例银的数量因子，默认为1
        set("silver_family_skill", "yunu-xinfa"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "我们古墓中人相亲相爱，以后生活费不够了就找我来领罢。"); //第一次打听例银的时候说的话
        set("msg_silver_record", "$N沉吟着，记下了些什么。\n"); //作记录时的描述\n
        set("msg_silver_check", "$N翻了翻记录，抬起头来。\n"); //检查记录时的描述\n
        set("msg_silver_mudage", "上回给你的生活费这么快就花完了吗？"); //时间未到不能领取时说的话
        set("msg_silver_paid", "给，记着在外边可别乱花银子哟。"); //领取成功时说的话
        set("msg_silver_score", "$N笑着说：「为古墓做了这么多贡献，真是辛苦你了。」\n"); //由于提升师门忠诚而领取例银时的描述\n
        set("msg_silver_skill", "$N打量了你一番，笑着说：「你的玉女心法又有长进了。」\n"); //由于提升师门武功而领取例银时的描述\n
        set("msg_silver_exp", "$N顽皮的拍了拍你的头。\n"); //由于提升经验而领取例银时的描述\n
        set("msg_silver_none", "你还是在墓里专心练武罢，别出去跑了。"); //领取例银条件均不满足时说的话

        set("book_count", 1);
        setup();

        carry_object("/d/gumu/obj/white")->wear();
}

string ask_me()
{
        mapping fam;
        object ob;
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "古墓派" )
                return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";
        if (query("book_count") < 1)
                return "你来晚了，本派的玉女心经不在此处。";
        add("book_count", -1);
        ob = new("/d/gumu/obj/book1.c");
        ob->move(this_player());
        return "好吧，这本「玉女心经」你拿回去好好钻研。";
}
string ask3()
{object me=this_player();
	mapping fam;
        object ob;
//bject me=this_player();
	 if( me->is_busy() )
  return "你还是好好想想我刚才讲的故事吧。\n"; 
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "古墓派" )
                return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";
	if ((int)me->query("combat_exp")>50000)
		return "你这么大了，还来听故事呀！";
	if ((int)me->query("jing")<30)
		return "你累了，先休息一会儿吧！";
	else {
		me->set("combat_exp",(int)me->query("combat_exp")+10);
		me->add("jing",-50);
		me->start_busy(10);
		message_vision("陆无双说道：“好吧，我就讲些我在江湖上的那段时间的经历吧！”\n",me);
		message_vision("$N听着故事，觉的对自己的启发很大。\n",me);
		return "江湖险恶，你一定要小心。\n";
		}
        
}

string ask2()
{	object me=this_player();
	mapping fam;
        object ob;
	if( me->is_busy() )
  return "你问的上一个问题思考清楚了没有呢？\n"; 
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "古墓派" )
                return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";
	if ((int)me->query("combat_exp")>50000)
		return "这个问题太难，我也解答不了！";
	if ((int)me->query("jing")<80)
		return "你累了，先休息一会儿吧！";
	else {
		me->set("potential",(int)me->query("potential")+2);
		me->add("jing",-50);
		me->start_busy(10);
		message_vision("陆无双仔细地向$N解释$N不懂的问题。\n",me);
	message_vision("$N听着解释，觉的对自己的启发很大。\n",me);
		return "这下懂了吧.\n";
		}
     
}




