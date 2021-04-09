// by Vast@pkuxkx
// all comments added by Vast
// modified by Whuan@pkuxkx

//这个列表用于增加在其他场景出现的物品列表，请不断更新
//请留意物品的选择，不合适的物品请不要放置在这个列表中, 比如在一些解密过程中才能拿到的物品
//总之这一部分放置最最常见的东西
//物品列表请分类明确(按出现场景或者按不同的类别来区分, 不怕重复)，但是一定要容易整理
string *misc_item_list = ({

	// /d/city/npc/obj/下出现的物品
	"/d/city/npc/obj/baozi",
	"/d/city/npc/obj/beixin",

	// /d/beijing/npc/obj/下出现的物品
	"/d/beijing/npc/obj/kaoya",
	"/d/beijing/npc/obj/yuchandan",
        "/d/beijing/npc/obj/goldleaf.c",
        "/d/beijing/npc/obj/junfu.c",
        "/d/beijing/npc/obj/magua.c",
        "/d/beijing/npc/obj/jinduan.c",
        "/d/beijing/npc/obj/tea.c",
        "/d/beijing/npc/obj/yaodai.c",

        // /d/shenlongdao/obj下出现的物品
        "/d/shenlongdao/obj/shepi.c",
        "/d/shenlongdao/obj/sherou.c",
        "/d/shenlongdao/obj/xionghuangjiu.c",
	// 普通兵器

	// 食物
        "/clone/food/ganliang.c",
        "/d/wudang/npc/obj/turou",

        //衣服
        "/clone/cloth/cloth.c",
        "/clone/cloth/dao-cloth.c",
        "/clone/cloth/daogu-cloth.c",
        "/clone/cloth/dao-xie.c",
        "/clone/cloth/female-shoe.c",
        "/clone/cloth/female1-cloth.c",
        "/clone/cloth/female2-cloth.c",
        "/clone/cloth/female3-cloth.c",
        "/clone/cloth/female4-cloth.c",
        "/clone/cloth/female5-cloth.c",
        "/clone/cloth/female6-cloth.c",
        "/clone/cloth/female7-cloth.c",
        "/clone/cloth/female8-cloth.c",
        "/clone/cloth/ni-cloth.c",
        "/clone/cloth/ni-xie.c",
        "/clone/cloth/seng-cloth.c",
        "/clone/cloth/seng-xie.c",


        // 灵丹妙药
        "/d/xiangyang/npc/obj/shanlw.c",
/*
        "/clone/story/obj/mengzi.c",
        "/clone/story/obj/bible.c",
        "/clone/story/obj/intdan.c",
        "/clone/story/obj/perwan.c",
        "/clone/story/obj/guigu.c",
*/
        
        //金钱
        "/clone/money/gold",
        "/clone/money/gold",
        "/clone/money/gold",
        "/clone/money/thousand-cash",
	//大家看看怎样分类比较好？
	//一些相对较好的物品可以放到/d/ludingshan/special目录下，比如菩提子，熊胆丸等等
	});

