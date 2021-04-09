//dynroom.c
//seagate@pkuxkx 2010/09/28
//房间属性dynroom下面有两个公共子项：
//其中type代表房间类型，1表示动态房间，则相关算法计算的时候会考虑该房间，否则为非动态房间
//其中static_exits代表固定方向阵列，这是一个阵列，存放在不要修改的方向列表。这些房间在地图类型为1，3的时候将不会修改它。
//
//seagate@pkuxkx 2010/10/27 更新
//1.增加对Virtual Map类型（地图类型4）的支持
//2.当地图类型为1的时候，query_dynamic_function()不是必须实现的，可以使用默认的随机方向选择函数randomExits。
//3.对方迷宫房间方向镜像列表产生函数filterMirrorExits(mixed,mapping)输入的房间类型变更为mixed，以支援地图类型4的处理方式。
//4.解决了迷宫链接随机方向选择的时候无效方向循环内错误叠加的Bug
//5.解决了迷宫后补的链接关系将以前处理好的房间链接方向叠加超过4个链接关系的Bug
//未来有计划把函数randomRoomRelate和virtualRoomRelate用一个函数来实现，以简化代码，提高代码的通用性
//函数原型varargs protected mapping randomRoomRelate(mixed *roomList,mapping exitsResult, mixed *resultRooms, object headRoom);

inherit ROOM;

protected void init_exits(string);
protected object *getObjs(string, string *);
protected void dynExitsInit(object *, object);
protected mapping randomRoomRelate(object *, object, mapping, object *);
protected mapping virtualRoomRelate(string *, mapping, string*,string);
protected void dynMazeInit(object *, object);
protected mapping mazeRoomRebuild(object *, object, mapping, object *);
protected string *query_dynamic_desc();
protected mapping query_dynamic_full_desc();
protected string *filterMirrorExits(mixed,mapping);
protected string randomExits(string *);
protected mapping virtualRoom(int,string,mapping,mapping);
mapping directMirror=([                  //取镜像方向
	  "north":"south",
		"south":"north",
		"east":"west",
		"west":"east",
		"northwest":"southeast",
		"northeast":"southwest",
		"southwest":"northeast",
		"southeast":"northwest",
		"enter":"out",
		"out":"enter",
		"up":"down",
		"down":"up",
		"northup":"southdown",
		"southup":"northdown",
		"eastup":"westdown",
		"westup":"eastdown",
		"northdown":"southup",
		"soutdown":"northup",
		"eastdown":"westup",
		"westdown":"eastup"]);
//当地图类型为4的时候本结构起作用，本结构关键字是虚房间标签，标签结构是
//迷宫编号_房间标号；比如第0个迷宫的入口就是0_entry，第0个迷宫的第一个迷宫房间
//就是0_1，值为一个mapping，包含该房间产生的关键信息，包含file-来源于那个代码
//模板，short-房间名，desc-房间描述，exits-房间出入口信息, mazeIndex-迷宫序号
mapping virtualMap;
int virtualFlag=0;

//获得动态地图的动态计算函数名称，动态地图的头房间需要实现这个函数。
//注意动态地图类型为1（动态方向）的时候对函数返回值为随机方向。输入参数为该房间已存在方向列表。建议设定方向列表
//的时候最好不要少于8个。本地图仅支持E S W N NW NE SW SE ENTER OUT NU ND SU SD EU ED WU WD U D这几种方向，请自己
//根据地形不同选择合适的随机方向集合。本函数在地图类型1的方式下可以不实现，不实现的时候将采用默认的randomExits函数。
//动态地图类型为2（动态解谜计算）的时候函数返回值就是计算获得的谜底。输入参数为object1表示指定的一个动态房间。
//动态地图类型为3（动态迷宫）的时候不需要函数实现，由于是固定算法，所以无需自己开发动态关联算法。
//动态地图类型为4（Virtual Map）的时候本函数不需要实现，也不会用本函数。
string query_dynamic_function()
{
	return "";
}

//获得动态地图所在的目录名称，动态地图的头房间需要实现这个函数。
//动态地图类型为4（Virtual Map）的时候本函数不需要实现
string query_dynamic_dir()
{
	return "";
}

//动态地图类型，区分如何实现动态地图的方式，仅动态地图的头房间需要设置，其中默认值为1
//返回值1----表示为动态方向类型，也就是动态地图两两之间连接动态计算。
//返回值2----表示为动态解谜计算类型，也就是对动态地图每个房间用指定动态函数进行计算。
//返回值3----表示为动态迷宫类型，方向固定为ESWN，但是对应房间动态计算。
//返回值4----表示为动态方向-虚拟地图类型，也就是说房间是虚拟物件。
//返回值其他为非法
int query_dynamic_type()
{
	return 1;
}

