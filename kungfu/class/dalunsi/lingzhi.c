// lingzhi.c 灵智上人
// by iceland

#include <ansi.h>
#include <title.h>
inherit NPC;
inherit F_MASTER;
inherit "/inherit/char/silver.c";

int ask_me_1();
int ask_me_2();

void create()
{
        set_name("灵智上人", ({ "lingzhi shangren", "lingzhishangren" ,"lingzhi","shangren" }));
        set("long",@LONG
他长得白白净净，身体肥胖，颈项中的肥肉叠了至少三四层。慈眉善目，老是
笑眯眯的模样，张嘴一乐就露出两颗虎牙。
LONG
        );
        set("title", HIY "大轮寺第十二代弟子" NOR);
        set("gender", "男性");
        set("age", 41);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 28);
        set("int", 20);
        set("con", 25);
        set("dex", 27);
        set("max_qi", 1800);
        set("eff_jing", 900);
        set("max_jing",900);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 100);
        set("combat_exp", 600000);
        set("score", 25000);
        set("unique", 1);

        set_skill("huanxi-chan", 120);
        set_skill("literate", 100);
        set_skill("force", 120);
        set_skill("longxiang-boruo", 120);
        set_skill("dodge", 120);
        set_skill("yuxue-dunxing", 120);
        set_skill("hand", 120);
        set_skill("poison",120);
        set_skill("dashou-yin", 120);
        set_skill("parry", 120 );
        set_skill("staff",200);
        set_skill("wushang-dali",200);

        map_skill("force", "longxiang-boruo");
        map_skill("dodge", "yuxue-dunxing");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "dashou-yin");
        map_skill("staff", "wushang-dali");

        prepare_skill("hand","dashou-yin");

        create_family("大轮寺", 12, "弟子");
        set("class", "huanxi");
        set("inquiry", ([
                "俸禄" : (: ask_me_1 :),
                "供奉" : (: ask_silver :),
        ]));
        
        set("silver_name", "供奉"); //例银的名称，默认为“例银”
        set("silver_factor", 1.5); //例银的数量因子，默认为1
        set("silver_family_skill", "longxiang-boruo"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "咱们大轮寺历来受吐蕃王室重视，以后你就找我领供奉吧。"); //第一次打听例银的时候说的话
        set("msg_silver_record", "$N转身取出一卷薄绢，记下了点什么。\n"); //作记录时的描述\n
        set("msg_silver_check", "$N转身取出一卷薄绢，看了看。\n"); //检查记录时的描述\n
        set("msg_silver_mudage", "历年供奉有所短缺，这个月的供奉你已经领过了！"); //时间未到不能领取时说的话
        set("msg_silver_paid", "拿好俸禄，你尽可去精研佛法，不必再为衣食些许俗务分心了"); //领取成功时说的话
        set("msg_silver_score", "$N对着$n哈哈大笑道：「不错，最近你为本寺出力甚多。」\n"); //由于提升师门忠诚而领取例银时的描述\n
        set("msg_silver_skill", "$N对着$n哈哈大笑道：「想不到你的龙象般若功长进不少啊。」\n"); //由于提升师门武功而领取例银时的描述\n
        set("msg_silver_exp", "$N对着$n哈哈大笑道：「看来你的武功长进不小啊。」\n"); //由于提升经验而领取例银时的描述\n
        set("msg_silver_none", "大伙或者为寺中出力，或者苦练功夫，你倒是做什么去了？"); //领取例银条件均不满足时说的话
        
        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: exert_function, "shield lingzhi shangren" :),
                (: perform_action, "hand.tianyin" :), }));

        setup();
        carry_object("/d/dalunsi/npc/obj/qinxiu-jiasha")->wear();

        add_money("silver",70);
}

