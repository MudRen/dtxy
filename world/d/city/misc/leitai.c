//Cracked by Roath

#include <ansi.h>

//inherit ROOM;
inherit "/d/city/misc/scoresheet.c";

#include <banned.h>
void finish(int r);
void fullup(object);
void pre_status(object);


void create ()
{
  restore();
  set ("short", "擂台");
  set ("long", "\n\t       八  仙  过  海         各  显  神  通\n\n");
  set("exits",([]));
  set("broadcast",1);
  set("alternative_die",1);
  set("no_fight",1);
  set("busy",0);
  setup();
}

void init() {
//  *string banned_action=({"bian","quit","accept","fly","surrender"}))
//  if (wizardp(this_player())) add_action("do_assign","assign");
  pre_status(this_player());
  add_action("do_quit",banned_action);
  add_action("do_cast",({"cast","perform","exert"}));
  add_action("do_checkscore","checkscore");
  add_action("do_ji","ji");
}
int do_checkscore() {
  report(this_player());
  return 1;
}

int do_quit(string arg) {
  write("你不能在这里用这条命令。\n");
  if (wizardp(this_player())) write("巫师请参阅同一路径内的banned.h文档。\n");
  return 1;
}

int do_ji(string arg) {
  write("你不能在这里用这条命令。\n");
  if (wizardp(this_player())) write("巫师请参阅同一路径内的banned.h文档。\n");
  return 1;
}
int do_cast(string arg) {
//    string *banned_cast=({"escape","chuqiao","qiankun","jieti","tudun","shuidun","yinshen"});

    if(!arg) return 0;
    while(sscanf(arg,"%s %*s",arg)==2);
    //write(arg+"\n");
    if(member_array(arg,banned_cast)==-1) return 0;
    write("擂台上请勿使用"+arg+",多谢合作。\n");
    return 1;
}

void alternative_die(object who)
{
  object p1=query("player1");
  object p2=query("player2");
  int winner=0;

  if (!userp(who)) {
    message_vision("$N死了。\n",who);
    destruct(who);
    return;
  }

  who->delete_temp("last_fainted_from");

  if (!p1 || !p2) {
     message_vision(HIW"BEEP!BUG!\n"NOR,who);
     fullup(who);
     who->move(__DIR__"kantai");
     return;
  }
  if (p1==who) winner=2;
  else winner=1;
  finish(winner);
}

void finish(int r) {
  object winner,loser,king,who,obj,item;
  
  remove_call_out("finish");
  
  set("no_fight",1);
  if (r==1) {
    winner=query("player1");
    loser=query("player2");
  } else {
     winner=query("player2");
     loser=query("player1");
  }
    
  fullup(loser);
  fullup(winner);
  winner->remove_killer(loser);
  loser->remove_killer(winner);
  winner->remove_enemy(loser);
  loser->remove_enemy(winner);

  if (!r) {     
    message_vision(HIG"$N$n大战三百回合，不分胜败，各自离场，改日再战！\n"NOR,winner,loser);
  } else {
     message_vision(HIG"$N把$n打翻在地，飞起一脚，将$n踢下了擂台。\n"NOR,winner,loser);
     //loser->move(__DIR__"kantai");
     message_vision(HIG"$N在观众的欢呼声中，高高兴兴地下场休息了。\n"NOR,winner);
//     update_score(winner,loser);
  }
  who=query("player1");
  obj=query("player2");
  king = present("tang taizong",load_object("/d/huanggong/dadian"));
  if(!king) king=load_object("/d/huanggong/npc/emperor");
  if(!king) tell_object(obj,"唐太宗载入失败，请报告巫师！\n");
  //tell_object(obj,"挑战者:"+king->query("tiaozhan")+ "、" +obj->query("id")+"\n应战者："+king->query("beitiaozhan")+ "、" +who->query("id")+"\n");
  if( king && king->query("tiaozhan") == obj->query("id") && king->query("beitiaozhan") == who->query("id") )
  {
  	if( !r )
  	{
  		loser->move("/d/huanggong/dadian");
  		winner->move("/d/huanggong/dadian");
  		king->command("chat " + winner->query("zhangmen/title") + " " + winner->query("name") + " 与 " + loser->query("zhangmen/title") + " " + loser->query("name") + " 比武不分胜负，改日再战。");
  	}
  	else
  	{
  		loser->move("/d/huanggong/dadian");
  		winner->move("/d/huanggong/dadian");
  		winner->set_temp("mieyaolevel",winner->query_temp("mieyao/level"));
  		winner->set_temp("mieyao/level",11);
  		king->set("daoxing",winner->query("daoxing")*2);
  		king->set("combat_exp",winner->query("combat_exp")*2);
  		item = "/d/obj/newitem/newitem"->get_item(king, winner);
  		winner->set_temp("mieyao/level",winner->query_temp("mieyaolevel"));
  		winner->delete_temp("mieyaolevel");
  		if( objectp(item) )
  		{
  			king->command("chat " + winner->query("zhangmen/title") + " " + winner->query("name") + " 比武战胜 " + loser->query("zhangmen/title") + " " + loser->query("name") + "，特赐"+item->name()+"一件。");
  			loser->add("daoxing",-2000);
  			loser->add("combat_exp",-2000);
  			tell_object(loser,HIR"你失败了，被惩罚武学两千，道行两年！\n"NOR);
  			winner->add("daoxing",1000);
  			winner->add("combat_exp",1000);
  			tell_object(winner,HIY"你胜利了，被奖励武学一千，道行一年！\n"NOR);
  			item->move(winner);
  		}
  		else
  		{
  			king->command("chat " + winner->query("zhangmen/title") + " " + winner->query("name") + " 比武战胜 " + loser->query("zhangmen/title") + " " + loser->query("name") + "，奖励武学两千，道行两年。");
  			loser->add("daoxing",-1000);
  			loser->add("combat_exp",-1000);
  			tell_object(loser,HIR"你失败了，被惩罚武学一千，道行一年！\n"NOR);
  			winner->add("daoxing",2000);
  			winner->add("combat_exp",2000);
  			tell_object(winner,HIY"你胜利了，被奖励武学两千，道行两年！\n"NOR);
  		}
	}
	king->delete("tiaozhan");
	king->delete("beitiaozhan");
  }
  else
  {
  	loser->move(__DIR__"kantai");
  	winner->move(__DIR__"kantai");
  }
  delete("player1");
  delete("player2");
  delete("busy");
}