//初始化动态地图，根据动态地图类型不同采取不同的初始化方式，其中动态方向类型的动态地图采用每个
//房间随机选择指定数量的动态房间作为连接对象，两个房间之间的链接方向随机。
//当动态地图属于动态解谜类型的时候采用每个房间根据谜题初始化函数进行谜题初始化，然后返回每个房
//间的谜底，本函数保证每个房间的谜底都不相同。
varargs nomask void init_dynMap(string dir,object dynHead,mixed mapDesc) {
	int dynType,dynDescItems,dynDescFItems,lp,dynMathSucFlag;
	object *dynRooms,dynRoom;
	string *dynDesc2,dynDesc3,*dynRNames,dynRName;
	mixed dynSingle;
//动态描述，当需要动态描述的时候请在头房间实现这个变量就可以了。要求至少三条记录。
//当地图初始化的时候会随机选择1-2条描述拼凑成该房间的地图描述。
	string *dynamicDesc;
//动态描述种类二，这个mapping的优先级比上一个字符串阵列的优先级更高，只要里面包含两个或者两个以上
//键字的时候就起作用，key为房间名，value为房间描述。
	mapping dynamicDescFull=([]);
//当动态地图类型为2-动态解谜计算类型的时候，每次执行该房间的动态解谜初始化函数以后
//将该房间的动态谜底存入该变量，以避免不同房间之间的动态解谜谜底相同。
	mixed *dynamicSingle=({});
	
	if(arrayp(mapDesc)&&stringp(mapDesc[0])) {
		dynamicDescFull=([]);
    dynamicDesc=mapDesc;
  }
  else if(mapp(mapDesc)) {
  	dynamicDesc=({});
 		dynamicDescFull=mapDesc;
  }
  else if(undefinedp(mapDesc)) {
		dynamicDescFull=([]);
  	dynamicDesc=({});  
  }
  else
  	error("错误的动态描述变量定义，仅支持mapping和string array两种形式的动态描述设置。");
	
	dynType=dynHead->query_dynamic_type();
	dynRooms=getObjs(dir,stat(dir));
	dynDescItems=sizeof(dynamicDesc);
	dynDescFItems=sizeof(dynamicDescFull);
	if(dynType==1)
		init_exits(dir);

//当地名-描述键值对的动态描述大于等于2的时候首先启动该动态描述机制
//随机从mapping中取出一对地名-描述的键值对更新到动态房间中。
  if(dynDescFItems>=2) {
  	foreach(dynRoom in dynRooms) {
  		dynRNames=keys(dynamicDescFull);
  		dynRName=dynRNames[random(dynDescFItems)];
  		dynRoom->set("short",dynRName);
  		dynRoom->set("long",dynamicDescFull[dynRName]+"\n");
  	}
  } else if(dynDescItems>=3) {
//当动态描述元素数量大于等于3的时候启动动态描述机制。随机取1到2条描述
//更新动态房间的描述。
		dynDesc3=dynamicDesc[random(sizeof(dynamicDesc))];
		foreach(dynRoom in dynRooms) {
			if(random(2)==0)
			  dynRoom->set("long",dynDesc3+"\n");
		  else {
		  	dynDesc2=dynamicDesc-({dynDesc3});
		  	dynRoom->set("long",dynDesc3+dynDesc2[random(sizeof(dynDesc2))]+"\n");
		  }
		}
	}
	
	switch(dynHead->query_dynamic_type()) {
		case 1:
			dynExitsInit(dynRooms,dynHead);
			break;
		case 2:
			foreach(dynRoom in dynRooms) {
				dynMathSucFlag=0;
				for(lp=0;lp<500;lp++) {
					dynSingle=call_other(dynHead,dynHead->query_dynamic_function(),dynRoom);
					printf("%s-%d:%O,%d\n",file_name(dynRoom),lp,dynSingle,member_array(dynSingle,dynamicSingle));
					if(member_array(dynSingle,dynamicSingle)==-1) {
						dynamicSingle+=({dynSingle});
						dynMathSucFlag=1;
						break;
					}
				}
				if(!dynMathSucFlag)
					error("动态地图类型：动态解密计算类型所在地图"+file_name(dynHead)+
					      "对应的计算函数："+dynHead->query_dynamic_function()+"提供的可选择项过少，请重新设计随机谜题。");
			}
			printf("%O\n",dynamicSingle);
			break;
		case 3:
			dynMazeInit(dynRooms,dynHead);
			break;
		default:
			error("错误的动态地图类型"+(string)dynHead->query_dynamic_type()+"，目前仅支持1，2，3三种取值方式。");
	}
}

