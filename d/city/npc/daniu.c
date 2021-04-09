// daniu.co.c
// by alanm
// 96-02-16 YZC disabled NPC killing, & "unknown" problem when revealed
#include <ansi.h>
inherit NPC;
string ask_me(object who);
void create()
{
        set_name("大妞", ({ "da niu", "niu" }) );
        set("title", "老师");
        set("gender", "女性" );
        set("shen_type", -1);
        set("age", 20);
        set("str", 25);
        set("cor", 25);
        set("cps", 25);
        set("int", 25);
        set("long",
                "这就是开放实验室的年轻女老师大妞，她用严厉的眼神看着你，
她的手里拿着刚刚没收的厚厚的一打机读卡。\n" )
;
        set("combat_exp", 20000);
        set("attitude", "heroism");
        set("chat_chance_combat", 15);
        set("chat_msg_combat", ({
                "大妞说道: 开放实验室不许玩游戏，难道你不知道？\n",
                "大妞忽然平平推出一掌，招数精奇，但掌到中途却又急忙收招。\n",
                "大妞说道: 快到门口划卡注销，我不和你过招....\n"
        }) );
        set("inquiry", ([
                "孟老师" : "哈哈哈! 有趣有趣，可惜你认错人了。" ,
                "MUD"   : (: ask_me :),
        ]) );
        set_skill("blade", 60);
        set_skill("dodge", 80);
        set_skill("unarmed", 30);
        set_skill("parry", 80);
        setup();
        carry_object(__DIR__"obj/ka");
        carry_object(__DIR__"obj/gangdao")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
}
string ask_me(object who)
{
        int i;
        object *ob;
        if( query("revealed") ) {
                if( is_killing(who->query("id")) ) return "你既然知道开放实验室的规矩，今日休
想活命
！\n";
                else {
                        kill_ob(who);
                        who->fight_ob(this_object());
                        return "说了不许玩MUD还玩，哼，去死吧！纳命来吧！
\n";
                }
        }
        if( (random(10) < 5) || is_fighting() )
                return "MUD就那么好玩？\n";
        set_temp("apply/attack",  60);
        set_temp("apply/defense", 60);
        set_temp("apply/damage",  20);
//      set("title", "杀手");
//      set("nickname", HIR "大妞" NOR);
        set("title", HIR "老师" NOR);
        message("vision",
                HIY "大妞眼中突然放出异样的光芒，颤声说道，看来...你还在玩MUD？\
n
"
                "大妞大喝一声，叫道，既然如此，本姑娘今天反正豁出去，跟你拼了。\
n"
                "大妞使开单刀，乱劈乱砸，沉猛狠辣，和刚才的老师简直判若两人。\n"
 NOR,
                environment(), this_object() );
        set("pursuer", 1);
        set("attitude", "aggressive");
        set("vendetta/authority", 1);
        set("chat_msg_combat", ({
                (: random_move :)
        }) );
        set("chat_chance", 15);
        set("chat_msg", ({
                (: random_move :)
        }) );
        set("bellicosity", 10000);
        set("combat_exp", 70000);
        ob = all_inventory(environment());
        for(i=sizeof(ob)-1; i>=0; i--) {
                if( !userp(ob[i]) ) continue;
                kill_ob(ob[i]);
                ob[i]->fight(this_object());
        }
//      carry_object("/d/city/obj/mianju.c");
        add_money("gold", 1);
        set("revealed", 1);
        return "我就是开放老师，开放老师就是这样子！纳命来吧！\n";
}
