     inherit ROOM;
void create()
{	
     set("short", "无际的工作室");
   set("long", 
    "这里是无际的工作室。\n" );
set("valid_startroom",1);
set("sleep_room",1);
set("no_steal", "1");
	set("exits", ([
		"bt" : "/d/baituo/dating",
		"tls" : "/d/dali/dadian",
		"tai" : "/d/taishan/yuhuang",
		"sl" : "/d/shaolin/guangchang1",
		"dyd" : "/d/diaoyudao/duhaitan",
		"em" : "/d/emei/shanmen",
                "wg" : "/d/wudang/sanqing",
		"xx" : "/d/xingxiu/xxgate",
		"thd" : "/d/taohuadao/dating",
		"gy" : "/d/guiyunzhuang/guiyunting",
		"gm" : "/d/gumu/dating",
		"wz" : "/d/wizard/wizard_room",
		"ct" : "/d/city/guangchang",
		"qz" : "/d/quanzhen/gongmen",
		"quan" : "/d/quanzhou/zhongxin",
		"hs" : "/d/huashan/shufang",
                  "lj" : "/d/lingjiu/zhengting",
		"mj" : "/d/mingjiao/guangchang",
		"px" : "/d/pingxiwangfu/shu_fang",
		"pker" : "/d/pker/zonghengfu",
		"ry" : "/d/riyuejiao/dadian1",
              "xy" : "/d/xiangyang/xycenter",
              "xkd": "/d/xiakedao/shishi1",
                   "bhd": "/d/bhdao/bhdong",
                     "east":"/u/vast/biwuchang",
                      "fd":"/d/dali/fudi",
                       "sz":"/d/suzhou/kedian",
                    "mr":"/d/murong/yketing",
                    "bj":"/d/beijing/kedian",

	]));
setup();
}
