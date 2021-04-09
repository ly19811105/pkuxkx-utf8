/* /kungfu/class/tiandihui/chen.c 陈近南
//将陈近南的特殊内功由300调整至360
 * @PKUxkx
 * modified by vast
 * 2003.3
 */
#include <ansi.h>
#include <title.h>
inherit NPC;
inherit F_MASTER;
#include <no1master.h>
inherit "/inherit/char/silver.c";
void heal();
int auto_perform();
string ask_me();
string ask_jing();
string ask_bian();
string ask_for_leave();
int ask_change();
#include "/new_quest/qzhengpai.h"
#include "/new_quest/quest.h"

void create()
{
    set_name("陈近南", ({ "chen jinnan", "chen","nan" }));
    set("title", HIR "天地会"HIM"总舵主"NOR );
    set("nickname", HIC "英雄无敌" NOR);
    set("long", 
            "\n这是一个文士打扮的中年书生，神色和蔼。\n"
            "他就是天下闻名的天地会总舵主陈近南,\n"
            "据说十八般武艺，样样精通。\n"
            "偶尔向这边看过来，顿觉他目光如电，英气逼人。\n");
    set("gender", "男性");
    set("age", 45);
    set("per", 20 + random(15));    
    set("attitude", "heroism");
    set("shen_type", 1);
    set("str", 40 + random(10));
    set("int", 40 + random(10));
    set("con", 30 + random(10));
    set("dex", 30 + random(10));
    set("max_qi", 15000);
    set("max_jing", 14000);
    set("max_jingli", 12500);
    set("jingli", 12500);
    set("neili", 15000);
    set("max_neili", 15000);
    set("jiali", 300);
    set("combat_exp", 12000000);
    set("repute", 200000);
    set_skill("literate", 200);
    set_skill("force", 360);
    set_skill("dodge", 300);
    set_skill("parry", 400);
    set_skill("whip", 350);
    set_skill("sword", 320);
    set_skill("hand", 280);
    set_skill("claw", 380);
    set_skill("cangming-gong", 360);
    set_skill("danxin-jian", 320);
    set_skill("houquan", 280);    
    set_skill("lingding-piao", 300);
    set_skill("jiulong-bian", 350);
    set_skill("fulong-shou", 280);
    set_skill("yunlong-zhua", 380);
    map_skill("dodge", "lingding-piao");
    map_skill("force", "cangming-gong");
    map_skill("hand", "fulong-shou");
    map_skill("parry", "danxin-jian");
    map_skill("claw", "yunlong-zhua");
    map_skill("sword", "danxin-jian");
    map_skill("whip", "jiulong-bian");
    prepare_wskill("sword","danxin-jian");
    prepare_wskill("whip","jiulong-bian");
    prepare_skill("hand","fulong-shou");
    prepare_skill("claw","yunlong-zhua");
    create_family("天地会",1, "开山祖师");
    set_temp("apply/armor", 500);
    set("book_count", 1);
    set("book2_count", 1);
    set("book3_count", 1);
    set("inquiry", ([
                "天地会" :  "\n只要是英雄好汉，都可以入我天地会。\n",
                "反清复明" : "这是我毕生的心愿和目标！\n",
                "暗号" : "敲三下！\n",
                "切口" : "敲三下！\n",
                "丹心剑谱" : (: ask_me :),
                "九龙鞭法" : (: ask_bian :),
                "云龙经" : (: ask_jing :),          
                "quest":   (: ask_quest() :),
                "cancelquest":   (: ask_cancel() :),
                "取消任务":   (: ask_cancel() :),
		            "经费" : (: ask_silver :),
		            "转换技能" : (: ask_change :),
		            "脱离帮派" : (: ask_for_leave :),
                ]) );

	set("silver_name", "经费"); //例银的名称，默认为“例银”
        set("silver_factor", 1); //例银的数量因子，默认为1
        set("silver_family_skill", "cangming-gong"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "每月发放一定的活动经费，以后就找我来要罢。"); //第一次打听例银的时候说的话
        set("msg_silver_paid", "加油干，为了我们的反清复明大业！"); //领取成功时说的话
		set_temp("apply/armor", 300);
		set_temp("apply/damage", 350);
    set("chat_chance_combat", 100);  
    set("chat_msg_combat", ({
                (: auto_perform :),
                }) );
    set("chat_chance",100);
    set("chat_msg",({
                (: heal :),
                }));
    setup();
	setup_no1master();
    carry_object("/clone/armor/jinzhuang")->wear();
    carry_object("/d/riyuejiao/obj/yaodai")->wear();
    carry_object("/clone/weapon/changjian")->wield();
    carry_object("/d/xiangyang/npc/obj/item/27")->wield();
}
string ask_me()
{
    mapping fam; 
    object ob;
    if (!(fam = this_player()->query("family")) 
            || fam["family_name"] != "天地会")
        return RANK_D->query_respect(this_player()) + 
            "与本派素无来往，不知此话从何谈起？";
    if( this_player()->query("score") < 100 )
        return "你对本派贡献还没作出什么贡献呢，还是以后再来吧。";
    if (query("book_count") < 1)
        return "你来晚了，本派的「丹心剑谱」不在此处。";
    add("book_count", -1);
    if((this_player()->query_skill("danxin-jian",1)) < 70)
        ob = new("/d/beijing/npc/obj/yljianpu1");
    else if((this_player()->query_skill("danxin-jian",1)) >= 70)
        ob = new("/d/beijing/npc/obj/yljianpu2");
    ob->move(this_player());
    return "好吧，这本「丹心剑谱」你拿回去好好钻研。";
}
string ask_bian()
{
    mapping fam; 
    object ob;
    if (!(fam = this_player()->query("family")) 
            || fam["family_name"] != "天地会")
        return RANK_D->query_respect(this_player()) + 
            "与本派素无来往，不知此话从何谈起？";
    if( this_player()->query("score") < 100 )
        return "你对本派贡献还没作出什么贡献呢，还是以后再来吧。";
    if (query("book2_count") < 1)
        return "你来晚了，本派的「九龙鞭法」不在此处。";
    add("book2_count", -1);
    ob = new("/d/beijing/npc/obj/ylbian");
    ob->move(this_player());
    return "好吧，这本「九龙鞭法」你拿回去好好钻研。";
}
string ask_jing()
{
    mapping fam; 
    object ob;
    if (!(fam = this_player()->query("family")) 
            || fam["family_name"] != "天地会")
        return RANK_D->query_respect(this_player()) + 
            "与本派素无来往，不知此话从何谈起？";
    if( this_player()->query("score") < 100 )
        return "你对本派贡献还没作出什么贡献呢，还是以后再来吧。";
    if (query("book3_count") < 1)
        return "你来晚了，本派的「云龙经」不在此处。";
    add("book3_count", -1);
    if(this_player()->query_skill("cangming-gong") < 50)
        ob = new("/d/beijing/npc/obj/yljing1");
    else if(this_player()->query_skill("cangming-gong") >= 50)
        ob = new("/d/beijing/npc/obj/yljing2");
    ob->move(this_player());
    return "好吧，这本「云龙经」你拿回去好好钻研。";
}

