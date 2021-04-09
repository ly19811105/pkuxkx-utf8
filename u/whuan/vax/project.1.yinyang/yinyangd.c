/*  /adm/daemons/yinyangd.c
*    功夫阴阳守护程序
*    Dewolf<deWolf_maTri_X@msn.com>  Nov, 24th. 2005
*
*    Last Edit from : 
*/

#include <ansi.h>
#include <localtime.h>

#define MIN_SKILL_LEVEL	100

// environment factors
#define YEAR_FACTOR		0.05
#define MONTH_FACTOR		0.1
#define HOUR_FACTOR		0.2
#define AREA_FACTOR		0.3

// requirement for diff kungfu 
#define REQ_1		25
#define REQ_2		28
#define REQ_3		33
#define REQ_4		40


mapping AREA_YINYANG = ([
// 地点			阴阳		原因
"anqimen"	:	"太阴" ,	// 鬼手射
"baituo"	:	"太阴" ,	// 蛤蟆功
"beijing"	:	"少阴" ,	// 碧血心法
"bhdao"		:	"没有" ,	// 七伤拳
"bwdh"		:	"没有" ,	// 比武大会，不碰偏颇
"changbai"	:	"纯阴" ,	// 冷 -_-#
"city"		:	"没有" ,
"dali"		:	"没有" ,	// 枯荣，北冥两个，不设置
"death"		:	"没有" ,
"diaoyudao"	:	"太阳" ,	// 伸张正义
"emei"		:	"太阳" ,	// 临济十二庄
"gaibang"	:	"少阳" ,	// 浑天气功, 少阴的坐地铁要郁闷 grin 
"gift"		:	"没有" ,
"guiyunzhuang"	:	"少阴" ,	// 碧海神功
"gumu"		:	"太阴" ,	// 玉女心经
"huashan"	:	"纯阳" ,	// 紫霞神功 (毕竟是气宗主政)
"jwhz"		:	"没有" ,	// 海战
"lingjiu"	:	"太阴" ,	// 八荒功
"lingzhou"	:	"没有" ,
"ludingshan"	:	"没有" ,
"marry"		:	"没有" ,
"mingjiao"	:	"纯阳" ,	// 九阳神功
"murong"	:	"太阴" ,	// 神元功
"newbie"	:	"没有" ,
"pingxiwangpu"	:	"少阴" ,	// 英雄剑法
"pker"		:	"太阴" ,	// 楚氏气功
"private"	:	"没有" ,
"quanzhen"	:	"太阳" ,	// 先天神功
"quanzhou"	:	"没有" ,
"riyuejiao"	:	"纯阴" ,	// 葵花神功
"selfcreate"	:	"没有" ,
"suzhou"	:	"没有" ,
"taishan"	:	"没有" ,
"taohuadao"	:	"少阴" ,	// 碧海神功
"tdh-bang"	:	"少阳" ,	// 云龙神功
"village"	:	"没有" ,
"wizard"	:	"没有" ,
"working"	:	"没有" ,
"wudang"	:	"太阳" ,	// 太极神功
"wudang3"	:	"太阳" ,	// 太极神功
"xiakedao"	:	"少阳" ,	// 侠客神功
"xiangyang"	:	"没有" ,
"xinfang"	:	"没有" ,
"xingxiu"	:	"太阴" ,	// 化功大法
"xytaskd"	:	"没有" ,
"yashan"	:	"没有" ,
"year2k"	:	"没有" ,
"yuewangmu"	:	"太阳" ,	// 岳家枪法
]);

mapping OPPOSITE_YINYANG = ([
// 相反阴阳
"没有"	:	"没有" ,
"少阳"	:	"少阴" ,
"太阳"	:	"太阴" ,
"纯阳"	:	"纯阴" ,
"少阴"	:	"少阳" ,
"太阴"	:	"太阳" ,
"纯阴"	:	"纯阳" ,
]);

mapping BREAD_YINYANG = ([
// 相生阴阳。 左生右
"没有"	:	"没有" ,
"少阳"	:	"太阴" ,
"太阳"	:	"纯阴" ,
"纯阳"	:	"太阳" ,
"少阴"	:	"少阳" ,
"太阴"	:	"纯阳" ,
"纯阴"	:	"少阴" ,
]);

// 月份--阴阳
nosave string *DATE_YINYANG = ({
"纯阴","纯阴","太阴","少阴","少阳","太阳","纯阳","纯阳","太阳","少阳","少阴","太阴"
});

int datetime, date_year, date_month, date_hour;

void create()
{
	datetime  = 0;	// a date small enough
	date_year = 0;
	date_month= 0;
	date_hour = 0;
}

string query_area(string area)
{
	if (!undefinedp(AREA_YINYANG[area]))
	{
		return AREA_YINYANG[area];
	}
	return "没有";
}

