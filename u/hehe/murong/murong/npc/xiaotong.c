//xiaotong.c
//by hehe
//2003.3.13

inherit NPC;
void create()
{
	set_name("小童", ({ "xiao tong", "tong" }));
    set("gender", "男性");
    set("age", 14);
	set("str", 15);
    set("int", 26);
    set("con", 26);
    set("dex", 26);
    set("combat_exp", 100);
    set("shen_type", 0);
    set("attitude", "peaceful");
	set("max_qi",400);
    set("max_jing",1000);

    set_temp("apply/attack", 10);
    set_temp("apply/defense", 10);

    setup();
	carry_object(__DIR__"obj/shoes1")->wear();
    carry_object(__DIR__"obj/cloth")->wear(); 
}
