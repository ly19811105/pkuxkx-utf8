//鹿杖客
//by picewolf 2009-5-8
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("鹤笔翁", ({ "hebi weng", "hebi","weng" }));
		set("title",HIB"玄冥二老"NOR);
        set("long","他大约60多岁年纪，与鹿杖客共称”玄冥二老“，凭借玄冥神掌纵横江湖。\n");
        set("shen_type", 1);
        set("gender", "男性");
        set("age", 66);
		set("combat_exp", 600000000);
		 set("str", 60);
        set("int", 50);
        set("con", 50);
        set("dex", 50);

        set("max_qi", 28000);
        set("max_jing",28000);
        set("neili", 28000);
        set("max_neili", 28000);
        set("jiali", 350);
       
        set("score", 500000);
		set_skill("force", 1500);
        set_skill("jiuyin-zhengong", 1500);
        set_skill("xuanming-zhangfa", 1500);
        set_skill("dodge", 1500);
        set_skill("jiuyin-shenfa", 1500);
        set_skill("strike", 1500);  
        set_skill("parry",1500);
        

        map_skill("force","jiuyin-zhengong");
        map_skill("dodge","jiuyin-shenfa");
        map_skill("strike","xuanming-zhangfa");
        map_skill("parry","xuanming-zhangfa");
		set_temp("apply/armor", 500);
		set_temp("apply/damage", 400);
        prepare_skill("strike", "xuanming-zhangfa");
		set("inquiry",([
			"赵敏":"那是我们郡主，她现在在绿柳山庄。你问这做什么？",
			"赵明":"那是我们小王爷。",
			"番邦武士":"这些不成材的武士都是郡主训练的，略晓中原武功，还请阁下手下留情。",
			"闯塔":"阁下只要入塔，比武就开始了，所以还请准备妥当之后再行进入。每过一层阁下
便可用“jiangli”查看王府送的厚礼。闯的层数越多，礼物也就越多，如果失败身亡，王府
也为您准备了上好的柳州棺木。",
			"玄冥神掌":"哈哈，这可是我们的看家本领，若是阁下能闯的过塔，老夫指点一二，也未尝不可。",
			"阴谋":"阴谋？哪里有什么阴谋，阁下切不可轻信谣言，郡主发这个英雄帖，只不过想结交中原豪杰而已。",
			]));

        setup();
}


int accept_object(object who, object ob)
{
	int a;
	object obj;
	a=random(20);
    if (ob->query("id")=="tiansheng kulou")		
    {
		write("鹤笔翁惊诧道:“原来王府也有赝品，壮士稍等。”\n");
		if (a<17)
		{
			who->add("shen",10000);
			write(HIW"你的道德增加了。\n"NOR);
		}
		if (a>=17)
		{
			obj=new("/d/xiangyang/npc/obj/shanlw.c");
			obj->move(who);
			write(HIW"这颗灵药还请壮士收下，万望海涵。\n"NOR);
		}
		call_out("dest_kulou",5,ob);
		return 1;
    }
	else
	{
		write("阁下休得消遣老夫！！！\n");
	}
    return 0;
}

void dest_kulou(object ob)
{
	destruct(ob);
	return;
}