//使用Virtual Object技术来产生随机地图，对应地图类型4，本函数为产生地图关系的核心函数。
//但是本函数不对应为产生最终地图，对于拼凑衔接类迷宫可以通过对此拼凑此函数来产生关系更加复杂的
//迷宫。迷宫对外出口的方向都是out
//其中rooms对应本次迷宫的房间数，room这个mapping是房间关键信息，里面包含出入口房间迷宫房间的
//关键信息，其中entry键字对应入口，out对应出口，maze对应迷宫房间，值里面还是包含一个mapping结构，
//值结构中file对应房间代码列表，desc对应描述列表（会随机选择一个描述，或者只有一个描述的时候就是
//固定描述）short对应房间名列表，virtual对应虚拟物品标志，如果为1表示为虚拟物品，0为非虚拟物品
//这个标志仅对entry或者out有效果，表示该入口或者出口是实体房间。这时候file只能有一个房间
//sample：
//room=(["entry":([
//           "file":({__DIR__"maze_entry1",__DIR__"maze_entry2"}),
//           "short":({"迷宫入口", "迷宫大门"}),
//           "desc":({"这是迷宫的进入门户", "前面就是一个迷宫"})
//           "virtual":1])]);
//flag 为第几个子迷宫，其中当第0个迷宫的时候会初始化virtualMap变量（迷宫信息结构对象），以后
//第N个迷宫的入口就是第N-1个迷宫的出口，第N个迷宫的出口就是第N+1个迷宫的入口，也就是说除了第0个
//迷宫的entry和out都有意义外，第N个迷宫只有out输入有意义，entry会直接参考之前第N-1个迷宫的出口。
//另外对于short和desc还支持另外一种替代形式就是show关键字来代替short+desc，show的内容是一个mapping，
//存放着房间名：房间描述的映射对
//另外一种形式的例子如下：
//room=(["entry":([
//           "file":({__DIR__"maze_entry1",__DIR__"maze_entry2"}),
//           "show":(["迷宫入口":"这是迷宫的进入门户", 
//                    "迷宫大门":"前面就是一个迷宫"]),
//           "virtual":1])]);
//create_virtualMap函数是一组virtual object地图产生的核心函数，每个地图最多25个房间，最少6个房间，
//可以将无限个类似的地图组合成一个非常巨大的迷宫，对于每个地方房间数的限制一方面是这个算法本身的局限性
//问题，另外一个方面可以适当控制迷宫的复杂度。
//输入参数complex（复杂度）是代表房间链接的复杂度（分别是2个链接，2-3个链接，3个链接三种复杂度）
//对应值分别是low、middle、high
varargs nomask void create_virtualMap(int rooms,mapping room,int flag,string complex)
{
	string key,buf,*mapKey,*mazeRoom,*effDirect,*direct=({"south","north","east","west"});
	int mazeIndex,lp;
	mapping exitsResult=([]);
	object entryRoom,outRoom;
	
	this_object()->set("no_reset",1);
	this_object()->set("no_clean_up",1);
	
//在创建第0号迷宫的时候整个迷宫初始化
	if(!flag) {
		virtualMap=([]);
		virtualFlag=0;
		mazeIndex=0;
	}
	else
		mazeIndex=flag;
	
	if(rooms<6)
		error("单个迷宫的房间数不能少于6个！\n");
	else if(rooms>25)
		error("单个迷宫的房间数最好不要多余25个！\n");
	
	mazeRoom=allocate(rooms);
	for(lp=0;lp<rooms;lp++)
		mazeRoom[lp]=sprintf("%d",lp);
	
	if(!mazeIndex)
		effDirect=direct;
	else
		effDirect=direct-keys(virtualMap[sprintf("%d_%s",mazeIndex-1,"out")]["exits"]);

	buf=effDirect[random(100)%sizeof(effDirect)];
//当入口是外面的固定地图的时候0房间出口直接写该入口房间对应文件
	if(!room["entry"]["virtual"]) {
//将固定的入口房间修改为常驻内存形式，并且进入方向固定为enter/out方向对，而且如果该方向已定义则不作处理
//增加对入口房间作为object传入参数的形式处理，支持出入口房间的副本形式。
//by seagate@pkuxkx 2011-12-19
    if ( objectp(room["entry"]["file"][0]) )
    	entryRoom=room["entry"]["file"][0];
  	else if(!(entryRoom=find_object(room["entry"]["file"][0])))
			entryRoom=load_object(room["entry"]["file"][0]);
		entryRoom->set("no_reset",1);
		entryRoom->set("no_clean_up",1);
		if(!entryRoom->query("exits/enter"))
			entryRoom->set("exits/enter",base_name(this_object())+sprintf("/%d_0",mazeIndex));
		entryRoom->delete("realmap");
		exitsResult["0"]=(["out":room["entry"]["file"][0]]);
	}
	else {
		if(mazeIndex) {
			virtualMap[sprintf("%d_%s",mazeIndex-1,"out")]["exits"]+=([buf:sprintf("%s/%d_0",base_name(this_object()),mazeIndex)]);
			exitsResult["0"]=([directMirror[buf]:"out"]);
		}
		else {
			exitsResult["entry"]=([buf:"0"]);
			exitsResult["0"]=([directMirror[buf]:"entry"]);
		}
	}

//当出口是外面的固定地图的时候最后一个房间出口直接写该出口房间对应文件
	if(!room["out"]["virtual"]) {
//将固定的出口房间修改为常驻内存形式，并且离开方向固定为enter/out方向对，而且如果该方向已定义则不作处理
//增加对入口房间作为object传入参数的形式处理，支持出入口房间的副本形式。
//by seagate@pkuxkx 2011-12-19
    if ( objectp(room["out"]["file"][0]) )
    	outRoom=room["out"]["file"][0];
  	else if(!(outRoom=find_object(room["out"]["file"][0])))
			outRoom=load_object(room["out"]["file"][0]);
		outRoom->set("no_reset",1);
		outRoom->set("no_clean_up",1);
		if(!outRoom->query("exits/out"))
			outRoom->set("exits/out",base_name(this_object())+sprintf("/%d_%s",mazeIndex,mazeRoom[rooms-1]));
  	outRoom->delete("realmap");
		exitsResult[mazeRoom[rooms-1]]=(["enter":room["out"]["file"][0]]);
	}
  else {
		exitsResult["out"]=([directMirror[buf]:mazeRoom[rooms-1]]);  	
  	exitsResult[mazeRoom[rooms-1]]=([buf:"out"]);
  }

  if(!complex)
  	exitsResult=virtualRoomRelate(mazeRoom,exitsResult,({}),"middle");
  else
		exitsResult=virtualRoomRelate(mazeRoom,exitsResult,({}),complex);
	
	if(!mazeIndex&&room["entry"]["virtual"])
    virtualMap[sprintf("%d_%s",mazeIndex,"entry")]=virtualRoom(mazeIndex,"entry",exitsResult["entry"],room["entry"]);
  
  if(room["out"]["virtual"])
  	virtualMap[sprintf("%d_%s",mazeIndex,"out")]=virtualRoom(mazeIndex,"out",exitsResult["out"],room["out"]);
  
  foreach(key in keys(exitsResult)) {
//  	printf("%d,%s,%O\n",mazeIndex,key,exitsResult[key]);
  	if(key=="entry"||key=="out") continue;
  	virtualMap[sprintf("%d_%s",mazeIndex,key)]=virtualRoom(mazeIndex,key,exitsResult[key],room["maze"]);
  }
  virtualFlag=1;
}

