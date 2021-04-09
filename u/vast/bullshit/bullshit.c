//kill bullshi task
//modified from taskd by vast 2003.3.24

inherit F_DBASE;

#include <ansi.h>
#define MAX_TIMES 20

protected nosave mapping task_list=([]);
protected nosave object *task_ob=({});
protected nosave mapping ok_dir=([
	"/d/huashan/":"华山",
        "/d/wudang2/":"武当山",
	"/d/shaolin/":"少林寺",
	"/d/gumu/":"古墓",
	"/d/daili/":"大理",
	"/d/pker/":"杀手帮",
	"/d/taishan/":"泰山",
	"/d/xiangyang/":"襄阳",
	"/d/xingxiu/":"星宿",
	"/d/quanzhou/":"泉州",
	"/d/village/":"小山村",
	"/d/quanzhen/":"全真",
	"/d/taohuadao/":"桃花岛",
	"/d/pingxiwangfu/":"平西王府",
	"/d/riyuejiao/":"日月神教",
	"/d/gaibang/":"丐帮",
	"/d/baituo/":"白驼山",
	"/d/mingjiao/":"明教",
	"/d/guiyunzhuang/":"归云庄",
        "/d/emei/":"峨嵋",
        "/d/city/":"扬州",
        "/d/lingjiu/":"灵鹫",
        "/d/yuewangmu/":"越王墓",
        "/d/bhdao/":"冰火岛",
        "/d/anqimen/":"暗器门",
        "/d/diaoyudao/":"钓鱼岛",
        "/d/lingzhou/":"灵州",
        "/d/xiakedao/":"侠客岛",
        "/d/yashan/":"牙山",
]);

void update_task();
object random_place();
int do_findn(string arg);

void create()
{
	seteuid(getuid());
	update_task();
}

void update_task()
{
	object target,where;
	string tmp;
	int timer=0;

	if (do_findn("bullshit"))
	{
		remove_call_out("update_task");
        call_out("update_task",300);
		return;
	}


	target=new("/task/bullshit.c");

	where=random_place();

	if(!objectp(where))
	{
		remove_call_out("update_task");
        call_out("update_task",300);
		return;
	}

	tmp=ok_dir[where->query("main_dir")];

	target->set("wait_time",600);

	target->goto_leave();
	target->move(where);

	message("channel:" + "baowei",HIW"\n【江湖传闻】"NOR + HIR"据说"NOR + target->query("title") + "「" + target->query("nickname") + "」" + target->name() + "(" + target->query("id") + ")" + HIR"在"HIG + tmp + HIR"出现!"NOR, users());
	message("channel:" + "baowei",HIW"\n【江湖传闻】"NOR + HIY"希望正义之士前去斩杀此恶贼。\n"NOR, users());
	remove_call_out("update_task");
    call_out("update_task",900); //任务更新时间
	return;
}

object random_place()
{
	string main_dir,*place=({}),*dir,filename,*dirs,err;
	object output;
	int num,tmp;
	dirs=keys(ok_dir);
	main_dir=dirs[random(sizeof(dirs))];

	dir=get_dir(main_dir);
	for(int i=0;i<sizeof(dir);i++)
	{
		if(file_size(main_dir+dir[i])<=0||sscanf(dir[i],"%s.c",filename)!=1)
		continue;
		place+=({dir[i]});
	}
	num=sizeof(place);

	while(num--)
	{
		tmp=random(sizeof(place));
		err=catch(call_other(main_dir+place[tmp],"??"));
		if(err)
		{
             log_file("task:",main_dir + place[tmp]+"is not load\n");
			continue;
		}
		else
		{
			if(!(output=load_object(main_dir+place[tmp]))) continue;
			output->set("main_dir",main_dir);
			return output;
		}
		
	}

	return this_object();
}


int do_findn(string arg)
{
        object *chn,env;
        int i,j,count=0;
    
        chn = livings();
     

        for(i=0;i<sizeof(chn);i++)
        {
                if(clonep(chn[i]) && (member_array(arg,chn[i]->parse_command_id_list())!=-1 || 
                                strsrch(chn[i]->query("name"),arg)!=-1))
                {
                
                        count++;

                        if ( !objectp(env=environment(chn[i])) )
                        destruct(chn[i]);            
              }                       
        
        }               
        
        if (count==0) return 0;
		return 1;               
                
}