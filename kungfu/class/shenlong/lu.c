// lu.c
#include <ansi.h>
#include <title.h>
inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
inherit "/inherit/char/silver.c";
string ask_me_wan1();
string ask_daggerbook();

void create()
{
	set_name("陆高轩", ({ "lu gaoxuan", "lu" ,"gaoxuan"}));
	set("title", HIY"神龙教"NOR"军师");
	set("nickname",HIC "神机妙算" NOR);
        set("count1", 1);
        set("book_count", 1);
	set("long", "他天庭饱满,地阔方圆,容貌颇为英俊.\n然而满面愁容,恰似顷刻间便有杀身之祸一般.\n" );
	set("gender", "男性");
	set("age", 37);
	set("str", 35);
	set("dex", 20);
	set("max_qi",1500);
        set("qi",1500);
	set("max_jing",500);
        set("jing",500);
	set("combat_exp", 300000);
	set("score", 40000);
	set("shen_type", -1);
	set("attitude", "peaceful");

        set_skill("force", 120);
	set_skill("poison", 150);
        set_skill("zhaosheshu", 100);
        set_skill("yangsheshu", 100);
        set_skill("flatter", 120);
        set_skill("strike", 120);
        set_skill("whip", 120);
        set_skill("parry", 120);
        set_skill("dodge", 120);
        set_skill("yixingbu", 120);
        set_skill("shenlong-bian", 120);
        set_skill("huagu-mianzhang", 120);
        set_skill("shenlong-xinfa", 120);
        set_skill("literate", 280);
        map_skill("dodge", "yixingbu");
        map_skill("force", "shenlong-xinfa");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shenlong-bian");
        map_skill("dodge", "yixingbu");
        map_skill("whip", "shenlong-bian");
        prepare_skill("strike", "huagu-mianzhang");

	create_family("神龙教",2,"弟子");

	set_temp("apply/damage", 60);
	set("neili", 1000); 
	set("max_neili", 1000);
	set("jiali", 100);
        set("inquiry", ([
		"神龙教" :  "一般人是入不了我神龙教的(join shenlongjiao).\n",
		"入教" :  "一般人是入不了我神龙教的(join shenlongjiao).\n",
		"洪安通" :  "教主脾气不好,要讨他欢心才好。\n",
		"教主" :  "教主脾气不好,要讨他欢心才好。\n",
		"口号" : "万年不老!永享仙福!寿与天齐!文武仁圣!\n",
                  "升天丸" : (: ask_me_wan1 :),
                  "秘籍" : (: ask_daggerbook :),
		"例银" : (: ask_silver :),
	]) );
        set("silver_factor", 1.4); //例银的数量因子，默认为1
        set("silver_family_skill", "force"); //门派武功，提升此武功时可以领取例银，默认为parry

	setup();
	carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changbian")->wield();
	add_money("silver", 10);
}

void init()
{
}

void attempt_apprentice(object ob)
{
        if (ob->query("party/party_name") != MAG "神龙教" NOR ) {
		command("say 你不是本教教众, 想来找死啊!");
		return;
	}
        if (ob->query("family/master_name") == "洪安通" || ob->query("family/master_id")=="hong antong") {
                command("say 不敢！有教主做您师傅还不够吗？");
                return;
        }
    if ((int)ob->query("repute") < 10000 ) {

        command("say 你在江湖上还没有混出什么名堂，我怎么能收你做我的弟子？");
        return;
    } 

    if ((int)ob->query("score") < 500 ) {
        command("say 你对本门的贡献太小了。");
        return;
    } 

        if ((int)ob->query_skill("shenlong-xinfa",1) < 50 ) {
                command("say 你的神龙心法太低了,还是努努力先提高一下吧!");
                return;
        }

	if ((int)ob->query_skill("literate",1) < 40 ) {
		command("say 你的学问太低了,还是努努力先提高一下吧!");
		return;
	}
	if ((int)ob->query("shen") > -0  ) {
		command("say 我神龙教与世隔绝，向来不与您这种白道人物打交道，您请回吧！");
		return;
	}
	command("say 很好，很好。");
	command("recruit " + ob->query("id"));
        ob->set("title",ob->query("party/party_name")+CYN"护法"NOR);
//title系统记录玩家title by seagate@pkuxkx
	      ob->set_title(TITLE_RANK, ob->query("title"));
}
string ask_me_wan1()
{
        mapping fam; 
        object ob;
        
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "神龙教")
                return RANK_D->query_respect(this_player()) + 
                "与本教素无来往，不知此话从何谈起？";
        if (this_player()->query("score")<500)
                                return RANK_D->query_respect(this_player()) + 
                "对本教并没有什么贡献，灵药不能给你。";
        if (query("count1") < 1)
                return "升天丸已经给完了。";
        add("count1", -1);
  ob = new("/d/shenlongdao/obj/shengtianwan");
        ob->move(this_player());
        command("rumor "+this_player()->query("name")+"拿到了一颗"+ob->query("name")+"啦！\n");
        return "好吧，这颗「"+ob->query("name")+"」你拿回去吧，不到关键时刻切勿乱用！";
}
string ask_daggerbook()
{
        mapping fam; 
        object ob;
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "神龙教")
                return RANK_D->query_respect(this_player()) + 
                "与本教素无来往，不知此话从何谈起？";
        if (this_player()->query("score")<500)
                return RANK_D->query_respect(this_player()) + 
                "对本教并没有什么贡献，秘籍不能给你。";
        if (query("book_count") < 1)
                return "秘籍被人拿走了！";
        add("book_count", -1);
        ob = new("/d/shenlongdao/obj/dagger-book");
        ob->move(this_player());
        command("rumor "+this_player()->query("name")+"拿到了一本"+ob->query("name")+"啦！\n");
        return "好吧，这本「"+ob->query("name")+"」你拿回去好好钻研吧，千万不要给别人哦！";
}
