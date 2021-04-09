//wang.c
//made by hacky
//王重阳
#include <ansi.h>
inherit NPC;
void consider();
void heal();
void create()
{
	int err;
	set_name("孤竹无名",({"chapion"}));
	set("nickname",HIR"无情剑"NOR+"——"+HIC+"剑无情人有情"+NOR);
	set("long",@LONG
他是全真派开山祖师王重阳的得意弟子。
他仗剑闯荡江湖几十载，鲜有败绩。
而今他虽归隐于《无情居》中，但一身武艺并未荒废。
等闲人切莫轻易上前试招。
LONG
		);
    set("title",HIY"消遥真人"NOR);
    set("gender","男性");
    set("age",37);
    set("attitude","friendly");
    set("shen_type",1);
    set("str",30);
    set("int",30);
    set("con",30);
	set("per",100);
    set("dex",30);
    set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: consider() :)
	}) );
    set("chat_chance",100);
    set("chat_msg",({
		(:heal:),
    }));
    set("max_qi",5000);
    set("max_jing",5000);
	set("max_neili",6000);
	set("neili",12000);
    set("jiali",110);
    set("combat_exp",21000000);
	
    set_skill("parry"			,	400);
    set_skill("dodge"			,	500);
    set_skill("hand"			,	400);
	set_skill("finger"			,	400);
	set_skill("blade"			,	400);
	set_skill("force"			,	400);
	set_skill("sword"			,	400);
	set_skill("iron-cloth"		,	400);
	set_skill("literate"		,	420);
	
	set_skill("taiji-jian"		,	400);
	set_skill("datengnuo-bufa"	,	500);
	set_skill("fuxue-shou"		,	400);
	set_skill("tanzhi-shengong"	,	400);
	set_skill("xiake-daofa"		,	400);
	set_skill("xiantian-gong"	,	400);
	set_skill("xiake-jianfa"	,	400);
	set_skill("quanzhen-jian"	,	400);
	set_skill("tonggui-jian"	,	525);
	set_skill("qixing-array"	,	400);
	set_skill("yiyang-zhi"		,	400);
	set_skill("xiake-jianfa"	,	400);
    
    map_skill("force"	,	"xiantian-gong");
    map_skill("dodge"	,	"datengnuo-bufa");
    map_skill("finger"	,	"tanzhi-shengong");
    map_skill("sword"	,	"xiake-jianfa");
    map_skill("parry"	,	"taiji-jian");
	map_skill("blade"	,	"xiake-daofa");
    prepare_skill("finger"	,	"tanzhi-shengong");
	prepare_skill("hand"	,	"fuxue-shou");
	prepare_wskill("blade"	,	"xiake-daofa");
	prepare_wskill("sword"	,	"xiake-jianfa");
	set("inquiry", ([
		]));
	
	
    setup();
    create_family("全真派",2,"天仙");
    set("class","taoist");
	
    carry_object(__DIR__"obj/chapion1")->wear();
	carry_object(__DIR__"obj/chapion2")->wear();
	carry_object(__DIR__"obj/chapion3")->wear();
	carry_object(__DIR__"obj/chapion4")->wear();
	carry_object(__DIR__"obj/chapion5")->wear();
	carry_object(__DIR__"obj/chapion6")->wear();
	carry_object(__DIR__"obj/chapion7")->wear();
	carry_object(__DIR__"obj/chapion8")->wear();
	carry_object(__DIR__"obj/chapion9")->wear();
    carry_object(__DIR__"obj/guihunjian.c")->wield();
	carry_object(__DIR__"obj/guihundao.c")->wield();
    
}
void consider()
{
	object *enemy,target;
	enemy = query_enemy() - ({ 0 });
	this_object()->set("neili",10000);
	target = enemy[random(sizeof(enemy))];
	switch( random(6) )
	{
	case 0:
		command("perform hand.fuxue " + target->query("id"));
		break;
	case 1:
		command("unwield jian");
		command("enable parry yiyang-zhi");
		command("perform parry.qiankun-yizhi " +target->query("id"));
		command("enable parry tonggui-jian");
		command("wield jian");
		break;
	case 2:
		command("enable parry taiji-jian");
		command("perform parry.chan");
		command("enable parry tonggui-jian");
		break;
	case 3:
		command("enable parry quanzhen-jian");
		command("perform parry.sanqing");
		command("enable parry tonggui-jian");
		break;
	case 4:
		command("enable parry quanzhen-jian");
		command("perform parry.tonggui");
		command("enable parry tonggui-jian");
		break;
	case 5:
		command("perform parry.qixing");
		break;
	}
}
void heal()                                             
{                                                       
	object ob=this_player();                        
	
	if (ob->query("eff_qi") < ob->query("max_qi"))  
	{                                               
		command("exert heal");                  
		command("enforce 30");                 
		return;                                 
	}                                               
	
	if (ob->query("qi") < ob->query("eff_qi"))      
	{                                               
		command("exert recover");               
		return;                                 
	}                                               
	
	if (ob->query("jing") < ob->query("eff_jing"))  
	{	command("exert regenerate");            
	
	return;
	}                                         
}                                                       