//采用Virtual Object技术产生N×M的矩阵，mapping room必须拥有entry，maze，out三种类型分别表示入口，迷宫，出口。
//入口和迷宫的坐标0，0到x-1，0之间随机选择一个房间作为入口房间，出口和迷宫的坐标0，y-1和x-1，y-1之间随机选择
//一个房间作为出口房间。
//entry和out的file都为固定房间，这个和create_VirtualMap的设置略有不同
nomask void create_StandardVirtualMap(int x, int y, mapping room )
{
	string index;
	mapping vRoom=([]);
	object entryRoom,outRoom;
  int lp, tlp, entry, out;
	
	virtualMap=([]);
	virtualFlag=0;

	this_object()->set("no_reset",1);
	this_object()->set("no_clean_up",1);
	
	if ( x<6 )
		error("横坐标不能少于6个房间。\n");
	
	if ( y<6 )
		error("纵坐标不能少于6个房间。\n");
		
//将固定的入口房间修改为常驻内存形式，并且进入方向固定为enter/out方向对，而且如果该方向已定义则不作处理
//增加对入口房间作为object传入参数的形式处理，支持出入口房间的副本形式。
//by seagate@pkuxkx 2011-12-19
  if ( objectp(room["entry"]["file"]) )
  	entryRoom=room["entry"]["file"];
  else if(!(entryRoom=find_object(room["entry"]["file"])))
		entryRoom=load_object(room["entry"]["file"]);
	entryRoom->set("no_reset",1);
	entryRoom->set("no_clean_up",1);
	entry=random(x);
	entryRoom->set("exits/enter",base_name(this_object())+sprintf("/%d_0",entry));
	entryRoom->delete("realmap");
	
//将固定的出口房间修改为常驻内存形式，并且离开方向固定为enter/out方向对，而且如果该方向已定义则不作处理
//增加对入口房间作为object传入参数的形式处理，支持出入口房间的副本形式。
//by seagate@pkuxkx 2011-12-19
  if ( objectp(room["out"]["file"]) )
   	outRoom=room["out"]["file"];
  if(!(outRoom=find_object(room["out"]["file"])))
		outRoom=load_object(room["out"]["file"]);
	outRoom->set("no_reset",1);
	outRoom->set("no_clean_up",1);
	out=random(x);
	outRoom->set("exits/out",base_name(this_object())+sprintf("/%d_%d",out,y-1));
  outRoom->delete("realmap");
  
  for(lp=0;lp<x;lp++)
    for(tlp=0;tlp<y;tlp++)
    {
    	vRoom=([]);
    	index=sprintf("%d_%d", lp, tlp);
      vRoom["file"]=room["maze"]["file"][random(100)%sizeof(room["maze"]["file"])];
	    if(mapp(room["maze"]["show"])) {
		    vRoom["short"]=keys(room["maze"]["show"])[random(100)%sizeof(keys(room["maze"]["show"]))];
		    vRoom["desc"]=room["maze"]["show"][vRoom["short"]];
	    }
	    else 
	    {
		    vRoom["short"]=room["maze"]["short"][random(100)%sizeof(room["maze"]["short"])];
		    vRoom["desc"]=room["maze"]["desc"][random(100)%sizeof(room["maze"]["desc"])];
	    }
	    vRoom["mazeIndex"]=0;
	    vRoom["mazeNo"]=index;
    	if ( tlp==0 && lp==entry )
    		vRoom["exits"]=(["out":room["entry"]["file"]]);
    	else if ( tlp==y-1 && lp==out )
    		vRoom["exits"]=(["enter":room["out"]["file"]]);
    	else
    		vRoom["exits"]=([]);

    	if ( tlp-1>=0 )
    	  vRoom["exits"]=vRoom["exits"]+(["south":sprintf("%s/%d_%d", base_name(this_object()), lp, tlp-1)]);
    	if ( tlp+1<y )
    		vRoom["exits"]=vRoom["exits"]+(["north":sprintf("%s/%d_%d", base_name(this_object()), lp, tlp+1)]);
      if ( lp-1>=0 )
      	vRoom["exits"]=vRoom["exits"]+(["west":sprintf("%s/%d_%d", base_name(this_object()), lp-1, tlp)]);
      if ( lp+1<x )
      	vRoom["exits"]=vRoom["exits"]+(["east":sprintf("%s/%d_%d", base_name(this_object()), lp+1, tlp)]);

      virtualMap[index]=([])+vRoom;
    }

  virtualFlag=1;
}

//Virtual Object迷宫Debug，由于无法画实际地图，所以只能以关联关系的形式提供地图
//detail标志表示debug的详细级别，目前分为两级0-级仅列出进出口，1-级列出所有房间
varargs nomask void debug_virtualMap(int detail,object me)
{
	string key;
	foreach(key in sort_array(keys(virtualMap),1)) {
	  if(!detail) {
	  	if(virtualMap[key]["mazeNo"]=="entry"||virtualMap[key]["mazeNo"]=="out")
				tell_object(me,sprintf("%s(%s):%O\n",key,virtualMap[key]["short"],virtualMap[key]["exits"]));
			else
				continue;
		}
		else
			tell_object(me,sprintf("%s(%s):%O\n",key,virtualMap[key]["short"],virtualMap[key]["exits"]));
	}
}

// 创造迷宫房间，由 VIRTUAL_D 调用。
// 迷宫创建函数init_virtualMap由virtual map配置对象来完成。
// 房间里面设置maze属性存放迷宫序号、迷宫房间号、迷宫房间类型（0-一般迷宫房间，1-迷宫出入口房间）
nomask object query_maze_room(string str)
{
	object ob,room;
	mapping vRoom;
	string mazeClass,mazeRoom;
	
	ob=this_object();
	if(ob->query_dynamic_type()!=4)
		return 0;
	else if(!stringp(str) || str == "")
		return 0;
//迷宫地图创建函数由Virtual Map配置object来完成，本函数只提供核心算法，不提供完整迷宫产生函数		
	else if(!virtualFlag)
		call_other(ob,"init_virtualMap");
	
	if(!virtualFlag)
		return 0;
	
	vRoom=virtualMap[str];
	if(!vRoom)
		return 0;
	ob=new(vRoom["file"]);
	if(!ob)
		return 0;
	if(!sscanf(str,"%s_%s",mazeClass,mazeRoom))
		return 0;
	
	ob->set("virtual_room",1);
  ob->set("short",vRoom["short"]);
  ob->set("long",vRoom["desc"]);
  ob->set("maze/class",vRoom["mazeIndex"]);
  ob->set("maze/room", str);
  if(mazeRoom=="entry"||mazeRoom=="out")
  	ob->set("maze/type",1);
  else
  	ob->set("maze/type",0);
  ob->set("exits",vRoom["exits"]);
  ob->setup();
  ob->set("no_reset", 1);
  ob->set("no_clean_up", 1);
  return ob;
}

