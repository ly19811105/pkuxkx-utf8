// File         : family_npc.c
// Created By   : iszt@pkuxkx, 2007-03-28
// Edited By	: kiden@pkuxkx, 2007-03-30
// Special weapon: zhen for riyuejiao,hammer for dalunsi ,xiao for taohuadao, ling for mingjiao

inherit NPC; // to use perform_action

string* family_zheng = ({    //正派 8个
	"shaolin", "wudang", "emei", "gaibang", 
	"tianlong", "tiandihui", "huashan1", "quanzhen","huashan2",
});

string* family_xie = ({     //邪派 5个
	"xingxiu", "baituo", "shenlongjiao", "riyuejiao","dalunsi",
});

string* family_peace = ({  //中立 5个
	"taohua", "gumu", "lingjiu", "murong", "mingjiao" , "chaoting",
});

string* family_special = ({ //特殊 1个 
	"xiake", "pker",
});

int set_shaolin(object me, int level, int armed);
int set_wudang(object me, int level, int armed);
int set_gaibang(object me, int level, int armed);
int set_emei(object me, int level, int armed);
int set_quanzhen(object me, int level, int armed);
int set_huashan1(object me, int level, int armed);
int set_huashan2(object me, int level, int armed);
int set_tiandihui(object me, int level, int armed);
int set_tianlong(object me, int level, int armed);
int set_xingxiu(object me, int level, int armed);
int set_baituo(object me, int level, int armed);
int set_shenlongjiao(object me, int level, int armed);
int set_riyuejiao(object me, int level, int armed);
int set_dalunsi(object me, int level, int armed);
int set_taohua(object me, int level, int armed);
int set_gumu(object me, int level, int armed);
int set_lingjiu(object me, int level, int armed);
int set_murong(object me, int level, int armed);
int set_mingjiao(object me, int level, int armed);
int set_chaoting(object me, int level, int armed);
int set_xiake(object me, int level, int armed);
int set_pker(object me, int level, int armed);

int family_skill(object me, string family, int level, int armed)
{
	// switch family
	if(family == "random")
		family = random(2)
			? (random(2) ? "zheng" : "xie")
			: (random(2) ? "peace" : "special");
	if(family == "zheng")
		family = family_zheng[random(sizeof(family_zheng))];
	if(family == "xie")
		family = family_xie[random(sizeof(family_xie))];
	if(family == "peace")
		family = family_peace[random(sizeof(family_peace))];
	if(family == "special")
		family = family_peace[random(sizeof(family_peace))];

	// set common skills
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("unarmed", level);
	me->set_skill("literate", level);
	switch(family)
	{
	case "shaolin" :
		set_shaolin(me, level, armed);
		break;
	case "wudang" :
		set_wudang(me, level, armed);
		break;
	case "gaibang" :
		set_gaibang(me, level, armed);
		break;
	case "tiandihui" :
		set_tiandihui(me, level, armed);
		break;
	case "quanzhen" :
		set_quanzhen(me, level, armed);
		break;
	case "emei" :
		set_emei(me, level, armed);
		break;
	case "tianlong" :
		set_tianlong(me, level, armed);
		break;
	case "huashan" :
	case "huashan1" :
		set_huashan1(me, level, armed);
		break;
	case "huashan2" :
		set_huashan2(me, level, armed);
		break;
	case "xingxiu" :
		set_xingxiu(me, level, armed);
		break;
	case "baituo" :
		set_baituo(me, level, armed);
		break;
	case "shenlongjiao" :
		set_shenlongjiao(me, level, armed);
		break;
	case "riyuejiao" :
		set_riyuejiao(me, level, armed);
		break;
	case "dalunsi" :
		set_dalunsi(me, level, armed);
		break;
	case "taohua" :
		set_taohua(me, level, armed);
		break;
	case "gumu" :
		set_gumu(me, level, armed);
		break;
	case "murong" :
		set_murong(me, level, armed);
		break;
	case "mingjiao" :
		set_mingjiao(me, level, armed);
		break;
	case "chaoting" :
		set_chaoting(me, level, armed);
		break;
	case "xiake" :
		set_xiake(me, level, armed);
		break;
	case "pker" :
		set_pker(me, level, armed);
		break;
	case "lingjiu" :
		set_lingjiu(me, level, armed);
		break;
	default :
		set_gaibang(me, level, armed);
		break;
	}
}

