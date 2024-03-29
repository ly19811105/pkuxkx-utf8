// by Vast@pkuxkx
// all comments added by Vast
// Modified by whuan@pkuxkx

nosave string *all_colors = ({BLK, HIR, HIB, HIG, HIY, HIC, HIW, HIM, GRN, RED, WHT, YEL, BLU, MAG, CYN});

nosave mapping gems = ([
	"yan": "★炎晶",
	"mu":	"★木灵",
	"sui":	"◎玉髓",
	"jin":	"☆精金",
	"bing":	"☆玄冰",
	"ri":	"★日魂",
	"yue":	"☆月魄",
	"gu": "神龙骨",
	"yu": "凤凰羽",
	"jiao": "麒麟角",
	"jia": "玄武甲",
]);
nosave mapping gems_color = ([
	"yan":	HIR,
	"mu":	HIG,
	"sui":	HIY,
	"jin":	HIW,
	"bing":	HIB,
	"ri":	HIC,
	"yue":	HIM,
	"gu": CYN,
	"yu": WHT,
	"jiao": RED,
	"jia": YEL,
]);
nosave string *gems_level = ({
	"地",
	"山",
	"水",
	"风",
	"雷",
  "火",
  "泽",
  "天",
});
nosave string *gems_yinyang = ({
	"☆",
	"★",
});
nosave string *gems_level_id = ({
	"di",
	"shan",
	"shui",
	"feng",
	"lei",
  "huo",
  "ze",
  "tian",
});
//以下效用请根据实际情况作相应调整
nosave mapping weapon_effect = ([
	"yan":  "增加兵器使用者的膂力",//apply(strength)
	"mu":	"提升兵器的最大耐久度",//rigidity,max_rigidity
	"yu":	"增加兵器使用者的攻击等级",//apply(attack)
	"jin":	"提升兵器的物理伤害",//apply(damage)
	"bing":	"给武器淬毒",// weapon_effect/poison
	"jin":	"命中对手时使其精减少",// weapon_effect/jing
	"ri":	"将武器造成的伤害转化为自己的气血和内力",// weapon_effect/suck
]);
nosave mapping armor_effect = ([
	"yan":		"让击中你的对手受伤",// armor_effect/rebound
	"yu":	"提升盔甲使用者的有效轻功等级",//apply(dodge)
	"bing":	"给防具淬毒",// armor_effect/poison
	"jin":	"提升盔甲使用者的防御",//apply(armor)
	"mu":	"将气血伤害变成内力减少",//apply(armor_vs_force,armor_vs_weapon)
	"jin":	"提升魔法石发挥效用的几率和掉宝率",//apply(magic)
	"ri":	"将敌人的伤害转化成自己的内力",// //apply/healup : heal_up()
]);
nosave mapping ring_effect = ([
	"yan":		"增加佩戴者的膂力",//apply(strength)
	"sui":	"增加佩戴者的攻击等级",//apply(attack)
	"jin":	"增加佩戴者各种空手功夫的有效等级",//apply(unarmed,strike,cuff,finger,hand,claw)
	"bing":	"提升佩戴者的有效轻功等级",//apply(dodge)
	"jin":	"提高佩戴者的防御等级",//apply(armor)
	"mu":	"提高佩戴者的招架等级",//apply(parry)
	"ri":	"大幅度提升魔法石发挥效用的几率和掉宝率",// apply(magic)
]);
//物品镶满之后得到一个前缀（考虑只给三个孔的物品此属性，设置7个等级）
nosave string *prefix_level =({
	({
		"老君", "风云", "幽明", "斗母",
		"浩气", "玉门", "集仙", "聚鹤",
		"娥眉", "飞燕", "璨星", "卧虎",
	}),
	({
		"青龙", "白虎", "朱雀", "玄武",
		"松鹤", "白虹", "起云", "承天",
		"延永", "须弥", "璎络", "天师",
	}),
	({
		"神力", "鬼力", "妖力", "修罗",
		"夜叉", "九幽", "北溟", "仙品",
		"啸天", "幻风", "文昌", "武圣",
	}),
	({
		"霸王", "九龙", "天渊", "飞仙",
		"七星", "玉衡", "北斗", "鸿均",
		"三清", "太白", "周天", "玄真",
	}),
	({
		"圣玄", "天玄", "地玄", "龙翔",
		"昆仑", "神圣", "麒麟", "凤舞",
		"天枢", "天璇", "天玑", "天权",
	}),
	({
		"天宇", "玄天", "太古", "无极",
		"神通", "创世", "旷世", "绝世",
		"亘古", "开元", "开天", "辟地",
	}),
	({
		"轩辕", "乾坤", "六合", "八卦",
		"寰宇", "混元", "太极", "天地",
		"盘古", "四象", "两仪", "八荒",
	})
});
nosave string *yan_prefix =({
		"炼狱", "真火", "鬼火", "烈火",
		"赤金", "丹霞", "凝血", "骄阳",
		"烈焰", "火云", "火花", "火光",
		"血饮", "隐血", "嗜血", "浴血",
		"慈云", "浮云", "青云", "朝云",
		"夜云", "飞云", "卷云", "白云",
		"蓝云", "紫云", "红云", "赤云",
		"霞蔚", "赤霞", "火鶴", "血斩",
});
nosave string *sui_prefix =({
		"雷鸣", "闪电", "霹雳", "玄黄",
		"惊雷", "电光", "黄泉", "削岩",
		"断川", "裂石", "劈空", "旋风",
		"千仞", "撼山", "苍岩", "开山",
});
nosave string *bing_prefix =({
		"冰霜", "寒冰", "冰玄", "凝霜",
		"寒霜", "飞雪", "冰寒", "霜华",
		"天水", "青霜", "聚泉", "春雨",
		"夏雨", "秋雨", "冬雨", "玉泉",
		"怒涛", "漩流", "流水", "流波",
		"沧海", "浪云", "飞雪", "烟雨",
		"瀚海", "潇湘", "海棠", "相思",
});
nosave string *mu_prefix =({
		"松纹", "寒毒", "松峦", "翠屏",
		"青羊", "松柏", "云竹", "幽兰",
		"寒梅", "百合", "含翠", "青陽",
		"碧落", "缥缈", "青黛", "青磷",
		"常青", "木樨", "绿影", "玉魔",
});
nosave string *yue_prefix =({
		"冷月", "紫电", "紫云", "弦月",
		"望月", "明月", "赶月", "追月",
		"夜月", "紫鶴", "月形", "飞星",
		"探星", "摘星", "星龙", "月龙",
});
nosave string *jin_prefix =({
		"白龙", "上灵", "破甲", "天兵",
		"神兵", "神灵", "圣才", "三才",
		"光华", "华彩", "天灵", "地灵",
		"人灵", "合灵", "智灵", "暗光",
		"曙光", "晦光", "天光", "神光",
});
nosave string *ri_prefix =({
		"魔王", "乱世", "鬼王", "夺魂",
		"勾魂", "拘魂", "慑魂", "鬼号",
		"鸱枭", "影残", "睚眦", "魔袱",
		"蚁峻", "螭吻", "蝙蝠", "降魔",
		"千芒", "黑魅", "扣骨", "翻天",
});
//本人才疏学浅想不出什么好的描述，欢迎大家来添加（weapon）
nosave string *yan_wield_msg =({
		"$N将手在风中一挥，无数的火星从四方飞来，渐渐聚在一起～～～$n"HIR"已经出现在$P手中！\n",
});
nosave string *yan_unwield_msg =({
		"$N将$n"HIR"随手一扔，只见$n"HIR"突然发出一片红光，仿佛化做无数的火星四散飘走！\n",
		"$N反手将$n"HIR"别在背后，红光渐渐隐去。\n",
});
nosave string *sui_wield_msg =({
		"$N将手在风中一挥，无数的金星从四方飞来，渐渐聚在一起～～～$n"HIY"已经出现在$P手中！\n",
});
nosave string *sui_unwield_msg =({
		"$N将$n"HIY"随手一扔，只见$n"HIY"突然变得光芒万道，仿佛化做无数的金星四散飘走了！\n",
		"$N反手将$n"HIY"别在背后，黄色光芒渐渐隐去。\n",
});
nosave string *yue_wield_msg =({
		"$N将手在风中一挥，无数的冰霜从四方飞来，渐渐聚在一起～～～$n"HIC"已经出现在$P手中！\n",
});
nosave string *yue_unwield_msg =({
		"$N将$n"HIC"随手一扔，只见$n"HIC"突然发出一片蓝光，仿佛化做无数的冰霜四散飘走了！\n",
		"$N反手将$n"HIC"别在背后，青光渐渐隐去。\n",
});
nosave string *bing_wield_msg =({
		"$N将手在风中一挥，无数的绿气从四周聚集过来，渐渐聚在一起～～～$n"HIG"已经出现在$P手中！\n",
});
nosave string *bing_unwield_msg =({
		"$N将$n"HIG"随手一扔，只见$n"HIG"突然变得光芒万道，仿佛化做无数的绿气四散飘走了！\n",
		"$N反手将$n"HIG"别在背后，绿色光芒渐渐隐去。\n",
});
nosave string *jin_wield_msg =({
		"$N将手在风中一挥，无数的紫色电花从四周聚集过来，渐渐聚在一起～～～$n"HIM"已经出现在$P手中！\n",
		"$n"HIM"突然自动跃入$N手中，发出柔和的光芒围绕着$N！\n",
});
nosave string *jin_unwield_msg =({
		"$N将$n"HIM"随手一扔，只见$n"HIM"突然变得光芒万道，仿佛化做无数的紫电四散飘走了！\n",
		"$N反手将$n"HIM"别在背后，紫色光芒慢慢的散去。\n",
});
nosave string *mu_wield_msg =({
		"$N将手在风中一挥，无数的星光从四方飞来，渐渐聚在一起～～～$n"HIW"已经出现在$P手中！\n",
		"$n"HIW"突然自动跃入$N手中，只见一道白光直透$n"HIW"，威力猛然大增！\n",
});
nosave string *mu_unwield_msg =({
		"$N将$n"HIW"随手一扔，只见$n"HIW"突然变得光芒万道，仿佛化做无数的星光四散飘走了！\n",
		"$N反手将$n"HIW"别在背后，白光渐渐隐去。\n",
});
nosave string *ri_wield_msg =({
		"$N将手在风中一挥，无数的幽魂从四方飞来，渐渐聚在一起～～～$n"WHT"已经出现在$P手中！\n",
});
nosave string *ri_unwield_msg =({
		"$N将$n"WHT"随手一扔，只见$n"WHT"突然变得诡异，仿佛化做无数的幽魂四散飘走了！\n",
});