//新旧技能转换
int ask_change()
{
  object me=this_player();
  int level;
  
  if ( (level=me->query_skill("yunlong-shengong",1)) > 0 )
  {
  	me->set_skill("cangming-gong", level);
  	me->delete_skill("yunlong-shengong");
  }
  
  if ( (level=me->query_skill("yunlong-shenfa",1)) > 0 )
  {
  	me->set_skill("lingding-piao", level);
  	me->delete_skill("yunlong-shenfa");
  }
  
  if ( (level=me->query_skill("yunlong-shou",1)) > 0 )
  {
  	me->set_skill("fulong-shou", level);
  	me->delete_skill("yunlong-shou");
  }
  
  if ( (level=me->query_skill("yunlong-bian",1)) > 0 )
  {
  	me->set_skill("jiulong-bian", level);
  	me->delete_skill("yunlong-bian");
  }

  if ( (level=me->query_skill("yunlong-jian",1)) > 0 )
  {
  	me->set_skill("danxin-jian", level);
  	me->delete_skill("yunlong-jian");
  }
  
  tell_object(me, "已经将天地会的功夫转换成新的功夫。\n");
  return 1;
}

void init()
{
    object ob;
    ::init();
    ob = this_player();
    add_action("do_leave",  "leave");
    if((int)ob->query("shen") < -1000000 && ob->query("family/master_id")=="chen jinnan")
    {
        CHANNEL_D->do_channel(this_object(), "jh", ob->query("name")+"!你这等邪恶奸诈之徒，我岂能仍是你的师傅。");
        command("expell "+ ob->query("id"));
        this_player()->set("title","天地会" + RED + "弃徒" NOR);
//title系统记录玩家title by seagate@pkuxkx
	      ob->set_title(TITLE_RANK, ob->query("title"));
    }
    if(userp(ob) && ob->query("shen") < - 1000000)
    {
        say( "陈近南说道：邪魔歪道怎么混到这里来的？\n");
        this_object()->kill_ob(ob);
        return;
    }        
}

string ask_for_leave()
{
	object me;

	me = this_player();

	if( (string)me->query("family/family_name") != "天地会")
		return "你非我天地会弟子，脱离帮派的事情我作不得主。";

	me->set_temp("pending/leave_tdh", 1);
  return "如果" + RANK_D->query_respect(me) + "真想离我天地会而去，就请下决心(leave)吧！";
}

int do_leave()
{
	object me = this_player();
	
	if (me->query_temp("pending/leave_tdh") != 1)
		return 0;
	message_vision("$N对$n说道：「从此你就不再是我天地会帮众了，请好自为之！」\n",this_object(), me );
	tell_object(me,HIR "你决定叛出天地会门下！\n" NOR);
	me->delete_temp("pending/leave_tdh");
  me->expell_family("天地会");
	if (me->query("combat_exp") >= 1000)
		me->add("betrayer",1);
	return 1;
}	