int set_shaolin(object me, int level, int armed)
{
	me->set_skill("hunyuan-yiqi", level);
	me->set_skill("shaolin-shenfa", level);
	me->set_skill("yizhi-chan", level);
	me->set_skill("jingang-quan", level);
	me->set_skill("xiuluo-dao", level);
	me->set_skill("blade", level);
	me->set_skill("buddhism", level);
	me->set_skill("finger", level);
	me->set_skill("cuff", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("wuying-jian", level);
	me->set_skill("whip", level);
	me->set_skill("riyue-bian", level);
	me->map_skill("force", "hunyuan-yiqi");
	me->map_skill("dodge", "shaolin-shenfa");
	me->map_skill("cuff", "jingang-quan");
	me->map_skill("finger", "yizhi-chan");
	me->map_skill("blade", "xiuluo-dao");
	me->map_skill("parry", "wuying-jian");
	me->map_skill("sword", "wuying-jian");
	me->map_skill("whip", "riyue-bian");
	me->prepare_skill("finger", "yizhi-chan");
	if(armed)
	{
		me->set("use_weapon1", "sword");
		me->set("use_weapon2", "whip");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "finger.jingmo" :),
		(: perform_action, "sword.wuying" :),   
                (: command("changewield") :),
		(: perform_action, "sword.wuying" :), 
		(: perform_action, "sword.lidichengfo" :), 
		(: perform_action, "whip.chan" :),
		(: exert_function, "powerup" :),		  
		(: exert_function, "jingang" :),		             
	}));
}

int set_wudang(object me, int level, int armed)
{
	me->set_skill("taiji-shengong", level);
	me->set_skill("tiyunzong", level);
	me->set_skill("taiji-quan", level);
	me->set_skill("taiji-zhao", level);
        me->set_skill("taiji-dao", level);
        me->set_skill("taiji-jian", level);
	me->set_skill("sword", level);
	me->set_skill("blade", level);
	me->set_skill("cuff", level);
	me->set_skill("claw", level);
	me->set_skill("dodge", level);
	me->set_skill("force", level);
	me->set_skill("parry", level);
	me->map_skill("force", "taiji-shengong");
	me->map_skill("dodge", "tiyunzong");
	me->map_skill("cuff", "taiji-quan");
	me->map_skill("claw", "taiji-zhao");
	me->map_skill("blade", "taiji-dao");
	me->map_skill("sword", "taiji-jian");
	me->map_skill("parry", "taiji-jian");
	me->prepare_skill("cuff", "taiji-quan");
	if(armed)
	{
		me->set("use_weapon1", "sword");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "sword.chan" :),
		(: perform_action, "sword.chan" :),
		(: perform_action, "sword.lian" :),   
		(: perform_action, "cuff.zhen" :), 	
		(: perform_action, "dodge.zong" :), 
		(: exert_function, "powerup" :),		               
	}));
}

int set_emei(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("blade", level);
	me->set_skill("finger", level);
	me->set_skill("linji-zhuang", level);
	me->set_skill("zhutian", level);
	me->set_skill("fuliu-jian", level);
	me->set_skill("tiangang-zhi", level);
	me->set_skill("yanxing-dao", level);
	me->map_skill("force", "linji-zhuang");
	me->map_skill("dodge", "zhutian");
	me->map_skill("finger", "tiangang-zhi");
	me->map_skill("blade", "yanxing-dao");
	me->map_skill("sword", "fuliu-jian");
	me->map_skill("parry", "fuliu-jian");
	me->prepare_skill("finger", "tiangang-zhi");
	if(armed)
	{
		me->set("use_weapon1", "sword");
        }
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "finger.lingkong" :),
		(: perform_action, "sword.miejian" :),
		(: perform_action, "sword.miejian" :),   
		(: perform_action, "sword.fuliu" :), 	
		(: exert_function, "powerup" :),		  		             
	}));
}

