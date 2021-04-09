// Modified by iszt@pkuxkx, 2007-04-04

#include <ansi.h>
#include <title.h>
inherit NPC;
string *clear_npc=({
            "/d/xytaskd/guojing.c",
            "/d/xytaskd/mgbn1.c",
            "/d/xytaskd/mgbn2.c",
            "/d/xytaskd/mgbs1.c",
            "/d/xytaskd/mgbs2.c",
            "/d/xytaskd/mgbw1.c",
            "/d/xytaskd/mgbw2.c",
            "/d/xytaskd/mgbe1.c",
            "/d/xytaskd/mgbe2.c",
            "/d/xytaskd/mgqbn1.c",
            "/d/xytaskd/mgqbn2.c",
            "/d/xytaskd/mgqbs1.c",
            "/d/xytaskd/mgqbs2.c",
            "/d/xytaskd/mgqbw1.c",
            "/d/xytaskd/mgqbw2.c",
            "/d/xytaskd/mgqbe1.c",
            "/d/xytaskd/mgqbe2.c",
            "/d/xytaskd/qianhuzhangn.c",
            "/d/xytaskd/qianhuzhangs.c",
            "/d/xytaskd/qianhuzhangw.c",
            "/d/xytaskd/qianhuzhange.c",
            "/d/xytaskd/cheatern1.c",
            "/d/xytaskd/cheatern2.c",
            "/d/xytaskd/cheaters1.c",
            "/d/xytaskd/cheaters2.c",
            "/d/xytaskd/cheaterw1.c",
            "/d/xytaskd/cheaterw2.c",
            "/d/xytaskd/cheatere1.c",
            "/d/xytaskd/cheatere2.c",
            "/d/xytaskd/shoujun.c",
});
string ask_for_baoguo();
string ask_for_citan();
string ask_for_huang();
int ask_quest();
void create()  
{
object *taskguojing_list=({}),guojing;
/*
taskguojing_list=children("/d/xytaskd/guojing.c");
for(int j=0;j<sizeof(taskguojing_list);j++)
{
guojing=taskguojing_list[j];
if(guojing)
{
set_name("襄阳守军",({"shou jun","jun"}));
        set("gender", "男性");
        set("age", 22);
        set("str", 20);
        set("dex", 20);
        set("long", "襄阳的普通守军。\n");
        set("combat_exp", 20000);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_skill("unarmed", 50);
        set("max_qi", 1000); 
        set("max_jing", 1000); 
        setup();
        carry_object(__DIR__"obj/tiejia")->wear();
       return;
}
}
*/
        set_name(RED "郭靖" NOR, ({ "guo jing","jing","guo" }));
        set("nickname", GRN"威震中原 名贯漠北"NOR);
        set("id", "guo jing");
        set("title",YEL"北侠"NOR);
        set("gender", "男性");
        set("age", 40);
        set("str", 30);
        set("dex", 60);
        set("long", "这就是一代大侠郭靖。\n");
        set("combat_exp", 1800000);
        set("shen_type",1);
        set("attitude", "peaceful");
        set_skill("strike", 220);
        set_skill("force", 200);
        set_skill("xianglong-zhang", 250);
        set_skill("xiaoyaoyou", 300);        // 逍遥游
        set_skill("huntian-qigong", 300);    // 混天气功

        set_skill("dodge", 200);
        set_skill("parry", 300);                

        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("parry", "xianglong-zhang"); 
        map_skill("dodge", "xiaoyaoyou");
        prepare_skill("strike", "xianglong-zhang");
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 30);

        set("neili", 4000); 
        set("qi", 6000); 
        set("max_qi", 6000); 
        set("max_neili", 4000);
        set("jingli", 4000); 
        set("max_jingli", 4000);

        set("inquiry",([ 
                "黄蓉"  : (: ask_for_huang :),
                "报国"  : (: ask_for_baoguo :),
                "刺探军情"  : (: ask_for_citan :),
                "精忠报国"  : (: ask_for_baoguo :),
                "从军"  : (: ask_quest :),
                "congjun"  : (: ask_quest :),
        ]));
        set("chat_chance",1);
        set("chat_msg", ({
                "郭靖叹道：「恩师云游四方，多年不见，也不知他老人家现在如何。」\n",
                "郭靖说着深深的叹了一口气。\n",
                "郭靖叹道：「蒙古大军虽然撤兵，但总有一天要卷土重来，亡国之日不远矣。」\n",
                "现在襄阳兵丁虽多，民众也团结，奈何兵器盔甲大大不足.\n",
                "郭靖自言自语道：「该想个釜底抽薪的办法才好。」\n"
        }) );

        setup();
        carry_object(__DIR__"obj/tiejia")->wear();
        for(int k=0;k<sizeof(clear_npc);k++)
        {
                taskguojing_list=children(clear_npc[k]);
                for(int j=0;j<sizeof(taskguojing_list);j++)
                        destruct(taskguojing_list[j]);
        }
}

