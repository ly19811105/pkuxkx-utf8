// que.c 虚竹
#include <ansi.h>
#include <title.h>
inherit NPC;
inherit F_MASTER;

#include <no1master.h>

inherit "/inherit/char/silver.c";
int ask_me();
void do_zoutiesuo(string);
string ask_for_leave();
string ask_tlbb();

void create()
{
    set_name("虚竹", ({ "xu zhu", "xu" }));
    set("long",
            "这是一个二十五六岁的年轻人, 长得颇为丑陋,\n"+
            "他浓眉大眼，鼻孔上翻，双耳招风，嘴唇甚厚。 \n"+
            "身穿长袍，乃是以一条条锦缎缝缀而成，红黄\n"+
            "青紫绿黑各色锦缎条纹相间，袖口衣领之处，\n"+
            "更镶以灰色貂皮,华贵之中具见雅致。\n");
    set("nickname", RED "梦郎" NOR );
    set("title", HIC"灵鹫宫尊主"NOR);
    set("gender", "男性");
    set("per", 16);
    set("age", 26);
    set("shen_type",1);
    set("attitude", "peaceful");

    set("str", 30);
    set("int", 25);
    set("con", 40);
    set("dex", 30);

    set("max_qi", 4000);
    set("max_jing", 1200);
    set("neili", 8000);
    set("max_neili", 8000);
    set("jiali", 160);
    set("combat_exp", 2500000);
    set("score", 5000);
    
    set_skill("literate",150);
    set_skill("force", 250);
    set_skill("bahuang-gong", 150);
    set_skill("dodge", 250);
    set_skill("yueying-wubu", 250);
    set_skill("parry", 250);
    set_skill("hand",280);
    set_skill("sword",280);
    set_skill("strike", 280);
    set_skill("zhemei-shou",250);
    set_skill("liuyang-zhang",250);
    set_skill("lingbo-weibu",200);
    set_skill("tianyu-qijian", 200);
    set_skill("beiming-shengong",250);
    set_skill("xiaowuxiang-gong",200);
    set_skill("throwing",180);

    map_skill("force", "beiming-shengong");
    map_skill("strike","liuyang-zhang");
    map_skill("dodge", "lingbo-weibu");
    map_skill("hand", "zhemei-shou");
    map_skill("parry", "liuyang-zhang");
    map_skill("sword", "tianyu-qijian");


    prepare_skill("strike","liuyang-zhang");
    prepare_skill("hand","zhemei-shou");

    create_family("灵鹫宫",2,"尊主");

    set("chat_msg_combat", ({
                (: perform_action, "strike.zhong" :),
                (: perform_action, "hand.duo" :),
                (: perform_action, "sword.changhen" :),
                (: command("unwield jian") :),
                (: command("wield jian") :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: command("unwield jian") :),
                (: command("wield jian") :),
                }) );
                
    set("inquiry", ([
    "梦姑" :(:ask_me:),
		"例银" : (: ask_silver :),
    "脱离门派" : (: ask_for_leave :), 
    "天龙八部" : (: ask_tlbb :),
                ]));
                
        set("silver_factor", 1.2); //例银的数量因子，默认为1
        set("silver_family_skill", "liuyang-zhang"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "善哉，身为灵鹫弟子，以后每月都可以来领取一份例银。"); //第一次打听例银的时候说的话
        set("msg_silver_mudage", "善哉，上次领取的还没用完罢？"); //时间未到不能领取时说的话
        set("msg_silver_paid", "善哉，拿去罢。"); //领取成功时说的话
        set("msg_silver_none", "善哉，你还是勤练武罢。"); //领取例银条件均不满足时说的话                
    setup();
	setup_no1master();
    carry_object("/d/lingjiu/obj/changpao")->wear();
    carry_object("/clone/weapon/jian")->wield();
    add_money("silver",50);
}

void init ()
{
    object me;

	  add_action("do_leave",  "leave");

    me = this_player();
    if (interactive(me) && !is_fighting()) {
        remove_call_out("greet");
        call_out("greet", 1, me);
    }
}

string ask_for_leave()
{
	object me;

	me = this_player();

	if( (string)me->query("family/family_name") != "灵鹫宫")
		return "你非我灵鹫宫弟子，脱离门派的事情我作不得主。";

	me->set_temp("pending/leave_lingjiu", 1);
  return "如果" + RANK_D->query_respect(me) + "真想离我灵鹫宫而去，就请下决心(leave)吧！";
}

string ask_tlbb()
{
    object me=this_player();
    
    if (!me->query("lingjiu/found"))
        return "我找不到梦姑，啥心情也没有啊！";

    if(!me->query_temp("lingjiu/getten") )
    {
        object book;

        message_vision("虚竹给了$N一本精装的天龙八部”\n",me);
        if ((int)me->query("combat_exp")<=50000000 )
                book=new("/d/lingjiu/obj/tlbb");
        else
                book=new("/d/reborn/jinyong/obj/tlbb");
        book->move(me);
        me->set_temp("lingjiu/getten",1); 
        me->delete("lingjiu/found");
        return RANK_D->query_respect(me)+",感谢你帮我找到了梦姑，我这里有一本金庸先生签过名的天龙八部，就送给你吧！";
    }
    else
        return "本想再给你一本书，不过刚才已经被你拿走了天龙八部。";
}