void attempt_apprentice(object ob)
{
    if (ob->query("family/family_name") != "天地会")
    {
        command("say 想加入天地会要脚踏实地，" + RANK_D->query_respect(ob) + "先去拜关夫子吧！\n");
        return;
    }
    if ((int)ob->query_skill("cangming-gong", 1) < 180) {
        command("say 我天地会武功，最重视内功心法。"); 
        command("say " + RANK_D->query_respect(ob) + 
                "是否还应该在浩气苍冥功上多下点功夫？");
        return;
    }
    if ((int)ob->query("repute") < 50000)
    {
        command("say 我天地会武功天下无敌，凡入我门，\n必闯荡江湖，行侠仗义，为天下苍生谋福利。\n"); 
        command("say " + RANK_D->query_respect(ob) + 
                "是否应该先出去闯一闯，做几件惊天动地的大事，以提高武林声望？");
        return ;
    }
    if ((int)ob->query("shen") >0&&(int)ob->query("shen") < 50000) {
        command("say 学武之人，德义为先，功夫的高低倒还在其次，未练武，要先学做人。");
        command("say 在德行方面，" + RANK_D->query_respect(ob) +
                "是否还做得不够？");
        return ;
    }
    if (ob->query("score")<1500)
    {
        command("say 你自问是否对本会尽力了?");
        return;
    }
    if (!ob->query_temp("tiandihui/kill_ao"))
    {
        command("say 鳌拜阴险狡诈，害死了我派众多弟子，你去把他杀了，回来我一定收你。");
        ob->set_temp("tiandihui/kill_ao",1);
        return;
    }
    if (!ob->query_temp("tiandihui/killer"))
    {
        command("say 你还没有杀掉鳌拜，大仇未报，我不还不能收你。");
        return;
    }
    if((int)ob->query("shen")<0 && (int)ob->query("shen") > -1000)
        command("say "+ RANK_D->query_respect(ob) +"你品行不端，但也还做了些好事，以后若敢再做坏事，我决不饶你。\n");
    command("say 我天地会所作所为，无一不是前人所未行之事。\n");
    command("say 万事开创在我，骇人听闻，物议沸然，又何足论？\n");
    command("say 今天就收了你吧！！\n");
    CHANNEL_D->do_channel(this_object(), "bd", "想不到我一身惊人艺业，今日终于有了传人，哈哈哈哈！！！！");
    message_vision(HIC "$N的江湖声望提高了！\n" NOR,this_player());
    ob->add("repute",10000);
    ob->delete_temp("tiandihui/kill_ao");
    ob->delete_temp("tiandihui/killer");
    command("recruit " + ob->query("id"));
}
void recruit_apprentice(object ob)
{
    if( ::recruit_apprentice(ob) )
    {
        ob->set("title",HIR "天地会" NOR + HIG +"青木堂堂主" NOR);
//title系统记录玩家title by seagate@pkuxkx
	      ob->set_title(TITLE_RANK, ob->query("title"));
	  }
    return;
}
void heal()
{
    object ob=this_player();
    if (ob->query("eff_qi") < ob->query("max_qi"))
    {
        command("exert heal");
        command("enforce 100");
        return;
    }
    if (ob->query("qi") < ob->query("eff_qi"))
    {
        command("exert recover");
        return;
    }
    if (ob->query("jing") < ob->query("eff_jing"))
    {   command("exert regenerate");
        return;
    }
}
int auto_perform()
{
    object me = this_object();
    object target = me->select_opponent();
    object weapon = me->query_temp("weapon");
    command("exert powerup");
    if ( !objectp(target) ) return 0;
    if (me->query("qi") < me->query("eff_qi"))
        command("exert recover");
    if (me->query("jing") < me->query("eff_jing"))
        command("exert regenerate");
    if ( !target->is_busy())
    {
        switch( random(6) )
        {
            case 0:
                command("unwield jian");
                command("unwield bian");
                command("perform hand.an " + target->query("id"));
                command("wield jian");
                command("wield bian");
                break;
            case 1:
                command("unwield jian");
                command("unwield bian");
                command("perform claw.ningxue " + target->query("id"));
                command("wield jian");
                command("wield bian");
                break;
            case 2:
                command("unwield jian");
                command("unwield bian");
                command("perform claw.ningxue " + target->query("id"));
                command("wield jian");
                command("wield bian");
                break;
            case 3:
                command("perform sword.xian " + target->query("id"));
                break;
            case 4:
                command("perform sword.xunlei " + target->query("id"));
                break;
            case 5:
                command("changewield");
                command("perform whip.baibi " +target->query("id"));
                command("changewield");
                break;
        }
    }
    else
    {
        switch( random(4) )
        {
            case 0:
                command("perform sword.xian " + target->query("id"));
                break;
            case 1:
                command("perform sword.xunlei " + target->query("id"));
                break;
            case 2:
                command("changewield");
                command("perform whip.suo " +target->query("id"));
                command("changewield");
                break;
            case 3:
                command("changewield");
                command("perform whip.baibi " +target->query("id"));
                command("changewield");
                break;
        }
    }
    return 1;
}

#include "/kungfu/class/masterdie.h"