inherit NPC;
#include <ansi.h>

void start(object leitai) {leitai->start();}
void create()
{
  set_name("��̫��", ({"tang taizong", "tang", "tai zong", "zong", "king", "emperor"}));
  set("long", "���ƹ�֮�ʵ���̫�ڡ�\n");
  set("title", "���ƹ�");
  set("gender", "����");
  set("rank_info/respect", "����");
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
  "$N��$n��̾����",
  "$N��$n���͵���",
  "$N΢Ц�Ŷ�$n˵����",
  "$N����ض�$n˵����",
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

  message_vision ("\nһ����$N����ӿ�𵭵���"+
	  (color>2?chinese_number(color)+"��":"")+
	  "���ơ�\n",who);
  
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
    message_vision ("$N��$n˵�������ǲ��ڣ�"+RANK_D->query_respect(who)+
                    "�Ժ�Ҳ��\n",me,who);
    return;
  }
  message_vision (strs[random(sizeof(strs))]+RANK_D->query_respect(who)+
                  "�������ƣ������������޹�Ȼ�����������㣡\n",me,who);
  message_vision ("\n$N����ǰ���Ͻ���$n�ĵ�ǰ������¡�\n",who,me);
  who->start_busy (3,3);
  call_out ("reward_player",2,me,who,dachen);
}

void reward_player (object me, object who, object dachen)
{

    // added by mon 5/29/98 to prevent players repeatedly
    // get reward.
  if ((int)who->query("quest/reward") < 1)
    return;

  message_vision ("\n�Ա�������$N������$n˵�˼��䣬$n���˵�ͷ��\n",dachen,me);
  dachen->reward(who);
  message_vision ("\n$N��æ����һ�ݣ�С�������վ������\n",who,me);
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
	    return notify_fail("��ս�Ǹ�������֮��ľ���������ȥŪ�����Ź����ɡ�\n");
	if(arg == obj->query("id"))
	        return notify_fail("�����Ҫ��ս�Լ�����־����\n");
	if( !arg || (!who=find_player(arg)) )
		return notify_fail("��Ҫ��ս˭?\n");
	if(!who->query("zhangmen"))
	    	return notify_fail("��ս�Ǹ�������֮��ľ������������Ҷ��˰ɡ�\n");
	myexp = obj->query("combat_exp");
	yourexp = who->query("combat_exp");
	if( myexp/4 > yourexp/3 )//������ս�����Լ�wx 20%����
		return notify_fail("��߶Է�̫�࣬��ǿ������ʲô��˼��\n");
	if( myexp/3 < yourexp/4)
		return notify_fail("�Է�����̫�࣬��ͱ�ȥ�����ˡ�\n");
	myexp = obj->query("daoxing");
	yourexp = who->query("daoxing");
	if( myexp/4 > yourexp/3 )//������ս�����Լ�dx 20%����
		return notify_fail("��߶Է�̫�࣬��ǿ������ʲô��˼��\n");
	if( myexp/3 < yourexp/4)
		return notify_fail("�Է�����̫�࣬��ͱ�ȥ�����ˡ�\n");
	if(me->query("tiaozhan"))
		return notify_fail("�Ѿ����˷�����ս�ˣ�����΢��һ��ɡ�\n"); 
	if( time()-me->query("biwu_time") < 180 )
		return notify_fail("����ȷʵ���ʣ����������ˣ�������ЪϢһ�ᣡ\n");
	 me->set("tiaozhan",obj->query("id"));
	 me->set("beitiaozhan",who->query("id"));
	 me->set("biwu_time",time());
	 command("chat " + obj->query("zhangmen/title") + " " + obj->query("name") + " ǰ����ս " + who->query("zhangmen/title") + " " + who->query("name") + "��" + who->query("name") + "�ٵ����Ӧս��");
	 tell_object(who,HIR + obj->query("zhangmen/title") + "���㷢������ս��Ϊ�������������Ͻ�ȥӦս(yingzhan)�ɣ�\n"NOR);
	 call_out("not_yingzhan",300,who);
	 return 1;
}	 
	
void not_yingzhan(object who)
{
	object me=this_object();
	command("chat " + who->query("zhangmen/title") + " " + who->query("name") + "��С���£�����ǰ��Ӧս��");
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
	    return notify_fail("�㲻�����ţ�����Ӧս��\n");
	if( !me->query("tiaozhan") )
	  	return notify_fail("û����������ս��\n"); 
	if( who->query("id") != me->query("beitiaozhan")  )
	   	return notify_fail("û����������ս��\n"); 
	obj = find_player(me->query("tiaozhan"));
	if( !obj )
	{
		me->delete("tiaozhan");
		me->delete("beitiaozhan");
		return notify_fail("��ս������Ѿ����ˣ�������սȡ����\n"); 
	}
	leitai = find_object("/d/city/misc/leitai");
	if(!leitai) leitai=load_object("/d/city/misc/leitai");
	if (leitai->query("busy")) 
    		return notify_fail("����������̨�Ͻ��֣����Ժ�\n");  
	remove_call_out("not_yingzhan");
        command("chat " + obj->query("zhangmen/title") + " " + obj->query("name") + " �� " + who->query("zhangmen/title") + " " + who->query("name") + " ����ս������ʼ�����ҵ�����̨��Ħѧϰ��");
        if (obj->move(leitai) && who->move(leitai)) 
        {
    		leitai->set("player1",who);
    		leitai->set("player2",obj);
    		leitai->set("busy",1);
    		call_out("start",5,leitai);
   	}
        return 1;
}	