void attempt_apprentice(object ob)
{
        if( (string)ob->query("gender") == "女性" ) {
               command("shake");
               command("say 我佛法还不够深湛，恐怕一个把持不住...你还是去找别人吧。");
               return;
             }

        if ((string)ob->query("family/family_name") != "大轮寺") {
                command("say"+ RANK_D->query_respect(ob) +
                        "不是本寺弟子，在这里捣什么乱？！");
                return;
             }

        if ((int)ob->query_skill("huanxi-chan", 1) < 80) {
                command("say 欢喜禅是各项武功之本，你再勤加修炼吧。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多钻研钻研本门的心法吧。");
                return;
        }

        command("say 好吧，以后你就是我的弟子了。");
        command("recruit " + ob->query("id"));
        ob->set("title", HIY "大轮寺第十三代弟子" NOR);
//title系统记录玩家title by seagate@pkuxkx
	      ob->set_title(TITLE_RANK, ob->query("title"));
}

int ask_me_1()
{
        object me;
        int skill,i,j;
        mapping myfam;
        me=this_player();
        skill=me->query_skill("huanxi-chan",1);
        myfam = (mapping)me->query("family");
        i = (int)me->query("join_age");  
        j = (int)me->query("gf_ok");

        if (!myfam || myfam["family_name"] != "大轮寺") 
        {
        command("sneer "+(string)me->query("id"));
        command("say 看"+ RANK_D->query_respect(me) +"贼眉鼠眼，面生得很呀，不知道问这个做什么？\n");
        return 1;
         }

        if((int)me->query("xs_given")>=(int)me->query("age")) 
        {
        command("sigh "+(string)me->query("id"));
        command("say 你今年的俸禄不是已经领走了么？明年再来吧。\n");
        return 1;
         }

        if(skill - me->query("silver/last_huanxichan") < 5)
        {
                command("buddhi");
                command("say 你的佛法修为毫无长进，要俸禄有什么用？");
                return 1;
        }
        me->set("silver/last_huanxichan", skill);
        //added by iszt@pkuxkx, 2007-01-16

        if( (( i + j ) < (int)me->query("age")) && ( skill < 100 ) )
        {
        if((int)me->query("xs_given")>=(int)me->query("age")) {
        command("shake "+(string)me->query("id"));
        command("say "+ RANK_D->query_respect(me) +"历年供奉有所短缺，今年不能领取俸禄，明年再来吧。\n");
        return 1;
        }
        command("shake "+(string)me->query("id"));
        command("say "+ RANK_D->query_respect(me) +"历年供奉有所短缺，今年不能领取俸禄，明年再来吧。\n");
    me->add("gf_ok",1);
        me->set("xs_given",(int)me->query("age"));
        return 1;
         }


        if((int)me->query("xs_given")<(int)me->query("age")) 
   {

        if (skill < 100)
         {
        command("pat "+(string)me->query("id"));
        command("say 你佛法尚未小成，还是勤加修炼为是。\n");
        return 1;
          }

        if (skill >= 100 && skill < 140)
         {
        me->set_temp("give_gold", 50);               
        remove_call_out("give_money");
        call_out("give_money", 1, me);
        return 1;
          }

        if (skill >= 140 && skill < 180)
         {
        me->set_temp("give_gold", 90);
        remove_call_out("give_money");
        call_out("give_money", 1, me);
        return 1;
          }

        if (skill >= 180 && skill < 240)
         {
        me->set_temp("give_gold", 200);
        remove_call_out("give_money");
        call_out("give_money", 1, me);
        return 1;
          }

        if (skill >= 240)
         {
        me->set_temp("give_gold", 360);
        remove_call_out("give_money");
        call_out("give_money", 1, me);
        return 1;
          }
    }
}

int give_money(object me)
{
        int amount;
        object n_money;
        command("buddhi lingzhi shangren");
        command("say"+ RANK_D->query_respect(me) +"请拿好俸禄，尽可去精研佛法，不必再为衣食些许俗务分心了。");
        message_vision("灵智上人拿出几锭黄金，递给了$N。\n",me);        
        n_money = new(GOLD_OB);
        n_money->move(me);
        amount = me->query_temp("give_gold"); 
        n_money->add_amount(amount);
        me->delete_temp("give_gold");
        me->set("xs_given",(int)me->query("age"));
}