//本人才疏学浅想不出什么好的描述，欢迎大家来添加（armor）
nosave string *yan_wear_msg =({
});
nosave string *yan_unequip_msg =({
});
nosave string *sui_wear_msg =({
});
nosave string *sui_unequip_msg =({
});
nosave string *yue_wear_msg =({
});
nosave string *yue_unequip_msg =({
});
nosave string *bing_wear_msg =({
});
nosave string *bing_unequip_msg =({
});
nosave string *jin_wear_msg =({
});
nosave string *jin_unequip_msg =({
});
nosave string *mu_wear_msg =({
});
nosave string *mu_unequip_msg =({

});
nosave string *ri_wear_msg =({
});
nosave string *ri_unequip_msg =({
});

//weapon
nosave int *jin_damage = ({6, 12, 18, 24, 30, 36, 42, 50});//增加的apply/damage数值
nosave int *yan_weapon_effect = ({1, 3, 5, 7, 9, 11, 13, 15});//增加的apply/strength数值
nosave int *sui_weapon_effect = ({4, 6, 8, 12, 16, 20, 24, 30});//增加的apply/attack数值
nosave int *yue_weapon_effect = ({20, 40, 60, 80, 100, 130, 160, 200});//增加的jing受到的伤害值
nosave int *bing_weapon_effect = ({1, 2, 3, 4, 5, 6, 7, 8});//增加的中毒时间长度
nosave int *mu_weapon_effect = ({100, 200, 300, 400, 500, 600, 700, 800});//增加的max_rigidity
nosave int *ri_weapon_effect = ({1, 2, 3, 4, 5, 6, 7, 8});//增加的吸取级别
//ring
nosave int *jin_ring_effect = ({6, 12, 18, 24, 30, 36, 42, 50});//增加的apply/armor数值
nosave int *yan_ring_effect = ({1, 2, 3, 4, 5, 6, 7, 8});//增加的apply/strength数值
nosave int *sui_ring_effect = ({6, 8, 10, 12, 14, 16, 18, 20});//增加的apply/attack数值
nosave int *yue_ring_effect = ({3, 6, 9, 12, 15, 18, 21, 25});//增加的apply/拳脚类功夫数值
nosave int *bing_ring_effect = ({6, 8, 10, 12, 14, 16, 18, 20});//增加的apply/dodge数值
nosave int *mu_ring_effect = ({4, 6, 8, 12, 16, 20, 24, 30});//增加的apply/parry数值
nosave int *ri_ring_effect = ({10, 20, 30, 40, 55, 70, 85, 100});//增加的apply/magic数值
//armor
nosave int *jin_defence = ({6, 12, 18, 24, 30, 36, 42, 50});//增加的apply/armor数值
nosave int *yan_armor_effect = ({4, 6, 8, 12, 16, 20, 24, 30});//armor_effect/rebound反弹伤害百分比
nosave int *sui_armor_effect = ({6, 8, 10, 12, 14, 16, 18, 20});//增加的apply/dodge数值
nosave int *yue_armor_effect = ({7, 14, 21, 28, 35, 42, 49, 55});//增加的apply/magic
nosave int *bing_armor_effect = ({1, 2, 3, 4, 5, 6, 7, 8});//增加的中毒时间长度
nosave int *mu_armor_effect = ({6, 12, 18, 24, 30, 36, 42, 50});//apply/armor_vs_force,armor_vs_weapon
nosave int *ri_armor_effect = ({5, 10, 15, 20, 25, 30, 35, 40});//apply/healup