int ask_quest()
{
    object me=this_player();
    object ob=this_object();
    
    if (me->query("statistics/newbie_target/guo_finish"))
    {
        command("say 你既已投军，多多为国效力吧。");
        return 1;
    }
    if (me->query("statistics/newbie_target/wg_suo_degree")>250)
    {
        me->delete("statistics/newbie_target/wg_suo_degree");
        me->set("statistics/newbie_target/guo_finish",1);
        message_vision("$n道：好吧，既然你达到了我的要求，那就为国效力吧。\n",me,ob);
        me->delete_temp("wg");
        me->add("combat_exp",5000);
        CHANNEL_D->do_channel(ob, "rw", HIC + me->query("name")+HIC+"完成了襄阳从军的任务。");
        tell_object(me,HIC+"完成襄阳从军的Quest，你获得了五千点经验！\n"+NOR);
        if (me->query("combat_exp")<200000&&!random(5))
        {
            me->set("statistics/newbie_target/gift_reward","str");
        }
        me->set("title",HIW+"侠之大者"+NOR);
        me->set_title(({TITLE_QUEST1,TITLE_QUEST2,TITLE_QUEST3,TITLE_QUEST4,TITLE_QUEST5,TITLE_QUEST6,TITLE_QUEST7,TITLE_QUEST8,TITLE_QUEST9,TITLE_QUEST10}), HIW+"侠之大者"+NOR);
        tell_object(me,HIW+"你获得了『侠之大者』的称号！\n"+NOR);
        return 1;
    }
    if (me->query_temp("wg/start")||me->query_temp("wg/permit"))
    {
        command("say 你的程度还不够啊，再去练练。");
        return 1;
    }
    if (me->query("statistics/newbie_target/selected")!=1)
    {
        command("say 现在满员了，多谢你的好意！");
        return 1;
    }
    me->set_temp("wg/start",1);
    command("say 军中壮士需要强壮的体力，你去东街的武馆练练石锁，到达一定程度再来找我吧。");
    return 1;
}

void init()
{
        object ob=this_player();
        ::init();
        if(this_player()->query_temp("killed")) 
                call_out("kill_ob",1,this_player());
//        add_action("do_kill","kill");
}

string ask_for_huang()
{
        return "蓉儿自蒙古兵退后，回桃花岛看望爹爹去了。如此民族危亡时刻，\n“
                ”我只想着精忠报国，于那儿女情长，也不十分挂怀了。\n";
}

string ask_for_citan()
{
        object me = this_player();
        me->set_temp("citan",1);
        message_vision(HIW"郭靖大喜：「既然$N有心报国，那就去蒙古大营刺探情报吧！」\n"NOR,me);
        tell_object(me,MAG"你装扮成蒙古人的模样，但是好像还差一件蒙古服装.....\n"NOR);
        return "快去快回！";
}

string ask_for_baoguo()
{
        object me,ob;
        me = this_player();
        if(!present("yao pai",this_player()))
                return "虽说国家兴亡匹夫有责，但寻常百姓还是好自为之，不要枉送性命。\n";
        if(!me->query_temp("shoujiang_asked"))
        {
                command("haha");
                command("heng");
                command("kill " + me->query("id"));
                return "你这腰牌是从那里来的？"; 
        }
        ob = new(__DIR__"obj/junling");
        ob->move(this_player());              
        command("say 蒙古骑兵锐不可当，要击败他们，必须釜底抽薪，擒贼先擒王。\n");
        command("say 我派你以送信为名，混入敌营，伺机刺杀蒙古皇帝，抢到他身上的兵符。\n");
        message_vision("郭靖给了$N一支大令。\n", me);
        me->set_temp("guojing", 1);  
        me->delete_temp("shoujiang_asked"); 
        return "国家兴亡，黎民生死，全仗英雄一人了！\n";
}

int accept_object(object me, object ob)
{
    int value;
        object book;
        if (ob->query("id")=="bing fu")
        {
                if (!me->query_temp("刺客") )
                {
                        command("say 大胆狂徒，竟敢欺瞒本帅，这兵符是从哪里仿造的？");
                        command("kill " + me->query("id"));
                        return 1;
                }
                else
                {
                        command("admire " + me->query("id"));
                        me->delete_temp("刺客"); 
                        me->delete_temp("杀"); 

                                if ((int)me->query("combat_exp")<=50000000 )
                                {
                        command("say 为国家为黎民出生入死，本帅不管送什么都无法表达我对" + RANK_D->query_respect(ob) + "的敬意。\n"
                                "这本书记载了我一生的造诣，也许英雄有点用处，请收下。\n");
                        book = new(__DIR__"obj/shediao");
                                }
                                else
                                {
                        command("say 我这里有一本金庸先生签过名的射雕英雄传，就送给你吧！");
                        book = new("/d/reborn/jinyong/obj/sdyxz");
                                }
                        book->move(this_player());
                        message_vision("郭靖给了$N一本" + YEL"射雕英雄传"NOR + "。\n", me);
                        call_out("destroy",1,ob);
                        return 1;
                }
        }
    //正道德任务，收兵器盔甲
    if(ob->is_equip() == 1 && !ob->query("no_give"))
    {
        value = load_object("/cmds/usr/donate")->calc_value(ob);
        
        //郭靖这里的道德比直接donate多一点点。
        value = value + value/10;

        command("say 感谢英雄资助襄阳兵械！");
        tell_object(me,"你的道德增加了"+chinese_number(value)+"点\n");
        me->add("shen",value);
        me->add_busy(2);        
        call_out("destroy",1,ob);
        return 1;
    }
}

int do_kill(string arg)
{
        object me = this_player();
        object ob = this_object();

        ob->kill_ob(me);
        me->kill_ob(ob);
        me->set_temp("killed",1);
        return 1;
}

void destroy(object ob)
{
     destruct(ob);
     return;
}

int unconcious()
{
    command("say 天不假年！可恨襄阳之围未解！\n");
    die();
}
