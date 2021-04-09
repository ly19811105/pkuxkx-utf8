//存放玩家永久物品的处理对象
#include <dbase.h>

inherit F_DBASE;
inherit F_SAVE;

int serial;
mapping autoload;

// This is used by F_SAVE to determinethe file name to save our data.
string query_save_file()
{
	string id;

	id = query("id", 1);
	if( !stringp(id) ) return 0;
	return sprintf(DATA_DIR "uitem/%c/%s", id[0], id);
}

int check_save()
{
  string id;
  int ret;
  
  id = query("id", 1);

  if ( ret=file_size(this_object()->query_save_file() + __SAVE_EXTENSION__)<0 )
  {
    log_file("wiz/useritem", sprintf("%s:%d\n", this_object()->query_save_file() + __SAVE_EXTENSION__,ret));
    return 0;
  }
  else 
    return 1;
}

/************************************************************************************
****
****第一种物品存储模式：autoload类物品
****  提供以下几个函数：autoload_equip  将物品记入autoload文件中
****                    disload_equip   将autoload物品从数据中挪出
****                    load_equip      将autoload装备恢复到玩家身上。
****                    query_autoload_dbase 查询存储在本物品上的autoload装备数据
****                    update_autoload 更新autoload装备的某些属性
****
************************************************************************************/
string autoload_equip(object ob, object who)
{
  mapping ob_dbase;
  string files, *ids, okey;
  
  serial++;
  if ( !mapp(autoload) )
    autoload=([]);
  
  ob_dbase=ob->query_entire_dbase();
  files=base_name(ob)+".c";
  ob_dbase+=(["files":files]);
  ob_dbase+=(["ids":ob->parse_command_id_list()]);
  ids=ob_dbase["ids"];
       
  ob->set("gem_ob_autoloaded",1);
  ob->set("no_give",1);
  ob->set("owner_id",getuid(who));
        
  ob->set("no_get",1);
  ob->set("no_put",1);
  ob->set("no_sell",1);
  ob->set("no_drop",1);
  ob->set("no_report_jh", 1);

  if(ob->query("weapon_prop"))
  {
    okey=sprintf("wp_%d",serial);
    ob->set_name(ob->query("name"), ids+({"my "+ob->query("id"),okey}) );
    ob->set("autoload_serial", okey);
    autoload[okey]=([])+ob_dbase;
    map_delete(autoload[okey], "actions");
    map_delete(autoload[okey], "equipped");
    add("gem_weapon_autoload_num",1);
  }
  else if(ob->query("armor_prop"))
  {
    okey=sprintf("am_%d",serial);
    ob->set_name(ob->query("name"), ids+({"my "+ob->query("id"),okey}) );
    ob->set("autoload_serial", okey);
    autoload[okey]=([])+ob_dbase;
    map_delete(autoload[okey], "equipped");
    add("gem_armor_autoload_num",1);
  }
  
  log_file("wiz/useritem-autoload", sprintf("%s %s(%s)将%s(%s) autoloaded\n", ctime(time()), who->query("name"), who->query("id"), ob->query("name"), okey));
  
  return okey;
}

int disload_equip(object ob, object who)
{
  string okey, *ids;
  
  okey=ob->query("autoload_serial");
  map_delete(autoload, okey);
  if ( ob->query("weapon_prop") )
    add("gem_weapon_autoload_num",-1);
  else
    add("gem_armor_autoload_num",-1);
  
  ob->delete("autoload_sereial");
  ob->delete("no_put");
  ob->delete("owner_id");
  ob->delete("gem_ob_autoloaded");
  ids=ob->parse_command_id_list();
  ob->set_name(ob->query("name"), ids-({"my "+ob->query("id"),okey}) );
  if(ob->query("no_gem_disload_give"))
  {       
    ob->set("no_give",1);
    ob->set("no_get",1);
    ob->set("no_sell",1);
    ob->set("no_drop",1);
  }
  else
  {
    ob->set("no_give",0);
    ob->set("no_get",0);
    ob->set("no_sell",1);// 不能是0，否则会出现disload以后能卖普通当铺刷属性的bug --- becool
    ob->set("no_drop",0);
  }
  
  return 1;
}

