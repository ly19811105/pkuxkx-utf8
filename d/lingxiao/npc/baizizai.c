// File         : baizizai.c
// Created By   : iszt@pkuxkx, 2007-03-06

#include "setdizi.h"
#include <title.h>
#include <no1master.h>

int ask_axiu();  
int ask_xiaocui(); 
int ask_ding();
string ask_for_leave();

void create()
{
        setcreate(350);

        set_name("白自在", ({ "bai zizai", "bai", "zizai", }));
        set("long",WHT
"这就是雪山派掌门人"HIC"「威德先生」"NOR+WHT"白自在。他巍巍踞坐，白发萧然，却是神态威\n"
"猛，身材特高，当真便似庙中神像一般形相庄严，令人肃然起敬。\n"NOR);

        set("age", 60);
        set("title", HIY"雪山派掌门人"NOR);
        set("nickname", HIC"威德先生"NOR);
        set("gender","男性");
        set("str", 45);
        set("dex", 28);
        set("con", 46);
        set("int", 30);
        set("per", 21);

        add("inquiry", ([
                "name" : "我白自在的名字又岂是你等小辈问得的！",
                "here" : "废话，这里是凌霄城，老子武功天下第一！",
                "rumors" : "哼，听说丁不四那老不死的要小翠去他那个狗屁碧螺岛，真是痴心妄想！",
                "阿绣":(: ask_axiu :),
                "小翠":(: ask_xiaocui :),
                "史小翠":(: ask_xiaocui :),
                "丁不四":(: ask_ding :),     
                "脱离门派" : (: ask_for_leave :),         
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "liuchu" :),
                (: perform_action, "fengjian" :),
                (: perform_action, "juebi" :),

        }));
        create_family("雪山派", 5, "弟子");

        setup();
		setup_no1master();
        carry_object(__DIR__"obj/sword.c")->wield();
        carry_object(__DIR__"obj/changpao.c")->wear();

}

void init ()
{
	  add_action("do_leave",  "leave");
	  ::init();
}

string ask_for_leave()
{
	object me;

	me = this_player();

	if( (string)me->query("family/family_name") != "雪山派")
		return "你非我雪山派弟子，脱离门派的事情我作不得主。";

	me->set_temp("pending/leave_xueshan", 1);
  return "如果" + RANK_D->query_respect(me) + "真想离我雪山派而去，就请下决心(leave)吧！";
}

int do_leave()
{
	object me = this_player();
	
	if (me->query_temp("pending/leave_xueshan") != 1)
		return 0;
	message_vision("$N对$n说道：「从此你就不再是我雪山派门下了，请好自为之！」\n",this_object(), me );
	tell_object(me,HIR "你决定叛出雪山派门下！\n" NOR);
	me->delete_temp("pending/leave_xueshan");
  me->expell_family("雪山派");
	if (me->query("combat_exp") >= 1000)
		me->add("betrayer",1);
	return 1;
}	

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping fam = ob->query("family");
        string name;

        if ( !fam || fam["family_name"] != "雪山派")
        {
                command("haha");
                command("say 算你有眼光，知道老子天下第一。你先去找我的徒弟们或者孙女阿绣学两招吧。");
                return;
        }
        if(fam["master_name"] != "白万剑" || fam["master_id"] != "bai wanjian")
        {
                command("say 你先去找剑儿学两招吧。");
                return;
        }
        if(fam["generation"] <= me->query("family/generation"))
        {
                CHANNEL_D->do_channel(this_object(), "jh", "bug", 1);
                CHANNEL_D->do_channel(this_object(), "jh", ob->name() + "，你在利用bug！");
                return;
        }
        if(ob->query("betrayer"))
        {
                command("say 我平生最恨背信弃义之人，你屡次叛师，嘿嘿！");
                return;
        }
        if(ob->query_int() < 40)
        {
                command("say 就凭你的悟性？罢了，再去读几年书吧。");
                return;
        }
        if(ob->query_skill("xueshan-jianfa", 1) < 250)
        {
                command("say 剑儿这个小混蛋，把你的剑法教成这样就让你来找我？");
                return;
        }
        if(ob->query_skill("xueshan-neigong", 1) < 160)
        {
                command("say 你的本门内功功力未到，再去练练罢。");
                return;
        }
        if(pow(ob->query_skill("sword", 1)/8, 3)*100 < ob->query("combat_exp"))
        {
                command("say 你的剑法太过疏于练习，再去练练罢。");
                return;
        }
        if(ob->query("score") < 1500)
        {
                command("say 你为雪山派的贡献不够，再去锤炼几年罢。");
                return;
        }
        
        ob->restore_face(FACE_ORIGIN);
        
        if(strwidth(ob->query("name")) > 2)
                name = ob->query("name")[0..1] + "万" + ob->query("name")[2..3];
        else
                name = ob->query("name")[0..1] + "万" + getname()[4..5];

        command("nod "+ ob->query("id"));
        CHANNEL_D->do_channel(this_object(), "jh", "haha "+ob->query("id"), 1);
        CHANNEL_D->do_channel(this_object(), "jh", "nod1", 1);
        command("recruit "+ ob->query("id"));
        ob->set("title", "雪山派第六代长门弟子");