int set_gaibang(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("staff", level);
	me->set_skill("strike", level);
	me->set_skill("huntian-qigong", level);
	me->set_skill("xiaoyaoyou", level);
	me->set_skill("dagou-bang", level);
	me->set_skill("xianglong-zhang", level);
	me->map_skill("force", "huntian-qigong");
	me->map_skill("dodge", "xiaoyaoyou");
	me->map_skill("strike", "xianglong-zhang");
	me->map_skill("staff", "dagou-bang");
	me->map_skill("parry", "dagou-bang");
	me->set("leiting",1);
        me->set("dagou-bang/zhuan",1);
        me->set("dagou-bang/tiao",1);
	me->prepare_skill("strike", "xianglong-zhang");
	if(armed)
	{
		me->set("use_weapon1", "staff");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
                (: perform_action, "strike.leiting" :),
		(: perform_action, "staff.chan" :),
		(: perform_action, "staff.chan" :),   
		(: perform_action, "staff.zhuan" :), 	
		(: perform_action, "staff.tiao" :), 
		(: exert_function, "powerup" :),		 		             
	}));
}

int set_tianlong(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("staff", level);
	me->set_skill("finger", level);
	me->set_skill("beiming-shengong", level);
	me->set_skill("lingbo-weibu", level);
	me->set_skill("liumai-shenjian", level);
	me->map_skill("force", "beiming-shengong");
	me->map_skill("dodge", "lingbo-weibu");
	me->map_skill("finger", "liumai-shenjian");
	me->map_skill("parry", "liumai-shenjian");
	me->prepare_skill("finger", "liumai-shenjian");
	if(armed)
	{
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "finger.qifa" :),
		(: perform_action, "finger.qifa2" :),
		(: perform_action, "finger.qifa2" :),   
		(: perform_action, "dodge.escape" :), 	
		(: perform_action, "dodge.luoshen" :),	  		             
	}));
}

int set_tiandihui(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("whip", level);
	me->set_skill("sword", level);
	me->set_skill("claw", level);
	me->set_skill("hand", level);
	me->set_skill("yunlong-shengong", level);
	me->set_skill("yunlong-shenfa", level);
	me->set_skill("yunlong-jian", level);
	me->set_skill("yunlong-bian", level);
	me->set_skill("yunlong-shou", level);
	me->set_skill("yunlong-zhua", level);
	me->map_skill("force", "yunlong-shengong");
	me->map_skill("dodge", "yunlong-shenfa");
	me->map_skill("parry", "yunlong-jian");
	me->map_skill("sword", "yunlong-jian");
	me->map_skill("whip", "yunlong-bian");
	me->map_skill("hand", "yunlong-shou");
	me->map_skill("claw", "yunlong-zhua");
	me->prepare_skill("finger", "liumai-shenjian");
	if(armed)
	{
		me->set("use_weapon1", "sword");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "claw.ningxue" :),
		(: perform_action, "hand.fuxue" :),
		(: perform_action, "sword.xian" :),   
		(: perform_action, "sword.xunlei" :), 	
		(: perform_action, "claw.ningxue" :), 	
		(: exert_function, "powerup" :),		 	             
	}));
}

int set_quanzhen(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("finger", level);
	me->set_skill("xiantian-gong", level);
	me->set_skill("fx-step", level);
	me->set_skill("quanzhen-jian", level);
	me->set_skill("yiyang-zhi", level);
	me->map_skill("force", "xiantian-gong");
	me->map_skill("dodge", "fx-step");
	me->map_skill("parry", "quanzhen-jian");
	me->map_skill("sword", "quanzhen-jian");
	me->map_skill("finger", "yiyang-zhi");
	me->prepare_skill("finger", "yiyang-zhi");
	if(armed)
	{
		me->set("use_weapon1", "sword");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "finger.fuxue" :),
		(: perform_action, "finger.yizhi" :),
		(: perform_action, "sword.ding" :),   
		(: perform_action, "sword.qixing" :), 	
		(: perform_action, "sword.tonggui" :), 
		(: perform_action, "sword.sanqing" :), 	
		(: perform_action, "sword.sanqing" :),
		(: exert_function, "powerup" :),		  	             
	}));
}