//清理内存中已经产生的虚拟物件
varargs nomask void virtualRoomDestruct(string room)
{
	object ob,inv,vRoom;
	string vNo;
	ob=this_object();
	
	if(!virtualMap)
		return;

	foreach(vNo in keys(virtualMap))
	  if((vRoom=find_object(sprintf("%s/%s",base_name(ob),vNo)))) {
	  	foreach(inv in all_inventory(vRoom))
	  	  if(userp(inv)) {
	  	  	tell_object(inv, "迷宫正在更新中！请稍候过来！\n");
	  	  	if(!room)
	  	  		inv->move(VOID_OB);
	  	  	else
	  	  		inv->move(room);
	  	  }
	  	destruct(vRoom);
	  }
}

//初始化动态房间信息，主要是将所有出口删除。（动态重新生成地图前调用次函数将以前的方向全部删除）
//入口参数是动态地图所在目录。（自动搜索该目录，将该目录下所有动态房间初始化掉）
protected void init_exits(string dir)
{
  object *dynRooms;
  object dynRoom;
  mapping exits;
  string exitDirect;
  string *direct;
  int i,dirIndex;
  
  direct=allocate(12);
  dynRooms=getObjs(dir,get_dir(dir));
  foreach(dynRoom in dynRooms) {
//如果该房间非动态房间则忽略
  	if(!dynRoom->query("dynroom/type"))
  		continue;
  		
  	exits=dynRoom->query("exits");
//首先找到该房间的所有非固定方向存入列表direct中。
    dirIndex=0;
  	foreach(exitDirect in keys(exits)) {
  		if(!arrayp(dynRoom->query("dynroom/static_exits"))||
  			 member_array(exitDirect,dynRoom->query("dynroom/static_exits"))==-1) {
  			direct[dirIndex]=exitDirect;
  			dirIndex++;
  		}
  	}
//将动态方向删除  	
  	for(i=0;i<dirIndex;i++) {
  		map_delete(exits,direct[i]);
  	}
  	dynRoom->set("exits",exits);
  	dynRoom->delete("realmap");
  }
}

//公共函数，取出指定目录下的所有object
protected object *getObjs(string dir,string *file) {
	object *objs,dynroom;
	string fn;
	int i,j;
	
	objs=allocate(sizeof(file));
	j=0;
	
	for(i=0;i<sizeof(file);i++) {
		if(!sscanf(file[i], "%*s.c")) continue;
		switch(file_size(dir+file[i])) {
			case -1:
			case -2:
				break;
			default:
				dynroom=find_object(dir+file[i]);
				if(!dynroom) {
					dynroom=load_object(dir+file[i]);
				}
				if(dynroom->query("dynroom/type")) {
					objs[j]=dynroom;
				  j++;
				}
		}
	}
	if(j<sizeof(file))
		objs=objs-({objs[sizeof(file)-1]});
	return objs;
}

//本函数的作用是对阵列roomArray建立两两之间的动态出口，每个房间最多建立4个动态关系，
//最少建立2个动态关系，所以建议roomArray传入房间数不要少于8个，不要多于16个（由于建立
//关系是一个递归过程，递归太深会有问题。）
protected void dynExitsInit(object *roomArray,object headRoom) {
//存放动态房间链接结果。key值是object，value是一个方向和目标房间object的键值对。	
	mapping dynExitsResult=([]);
	mapping exitMap;
	object roomBuf;
	string roomExit;
	
	dynExitsResult=randomRoomRelate(roomArray,headRoom,([]),({}));
//得到动态关联关系以后，修改房间的出口	
	foreach(roomBuf in keys(dynExitsResult)) {
		exitMap=dynExitsResult[roomBuf];
		foreach(roomExit in keys(exitMap))
			roomBuf->set("exits",roomBuf->query("exits")+([roomExit:replace_string(file_name(exitMap[roomExit]),".c","")]));
	}
}