int do_leave()
{
	object me = this_player();
	
	if (me->query_temp("pending/leave_lingjiu") != 1)
		return 0;
	message_vision("$N对$n说道：「从此你就不再是我灵鹫宫门下了，请好自为之！」\n",this_object(), me );
	tell_object(me,HIR "你决定叛出灵鹫宫门下！\n" NOR);
	me->delete_temp("pending/leave_lingjiu");
  me->expell_family("灵鹫宫");
	if (me->query("combat_exp") >= 1000)
		me->add("betrayer",1);
	return 1;
}	

void greet(object me)
{
    object ob=this_object(),she,room;
	if (!me) return;
    if ((me->query_temp("lingjiu/find")==2) && (present("princess", environment(me))))
    {
        command("follow none");
        message_vision("虚竹走上前去，仔细端详了梦姑一眼，说道：“梦姑，苍天有眼，我终于找到你了”\n",me);
        me->set("lingjiu/found",1);
        me->delete_temp("lingjiu/find");
        message_vision("虚竹对$N说道：“你先回去吧，等我带梦姑回去后再好好谢你”\n",me);
        message_vision("虚竹和梦姑转身一起走出了房间。\n",me);
        me->delete_temp("lingjiu/leading");
        room = load_object("/d/lingjiu/zhengting");
        ob->move(room);
        she = present ("princess",environment(me));     
        destruct(she);
    }
    return;
}
int ask_me()
{
    object me=this_player();
/*
    if (me->query("lingjiu/found"))
    {
        command("say 梦姑现在就和我生活在一起，这位"+RANK_D->query_respect(me)+",多谢你了！\n");
        return 1;
    }
*/
    if (me->query_temp("lingjiu/find"))
    {
        command("say 这位"+RANK_D->query_respect(me)+",你不是已经答应去给我找梦姑了吗？\n");        return 1;
    }
    if ((string)me->query("family/family_name") == "灵鹫宫" )
        command("say 这位"+RANK_D->query_respect(me)+",你如果能给我找回梦姑，我就收你为徒！\n");
    else
        command("say 这位"+RANK_D->query_respect(me)+",你如果能给我找回梦姑，我必有重谢！\n");          
    me->set_temp("lingjiu/find",1);
    return 1;

}


void attempt_apprentice(object me)
{
    if (!me->query("lingjiu/found"))
    {
        command("say 我找不到梦姑，哪里有心情收什么徒弟呢？");
        return;
    }

    if ((int)me->query_skill("bahuang-gong", 1) < 120) 
    {
        command("say " + RANK_D->query_respect(me) + "是否还应该在八荒功上多下点功夫？");
        return;
    }
    if (me->query_con() < 25) 
    {
        command("say 本门功法极为难练,你的根骨似乎不够.");
        return;
    }
    if  ((int)me->query("family/generation") < 3 )
    {
        command("say " + RANK_D->query_respect(me)+ "已是童姥的弟子，何必来向我请教。\n");
        return;
    }
    if  ((int)me->query("score") < 1000 )
    {
        command("say " + RANK_D->query_respect(me)+ "对本门的贡献不够，我暂时不能收你。\n");
        return;
    }
    command("say 好吧，"+RANK_D->query_respect(me)+"！我就收下你了！\n");
    command("recruit " + me->query("id"));
    return;
}

void recruit_apprentice(object me)
{
    if( ::recruit_apprentice(me) )
    {
        me->set("title",MAG "灵鹫宫" NOR + HIG +"首领" NOR); 
//title系统记录玩家title by seagate@pkuxkx
	      me->set_title(TITLE_RANK, me->query("title"));
	  }
    return;
}


int accept_object(object me,object ob)
{
    if ((string)ob->query("id") == "letter")
        if (me->query_temp("lingjiu/find") == 2)
        {
            message_vision("虚竹接过信，打开看了一遍。\n", me);
            message_vision ("虚竹自言自语地说“终于有梦姑消息了！”\n",me);
            command("say 多谢这位" + RANK_D->query_respect(me) + "。梦姑她现在在哪里？你带我去好吗？");
            me->set_temp("lingjiu/leading",1);
            command("follow " + me->query("id"));
        }
        else    {
            message_vision("虚竹接过信，狐疑地看了你一眼，说道：「这信不是梦姑亲手交给你的吧？」\n",me);
        }

    return 1;
}

void do_zoutiesuo(string arg)
{
    command("zou "+arg);
    return;
}

#include "/kungfu/class/masterdie.h"