int set_huashan1(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("cuff", level);
	me->set_skill("strike", level);
	me->set_skill("huashan-neigong", level);
	me->set_skill("zixia-shengong", level);
	me->set_skill("huashan-shenfa", level);
	me->set_skill("huashan-jianfa", level);
	me->set_skill("hunyuan-zhang", level);
	me->set_skill("poyu-quan", level);
	me->map_skill("force", "huashan-neigong");
	me->map_skill("dodge", "huashan-shenfa");
	me->map_skill("parry", "huashan-jianfa");
	me->map_skill("sword", "huashan-jianfa");
	me->map_skill("cuff", "poyu-quan");
	me->map_skill("strike", "hunyuan-zhang");
	me->prepare_skill("cuff", "poyu-quan");
	me->prepare_skill("strike", "hunyuan-zhang");
	me->set("feilong",1);
	if(armed)
	{
		me->set("use_weapon1", "sword");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "cuff.leidong" :),
		(: perform_action, "strike.wuji" :),
		(: perform_action, "sword.feilong" :),   
		(: perform_action, "sword.jianzhang" :), 	
		(: perform_action, "sword.jianzhang" :), 
		(: perform_action, "sword.feilong" :), 	
		(: perform_action, "sword.sanqingfeng" :), 	 
		(: perform_action, "sword.kuaijian" :),  
		(: perform_action, "sword.shijiushi" :),
		(: exert_function, "powerup" :),		              
	}));
}

int set_huashan2(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("cuff", level);
	me->set_skill("strike", level);
	me->set_skill("huashan-neigong", level);
	me->set_skill("zixia-shengong", level);
	me->set_skill("huashan-shenfa", level);
	me->set_skill("dugu-jiujian", level);
	me->set_skill("hunyuan-zhang", level);
	me->set_skill("poyu-quan", level);
	me->map_skill("force", "huashan-neigong");
	me->map_skill("dodge", "huashan-shenfa");
	me->map_skill("parry", "dugu-jiujian");
	me->map_skill("sword", "dugu-jiujian");
	me->map_skill("cuff", "poyu-quan");
	me->map_skill("strike", "hunyuan-zhang");
	me->prepare_skill("cuff", "poyu-quan");
	me->prepare_skill("strike", "hunyuan-zhang");
	if(armed)
	{
		me->set("use_weapon1", "sword");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "cuff.leidong" :),
		(: perform_action, "strike.wuji" :),
		(: perform_action, "sword.pobingqi" :),   
		(: perform_action, "sword.pozhang" :), 	
		(: perform_action, "sword.po" :), 
		(: perform_action, "sword.po" :), 
		(: exert_function, "powerup" :),		  		             
	}));
}

int set_xingxiu(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("staff", level);
	me->set_skill("strike", level);
	me->set_skill("poison", level);
	me->set_skill("huagong-dafa", level);
	me->set_skill("zhaixinggong", level);
	me->set_skill("tianshan-zhang", level);
	me->set_skill("xingxiu-duzhang", level);
	me->map_skill("force", "huagong-dafa");
	me->map_skill("dodge", "zhaixinggong");
	me->map_skill("strike", "xingxiu-duzhang");
	me->map_skill("staff", "tianshan-zhang");
	me->map_skill("parry", "xingxiu-duzhang");
	me->prepare_skill("strike", "xingxiu-duzhang");
	if(armed)
	{
		me->set("use_weapon1", "staff");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "strike.huoqiang" :),
		(: perform_action, "strike.huoqiu" :),
		(: perform_action, "strike.sandu" :),   
		(: perform_action, "staff.handu" :), 	
		(: perform_action, "staff.handu" :), 		
		(: perform_action, "staff.feizhi" :),
		(: exert_function, "dianhuo" :),		 
	}));
}

int set_baituo(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("staff", level);
	me->set_skill("strike", level);
	me->set_skill("hamagong", level);
	me->set_skill("lingshe-zhangfa", level);
	me->set_skill("chanchu-bufa", level);
	me->map_skill("force", "hamagong");
	me->map_skill("dodge", "chanchu-bufa");
	me->map_skill("strike", "hamagong");
	me->map_skill("staff", "lingshe-zhangfa");
	me->map_skill("parry", "lingshe-zhangfa");
	me->prepare_skill("strike", "hamagong");
	me->set("reverse", 1);
	if(armed)
	{
		me->set("use_weapon1", "staff");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "strike.puji" :),
		(: perform_action, "strike.puji" :),
		(: perform_action, "staff.saoluoye" :), 	
		(: perform_action, "staff.saoluoye" :), 
		(: exert_function, "reverse" :),		             
		(: exert_function, "yixue" :),
		(: exert_function, "yixue" :),
	}));
}

