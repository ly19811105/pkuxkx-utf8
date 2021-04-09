// killer.c 自动玩炸弹人的杀手
//by Vast@PKUXKX , 2009-5

inherit NPC;
#include <ansi.h>
int consider();
int check_room(object env);

void create()
{
	string *skills = ({"kongling-jian", "fengyun-jian"});
	string *pfm = ({"sword.pokong", "sword.biri"});
	int i = random(2);
	
        set_name(HIB"锦衣卫"NOR, ({ "jin yiwei", "jin", "wei" }));
        set("gender", "男性");
        set("age", random(20) + 20);
        set("str", random(20) + 20);
        set("dex", random(20) + 20);
        set("long", "这些人在京城侍卫中小有名气，武功也十分了得\n");
        set("combat_exp", 3000000 + random(7000000));
        set("shen_type", 1);
        set("attitude", "peaceful");
 
				set_skill("force", 100 + random(200));
				set_skill("dodge", 100 + random(200));
				set_skill("cuff", 100 + random(200));
				set_skill("strike",100 + random(200));
				set_skill("parry", 100 + random(200));
				set_skill("blade", 100 + random(200));
				set_skill("sword", 100 + random(200));
        set_skill("throwing", 100 + random(200));
        
				set_skill("kongdong-xinfa", 100 + random(200));
				set_skill("luofeng-liushi", 100 + random(200));
				set_skill("shizi-zhan", 100 + random(200));
        set_skill("fengyun-jian", 200 + random(100));
        set_skill("kongling-jian", 200 + random(100));
        set_skill("wulong-quan", 100 + random(200));

        map_skill("dodge", "luofeng-liushi");
        map_skill("parry", "fengyun-jian");
        map_skill("force", "kongdong-xinfa");
				map_skill("sword", skills[i]);
				map_skill("strike", "shizi-zhan");
				map_skill("cuff", "wulong-quan");
	
				prepare_skill("strike", "shizi-zhan");
				prepare_skill("cuff", "wulong-quan");

        set("neili", 8400);
        set("max_neili", 8400);
        set("eff_jingli", 8200);
        set("max_jingli", 8200);
        set("jingli", 8200);
				set("max_qi", 5800);
				set("eff_qi", 5800);
				set("qi", 5800);
				
     		set("chat_chance_combat", 100);
     		set("chat_msg_combat", ({
                (: consider :),
                            }) );
        setup();
        carry_object("/d/city/obj/gangjian")->wield();
        carry_object("/d/beijing/npc/obj/shiweifu")->wear();
}

int is_fighting()//npc既无战斗，周围也无其他人的情况下，会自动停止心跳，此处强制设定战斗状态
{
    return 1;
}

int consider()//此程序还可以进一步优化
{
	string *dir, *room, *val_dir, *val_dir2, *val_room, tar_dir, *inval_dir, str1;
	object me, env, tar, bomb;
	mapping dirs;

	int n, m, i, j, k, flag1, flag2, x, y;
	
	me = this_player();
	env = environment(me);
	
	dirs = env->query("exits");
	
	if(!dirs) return 1;
		
	dir = keys(dirs);
	room = values(dirs);
	val_dir = dir;
	val_room = room;

	n = sizeof(dir);
	
	flag1 = 0;

//周围房间是否有炸药
	for(j = 0; j < n; j++)
	{
		if(!tar = find_object(room[j]))
			tar = load_object(room[j]);
			
		if(present("zha dan", tar))
			{
				val_dir -= ({dir[j]});
				val_room -= ({room[j]});
				flag1 = 1;
			}
	}

//周围所有房间有炸药，必死无疑，不用动了
	m = sizeof(val_dir);
	if( m == 0 )	return 1;

//只有一个出口，跑～	
	if( m == 1 )
		{
			tar_dir = val_dir[0];
			CHANNEL_D->do_channel(this_object(), "sys", 	sprintf("dir = %s" , tar_dir));
			command("go " + tar_dir);			
			return 1;			
		}
		
	val_dir2 = val_dir;

//自己所在房间有炸药的情况下，强制移动，并且从危险较小的出口撤退，机会均等时，先等待		
	if(bomb = present("zha dan", env))
		{
    	for(i = 0; i < m; i++)
    	{
    		if(!tar = find_object(val_room[i]))
    			tar = load_object(val_room[i]);
    			
    			bomb->move("/adm/room/quitroom.c");//先移走Bomb再进行判断
    			flag2 = check_room(tar);
    			bomb->move(env);//判断完之后移回来
    			
    			if(flag2)
    				val_dir2 -= ({val_dir[i]});
    	}
			if(sizeof(val_dir2) == 0)	//危险均等,则先等待
				return 1;
//				val_dir2 = val_dir;
		
			tar_dir = val_dir2[random(sizeof(val_dir2))];
			command("go " + tar_dir);			
			return 1;
		}

//自己房间没有炸药的情况，伺机而动，选择随机出口离开，在周围房间均无炸药的情况下，先setbomb再离开						
	for(i = 0; i < n; i++)
	{
		if(!tar = find_object(room[i]))
			tar = load_object(room[i]);
			
		flag2 = check_room(tar);
		
		if(flag2)
			val_dir -= ({dir[i]});
	}

			k = sizeof(val_dir);

//			CHANNEL_D->do_channel(this_object(), "sys", 	sprintf("k = %d", k) );

			if(k == 0)	return 1;
				
			if(!flag1 && random(10) != 0)//不一定每次都放，10%概率不放炸弹，给玩家判断制造麻烦
				command("setbomb");
	
		if(bomb = present("zha dan", env))//在四个角旁边放置炸弹后，下一步最好不要进角，也不要在边上退，防止被困
			{
					str1 = base_name(env);
	
					i = strsrch(str1, "room");
	
					x = atoi(str1[(i + 4)..(i + 4)]);
					y = atoi(str1[(i + 5)..(i + 5)]);		
					
					inval_dir = allocate(2);
					
					if(x == 1 && (y == 0 || y == 3))
						inval_dir = ({"west", "east"});
					if(x == 2 && (y == 0 || y == 3))
						inval_dir = ({"east", "west"});					
					if((x == 0 || x == 3) && y == 1)
						inval_dir = ({"south", "north"});
					if((x == 0 || x == 3) && y == 2)
						inval_dir = ({"north", "south"});
					if(sizeof(inval_dir) != 0)
						{
							if(k >= 2)
								val_dir -= ({inval_dir[0]});//不进角(实际上在某些情况下还是有可能进角)
							if(sizeof(val_dir) >= 2)
								val_dir -= ({inval_dir[1]});//不退边
						}
			}	
			tar_dir = val_dir[random(sizeof(val_dir))];

			CHANNEL_D->do_channel(this_object(), "sys", 	sprintf("dir = %s" , tar_dir));
						
			command("go " + tar_dir);	
			return 1;		
}

int check_room(object env)//检查此房间四周是否有炸药包
{
	string *dir, *room, *val_dir;
	object tar;
	mapping dirs;

	int n, i, flag;
	
	flag = 0;
	
	dirs = env->query("exits");
	
	dir = keys(dirs);
	room = values(dirs);
	val_dir = dir;

	n = sizeof(dir);
	
	for(i = 0; i < n; i++)
	{
		if(!tar = find_object(room[i]))
			tar = load_object(room[i]);
			
		if(present("zha dan", tar))
			{
				val_dir -= ({dir[i]});
				flag = 1;
			}
	}
				
	return flag;
}