void set_time(int date)
{
	mixed *local;
	// 用这个判断减少同一个时间内对“时间-阴阳”的 重复计算量。 大约每个时辰（20秒）重新计算一次
	if ( date - datetime > 20)
	{
		local = localtime(date);
	
		date_year = local[LT_YEAR] % 12;			// 地支
              date_month= local[LT_MON];				// 月份
              date_hour = ((local[LT_HOUR] + 1) % 24) / 2;	// 时辰
	};
}

string query_year()
{
	return DATE_YINYANG[date_year];
}
string query_month()
{
	return DATE_YINYANG[date_month];
}
string query_hour()
{
	return DATE_YINYANG[date_hour];
}

string query_opposite(string arg1)
{
	if (!undefinedp(OPPOSITE_YINYANG[arg1]))
	{
		return OPPOSITE_YINYANG[arg1];
	}
	return "没有";
}

string query_yinyang(object me)
{
	int enable_force_level, force_lvl, max_force,i;
	string enable_force, my_yinyang;
	string *skills;
	
	if (!living(me))
	{
		return "没有"; // 死东西没有阴阳
	}
	
	/*
	if (!userp(me))
	{
		return "没有";  // npc 
	}*/
	
	if ( !(force_lvl = (int)me->query_skill("force",1)) 
		|| !(enable_force = me->query_skill_mapped("force")) )
	{
		// no force skill || no mapped force
		return "没有";
	}
	enable_force_level = (int)me->query_skill(enable_force, 1);
	if (enable_force_level <= MIN_SKILL_LEVEL)
	{
		return "没有"; // skill too low
	}
	return SKILL_D(enable_force)->query_yinyang();
}

float yinyang_factor(object me)
{
	int force_lvl, enable_force_level;
	float npc_enhance, factor;
	string enable_force, skill_yinyang, here;
	string dir1, dir2, dir3;
	
	if (!living(me))
	{
		// 死东西没有阴阳
		return 0.0;
	}
	
	npc_enhance = 0.0;
	if (!userp(me))
	{
		// enhance npc without force/ enable_force
		npc_enhance = 0.1 * random(5);
	}
	
	if ( !(force_lvl = (int)me->query_skill("force",1)) 
		|| !(enable_force = me->query_skill_mapped("force")) )
	{
		return npc_enhance;
	}
	
	factor = 0.0;
	enable_force_level = (int)me->query_skill(enable_force, 1);
	if (enable_force_level > MIN_SKILL_LEVEL)
	{
		set_time(time());
		skill_yinyang = SKILL_D(enable_force)->query_yinyang();
		if (skill_yinyang != "没有")
		{
			// year factor
			if (skill_yinyang == query_year())
			{
				factor += YEAR_FACTOR;
			}
			else if (skill_yinyang == query_opposite(query_year()))
			{
				factor -= YEAR_FACTOR;
			}
			// month factor
			if (skill_yinyang == query_month())
			{
				factor += MONTH_FACTOR;
			}
			else if (skill_yinyang == query_opposite(query_month()))
			{
				factor -= MONTH_FACTOR;
			}
			// hour factor
			if (skill_yinyang == query_hour())
			{
				factor += HOUR_FACTOR;
			}
			else if (skill_yinyang == query_opposite(query_hour()))
			{
				factor -= HOUR_FACTOR;
			}
			
			// find area
			here = (string)file_name( environment(me) );
			sscanf(here, "\/%s\/%s\/%s", dir1, dir2, dir3);
			if (dir1 || dir2 || dir3 || dir1=="d")
			{
				if (skill_yinyang == query_area(dir2))
				{
					factor += AREA_FACTOR;
				}
				else if (skill_yinyang == query_opposite(query_area(dir2)))
				{
					factor -= AREA_FACTOR;
				}
			}
		}
	}
	
	factor += npc_enhance;
	// constrain factor in [-0.6 .. 0.8]
	if (factor > 0.8)
	{
		factor = 0.8;
	}
	else if (factor < -0.6)
	{
		factor = -0.6;
	}
	return factor;
}

int yinyang_xiangsheng(string my_yinyang, string ob_yinyang)
{
	// dummy function.  Its importance is waiting to be ensured.
	return 0;
}