int set_shenlongjiao(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("whip", level);
	me->set_skill("dagger", level);
	me->set_skill("strike", level);
	me->set_skill("shenlong-xinfa", level);
	me->set_skill("shenlong-bian", level);
	me->set_skill("dulong-bi", level);
	me->set_skill("yixingbu", level);
	me->set_skill("huagu-mianzhang", level);
	me->map_skill("force", "shenlong-xinfa");
	me->map_skill("dodge", "yixingbu");
	me->map_skill("strike", "huagu-mianzhang");
	me->map_skill("dagger", "dulong-bi");
	me->map_skill("parry", "dulong-bi");
	me->map_skill("whip", "shenlong-bian");
	me->prepare_skill("strike", "huagu-mianzhang");
	me->set("shenlong/meiren",1);
	me->set("shenlong/yingxiong",1);
	if(armed)
	{
		me->set("use_weapon1", "dagger");
		me->set("use_weapon2", "whip");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "dagger.meiren" :),
		(: perform_action, "dagger.meiren" :),
		(: perform_action, "dagger.yingxiong" :),
		(: perform_action, "whip.chan" :),
		(: perform_action, "whip.yunqi" :),
		(: exert_function, "chang" :),
		(: exert_function, "powerup" :),
		(: exert_function, "shexin" :),
	}));
}

int set_dalunsi(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("whip", level);
	me->set_skill("hammer", level);
	me->set_skill("strike", level);
	me->set_skill("longxiang-boruo", level);
	me->set_skill("yuxue-dunxing", level);
	me->set_skill("huoyan-dao", level);
	me->set_skill("xiangfu-lun", level);
	me->map_skill("force", "longxiang-boruo");
	me->map_skill("dodge", "yuxue-dunxing");
	me->map_skill("strike", "huoyan-dao");
	me->map_skill("hammer", "xiangfu-lun");
	me->map_skill("parry", "xiangfu-lun");
	me->prepare_skill("strike", "huoyan-dao");
	if(armed)
	{
		me->set("use_weapon1", "hammer");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "strike.ran" :),
		(: perform_action, "strike.fen" :),
//                (: perform_action, "hammer.dazhuan" :),  
		(: perform_action, "hammer.wushuai" :), 	
		(: perform_action, "hammer.wushuai" :),	 		             
		(: exert_function, "longxiang" :),	
	}));
}

int set_riyuejiao(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("hammer", level);
	me->set_skill("strike", level);
	me->set_skill("kuihua-shengong", level);
	me->set_skill("shandian-chui", level);
	me->set_skill("pixie-jian", level);
	me->set_skill("riyue-jian", level);
	me->map_skill("force", "kuihua-shengong");
	me->map_skill("dodge", "pixie-jian");
	me->map_skill("sword", "pixie-jian");
	me->map_skill("strike", "kaishan-zhang");
	me->map_skill("hammer", "shandian-chui");
	me->map_skill("parry", "riyue-jian");
	me->prepare_skill("strike", "kaishan-zhang");
	if(armed)
	{
		me->set("use_weapon1", "zhen");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "sword.ciwan" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.cimu" :), 	
		(: perform_action, "sword.cixue" :),				             
		(: exert_function, "powerup" :),	
	}));
}

int set_taohua(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("finger", level);
	me->set_skill("hand", level);
	me->set_skill("music", level);
	me->set_skill("bihai-shengong", level);
	me->set_skill("luoying-shenfa", level);
	me->set_skill("fuxue-shou", level);
	me->set_skill("tanzhi-shengong", level);
	me->set_skill("yuxiao-jian", level);
	me->map_skill("force", "bihai-shengong");
	me->map_skill("dodge", "luoying-shenfa");
	me->map_skill("hand", "fuxue-shou");
	me->map_skill("parry", "yuxiao-jian");
	me->map_skill("sword", "yuxiao-jian");
	me->map_skill("finger", "tanzhi-shengong");
	me->prepare_skill("finger", "tanzhi-shengong");
	me->prepare_skill("hand", "fuxue-shou");
	if(armed)
	{
		me->set("use_weapon1", "xiao");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "sword.chan" :),
		(: perform_action, "sword.xiaohua" :),
		(: perform_action, "sword.xiaohua" :),
		(: perform_action, "sword.zouxiao" :),	 	
		(: perform_action, "hand.fuxue" :),
		(: perform_action, "finger.tan" :),
		(: perform_action, "finger.tan" :),	
		(: exert_function, "powerup" :),		             
	}));
}

