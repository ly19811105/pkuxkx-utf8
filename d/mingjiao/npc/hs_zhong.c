#include <ansi.h>
inherit NPC;
void create()
{
        set_name(BLU"洪水旗众"NOR, ({ "qi zhong","zhong" }));
        set("long",
                "他是明教洪水旗的旗众。\n"
                "他身穿黄衣，脸露狞笑，一付凶神恶煞的样子\n");
        set("gender", "男性");
        set("age", 36);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 16);
        set("int", 16);
        set("con", 20);
        set("dex", 22);
        set("max_qi", 400);
        set("max_jing", 150);
        set("neili", 300);
        set("max_neili", 200);
        set("jiali", 5);
        set("combat_exp", 4800);
        set_skill("force", 42);
        set_skill("dodge", 42);
        set_skill("unarmed",42);
        set_skill("parry", 42);
        create_family("明教",22,"教徒");
        setup();
/*        set("chat_chance", 2);
        set("chat_msg", ({
"明教洪水旗旗众唱到:“ 焚我残躯，烈烈圣火，生亦何欢,死亦何苦！！”。\n",
        }) );
*/
     carry_object("/d/mingjiao/obj/lanyi.c")->wear();
}
