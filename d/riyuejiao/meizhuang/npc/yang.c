//yang.c	杨莲亭
//by bing
inherit NPC;
inherit "/inherit/char/silver.c";
#include "riyuenpc.h"
#include <ansi.h>

string askdf();
void create()
{
        set_name("杨莲亭", ({ "yang lianting", "yang" }));
        set("long","他是日月神教教下弟子，身形魁梧，满脸虬髯，形貌极为雄健威武。
他武功既低，又无办事才干，但近来东方不败却对他宠信得很，所以
在教中独掌权柄，风光的很。\n");
	set("title",MAG "日月神教" + HIG "总管" NOR);
	set("gender", "男性");
        set("age", 24);
        set("shen_type", -1);
        set("str", 20);
        set("int", 23);
        set("con", 24);
        set("dex", 20);
        set("max_qi", 200);
        set("max_jing", 200);
        set("neili", 200);
        set("max_neili", 200);
        set("combat_exp", 5000);

        set("inquiry", ([
            "东方不败" : "东方教主的名字也是你叫得的？",
            "东方教主" : (: askdf :),
	    "任我行" : (: ask_ren :),
		"赏银" : (: ask_silver :),
	      ]) );


	set("silver_name", "赏银"); //例银的名称，默认为“例银”
        set("silver_factor", 1); //例银的数量因子，默认为1
        set("silver_family_skill", "flatter"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "教主文成武德，决定以后每月赏你点银子。还不谢恩！"); //第一次打听例银的时候说的话
        set("msg_silver_record", "$N跟旁边的弟子说了点什么，那弟子忙点头。\n"); //作记录时的描述\n
        set("msg_silver_check", "$N问了问身边的一个弟子，那弟子毕恭毕敬的答了。\n"); //检查记录时的描述\n
        set("msg_silver_mudage", "大胆，哪有你的赏银！"); //时间未到不能领取时说的话
        set("msg_silver_paid", "拿去，快谢教主！"); //领取成功时说的话
        set("msg_silver_score", "$N皮笑肉不笑的拍着$n道：「看你还挺忠心啊。」\n"); //由于提升师门忠诚而领取例银时的描述\n
        set("msg_silver_skill", "$N皮笑肉不笑的拍着$n道：「看不出你还挺忠心啊。」\n"); //由于提升师门武功而领取例银时的描述\n
        set("msg_silver_exp", "$N皮笑肉不笑的拍着$n道：「武功又有长进啊？」\n"); //由于提升经验而领取例银时的描述\n
        set("msg_silver_none", "哼，一点贡献都没有，滚！"); //领取例银条件均不满足时说的话

        set_skill("force", 40);
        set_skill("riyue-shengong", 40);
        set_skill("dodge", 20);
        set_skill("parry", 30);
	set_skill("strike",30);
	set_skill("kaishan-zhang",30);
        set_skill("feitian-shenfa", 20);
        set_skill("literate",40);
        map_skill("force", "riyue-shengong");
        map_skill("parry", "kaishan-zhang");
        map_skill("dodge", "feitian-shenfa");
        map_skill("strike","kaishan-zhang");
	create_family("日月神教", 22, "弟子");
        setup();
        carry_object(__DIR__"obj/heiyi")->wear();
}

string askdf()
{
	object key;
	object me = this_player();

	if ( me->query("save_ren") || me->query("family/master_id") == "ren woxing")
		return "圣教主千秋万载，一统江湖！\n";
	
	if ( me->query_temp("riyue/give杨"))
	{
		key = new(__DIR__"obj/doorkey");
		key->move(me);
		message_vision("杨莲亭给$N一把钥匙。\n",me);
		me->delete_temp("riyue/give杨");
		me->set_temp("riyue/杨ok",1);
		call_out("destroying",0);
		return 	"这把钥匙给你，你去吧！\n";
	}
	me->set_temp("riyue/ask杨",1);
	message_vision("杨莲亭清了清嗓子，顿了一顿，见$N毫无反应，脸露不愉之色。\n",me);
	return "圣教主文成武德，仁义英明，中兴圣教，泽被苍生。\n";

}

int accept_object(object who, object ob)
{
	object key;
	
	if (ob->query("money_id") && ob->value() >= 200000) 
	{
		if (who->query_temp("riyue/ask杨"))
		{
			message_vision("杨莲亭顿时喜笑颜开，对$N说道：「这把钥匙给你，你去吧！」\n",who);
			key = new(__DIR__"obj/doorkey");
			key->move(who);
			message_vision("杨莲亭给$N一把钥匙。\n",who);
			who->delete_temp("riyue/ask杨");
			who->set_temp("riyue/杨ok",1);
			call_out("destroying",0);
			return 1;
		}
		else	{
				message_vision("杨莲亭顿时喜笑颜开，对$N说道：「" + RANK_D->query_respect(who) + "有什么事？」\n",who);
				who->set_temp("riyue/give杨",1);
				call_out("destroying",0);
				return 1;
			}
	}
	return 0;
}

				