//通过递归来建立动态方向的产生以保证肯定会出现一条有效通道。每个房间随机出现2-4个动态方向，其中一个方向
//是链接之前未出现的房间，其他方向随机选择本房间中非本房间非已建立关联关系的房间。
protected mapping randomRoomRelate(object *roomArray,object headRoom,mapping exitsResult,object *resultRooms) {
	string *exits,*effExits,randomExit,*staticExits;
	int exitsLen,i;
	object randomRoom,*effRooms,endRoom,roomBuf,*resultRBuf;
	mapping exitsRValue,exitsRBuf;
	
	exitsLen=random(2)+2;
	exitsRBuf=exitsResult;
	resultRBuf=resultRooms;
	
	if(resultRBuf==({})) {
		staticExits=roomArray[0]->query("dynroom/static_exits");
		if(mapp(roomArray[0]->query("exits"))&&sizeof(roomArray[0]->query("exits"))>0) 
		  exits=staticExits?keys(roomArray[0]->query("exits"))-staticExits:keys(roomArray[0]->query("exits"));
		else
			exits=({});
		
		if(sizeof(exits)>0)
			error("房间："+file_name(roomArray[0])+"存在遗留未清理的旧动态方向。初始化动态方向出错。");
		else
			exits=staticExits?staticExits:({});
		
		effRooms=roomArray-resultRBuf-({roomArray[0]});
		for(i=0;i<exitsLen;i++) {
			if(sizeof(effRooms)<exitsLen-i)
				error("提供的动态地图房间数过少导致动态地图产生失败。");
			
			randomRoom=effRooms[random(sizeof(effRooms))];
			effExits=exits+filterMirrorExits(randomRoom,exitsRBuf);
			if(arrayp(randomRoom->query("dynroom/static_exits")))
				foreach(randomExit in randomRoom->query("dynroom/static_exits"))
					effExits=effExits+({directMirror[randomExit]});

			if(headRoom->query_dynamic_function()=="")
				randomExit=randomExits(effExits);
			else
				randomExit=call_other(headRoom,headRoom->query_dynamic_function(),effExits);
			
			if(member_array(roomArray[0],keys(exitsRBuf))==-1)
				exitsRBuf[roomArray[0]]=([randomExit:randomRoom]);
			else
		  	exitsRBuf[roomArray[0]]=exitsRBuf[roomArray[0]]+([randomExit:randomRoom]);
			exitsRBuf[randomRoom]=([directMirror[randomExit]:roomArray[0]]);
		  exits=exits+({randomExit});
		  effRooms=effRooms-({randomRoom});
		}
		resultRBuf=resultRBuf+({roomArray[0]});
	} else {
//取出已经完成动态计算的结果房间列表中取出最后一个房间，从该房间的关联关系中取出没有做过动态计算的房间作为计算对象。		
		endRoom=resultRBuf[sizeof(resultRBuf)-1];
		foreach(roomBuf in values(exitsRBuf[endRoom])) {
			if(member_array(roomBuf,resultRBuf)==-1) {
				endRoom=roomBuf;
				break;
			}
		}
		
		staticExits=endRoom->query("dynroom/static_exits");
		if(mapp(endRoom->query("exits"))&&sizeof(endRoom->query("exits"))>0)
		  exits=staticExits?keys(endRoom->query("exits"))-staticExits:keys(endRoom->query("exits"));
		else
			exits=({});

		if(sizeof(exits)>0)
			error("房间："+file_name(endRoom)+"存在遗留未清理的旧动态方向。初始化动态方向出错。");
		else
			exits=staticExits?staticExits:({});
//由于关联的时候是room1和room2的关系是成对写入的，即对room1写入和room2的关系正方向，也对room2写入和room1关系的反方向。
//所以即使对目标房间没有作任何计算也存在计算好的关联关系。		
		if(mapp(exitsRBuf[endRoom]))
			exits=exits+keys(exitsRBuf[endRoom]);
		
		effRooms=roomArray-resultRBuf-({endRoom});
		if(sizeof(effRooms)>0) {
			randomRoom=effRooms[random(sizeof(effRooms))];
			effExits=exits+filterMirrorExits(randomRoom,exitsRBuf);

			if(headRoom->query_dynamic_function()=="")
				randomExit=randomExits(effExits);
			else
				randomExit=call_other(headRoom,headRoom->query_dynamic_function(),effExits);

			if(!mapp(exitsRBuf[endRoom]))
			 	exitsRBuf[endRoom]=([randomExit:randomRoom]);
			else
			 	exitsRBuf[endRoom]=exitsRBuf[endRoom]+([randomExit:randomRoom]);

			if(!mapp(exitsRBuf[randomRoom])) 
				exitsRBuf[randomRoom]=([directMirror[randomExit]:endRoom]);
			else
				exitsRBuf[randomRoom]=exitsRBuf[randomRoom]+([directMirror[randomExit]:endRoom]);
		}
		
		if(exitsLen>sizeof(keys(exitsRBuf[endRoom]))) {
			exitsLen-=sizeof(keys(exitsRBuf[endRoom]));
			effRooms=roomArray-({endRoom})-values(exitsRBuf[endRoom]);
//减去房间链接数到达4个上限的那些房间
			foreach(roomBuf in resultRBuf)
				if(sizeof(keys(exitsRBuf[roomBuf]))>=4)
					effRooms=effRooms-({roomBuf});

		  for(i=0;i<exitsLen;i++) {
		  	if(sizeof(effRooms)==0)
		  		break;
			  randomRoom=effRooms[random(sizeof(effRooms))];
				effExits=exits+keys(exitsRBuf[endRoom])+filterMirrorExits(randomRoom,exitsRBuf);
				
				if(headRoom->query_dynamic_function()=="")
					randomExit=randomExits(effExits);
				else
			  	randomExit=call_other(headRoom,headRoom->query_dynamic_function(),effExits);
			  
			  if(!mapp(exitsRBuf[endRoom]))
			  	exitsRBuf[endRoom]=([randomExit:randomRoom]);
			  else
			  	exitsRBuf[endRoom]=exitsRBuf[endRoom]+([randomExit:randomRoom]);
			  
			  if(!mapp(exitsRBuf[randomRoom])) 
				  exitsRBuf[randomRoom]=([directMirror[randomExit]:endRoom]);
			  else
				  exitsRBuf[randomRoom]=exitsRBuf[randomRoom]+([directMirror[randomExit]:endRoom]);
			  exits=exits+({randomExit});
			  effRooms=effRooms-({randomRoom});
		  }
		}
		resultRBuf=resultRBuf+({endRoom});
  }
  if(sizeof(roomArray)==sizeof(resultRBuf))
  	return exitsRBuf;
  else {
  	exitsRBuf=randomRoomRelate(roomArray,headRoom,exitsRBuf,resultRBuf);
	  return exitsRBuf;
  }
}

