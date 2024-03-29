// xie.c
// modified by iszt@pkuxkx, 2007-01-26

#include <ansi.h>

inherit NPC;

string ask_me();
void heal();

void create()
{
        set_name(HIY"谢逊"NOR, ({ "xie xun","xie" }));
        set("long","他就是号称金毛狮王的谢逊。他身材魁伟异常，满头黄发，散披肩头，
眼睛碧油油的发光。在洞前这么一站，威风凛凛，真如天神天将一般。\n");
        set("age", 40);
        set_weight( 5000000);
        set("combat_exp", 90000000);
        set("bellicosity", 0);
        set("title",YEL"金毛"NOR+BLU"狮王"NOR);
        set("gender","男性");
        set("attitude","peaceful");
        add_money("gold",2);
        set("str", 40);
        set("dex", 40);
        set("con", 40);
        set("int", 60);
        set_skill("literate", 300);
        set_skill("blade", 900);
        set_skill("unarmed", 900);
        set_skill("parry", 900);
        set_skill("force", 900);
        set_skill("dodge", 900);
        set_skill("jiuyang-shengong",900);
        set_skill("datengnuo-bufa", 900);
        set_skill("qishang-quan", 900);
        set_skill("cuff", 900);
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "datengnuo-bufa");
        map_skill("parry", "qishang-quan");
        map_skill("cuff", "qishang-quan");
        prepare_skill("cuff", "qishang-quan");
        set("max_jingli",4000);
        set("max_qi", 5000);
        set("jingli",3860);
        set("jiali",200);
        set("max_neili",7000);
        set("neili",7000);
        set("eff_jing",3860);
        set("jing",3860);
        set("eff_qi",5000);
        set("qi",5000);
        set("chat_chance", 100);
        set("chat_chance", 5);
        set("chat_msg", ({
                "谢逊叹了口气道：“唉……我怎么参悟不出这宝刀的秘密呢……”\n",
                "谢逊喃喃道：“无忌孩儿如能回归中土，我死而无憾。”\n",
                "谢逊说道：“七伤拳虽然霸道，但于自己身体不利。”\n",
        }));
        set("inquiry", ([
                "屠龙刀" : (: ask_me :),
                "张无忌" : "他是我的义子，我最喜欢这小家伙了。\n",
                "张翠山" : "我这兄弟人是不错，就是迂腐了一点儿。\n",
                "殷素素" : "她和我义弟真是一对璧人，言行处世深合我心。\n",
        ]) );
        set("dao_count", random(3));
        set("shen_type",1);set("score",100000);setup();
        carry_object("/clone/armor/cloth")->wear();
}
int accept_object(object who,object ob)
{

        object me=this_player();
        if ((string)ob->query("id") != "kao lurou" && (string)ob->query("id") != "mu pai" )
        {
                command("say 想拿" + (string)ob->query("name") + "来唬老子？！");
                command("heng");
                return 0;
        }
        else
        {
                if ((string)ob->query("name") == "烤鹿肉" )
                {
                        command("say 唔，好久没吃过如此美味了，好吧，准你进去！");
                //      command("eat rou");
                        command("taste");
                        me->set_temp("marks/hole",1);
                }
                if ((string)ob->query("name") == "木排" )
                {
                        command("wa");
                        command("say 我的无忌孩儿可以回中土了！");
                        me->set("marks/mupai",1);
						if (!query("dao_count"))
							add("dao_count", 1);
                }
        return 1;
        }
}

string ask_me()
{
        object me = this_player();
        object ob;
        if ((int)me->query_skill("qishang-quan", 1) < 400)
                return "原来你也是一心窥视我宝刀之人！哼！";
        if (query("dao_count") < 1)
                return "你来晚了，屠龙宝刀已经送与有缘人。";
        add("dao_count", -1);
        ob = new(__DIR__"obj/tulong-dao");
        ob->move(me);
        me->set("bh/yj",1);
        CHANNEL_D->do_channel(this_object(), "rumor", "听说屠龙宝刀落入了"+me->name()+"之手！");
        return RANK_D->query_respect(this_player()) +
                "天资聪颖，已得我七伤拳真传，想必能参出屠龙刀中秘密，就交与你保管吧!";
}

void heal()
{
        object ob=this_object();
        if (ob->query("eff_qi") < ob->query("max_qi"))
        {
                command("exert heal");
                command("enforce 200");
                return;
        }
        if (ob->query("qi") < ob->query("eff_qi"))
        {
                command("exert recover");
                return;
        }
        if (ob->query("jing") < ob->query("eff_jing"))
                command("exert regenerate");
        return;
}