varargs object item_drop(int *gem_level, int *drop_odds)
{
/************************************************************************************************
1.drop_odds参数可以省略
  缺省情况下drop几率:80% misc, 6% weapon, 6% armor, 1.5% special, 2.5% ring, 4% gems, 0% unique(根据实际情况调整)
  //普通情况下不会出现unique物品，一般boss级别npc可以设置此参数调整drop几率
2.weapon,armor,ring的不同类别稀有度在各自的文件中定义了，如果不太好控制可以考虑采取和gems级别限制的相同方法
3.npc设置参数限制gems的最高级别,和非缺省情况下的drop几率
  set("item_drop_odds", ({500, 150, 150, 100, 50, 45, 5, }));
  总和1000。分别代表7种不同类物品的drop几率
  set("gem_level", ({0, 10000}));
  数值为0-10000代表最高能够生成的gem级别
  	< 5000  1级
	5000 - 8334  2级
	8335 - 9444  3级
	9445 - 9814  4级
	9815 - 9939  5级
	9940 - 9979  6级
	9980 - 9994  7级
	9995 - 10000 8级
  具体请看/clone/gem/gem.c  set_level()函数
4.每位npc具体能够drop多少Item, 在各自的文件中自己定义，需要drop多个item的情况，多次调用本函数即可
4.misc包括普通场景中能够得到的各种物品，也包括部分特殊药品
************************************************************************************************/

	//其实n可以直接设定为7, 这个看以后是否增加新的物品类别而定，这样写只是为了减少以后的劳动量尽量避免出错
	//如果增加新的类别，下面的if ....else if还是需要手动修改
	int i, n, sum, *layer;
	int odds;
	object item;
	string *file;

	if(nullp(drop_odds)) drop_odds = ({800, 60, 60, 15, 25, 40, 0});
        if(nullp(gem_level)) gem_level = ({0, 10000});
	n = sizeof(drop_odds);
	layer = allocate(n);
	if(n != 7) error("错误：drop参数数量设置错误。请通知巫师！\n");
	for(i= 0; i < n; i++)	sum = sum + drop_odds[i];
	if( sum != 1000) error("错误：drop率总和错误。请通知巫师！\n");

	layer[0] = drop_odds[0];
	for(i= 1; i < n; i++)
	layer[i] = layer[i - 1] + drop_odds[i];

	odds = random(1000);
	if (odds < layer[0])
	{
		//这部分还需要细分为 1.misc/目录下的物品;2.misc_item_list列表中的物品;3.特殊的药品
//		file = get_dir(LDC_OBJ("misc/"));
//		item = new(file[random(sizeof(file))]);
		item = new(misc_item_list[random(sizeof(misc_item_list))]);
		if(objectp(item))
		return item;
		else error("错误：物品(misc)生成错误，请报告巫师。\n");
	}
	else if (odds < layer[1])
	{
		item = new("/clone/gem/weapon");
		if(objectp(item))
		return item;
		else error("错误：物品(weapon)生成错误，请报告巫师。\n");
	}
	else if (odds < layer[2])
	{
		item = new("/clone/gem/armor");
		if(objectp(item))
		return item;
		else error("错误：物品(armor)生成错误，请报告巫师。\n");
	}
	else if (odds < layer[3])
	{
		file = get_dir(LDC_OBJ("special/"));
		item = new(LDC_OBJ("special/" + file[random(sizeof(file))]));
		if(objectp(item))
		return item;
		else error("错误：物品(special)生成错误，请报告巫师。\n");
	}
	else if(odds < layer[4])
	{
		item = new("/clone/gem/ring");
		if(objectp(item))
		return item;
		else error("错误：物品(ring)生成错误，请报告巫师。\n");
	}
	else if(odds < layer[5])
	{
		item = new("/clone/gem/gem");
		item->set_level(gem_level[0], gem_level[1], item->query("material"));
		if(objectp(item))
		return item;
		else error("错误：物品(gem)生成错误，请报告巫师。\n");
	}
	else
	{
		file = get_dir(LDC_OBJ("unique/"));
		item = new(LDC_OBJ("unique/" + file[random(sizeof(file))]));
		if(objectp(item))
		return item;
		else error("错误：物品(uniqie)生成错误，请报告巫师。\n");
	}
}

object gem_drop(int *gem_level)
{
	object item;
	item = new("/clone/gem/gem");
	item->set_level(gem_level[0], gem_level[1], item->query("material"));
	if(objectp(item))
	return item;
	else error("错误：物品(gem)生成错误，请报告巫师。\n");
}

object misc_drop()
{
	string *file;
	object item;
              file = get_dir(LDC_OBJ("misc/"));
              item = new(file[random(sizeof(file))]);
	if(objectp(item))
	return item;
	else error("错误：物品(misc)生成错误，请报告巫师。\n");
}