//virtual object版本的动态地图产生函数，和randomRoomRelate秉承一个算法，不过由建立object之间关联关系变更为
//建立房间代码之间的对应关系，房间方向选择范围固定为W S E N NE NW SE SW八个方向。
protected mapping virtualRoomRelate(string *roomArray, mapping exitsResult, string*resultRooms, string complex) {
	string *exits,randomExit,*staticExits,randomRoom,*effRooms,endRoom,roomBuf,*resultRBuf;
	int exitsLen,i;
	mapping exitsRValue,exitsRBuf;
	
	if(complex=="low")
		exitsLen=2;
	else if(complex=="middle")
		exitsLen=random(2)+2;
	else
		exitsLen=3;

	exitsRBuf=exitsResult;
	resultRBuf=resultRooms;
	
	if(resultRBuf==({})) {
		effRooms=roomArray-resultRBuf-({roomArray[0]});
		exitsLen=exitsLen-sizeof(keys(exitsRBuf[roomArray[0]]));
		for(i=0;i<exitsLen;i++) {
			if(sizeof(effRooms)<exitsLen-i)
				error("提供的动态地图房间数过少导致动态地图产生失败。");
			
			randomRoom=effRooms[random(sizeof(effRooms))];
			exits=keys(exitsRBuf[roomArray[0]])+filterMirrorExits(randomRoom,exitsRBuf);
//如果本房间存在外部出口，则不分配south方向给该房间。主要为了地图显示更合理
			if(member_array("out",keys(exitsRBuf[roomArray[0]]))!=-1)
				exits=exits+({"south"});
			else if(member_array("enter",keys(exitsRBuf[roomArray[0]]))!=-1)
				exits=exits+({"north"});
			randomExit=randomExits(exits);
			
			if(member_array(roomArray[0],keys(exitsRBuf))==-1)
				exitsRBuf[roomArray[0]]=([randomExit:randomRoom]);
			else
		  	exitsRBuf[roomArray[0]]=exitsRBuf[roomArray[0]]+([randomExit:randomRoom]);
		  if(!mapp(exitsRBuf[randomRoom]))
		  	exitsRBuf[randomRoom]=([directMirror[randomExit]:roomArray[0]]);
		  else
				exitsRBuf[randomRoom]=exitsRBuf[randomRoom]+([directMirror[randomExit]:roomArray[0]]);
		  exits=exits+({randomExit});
		  effRooms=effRooms-({randomRoom});
		}
		resultRBuf=resultRBuf+({roomArray[0]});
	} else {
//取出已经完成动态计算的结果房间列表中取出最后一个房间，从该房间的关联关系中取出没有做过动态计算的房间作为计算对象。		
		endRoom=resultRBuf[sizeof(resultRBuf)-1];
		foreach(roomBuf in values(exitsRBuf[endRoom])) {
			if(roomBuf=="entry"||roomBuf=="out"||objectp(roomBuf)||
				 (stringp(roomBuf) && strsrch(roomBuf,"/")>=0) ) continue;     //去除entry/out/目标为object/目标为带/的路径的所有对象。
			if(member_array(roomBuf,resultRBuf)==-1) {
				endRoom=roomBuf;
				break;
			}
		}
		
//由于关联的时候是room1和room2的关系是成对写入的，即对room1写入和room2的关系正方向，也对room2写入和room1关系的反方向。
//所以即使对目标房间没有作任何计算也存在计算好的关联关系。		
		if(mapp(exitsRBuf[endRoom])) {
			exits=keys(exitsRBuf[endRoom]);
//如果本房间存在外部出口，则不分配south方向给该房间。主要为了地图显示更合理
			if(member_array("out",keys(exitsRBuf[endRoom]))!=-1)
				exits=exits+({"south"});
			else if(member_array("enter",keys(exitsRBuf[endRoom]))!=-1)
				exits=exits+({"north"});
	  }
		else
			exits=({});
		
		effRooms=roomArray-resultRBuf-({endRoom});
		if(sizeof(effRooms)>0) {
			randomRoom=effRooms[random(sizeof(effRooms))];
			exits=exits+filterMirrorExits(randomRoom,exitsRBuf);
			if(exitsRBuf[randomRoom]&&member_array("out",keys(exitsRBuf[randomRoom]))!=-1)
				exits=exits+({"north"});
			else if(exitsRBuf[randomRoom]&&member_array("enter",keys(exitsRBuf[randomRoom]))!=-1)
				exits=exits+({"south"});
			randomExit=randomExits(exits);
			if(!mapp(exitsRBuf[endRoom]))
			 	exitsRBuf[endRoom]=([randomExit:randomRoom]);
			else
			 	exitsRBuf[endRoom]=exitsRBuf[endRoom]+([randomExit:randomRoom]);

			if(!mapp(exitsRBuf[randomRoom])) 
				exitsRBuf[randomRoom]=([directMirror[randomExit]:endRoom]);
			else
				exitsRBuf[randomRoom]=exitsRBuf[randomRoom]+([directMirror[randomExit]:endRoom]);
			exits=exits+({randomExit});
		}

		if(exitsLen>sizeof(keys(exitsRBuf[endRoom]))) {
			exitsLen-=sizeof(keys(exitsRBuf[endRoom]));
			effRooms=roomArray-({endRoom})-values(exitsRBuf[endRoom]);
//减去房间链接数到达4个上限的那些房间
			foreach(roomBuf in resultRBuf)
				if(sizeof(keys(exitsRBuf[roomBuf]))>=4)
					effRooms=effRooms-({roomBuf});

		  for(i=0;i<exitsLen;i++) {
		  	if(sizeof(effRooms)==0)
		  		break;
			  randomRoom=effRooms[random(sizeof(effRooms))];
				exits=keys(exitsRBuf[endRoom])+filterMirrorExits(randomRoom,exitsRBuf);
//如果本房间存在外部出口，则不分配south方向给该房间。主要为了地图显示更合理
				if(member_array("out",keys(exitsRBuf[endRoom]))!=-1)
					exits=exits+({"south"});
				else if(member_array("enter",keys(exitsRBuf[endRoom]))!=-1)
					exits=exits+({"north"});
				if(exitsRBuf[randomRoom]&&member_array("out",keys(exitsRBuf[randomRoom]))!=-1)
					exits=exits+({"north"});
				else if(exitsRBuf[randomRoom]&&member_array("enter",keys(exitsRBuf[randomRoom]))!=-1)
					exits=exits+({"south"});
			  randomExit=randomExits(exits);
			  
			  if(!mapp(exitsRBuf[endRoom]))
			  	exitsRBuf[endRoom]=([randomExit:randomRoom]);
			  else
			  	exitsRBuf[endRoom]=exitsRBuf[endRoom]+([randomExit:randomRoom]);
			  
			  if(!mapp(exitsRBuf[randomRoom])) 
				  exitsRBuf[randomRoom]=([directMirror[randomExit]:endRoom]);
			  else
				  exitsRBuf[randomRoom]=exitsRBuf[randomRoom]+([directMirror[randomExit]:endRoom]);
			  exits=exits+({randomExit});
			  effRooms=effRooms-({randomRoom});
		  }
		}
		resultRBuf=resultRBuf+({endRoom});
  }
  if(sizeof(roomArray)==sizeof(resultRBuf))
  	return exitsRBuf;
  else {
  	exitsRBuf=virtualRoomRelate(roomArray,exitsRBuf,resultRBuf,complex);
	  return exitsRBuf;
  }
}