int set_gumu(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("whip", level);
	me->set_skill("strike", level);
	me->set_skill("jiuyin-shengong", level);
	me->set_skill("xianyun", level);
	me->set_skill("xiaohun-zhang", level);
	me->set_skill("yunu-jianfa", level);
	me->set_skill("changhen-bian", level);
	me->map_skill("force", "jiuyin-shengong");
	me->map_skill("dodge", "xianyun");
	me->map_skill("strike", "xiaohun-zhang");
	me->map_skill("parry", "yunu-jianfa");
	me->map_skill("sword", "yuxiao-jian");
	me->map_skill("whip", "changhen-bian");
	me->prepare_skill("strike", "xiaohun-zhang");
        me->set("suxin", 1);
	if(armed)
	{
		me->set("use_weapon1", "sword");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "sword.suxin" :),
		(: perform_action, "sword.suxin" :),
		(: perform_action, "sword.suxin" :),	 	
		(: perform_action, "strike.anran" :),	
		(: exert_function, "powerup" :),	
		(: exert_function, "yihun" :),			             
	}));
}

int set_murong(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("finger", level);
	me->set_skill("shenyuan-gong", level);
	me->set_skill("yanling-shenfa", level);
	me->set_skill("murong-jianfa", level);
	me->set_skill("douzhuan-xingyi", level);
	me->set_skill("canhe-zhi", level);
        me->set_skill("strike", level);
        me->set_skill("xingyi-zhang", level);
        me->map_skill("strike","xingyi-zhang");
	me->map_skill("force", "shenyuan-gong");
	me->map_skill("dodge", "yanling-shenfa");
	me->map_skill("finger", "canhe-zhi");
	me->map_skill("parry", "douzhuan-xingyi");
	me->map_skill("sword", "murong-jianfa");
	me->prepare_skill("finger", "canhe-zhi");
        me->prepare_skill("strike", "xingyi-zhang");
	if(armed)
	{
		me->set("use_weapon1", "sword");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "parry.xingyi" :),
		(: perform_action, "finger.dianxue" :),
		(: perform_action, "sword.lianhuan" :),
		(: perform_action, "sword.liuxing" :),
		(: perform_action, "sword.xingdou" :),	
		(: perform_action, "sword.douzhuanxingyi" :),	
		(: exert_function, "powerup" :),			             
	}));
}

int set_mingjiao(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("finger", level);
	me->set_skill("jiuyang-shengong", level);
	me->set_skill("datengnuo-bufa", level);
	me->set_skill("qiankun-danuoyi", level);
	me->set_skill("shenghuo-lingfa", level);
	me->set_skill("hanbing-zhang", level);
        me->set_skill("throwing", level);
        me->set_skill("feihua-shou", level);
        me->map_skill("throwing", "feihua-shou");
	me->map_skill("force", "jiuyang-shengong");
	me->map_skill("dodge", "datengnuo-bufa");
	me->map_skill("strike", "hanbing-zhang");
	me->map_skill("parry", "qiankun-danuoyi");
	me->map_skill("sword", "shenghuo-lingfa");
        me->prepare_skill("throwing", "feihua-shou");
	if(armed)
	{
		me->set("use_weapon1", "ling");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "dodge.tisha" :),
		(: perform_action, "sword.duo" :),
		(: perform_action, "sword.fenxin" :),
		(: perform_action, "sword.fenxin" :),
		(: perform_action, "dodge.tisha" :),
		(: command("enable parry shenghuo-lingfa") :),	//免得太强了
		(: command("enable parry qiankun-danuoyi") :),	//免得太强了		
		(: exert_function, "powerup" :),			             
                (: perform_action, "throwing.tan" :),
                (: perform_action, "throwing.tan" :),
	}));
}