//title系统记录玩家title by seagate@pkuxkx
	      ob->set_title(TITLE_RANK, "雪山派第六代长门弟子");
        command("say 以后你就叫「" + name +"」罢！");
        ob->set("lingxiao/old_name", ob->query("name"));
        ob->set("name", name);
        ob->set_face( FACE_FACT, ob->query("name") );
}
int ask_axiu()
{
        object me = this_player();
        object ob = this_object();
        if (!me->query_temp("jinwudao/ask_axiu2")) 
        {
        command("say 阿绣是我的孙女儿，乖巧可爱，现在在自己的闺房里。\n");
        command("say 你可不要欺负她哟。");
        return 1;
        }
        message_vision("$N走上前去，对着$n施了一礼，道：“师傅，阿绣可在这里？”\n",me,ob);
        command("ah");
        command("say "+me->query("rank_info/respect")+"此话怎讲，发生什么事情了么？\n");
        message_vision("$N道：“适才我去阿绣闺房，看到小丫鬟昏迷不醒，
        她醒来道有奸人意图非礼阿绣，但此刻阿绣已经不见了。”\n",me,ob);
        command("oh");
        command("say 你再去她闺房看看，可有什么线索。");
        me->set_temp("jinwudao/ask_axiu3", 1); 
        return 1;
}
int ask_xiaocui()
{
        object me = this_player();
        object ob = this_object();
        if (!me->query_temp("jinwudao/ask_xiaocui1")) 
        {
        command("say 小翠是你师娘，她的名号可不是你随便叫得的。\n");
        return 1;
        }
        message_vision("$N走上前去，恭恭敬敬的对着$n道：“师傅，阿绣跌落谷底，
        被师娘救走，师娘可在凌霄城中？”\n",me,ob); 
        command("sigh4 " +"bai zizai");
        command("say 此事我已知悉，我和你师娘因此事大吵了一架，她一怒之下，离开凌霄城了。");
        command("say 小翠早年间是江湖中有名的美女，有些痴心妄想者如丁不四之流至今仍然纠缠不清。");
        me->set_temp("jinwudao/ask_xiaocui2", 1);        
        return 1;
}
int ask_ding()
{
        object me = this_player();
        object ob = this_object();
        if (!me->query_temp("jinwudao/ask_xiaocui2")) 
        {
        command("say 丁不四这个老不死的，老纠缠着小翠，下次让我看到，哼！\n");
        return 1;
        }
        command("say 江湖险恶，她只身犯险，我心难安。你能帮我找回来吗？");
        command("say 小翠可能去了海外的小岛散心。");  
        me->set("jinwudao/phase1", 1); 
        return 1;
}