//载入装备，当copyob存在时，表示载入装备不是给拥有着who，而是给复制者copyob，
//          这时候copytype表示你要复制的类型，拥有着armor，weapon， all
varargs int load_equip(object who, object copyob, string copytype )
{
  int wp, arm, twp, tarm, lp;
  string *autk, files, *ids, *prop;
  mapping dbase;
  object newob, *oblist;
  
  wp=query("gem_weapon_autoload_num");
  arm=query("gem_armor_autoload_num");
  
  if ( !wp && !arm ) 
  {
    tell_object(who,"你在我这里并没有保存任何装备。\n");
    return 0;
  }
  
  autk=keys(autoload);
  oblist=({});
  
  for(lp=0;lp<sizeof(autk);lp++)
  {
    if ( autk[lp][0..1]=="wp" )
    {
      twp++;
      if ( twp>wp )
        continue;
    }
    else
    {
      tarm++;
      if ( tarm> arm )
        continue;
    }
    
    dbase=autoload[autk[lp]];
    
    if(!mapp(dbase) || undefinedp(dbase["files"])) 
      continue;
    
    files=dbase["files"];
    ids=dbase["ids"];
    prop=keys(dbase);
    prop-=({"equipped"});
    if(!newob=new(files))
    {
      if ( objectp(copyob) )
        continue;
      else {
        tell_object(who,"无法自动加载你的随机武器装备！请和wiz联系。\n");
        return 0;
      }
    }
    else 
    {
      newob=new(files);
      newob->set_name(newob->query("name"), ids+({"my "+ids[0],autk[lp]}));
      for(int z=0;z<sizeof(prop);z++)
        newob->set(prop[z],dbase[prop[z]]);
		  
		  if ( newob->is_gems() &&
			     newob->query("cjg_weapon") &&
				   !newob->query("unique_owner") )
			{
			  newob->set("unique_owner", who->query("id"));
		  }
      newob->set("no_report_jh", 1);
      if ( !objectp(copyob) )
        newob->move(who);
      else if ( stringp(copytype) &&
        ( ( copytype=="armor" && autk[lp][0..1]=="am" ) ||
          ( copytype=="weapon" && autk[lp][0..1]=="wp" ) ||
          copytype=="all" )
        )
      {
        newob->move(copyob);
        oblist=oblist+({newob});
      }
      newob->set("owner_id",who->query("id"));
      newob->set("gem_autoloaded",1);
      newob->set("no_drop",1);
      if ( autk[lp][0..1]=="wp" )
      {
        if(!newob->query("weapon_prop"))
          newob->set("weapon_prop/damage",1);
        if(!newob->query("rigidity"))
          newob->set("rigidity",1);
      }
      else
      {
        if(!newob->query("armor_prop"))
          newob->set("armor_prop/armor",1);
        if(!newob->query("rigidity"))
          newob->set("rigidity",100+random(50));
      }
    }
  }
  
  //如果复制装备，则复制目标哪儿保存本次复制到他那里的装备明细清单
  if ( objectp(copyob) &&
       sizeof(oblist)>0 )
    copyob->set_temp("copy_autoload_list", oblist);
  return 1;
}

//根据load_key定位到哪一条属性，
//    type是修改模式，分为set和add两种模式
//    prop是想要修改的属性
void update_autoload(string load_key, string type, mapping prop)
{
  int lp, chv;
  string *pks, chk;
  
  if ( undefinedp(autoload[load_key]) )
    return;
  
  pks=keys(prop);
  if ( type == "set" )
  {
    for(lp=0;lp<sizeof(pks);lp++)
      autoload[load_key][pks[lp]]=prop[pks[lp]];
  }
  else if ( type == "add" )
  {
    for(lp=0;lp<sizeof(pks);lp++)
    {
      if ( intp(prop[pks[lp]]) )
      {
        chk=""+pks[lp];
        chv=0+prop[pks[lp]];
        if ( undefinedp(autoload[load_key][chk]) )
          autoload[load_key][chk]=prop[chk];
        else
          autoload[load_key][chk]+=prop[chk];
      }
    }
  }
}


void levelup_autoload(object who)
{
  mapping gem_weapon_map, gem_armor_map, dbase ;
  string *weapon_list, *armor_list, files, okey;
  object newob;
  
  if ( !mapp(autoload) )
    autoload=([]);
  
  if( who->query("gem_weapon_autoload_num") )
  {
    gem_weapon_map=who->query("gem_weapon_autoload");  
    if( mapp(gem_weapon_map) )
    {
      weapon_list=keys(gem_weapon_map);
      for(int wj = 0;wj < sizeof(weapon_list);wj++)
      {      
        dbase=gem_weapon_map[weapon_list[wj]];
    
        if(!mapp(dbase) || undefinedp(dbase["files"])) continue;
        files=dbase["files"];
    
        if(!newob=new(files))
          continue;
        else{
          serial++;
          okey=sprintf("wp_%d",serial);
          dbase+=(["autoload_serial":okey]);
          autoload[okey]=([])+dbase;
          add("gem_weapon_autoload_num",1);
        }
      }
    }
  }
  
  if( who->query("gem_armor_autoload_num") )
  {
    gem_armor_map=who->query("gem_armor_autoload");  
    if(mapp(gem_armor_map) )
    {
      armor_list=keys(gem_armor_map);
      for(int j=0;j<sizeof(armor_list);j++)
      {
        dbase=gem_armor_map[armor_list[j]];
        if(!mapp(dbase) || undefinedp(dbase["files"])) continue;
        files=dbase["files"];
        if(!newob=new(files))
          continue;
        else{
          serial++;
          okey=sprintf("am_%d",serial);
          dbase+=(["autoload_serial":okey]);
          autoload[okey]=([])+dbase;
          add("gem_armor_autoload_num",1);
        }
      }
    }
  }
  save();
}

mapping query_autoload_dbase()
{
  return autoload;
}