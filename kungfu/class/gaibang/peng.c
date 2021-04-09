// sample master.c code

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit "/inherit/char/silver.c";
#include "bonus.h"
#include "gb_extra_job.h"
#include "/new_quest/qzhengpai.h"
#include "/new_quest/quest.h"
void consider();
int ask_job();
int ask_fail();
void create()
{
        set_name("彭有敬", ({"peng youjing", "peng", "youjing"}));
        set("title",MAG "丐帮" NOR + YEL "九袋" NOR+ MAG "长老" NOR);
        set("nickname", GRN "掌钵龙头" NOR);
        set("gender", "男性");
        set("age", 50);
        set("long",
                "彭有敬是丐帮中净衣派的首领，衣着干净华丽，不象叫化子。\n"
                "他脸上挂着慈祥的笑容，一双眼睛有摄人心魄的力量。\n");

        set("attitude", "peaceful");

        set("str", 24);
        set("int", 20);
        set("con", 24);
        set("dex", 20);

        set("qi", 2000);
        set("max_qi", 2000);
        set("jing", 100);
        set("max_jing", 100);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 120);
        set("is_peng",1);
        set("combat_exp", 1200000);
        set("score", 20000);

        set_skill("force", 120); // 基本内功
        set_skill("huntian-qigong", 120); // 混天气功
        set_skill("strike", 115);
        set_skill("xianglong-zhang", 110); // 降龙十八掌
        set_skill("dodge", 125); // 基本躲闪
        set_skill("xiaoyaoyou", 115); // 逍遥游
        set_skill("parry", 120); // 基本招架
        set_skill("staff", 120); // 基本棍杖

        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");

        prepare_skill("strike", "xianglong-zhang");
        set("inquiry", ([
        "quest":   (: ask_quest() :),
        "cancelquest":   (: ask_cancel() :),
                "例钱" : (: ask_silver :),
                "job" : (: ask_job :),
                "任务" : (: ask_job :),
                "fail" : (: ask_fail :),
                "失败" : (: ask_fail :),
      ]));

	set("silver_name", "例钱"); //例银的名称，默认为“例银”
        set("silver_factor", 0.5); //例银的数量因子，默认为1
        set("silver_family_skill", "xianglong-zhang"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "咱们丐帮虽然穷，对弟子还是有点福利的，以后你就找我领例钱吧。"); //第一次打听例银的时候说的话
        set("msg_silver_record", "$N转身取出一块小木板，刻下了点什么。\n"); //作记录时的描述\n
        set("msg_silver_check", "$N转身取出一块小木板，看了看。\n"); //检查记录时的描述\n
        set("msg_silver_mudage", "你当咱们丐帮是开造币场的不成？这个月的例钱你已经领过了！"); //时间未到不能领取时说的话
        set("msg_silver_paid", "拿去吧，这是你的例钱。记得要多行义举，将丐帮发扬光大。"); //领取成功时说的话
        set("msg_silver_score", "$N对着$n哈哈大笑道：「不错，最近你为丐帮出力甚多。」\n"); //由于提升师门忠诚而领取例银时的描述\n
        set("msg_silver_skill", "$N对着$n哈哈大笑道：「想不到你的降龙十八掌越来越有一套了。」\n"); //由于提升师门武功而领取例银时的描述\n
        set("msg_silver_exp", "$N对着$n哈哈大笑道：「看来你的武功长进不小啊。」\n"); //由于提升经验而领取例银时的描述\n
        set("msg_silver_none", "大伙或者为帮中出力，或者苦练功夫，你倒是做什么去了？"); //领取例银条件均不满足时说的话

        create_family("丐帮", 18, "九袋长老");
        set("shen_type",1);set("score",1000);setup();
		carry_object("/d/gaibang/obj/jing_cloth")->wear();
}