int skill_support(object me, string yinyang)
{
	// support : 1 , no : 0
	int mystr, mycon, mydex, mymax_strdex;
	string my_yinyang;
	
	my_yinyang = query_yinyang(me);
	if (my_yinyang == "没有")
	{
		return 0; // non-yinyang force
	}
	
	mystr = me->query("str");
	mycon = me->query("con");
	mydex = me->query("dex");
	mymax_strdex = mystr > mydex ? mystr : mydex;
	if (my_yinyang == "少阳")
	{
		switch(yinyang)
		{
			case "少阳" :
				return 1;
			case "太阳" :
				return mystr>=REQ_1;
			case "纯阳" :
				return mycon>=REQ_1 && mystr>=REQ_3;
			case "少阴" :
				return mycon>=REQ_1 && mymax_strdex>=REQ_1;
			case "太阴" :
				return mycon>=REQ_1 && mystr>=REQ_1 && mydex>=REQ_1;
			case "纯阴" :
				return mycon>=REQ_2 && mystr>=REQ_2 && mydex>=REQ_2;
			case "没有" :
				return 1;
			default :
				return 0; // i guess this will not occur 
		}
	}
	else if (my_yinyang == "太阳")
	{
		switch(yinyang)
		{
			case "少阳" :
				return mystr>=REQ_1;
			case "太阳" :
				return 1;
			case "纯阳" :
				return mystr>=REQ_3;
			case "少阴" :
				return mycon>=REQ_1 && mystr>=REQ_1 && mydex>=REQ_1;
			case "太阴" :
				return mycon>=REQ_2 && mystr>=REQ_2 && mydex>=REQ_2;
			case "纯阴" :
				return mycon>=REQ_3 && mystr>=REQ_3 && mydex>=REQ_3;
			case "没有" :
				return 1;
			default :
				return 0; // i guess this will not occur 
		}
	}
	else if (my_yinyang == "纯阳")
	{
		switch(yinyang)
		{
			case "少阳" :
				return mycon>=REQ_1 && mystr>=REQ_3;
			case "太阳" :
				return mystr>=REQ_1;
			case "纯阳" :
				return 1;
			case "少阴" :
				return mycon>=REQ_2 && mystr>=REQ_2 && mydex>=REQ_2;
			case "太阴" :
				return mycon>=REQ_3 && mystr>=REQ_3 && mydex>=REQ_3;
			case "纯阴" :
				return mycon>=REQ_4 && mystr>=REQ_4 && mydex>=REQ_4;
			case "没有" :
				return 1;
			default :
				return 0; // i guess this will not occur 
		}
	}
	else if (my_yinyang == "少阴")
	{
		switch(yinyang)
		{
			case "少阳" :
				return mycon>=REQ_1 && mymax_strdex>=REQ_1;
			case "太阳" :
				return mycon>=REQ_1 && mystr>=REQ_1 && mydex>=REQ_1;
			case "纯阳" :
				return mycon>=REQ_2 && mystr>=REQ_2 && mydex>=REQ_2;
			case "少阴" :
				return 1;
			case "太阴" :
				return mydex>=REQ_1;
			case "纯阴" :
				return mycon>=REQ_1 && mydex>=REQ_3;
			case "没有" :
				return 1;
			default :
				return 0; // i guess this will not occur 
		}
	}
	else if (my_yinyang == "太阴")
	{
		switch(yinyang)
		{
			case "少阳" :
				return mycon>=REQ_1 && mystr>=REQ_1 && mydex>=REQ_1;
			case "太阳" :
				return mycon>=REQ_2 && mystr>=REQ_2 && mydex>=REQ_2;
			case "纯阳" :
				return mycon>=REQ_3 && mystr>=REQ_3 && mydex>=REQ_3;
			case "少阴" :
				return mydex>=REQ_1;
			case "太阴" :
				return 1;
			case "纯阴" :
				return mydex>=REQ_3;
			case "没有" :
				return 1;
			default :
				return 0; // i guess this will not occur 
		}
	}
	else if (my_yinyang == "纯阴")
	{
		switch(yinyang)
		{
			case "少阳" :
				return mycon>=REQ_2 && mystr>=REQ_2 && mydex>=REQ_2;
			case "太阳" :
				return mycon>=REQ_3 && mystr>=REQ_3 && mydex>=REQ_3;
			case "纯阳" :
				return mycon>=REQ_4 && mystr>=REQ_4 && mydex>=REQ_4;
			case "少阴" :
				return mycon>=REQ_1 && mydex>=REQ_3;
			case "太阴" :
				return mydex>=REQ_1;
			case "纯阴" :
				return 1;
			case "没有" :
				return 1;
			default :
				return 0; // i guess this will not occur 
		}
	}
	
	return 0; // i guess this will not occur 
}

int skill_isvalid(object player, string skill)
{
	if (((int)player->query_skill(skill,1)) < 100 )
		return 1;
	if (query_yinyang(player) == "没有" && SKILL_D(skill)->valid_enable("force"))
		return 1;
	if( !find_object(SKILL_D(skill)) || file_size(SKILL_D(skill)+".c") < 0)//判断是否是非自创武功
		return 1;  // 自创武功没有阴阳限制
	return skill_support(player, SKILL_D(skill)->query_yinyang());
}

string query_yinyang_color(string my_yinyang)
{
	switch (my_yinyang)
	{
		case "少阳" :
			return YEL"少阳"NOR;
		case "太阳" :
			return RED"太阳"NOR;
		case "纯阳" :
			return HIW"纯阳"NOR;
		case "少阴" :
			return GRN"少阴"NOR;
		case "太阴" :
			return CYN"太阴"NOR;
		case "纯阴" :
			return HIB"纯阴"NOR;
	}
	return "没有";
}