int set_chaoting(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("blade", level);
	me->set_skill("claw", level);
	me->set_skill("bixue-xinfa", level);
	me->set_skill("longfeng-xiang", level);
	me->set_skill("kuangfeng-jian", level);
	me->set_skill("kuangfeng-dao", level);
	me->set_skill("kuihua-zhua", level);
	me->map_skill("force", "bixue-xinfa");
	me->map_skill("dodge", "longfeng-xiang");
	me->map_skill("claw", "kuihua-zhua");
	me->map_skill("parry", "kuangfeng-jian");
	me->map_skill("sword", "kuangfeng-jian");
	me->map_skill("blade", "kuangfeng-dao");
	me->prepare_skill("claw", "kuihua-zhua");
	if(armed)
	{
		me->set("use_weapon1", "blade");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "claw.three" :),
		(: perform_action, "claw.xiaofeng" :),
		(: perform_action, "blade.kuang" :),
		(: perform_action, "claw.three" :),	
		(: exert_function, "powerup" :),			             
	}));
}

int set_xiake(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("unarmed", level);
	me->set_skill("xiake-shengong", level);
	me->set_skill("xiake-jianfa", level);
	me->set_skill("xiake-shenfa", level);
	me->set_skill("xiake-quanjiao", level);
	me->map_skill("force", "xiake-shengong");
	me->map_skill("dodge", "xiake-shenfa");
	me->map_skill("unarmed", "xiake-quanjiao");
	me->map_skill("parry", "xiake-jianfa");
	me->map_skill("sword", "xiake-jianfa");
	me->prepare_skill("unarmed", "xiake-quanjiao");
	me->set("age",40);
	set("shen_type", 1);
	set("shen",99999999);
	if(armed)
	{
		me->set("use_weapon1", "sword");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "unarmed.hqgy" :),
		(: perform_action, "sword.feijian" :),
		(: perform_action, "sword.feijian" :),
		(: perform_action, "sword.feijian" :),	
		(: exert_function, "powerup" :),			             
	}));
}

int set_pker(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("chuforce", level);
	me->set_skill("shenxing-baibian", level);
	me->set_skill("guihun-jian", level);
	me->map_skill("force", "chuforce");
	me->map_skill("dodge", "shenxing-baibian");
	me->map_skill("parry", "guihun-jian");
	me->map_skill("sword", "guihun-jian");
	if(armed)
	{
		me->set("use_weapon1", "sword");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "dodge.escape" :),
		(: perform_action, "sword.wuyong" :),
		(: perform_action, "sword.wuyong" :),
		(: perform_action, "sword.wuyong" :),	
		(: exert_function, "force" :),			             
	}));
}

int set_lingjiu(object me, int level, int armed)
{
	me->set_skill("force", level);
	me->set_skill("dodge", level);
	me->set_skill("parry", level);
	me->set_skill("sword", level);
	me->set_skill("throwing", level);
	me->set_skill("hand", level);
	me->set_skill("bahuang-gong", level);
	me->set_skill("yueying-wubu", level);
	me->set_skill("tianyu-qijian", level);
	me->set_skill("zhemei-shou", level);
	me->set_skill("liuyang-zhang", level);
	me->map_skill("force", "bahuang-gong");
	me->map_skill("dodge", "yueying-wubu");
	me->map_skill("parry", "tianyu-qijian");
	me->map_skill("sword", "tianyu-qijian");
	me->map_skill("hand","zhemei-shou");
	me->map_skill("throwing","liuyang-zhang");
	me->prepare_skill("throwing","liuyang-zhang");
	me->prepare_skill("hand","zhemei-shou");
	if(armed)
	{
		me->set("use_weapon1", "sword");
	}
	me->set("chat_chance_combat", 100);
	me->set("chat_msg_combat", ({
		(: perform_action, "sword.fengwu" :),
		(: perform_action, "sword.fengwu" :),
		(: perform_action, "sword.fenfei" :),
		(: perform_action, "hand.duo" :),
		(: perform_action, "hand.tanmei" :),	
		(: exert_function, "powerup" :),			             
	}));
}
