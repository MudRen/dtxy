inherit NPC;
#include <ansi.h>

void start(object leitai) {leitai->start();}
void create()
{
  set_name("唐太宗", ({"tang taizong", "tang", "tai zong", "zong", "king", "emperor"}));
  set("long", "大唐国之皇帝唐太宗。\n");
  set("title", "大唐国");
  set("gender", "男性");
  set("rank_info/respect", "陛下");
  set("age", 80);
  set("attitude", "peaceful");
  set("shen_type", 1);
  set("per", 30);
  set("int", 30);
  set("max_kee", 700);
  set("max_gin", 700);
  set("max_sen", 700);
  set("force", 800);
  set("max_force", 800);
  set("force_factor", 50);
  set("max_mana", 800);
  set("mana", 800);
  set("mana_factor", 40);
  set("combat_exp", 150000000);
  set("daoxing", 150000000);
  set_skill("unarmed", 50);
  set_skill("dodge", 50);
  set_skill("parry", 50);
  set_skill("spells", 50);
  set_skill("force", 50);
  set_skill("seashentong", 50);
  set_skill("dragonforce", 50);
  set_skill("dragonstep", 50);
  set_skill("dragonfight", 50);
  map_skill("unarmed", "dragonfight");
  map_skill("dodge", "dragonstep");
  map_skill("force", "dragonforce");
  map_skill("spells", "seashentong");
  set_weight(5000000);  
  setup();
  carry_object("/d/obj/cloth/mangpao")->wear();
  
}

void init ()
{
    object who=this_player();
    if(!who) return;

  call_out ("test_player",1,this_player());
  if ((int)who->query("quest/reward") ){
      who->start_busy(2);
  }
  add_action("do_tiaozhan", "tiaozhan");
  add_action("do_jieshou", "yingzhan");
}

string *strs = ({
  "$N对$n惊叹道：",
  "$N对$n赞赏道：",
  "$N微笑着对$n说道：",
  "$N赞许地对$n说道：",
});

void test_player (object who)
{
  object me = this_object();
  object where = environment (me);
  object dachen;
  string str;
  int rand, reward, color;
  mapping colors;

  if (who->query("quest/reward") < 1)
    return;

    colors=who->query("quest/colors");
    color=sizeof(colors);
//    if(!color) return;
    switch(color) {
      case 1: reward=1;break;
      case 2: reward=1;break;
      case 3: reward=3;break;
      case 4: reward=7;break;
      case 5: reward=10;break;
      case 6: reward=15;break;
      case 7: reward=25;break;
      default: reward=1;
    }
    
  // mon 12/17/98
  if(((int)who->query("combat_exp")+(int)who->query("daoxing"))/2
	  <20000) { // for newbie, no color request.
             // for older players, rewards depends on number of colors.
      if(color<2) color=2;
      if(reward<10) reward=10;
  }

  who->set_temp("quest/reward_point",
	  (int)who->query("quest/reward")*reward/6);

  message_vision ("\n一进大殿，$N身上涌起淡淡的"+
	  (color>2?chinese_number(color)+"彩":"")+
	  "祥云。\n",who);
  
  if(color==1) { // no dx & pot rewards.
      rand=random(6);
  } else {
    rand=random(100);
  }
    
  if(rand==0)
        str = "zhang shiheng";  
  else if(rand<3)
        str = "meng ziru";
  else if(rand<6)
        str = "du ruhui";       
  else if(rand<53)
        str = "duan zhixian";
  else 
        str = "xu maogong";     
    
  dachen = present (str, where);

  if (! dachen) {
    dachen = present ("da chen", where);
    //someone took dachen out of this room. nobody should do this.
    //here only give minimum reward as penalty.
    who->set_temp("quest/reward_point",0);
  }

  if (! dachen ||
      !living(dachen))
  {
    message_vision ("$N对$n说道：大臣们不在，"+RANK_D->query_respect(who)+
                    "稍候也。\n",me,who);
    return;
  }
  message_vision (strs[random(sizeof(strs))]+RANK_D->query_respect(who)+
                  "祥云缭绕，面生瑞气，朕果然有赏御赐与你！\n",me,who);
  message_vision ("\n$N走上前，赶紧在$n的殿前俯身跪下。\n",who,me);
  who->start_busy (3,3);
  call_out ("reward_player",2,me,who,dachen);
}

