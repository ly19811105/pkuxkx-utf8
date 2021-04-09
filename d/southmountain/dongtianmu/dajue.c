// 东天目山，一座随机生成的区域。玩家副本 Zine 2014/7/14
inherit ROOM;
#include <ansi.h>
#define LOOK "/cmds/std/look.c"
string look_mirror();
void create()
{
	set("short", "大觉寺内");
	set("long", @LONG
这里是大觉寺的内殿，菩萨的金身已经剥落，殿里只有一个老和尚，东侧放
着一面铜镜(mirror)。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("item_desc", ([
                "mirror" : (:look_mirror:),]));
	set("exits", ([
		"out" : __DIR__"dajuesi",
		//"southwest" : __DIR__"xiaoxib",
		//"north" : __DIR__"shanlus1",
		//"west" : __DIR__"wall1",
	]));

	set("objects", ([
		__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
int look(object me, object obj)
{
    string str, limb_status, pro;
    mixed *inv;
    mapping my_fam, fam;
    int age, complex, anti_complex;
    string gender;
    string MUD_HOST;
    object head;
	str = obj->long();

    if (obj->query_temp("apply/gender"))
        gender = obj->query_temp("apply/gender")[0];
    else
        gender = obj->query("gender");

    pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(gender);

    if (obj->query_temp("apply/age"))
        age = obj->query_temp("apply/age")[0];
    else
        age = obj->query("age");

    if( (string)obj->query("race")=="人类"
            &&      intp(obj->query("age")) )
    {
//内力深厚以后对年龄的视觉效果有轻微影响。
//by seagate@pkuxkx
      if ( !obj->query_temp("apply/age") &&
      	   obj->query_skill("force")>800 )
      {
        	if( age-(obj->query_skill("force")-800)/120>=100 )
            str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number( (age-(obj->query_skill("force")-800)/120) / 100 * 100));
          else if( age-(obj->query_skill("force")-800)/120>=30 )
          	str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number( (age-(obj->query_skill("force")-800)/120) / 10 * 10));
          else if ( age >= 30 )
          	str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number(30));
          else
          	str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number(age / 10 * 10));
      }
      else
      {
      	if (age<100)
          str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number(age / 10 * 10));
        else		
          str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number(age / 100 * 100));
      }
    }

    
    if ( me->query("age") <= 14 ) 
        //str += "你才十四岁就要看吗,你什么也不懂呀.\n";
        str += "";
    else if(obj->is_character()&&obj->query("race")=="人类")//必须是人类才出容貌或者稚气未脱，否则对一个动物用这个形容太弱了，By Zine
    {
        if (obj->query("age") > 14)
            str += LOOK->getper(me, obj);
        else
            str += "年纪太小，还是稚气未脱的孩子。\n";
    }
    // If we both has family, check if we have any relations.
    if( obj!=me
            &&      !obj->query_temp("apply/name")
            &&      mapp(fam = obj->query("family"))
            &&      mapp(my_fam = me->query("family")) 
            &&      fam["family_name"] == my_fam["family_name"] ) {

        if( fam["generation"]==my_fam["generation"] ) {
            if( (string)obj->query("gender") == "男性" ||
                    (string)obj->query("gender") == "无性")
                str += sprintf( pro + "是你的%s%s。\n",
                        my_fam["master_id"] == fam["master_id"] ? "": "同门",
                        my_fam["enter_time"] > fam["enter_time"] ? "师兄": "师弟");
            else
                str += sprintf( pro + "是你的%s%s。\n",
                        my_fam["master_id"] == fam["master_id"] ? "": "同门",
                        my_fam["enter_time"] > fam["enter_time"] ? "师姐": "师妹");
        } else if( fam["generation"] < my_fam["generation"] ) {
            if( my_fam["master_id"] == obj->query("id") )
                str += pro + "是你的师父。\n";
            else if( my_fam["generation"] - fam["generation"] > 1 )
                str += pro + "是你的同门长辈。\n";
            else if( fam["enter_time"] < my_fam["enter_time"] )
                str += pro + "是你的师伯。\n";
            else
                str += pro + "是你的师叔。\n";
        } else {
            if( fam["generation"] - my_fam["generation"] > 1 )
                str += pro + "是你的同门晚辈。\n";
            else if( fam["master_id"] == me->query("id") )
                str += pro + "是你的弟子。\n";
            else
                str += pro + "是你的师侄。\n";

        }
    }
	if (obj->query("race")=="人类")//必须是人类才用人类的武功级别描述，否则对一个动物用这个形容太弱了，By Zine
	{
		if (!obj->is_corpse() ) {
		str +=sprintf("%s的武艺看上去", pro);
		str +=LOOK->gettof(obj);
		str +="，";
		str +=sprintf("出手似乎");
		str +=LOOK->getdam(obj);
		str += sprintf("。\n");
		 }
		if( obj->query("max_qi") )
			str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_qi") * 100 / (int)obj->query("max_qi")) + "\n";
	}
   
	write("你在铜镜里看到：\n\n");
    write(str);



    return 1;
}

string look_mirror()
{
	object me=this_player(),*ob,pl;
	ob=children(USER_OB);
	ob=filter(ob,(:environment($1) && living($1):));
	pl=ob[random(sizeof(ob))];
	look(me,pl);
	if (me->query("tianmuQuests/dajue/look_mirror")-time()>1800&&me==pl)
	{
		write("V");
	}
	me->set("tianmuQuests/dajue/look_mirror",time());
	return "";
}
