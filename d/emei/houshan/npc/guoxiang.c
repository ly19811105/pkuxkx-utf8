#include <ansi.h>

inherit NPC;
void consider();
void create()
{
        set_name("郭襄", ({ "guo xiang", "guo","xiang"}));
        set("long", "这便是传说中的峨嵋派开山祖师郭襄。
她肤色白皙，眉目如画，依稀可见当年的秀丽容色。\n
她本是义守襄阳的[北侠]郭靖之女，为人古道热肠，行事不拘小节，
深得桃花岛主潇洒自由之风范，江湖人称“小东邪”。少年时曾因痴恋
携妻隐居的[神雕大侠]杨过而浪迹江湖苦寻十数年。直至襄阳城破郭
大侠殉国后，方始大彻大悟，于四十岁上创立了峨嵋一派。郭女侠一
生际遇繁多，武功亦博采儒、释、道诸家所长，与少林、武当关系深
远，手中所持倚天神剑更是来历非凡。");
        set("title",HIC"峨眉派祖师");
        set("nickname",HIY"小东邪"NOR);
        set("gender", "女性");
        set("age", 40);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 50);
        set("max_qi", 18000);
        set("qi",18000);
        set("max_jing", 18000);
        set("jing",18000);
        set("neili", 18000);
        set("max_neili", 18000);
        set("max_jingli",18000);
        set("jingli",18000);
        set("jiali", 500);
        set("combat_exp", 200000000);

        set("attitude", "peaceful");
        set("shen_type", 1);
        
        set("sword",1);
        set_skill("force", 800);
        set_skill("linji-zhuang", 850);
        set_skill("dodge", 800);
        set_skill("zhutian", 800);
        set_skill("tiangang-zhi", 880);
        set_skill("finger", 880);
        set_skill("jinding-mianzhang",860);
        set_skill("strike",880);
        set_skill("fuliu-jian",850);
        set_skill("sword",800);
        set_skill("yanxing-dao",850);
        set_skill("blade",800);
        set_skill("throwing",800);
        set_skill("pili-dan",850);
        set_skill("parry", 800);
        set_skill("mahayana", 850);
        set_skill("literate", 800);
        map_skill("force", "linji-zhuang");
        map_skill("dodge", "zhutian");
        map_skill("finger", "tiangang-zhi");
        map_skill("parry", "fuliu-jian");
        map_skill("blade", "yanxing-dao");
        map_skill("sword", "fuliu-jian");
        map_skill("strike", "jinding-mianzhang");
        map_skill("throwing", "pili-dan"); 
        prepare_skill("throwing", "pili-dan");

        set("chat_chance",5);
        set("chat_msg", ({
        	"郭襄不知想着什么出神，忽地惊醒，微微笑道：“"+HIY"一念愚即般若绝,一念智即般若生.般若无形相,智慧心即是.此言果真不假。"+NOR"”  \n",
        	"郭襄望着窗外的寒梅，喃喃道：“"+HIY"又是十月廿四啦，……他……他可还会来么？"+NOR"”\n",
        	"郭襄脸上露出喜乐神色，道：“"+HIY"我盼望爹爹妈妈率领人马,会同众位英雄好汉,把来犯的蒙古兵尽数杀退,襄阳城百姓得保太平。"+NOR"”
又叹了口气道：“"+HIY"那……那也是十几年前的事啦。”"+NOR"\n",
          "郭襄面对着一束高山杜鹃虚捏起拇、食二指，痴痴道：“"+HIY"杨大哥，如果我这第三个愿望是要一生一世陪在你身边，你会同意么？"+NOR"” 
言罢缓缓流下两行清泪。\n",
          "郭襄阖上双目喃喃地说道：“"+HIY"爹，娘，外公，姐姐，姐夫，破虏，你们都在哪里？山上又下雪了，……好冷啊。"+NOR"”\n",
          "郭襄一弹剑鞘，缓缓吟道：“"+HIY"独臂挽神雕，重剑斩英豪，屠龙千山外，倚天上九霄。"+NOR"”\n",
          "郭襄叹了口气，幽幽念道：“"+HIY"非是情断恩义尽，缘何终南古墓空？杨大哥，其实我只是想见见你而已啊。"+NOR"”\n",
        	}));
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
		       (: perform_action, "finger.lingkong" :),
		       (: perform_action, "sword.miejian" :),
		       (: perform_action, "sword.miejian" :),
		       (: perform_action, "sword.fuliu" :),
		       (: exert_function, "powerup" :),  
		       (: perform_action, "throwing.tan" :),    	
		       (: consider :),
        }) );
        
        set("inquiry", ([
                "杨过"   : "我也在找他。",
                "郭靖"   : "北侠郭靖便是我的父亲。",
                "黄蓉"   : "她是我的妈妈，可是她最疼爱我的姐姐。",
                "郭芙"   : "她是我的姐姐，可是她砍断了杨大哥的手臂，我很不喜欢她。"	 	
                ]));
        
        create_family("峨嵋派", 1, "掌门");
        setup();
        carry_object("/d/emei/houshan/npc/obj/changjian")->wield();
        carry_object("/d/emei/houshan/npc/obj/gangdao");
        carry_object("/d/emei/houshan/npc/obj/cloth")->wear();
}
void attempt_apprentice(object ob)
{
	      command("say 我已经不收徒了，你去找灭绝吧。");
	      return;
}
void unconcious()                                                                                 
{                                                                                                 
        die();                                                                                    
}                                                                                                 
                                                                                                  
void die()                                                                                        
{                                                                                                 
        object xiang=this_object();                                                                 
        message("vision","郭襄拱了拱手，道：我不喜和人打斗，你我就此罢手吧。言毕跳出战圈不打了。\n",environment(xiang));
        xiang->remove_all_killer();                                                                 
        xiang->remove_all_enemy();                                                                  
        xiang->set("eff_qi",xiang->query("max_qi"));                                                  
        xiang->set("qi",xiang->query("max_qi"));                                                      
        xiang->set("eff_jing",xiang->query("max_jing"));                                              
        xiang->set("jing",xiang->query("max_jing"));                                                  
        xiang->set("neili",xiang->query("max_neili"));                                                
        return;                                                                                   
}  
void consider()
{
	      object obj;
		    obj = new("/d/emei/houshan/npc/obj/pilidan.c");
		    obj->move(this_object());
		    obj = new("/d/emei/houshan/npc/obj/pilidan.c");
		    obj->move(this_object());
		    command("perform throwing.tan");   	      
}