void reward_player (object me, object who, object dachen)
{

    // added by mon 5/29/98 to prevent players repeatedly
    // get reward.
  if ((int)who->query("quest/reward") < 1)
    return;

  message_vision ("\n旁边闪过大臣$N低声向$n说了几句，$n点了点头。\n",dachen,me);
  dachen->reward(who);
  message_vision ("\n$N连忙俯身一拜，小心翼翼地站起来。\n",who,me);
  who->delete("quest/reward");
  who->interrupt_me();
}

int do_tiaozhan(string arg)
{
	object obj,me,who;
	int myexp,yourexp;
	obj =this_player();
	me = this_object();
	
	if(!obj->query("zhangmen"))
	    return notify_fail("挑战是各派掌门之间的竞争，你先去弄个掌门过过瘾吧。\n");
	if(arg == obj->query("id"))
	        return notify_fail("你打算要挑战自己？有志气！\n");
	if( !arg || (!who=find_player(arg)) )
		return notify_fail("你要挑战谁?\n");
	if(!who->query("zhangmen"))
	    	return notify_fail("挑战是各派掌门之间的竞争，还是先找对人吧。\n");
	myexp = obj->query("combat_exp");
	yourexp = who->query("combat_exp");
	if( myexp/4 > yourexp/3 )//不能挑战低于自己wx 20%的人
		return notify_fail("你高对方太多，以强凌弱有什么意思。\n");
	if( myexp/3 < yourexp/4)
		return notify_fail("对方高你太多，你就别去送死了。\n");
	myexp = obj->query("daoxing");
	yourexp = who->query("daoxing");
	if( myexp/4 > yourexp/3 )//不能挑战低于自己dx 20%的人
		return notify_fail("你高对方太多，以强凌弱有什么意思。\n");
	if( myexp/3 < yourexp/4)
		return notify_fail("对方高你太多，你就别去送死了。\n");
	if(me->query("tiaozhan"))
		return notify_fail("已经有人发起挑战了，你稍微等一会吧。\n"); 
	if( time()-me->query("biwu_time") < 180 )
		return notify_fail("比武确实精彩，不过朕累了，先让朕歇息一会！\n");
	 me->set("tiaozhan",obj->query("id"));
	 me->set("beitiaozhan",who->query("id"));
	 me->set("biwu_time",time());
	 command("chat " + obj->query("zhangmen/title") + " " + obj->query("name") + " 前来挑战 " + who->query("zhangmen/title") + " " + who->query("name") + "，" + who->query("name") + "速到大殿应战。");
	 tell_object(who,HIR + obj->query("zhangmen/title") + "向你发起了挑战，为了门派荣誉，赶紧去应战(yingzhan)吧！\n"NOR);
	 call_out("not_yingzhan",300,who);
	 return 1;
}	 
	
void not_yingzhan(object who)
{
	object me=this_object();
	command("chat " + who->query("zhangmen/title") + " " + who->query("name") + "胆小怕事，不敢前来应战。");
	me->delete("tiaozhan");
	me->delete("beitiaozhan");
	return;
}

int do_jieshou()
{
	object me,obj,who;
	object leitai;
	who =this_player();
	me = this_object();
	if( !who->query("zhangmen") )
	    return notify_fail("你不是掌门，不能应战。\n");
	if( !me->query("tiaozhan") )
	  	return notify_fail("没有人向你挑战。\n"); 
	if( who->query("id") != me->query("beitiaozhan")  )
	   	return notify_fail("没有人向你挑战。\n"); 
	obj = find_player(me->query("tiaozhan"));
	if( !obj )
	{
		me->delete("tiaozhan");
		me->delete("beitiaozhan");
		return notify_fail("挑战你的人已经走了，本次挑战取消。\n"); 
	}
	leitai = find_object("/d/city/misc/leitai");
	if(!leitai) leitai=load_object("/d/city/misc/leitai");
	if (leitai->query("busy")) 
    		return notify_fail("有人正在擂台上交手，请稍候。\n");  
	remove_call_out("not_yingzhan");
        command("chat " + obj->query("zhangmen/title") + " " + obj->query("name") + " 与 " + who->query("zhangmen/title") + " " + who->query("name") + " 争霸战即将开始，请大家到观礼台观摩学习。");
        if (obj->move(leitai) && who->move(leitai)) 
        {
    		leitai->set("player1",who);
    		leitai->set("player2",obj);
    		leitai->set("busy",1);
    		call_out("start",5,leitai);
   	}
        return 1;
}	