//根据计算获得的迷宫方向信息和房间的基础信息获得virtual object的所有基本要素
protected mapping virtualRoom(int flag,string vNo, mapping exitsResult,mapping room)
{
	mapping vRoom=([]);
	string exit;
	
	vRoom["exits"]=([]);
//多地图拼接的时候第N个地图的0号房间拼接到N-1个地图的出口
	foreach(exit in keys(exitsResult)) {
		if(flag&&vNo=="0"&&exitsResult[exit]=="out")
			vRoom["exits"]+=([exit:sprintf("%s/%d_%s",base_name(this_object()),flag-1,exitsResult[exit])]);
//迷宫出口链接到固定地图的时候直接取路径
		else if(exit=="enter"||exit=="out")
		  vRoom["exits"]+=([exit:exitsResult[exit]]);
		else
			vRoom["exits"]+=([exit:sprintf("%s/%d_%s",base_name(this_object()),flag,exitsResult[exit])]);
	}
	
	vRoom["file"]=room["file"][random(100)%sizeof(room["file"])];
	if(mapp(room["show"])) {
		vRoom["short"]=keys(room["show"])[random(100)%sizeof(keys(room["show"]))];
		vRoom["desc"]=room["show"][vRoom["short"]];
	}
	else {
		vRoom["short"]=room["short"][random(100)%sizeof(room["short"])];
		vRoom["desc"]=room["desc"][random(100)%sizeof(room["desc"])];
	}
	vRoom["mazeIndex"]=flag;
	vRoom["mazeNo"]=vNo;
	return vRoom;
}

//本函数的作用是对阵列roomArray每个房间除固定出口以外的所有出口进行动态变动。除了保证建立连接所有房间的通路
//以外其他通路都是全随机产生。
protected void dynMazeInit(object *roomArray,object headRoom) {
//存放动态房间链接结果。key值是object，value是一个方向和目标房间object的键值对。	
	mapping dynExitsResult=([]);
	mapping exitMap,roomExits;
	object roomBuf;
	string roomExit;
	
	dynExitsResult=mazeRoomRebuild(roomArray,headRoom,([]),({}));
//得到动态关联关系以后，修改房间的出口	
	foreach(roomBuf in keys(dynExitsResult)) {
		exitMap=dynExitsResult[roomBuf];
		roomExits=roomBuf->query("exits");
		foreach(roomExit in keys(exitMap))
			roomExits[roomExit]=replace_string(file_name(exitMap[roomExit]),".c","");
		roomBuf->set("exits",roomExits);
	}
}

//首先通过递归保证每个房间都通向链路上一个不同的房间，然后其他方向全部随机。计算前提是必须保证房间中存在可以利用的
//动态方向大于等于三个。（可利用的动态方向过少就不是迷宫了）
protected mapping mazeRoomRebuild(object *roomArray,object headRoom,mapping exitsResult,object *resultRooms) {
	string *exits;
	int lp,staticExit;
	object *effRooms,randomRoom,endRoom,roomBuf,*resultRBuf;
	mapping exitsRBuf;
	
	exitsRBuf=exitsResult;
	resultRBuf=resultRooms;
	
	if(resultRooms==({}))
		roomBuf=roomArray[0];
	else {
		endRoom=resultRBuf[sizeof(resultRBuf)-1];
		foreach(roomBuf in values(exitsRBuf[endRoom])) {
			if(member_array(roomBuf,resultRBuf)==-1) {
				break;
			}
		}
	}
	
	if(arrayp(roomBuf->query("dynroom/static_exits")))
		exits=keys(roomBuf->query("exits"))-roomBuf->query("dynroom/static_exits");
	else
		exits=keys(roomBuf->query("exits"));
		
	if(sizeof(exits)<3)
		error("房间："+file_name(roomBuf)+"可利用的动态方向过少无法生产动态迷宫。");
	
	staticExit=random(sizeof(exits));
	for(lp=0;lp<sizeof(exits);lp++) {
		if(lp==staticExit) {
			effRooms=roomArray-resultRBuf-({roomBuf});
			if(sizeof(effRooms)>0)
				randomRoom=effRooms[random(sizeof(effRooms))];
			else
				randomRoom=roomArray[random(sizeof(roomArray))];
		} else
			randomRoom=roomArray[random(sizeof(roomArray))];
		if(!mapp(exitsRBuf[roomBuf]))
			exitsRBuf[roomBuf]=([exits[lp]:randomRoom]);
		else
			exitsRBuf[roomBuf]=exitsRBuf[roomBuf]+([exits[lp]:randomRoom]);
	}
	resultRBuf+=({roomBuf});

  if(sizeof(roomArray)==sizeof(resultRBuf))
  	return exitsRBuf;
  else {
  	exitsRBuf=mazeRoomRebuild(roomArray,headRoom,exitsRBuf,resultRBuf);
	  return exitsRBuf;
  }
}

//取得该房间的已存在方向的镜像，包括固定方向的镜像，已经计算获得的方向的镜像
protected string *filterMirrorExits(mixed room,mapping exitsResult)
{
	string *mirrorExits,tExit;
	mirrorExits=({});
//处理固定方向的镜像
	if(objectp(room)&&arrayp(room->query("dynroom/static_exits")))
		foreach(tExit in room->query("dynroom/static_exits"))
			mirrorExits=mirrorExits+({directMirror[tExit]});

//处理已产生结果的方向镜像
  if(exitsResult[room])
  	foreach(tExit in keys(exitsResult[room]))
  		mirrorExits=mirrorExits+({directMirror[tExit]});
  
  return mirrorExits;
}

//标准的随机方向处理函数，如果不存在随机方向处理函数则用本函数进行随机方向选择
protected string randomExits(string *exceptExits)
{
	string *direct=({"north","south","east","west","northeast","northwest","southeast","southwest"});
	string *effDirect;
	
	effDirect=direct-exceptExits;
	return effDirect[random(100)%sizeof(effDirect)];
}