void attempt_apprentice(object ob)
{
        command("say 老夫不收徒弟，" + RANK_D->query_respect(ob) + "还是请回吧。
");
}

void init()
{
    add_action("do_answer","answer");
}

int ask_job()
{
    object me=this_player();
    object ob=this_object();
    object tasks,target,where,thing;
    mapping new_task=ZQUEST_D->get_quest();
    string targetfile,rm,item_name,item_id;
    int times=0,n=random(100);
    int pin=1+random(10000);
    string *color=({HIR,RED,HIW,WHT,MAG,HIM,HIC,CYN,HIB,BLU,HIG,GRN,HIY,YEL});
    
    string *desc2=({"素有善名","铺路修桥","名声尚好","慈悲心肠","济世活人"});
    
    if (me->query("family/family_name")!="丐帮")
    {
        command("say 阁下不是我帮弟子，这是何意？");
        return 1;
    }
    if (!me->query("is_beggar2"))
    {
        command("say 你不是净衣派弟子，去看看鲁长老有没有活吧。");
        return 1;
    }
    if (me->is_busy()||me->is_fighting())
    {
        command("say 等你忙完再来找我吧。");
        return 1;
    }
    if (me->query_temp("gb_newbie_finish"))
    {
        command("say 你打探到的消息还没有回复(answer)我呢。");
        return 1;
    }
    if (me->query("gbnewbiejob/start"))
    {
        command("say 你上次任务还没有完成呢！");
        return 1;
    }
    if (time()-me->query("gbnewbiejob/lasttime")<120)
    {
        command("say 你刚刚做过任务，先去休息一会吧。");
        return 1;
    }
    else
    {
        if ((int)me->query("gbnewbiejob/times")%2==0)
        {
            extra_job(me,0);
            return 1;
        }
        while (!find_living(new_task["id"])||time()-(int)find_living(new_task["id"])->query("questtime")<900||
            (find_living(new_task["id"])&&environment(find_living(new_task["id"]))&&base_name(environment(find_living(new_task["id"])))!=find_living(new_task["id"])->query("startroom")))
        {
            times+=1;
            if (times>10)
            {
                command("say 我略感不适，你片刻之后再来吧。");
                return 1;
            }
            new_task=ZQUEST_D->get_quest();
        }
        target=find_living(new_task["id"]);
        where=environment(target);
        if (!where||TASK_D->place_belong(where)=="未知区域"||TASK_D->place_belong(where)=="不明区域")
        {
            me->delete("gbnewbiejob/start");
            me->delete_temp("gbnewbiejob");
            command("say 我暂时没什么事，你迟点再来吧。");
            return 1;
        }
        me->set_temp("gbnewbiejob/pin",pin);
        me->set("gbnewbiejob/start","beg");
        me->set("gbnewbiejob/lasttime",time());
        me->set_temp("gbnewbiejob/beg",1);
        me->set_temp("gbnewbiejob/accept_msg",new_task["accept_msg"]);
        me->set_temp("gbnewbiejob/refuse_msg",new_task["refuse_msg"]);
        me->set_temp("gbnewbiejob/people",target->query("name"));
        me->set_temp("gbnewbiejob/target",target);
        n=random(sizeof(color));
        thing=new(__DIR__"newbie_job/item");
        item_name=color[n]+new_task["item"]+NOR;
        item_id=new_task["item_id"];
        thing->set_name(item_name,({item_id,}));
        thing->set("long",new_task["item_desc"]);
        thing->set("begby",0);
        thing->set("pin",pin);
        thing->move(target);
        target->set("questtime",time());
        me->set_temp("gbnewbiejob/item",thing->query("name"));
        me->set_temp("gbnewbiejob/theitem",thing);
        
        message_vision("$N对$n说道："+target->query("name")+"在"+TASK_D->place_belong(where)+desc2[random(sizeof(desc2))]+"，你去把其身上的"+color[n]+thing->query("name")+NOR+"("+thing->query("id")+")讨(beg)来，上缴(jiao)帮里。\n",ob,me);
        return 1;
    }
}



int ask_fail()
{
    object me=this_player();
    object ob=this_object();
    
    if (me->query("family/family_name")!="丐帮")
    {
        command("say 阁下不是我帮弟子，这是何意？");
        return 1;
    }
    if (me->is_busy()||me->is_fighting())
    {
        command("say 等你忙完再来找我吧。");
        return 1;
    }
    if (!me->query("gbnewbiejob/start"))
    {
        command("say 你没接过任务啊！");
        return 1;
    }
    me->delete("gbnewbiejob/start");
    me->delete_temp("gbnewbiejob");
    command("say 没关系，没做到就算了吧。");
    punish(me);
    return 1;
}

