// huoji. 药铺伙计

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("铁匠铺伙计", ({ "huo ji", "huoji" }));
	set("str", 20);
	set("gender", "男性");
	set("age", 18);
        set("long", "他是王铁匠的学徒，平常除了和师傅学习锻造的本事之外，还负责出售一些价值不菲的兵器。\n");
	set("combat_exp", 250);
	set("attitude", "friendly");
	set("vendor_goods", ({
              "/clone/weapon/hammer/tongchui.c",
              "/clone/weapon/hammer/jingua.c",
              "/clone/weapon/whip/caichou.c",
              "/clone/weapon/staff/shawei.c",
              "/clone/weapon/staff/wuchangbang.c",
              "/clone/weapon/staff/tiezhang.c",
              "/clone/weapon/blade/dadan.c",
              "/clone/weapon/blade/fengdao.c",
              "/clone/weapon/blade/gudingdao.c",
              "/clone/weapon/blade/jindao.c",
              "/clone/weapon/blade/kandao.c",
              "/clone/weapon/blade/wandao.c",
              "/clone/weapon/blade/yanblade.c",
                "/d/city/weapon/tongqianbiao.c",
//              "/clone/weapon/sword/panguanbi.c",
//用判官笔限制panguan-bifa写字的频率
              "/clone/weapon/sword/qingfeng.c",
              "/clone/weapon/sword/ruler.c",
              "/clone/weapon/sword/yudi.c",
                "/d/city/weapon/yingzhen.c",
                "/d/city/weapon/xiuzhongjian.c",
                "/d/city/weapon/huaguzhen.c",
                "/d/city/weapon/suohoubiao.c",
                "/d/city/weapon/dmqiang",
                "/d/city/weapon/hyqiang",
                "/d/city/weapon/changqiang",
                "/d/city/weapon/fangtianji",
                "/d/city/weapon/mingyueji",
                "/d/city/weapon/jinfengji",
	}));

	set("shen_type",1);set("score",200);setup();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
