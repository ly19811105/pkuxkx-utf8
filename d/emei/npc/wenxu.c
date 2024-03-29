//wenxu.c 文虚师太
// create bye cuer
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include <title.h>

string ask_for_join();
string ask_for_leave();
void do_answer(string);
void create()
{
        set_name("文虚师太", ({
                "wenxu shitai",
                "wenxu",
                "shitai",
        }));
        set("long",
                "她是一位年轻的师太。\n"
        );
        set("gender", "女性");
        set("attitude", "friendly");
        set("class", "bonze");
        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
                "还俗"  : (: ask_for_leave :),
        ]));
        set("age", 28);
        set("shen_type", 1);
        set("str", 17);
        set("int", 20);
        set("con", 50);
        set("dex", 21);
        set("max_qi", 500);
        set("max_jing", 200);
        set("neili", 400);
        set("max_neili", 400);
        set("jiali", 40);
        set("combat_exp", 10000);
        set("score", 100);
        set_skill("force", 60);
        set_skill("linji-zhuang", 60);
        set_skill("dodge", 70);
        set_skill("zhutian", 70);
        set_skill("jinding-mianzhang", 70);
        set_skill("strike", 70);
        set_skill("parry", 60);
        set_skill("mahayana", 70);
        set_skill("literate", 60);
        map_skill("force", "linji-zhuang");
        map_skill("dodge", "zhutian");
        map_skill("strike", "jinding-mianzhang");
        map_skill("parry", "jinding-mianzhang");
        prepare_skill("strike", "jinding-mianzhang");
        create_family("峨嵋派", 5, "弟子");
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
}
void init()
{
        add_action("do_kneel", "kneel");
        add_action("do_decide","decide");
}
string ask_for_join()
{
        object me;
        me = this_player();
        if( (string)me->query("class")=="bonze" )
                return "阿弥陀佛！你我同是出家人，何故跟贫尼开这等玩笑？\n";

        if(!undefinedp(me->query("marry/lover")))
                return "阿弥陀佛！施主尘缘未了，还是罢了吧。\n";
 
        if( (string)me->query("gender") != "女性" )
                return "阿弥陀佛！善哉！善哉！施主若真心皈依我佛，可去少林寺里受戒。\n";
        if (me->query("family/family_name")!= "峨嵋派")
                return "阿弥陀佛！善哉！善哉！施主若真心皈依我佛，可入我峨嵋俗门后再做思量\n";
        me->set_temp("pending/join_emei", 1);
        return "阿弥陀佛！善哉！善哉！施主若真心皈依我佛，请跪下(kneel)受戒。\n";
}
int do_kneel()
{
        object me = this_player();
        string *prename =
         ({ "园", "悟", "法", "怡" });
        string name, new_name;
        if( !me->query_temp("pending/join_emei") )
                return 0;
        message_vision(
                "$N双手合十，恭恭敬敬地跪了下来。\n\n"
                "$n伸出手掌，在$N头顶轻轻地摩挲了几下，将$N的头发尽数剃去。\n\n",
                me, this_object() );
        me->restore_face(FACE_ORIGIN);
        name = me->query("name");
        new_name = prename[random(sizeof(prename))] + name[0..0];
        command("say 从今以后你的法名叫做" + new_name + "。");
        command("smile");
        me->delete_temp("pending/join_bonze");
        me->set("name", new_name);
        me->set_face( FACE_FACT, me->query("name") );
        me->set("class", "bonze");
        me->set("K_record", me->query("PKS") + me->query("MKS"));
        me->set("shen_record", me->query("shen"));
        me->set("shen", 0);
        return 1;
}
void attempt_apprentice(object ob)
{
        if( (string)ob->query("gender") != "女性" )
        {
                command ("say 阿弥陀佛！施主呀，贫尼可不敢开这等玩笑啊。");
                return;
        }
        if( ob->query("shen") < 0)
           {
            command("say 阿弥陀佛！本派不收为非作歹之徒。");  
            command("sigh");
            command("say 以后多做善事吧！！阿弥陀佛！");                     
            return;
           }  
	if ((string)ob->query("family/family_name") == "灵鹫宫" && ob->query("lingjiu/xiulian"))
		{
			ob->set_temp("bai/ask",1);
        		command("say "+RANK_D->query_respect(ob)+"，你现在拜我似乎会有很大损失，你能拿定主意吗？(answer)");
			
		}
	else  if( (string)ob->query("class")!="bonze" )
        {  
              command("say 阿弥陀佛！贫尼就收下你做『俗家弟子』了。");
              command("say 以后想出家的话跟我说一声吧。阿弥陀佛！");              
              command("say 阿弥陀佛，善哉！善哉！");
	}
       	ob->set("xiashan",1);
       	command("recruit " + ob->query("id"));
	return;
}
string ask_for_leave()
{
        object me;

        me = this_player();

        if( (string)me->query("class")!="bonze" )
                return "阿弥陀佛！施主并未出家，何故跟贫尼开这等玩笑？\n";

        if( (string)me->query("family/family_name") != "峨嵋派")
                return "阿弥陀佛！施主非我峨嵋弟子，还俗的事情贫尼作不得主。\n";

        me->set_temp("pending/leave_emei", 1);
                return "阿弥陀佛！如果" + RANK_D->query_respect(me) + "真想离我佛门而去，就请下决心(decide)吧！。\n";
}
int do_decide()
{
        string* skillname;
        int lev;
        mapping skills;
        int i;
        object me = this_player();
//        object body;
        
        if (me->query_temp("pending/leave_emei") != 1)
        {
                tell_object(me,"什么?\n");
                return 1;
        }
        message_vision("文虚师太对$N说道：「阿弥陀佛！从此施主就不再是我峨嵋门下了，请好自为之！」\n",me);
        tell_object(me,"你决定判出峨嵋门下！\n");
        me->delete_temp("pending/leave_emei");
        me->expell_family("峨嵋派");
        if (me->query("combat_exp") >= 1000)
                me->add("betrayer",1);
        return 1;
}               
void do_answer(string arg)
{
	object me=this_player();
	if (!me->query_temp("bai/ask")) return;
	if (!arg || (arg != "是" && arg != "能" && arg != "yes"))
        	command("say 你说的什么乱七八糟的，看来你是没有诚心，算了！");
	else
	{
        	command("say 好吧，"+RANK_D->query_respect(me)+"，我就收下你了！");
		me->set("mud_age",me->query("lingjiu/mud_age"));
		me->set("age",14+me->query("mud_age")/3600/24);
		me->delete("lingjiu/skill_status");
		me->delete("lingjiu/qi");
		me->delete("lingjiu/eff_qi");
		me->delete("lingjiu/max_qi");
		me->delete("lingjiu/jing");
		me->delete("lingjiu/eff_jing");
		me->delete("lingjiu/max_jing");
		me->delete("lingjiu/jingli");
		me->delete("lingjiu/neili");
		me->delete("lingjiu/max_jingli");
		me->delete("lingjiu/max_neili");
		me->delete("lingjiu/combat_exp");
		me->delete("lingjiu/need_xiulian");
		me->delete("lingjiu/mud_age");
		me->delete("lingjiu/xiulian");
		me->delete("lingjiu/last_xiulian_time");
		me->delete_temp("bai/ask");
	       command("recruit "+me->query("id"));
	}
}