void die(object who)
{
    alternative_die(who);
}
void fullup(object obj) {
  string *conditions;
  int *condition_values;

  if (!obj) return;
  obj->set("kee",(int)obj->query_temp("leitai/kee"));
  obj->set("eff_kee",(int)obj->query_temp("leitai/eff_kee"));
  obj->set("sen",(int)obj->query_temp("leitai/sen"));
  obj->set("eff_sen",(int)obj->query_temp("leitai/eff_sen"));
  obj->set("force", (int)obj->query_temp("leitai/force"));
  obj->set("mana",(int)obj->query_temp("leitai/mana"));

  obj->clear_condition();
  if (conditions=obj->query_temp("leitai/conditions")) {
    condition_values=obj->query_temp("leitai/condition_values");
    for (int i=0;i<sizeof(conditions);i++) 
       obj->apply_condition(conditions[i],condition_values[i]);
  }
}

void pre_status(object obj) {
  string *conditions;
  int *condition_values=allocate(10);
  mapping con;

  if (!obj) return;
  obj->set_temp("leitai/kee",(int)obj->query("kee"));
  obj->set_temp("leitai/eff_kee",(int)obj->query("eff_kee"));
  obj->set_temp("leitai/sen",(int)obj->query("sen"));
  obj->set_temp("leitai/eff_sen",(int)obj->query("eff_sen"));
  obj->set_temp("leitai/force", (int)obj->query("force"));
  obj->set_temp("leitai/mana",(int)obj->query("mana"));

  if (con=obj->query_condition()) {
    conditions=keys(con);
    for (int i=0;i<sizeof(conditions);i++) {
       //write(conditions[i]+"\n");
       condition_values[i]=obj->query_condition(conditions[i]);
    }
    obj->set_temp("leitai/conditions",conditions);
    obj->set_temp("leitai/condition_values",condition_values);
  }
  obj->clear_condition();
}       
int do_assign(string arg) {
  object player;

  if (!arg) return notify_fail("select a player.\n");
  if (!player=present(arg,this_object()))
     return notify_fail("player not found.\n");

  if (!query("player1")) {
    write("Player 1: "+player->name()+" ("+player->query("id")+ ")\n");
    set("player1",player);
    return 1;
  }
  if (!query("player2")) {
    write("Player 2: "+player->name()+" ( "+player->query("id")+ ")\n");
    set("player2",player);
    return 1;
  }
  return notify_fail("2 players already selected.\n");
}

void start() {
  object p1=query("player1");
  object p2=query("player2");
  if ((!p1) || (!p2)) return;
  message_vision(HIW"$N和$n比武开始！限时五分钟！\n"NOR,p1,p2);  
  delete("no_fight");
  p1->kill_ob(p2);
  p2->kill_ob(p1);
  call_out("finish",300,0);
}

void broadcast_room (object room, string str)
{
  string prefix = HIR"【擂台上】"NOR;
  string s1 = str, s2 = "", s3;
  int i;

  reset_eval_cost();

  // remove extra trailing NOR. mon 7/13/99
  s1=replace_string(s1,"\n"NOR,"\n");

  while (strsrch(s1,"\n\n") != -1)
    s1 = replace_string(s1,"\n\n","\n");

  while (sizeof(s1)>1 && s1[sizeof(s1)-1]=='\n')
  {
    s1 = s1[0..(sizeof(s1)-2)];
    s2 = "\n";
  }
  if (sizeof(s1) <= 1)
    return;

  s1 = replace_string(s1,"\n","\n"+prefix);
  if (room)
  {
   tell_room (room, prefix+s1+ NOR+"\n");     
  }
}

void broadcast(string msg) {
  object room=load_object(__DIR__"kantai");
  if (room) broadcast_room(room,msg);
}
