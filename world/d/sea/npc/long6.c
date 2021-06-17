// long1.c
// created 6-6-97 pickle
#include <ansi.h>

#include <skill.h>

inherit NPC;
//inherit F_MASTER;

void create()
{
  set_name("����",({"tao tie","tao","tie","long","taotie","dragon"}));
  set("long","�������Ӳ��������������ã������˵����ӣ�ƽ����ʳ��\n");
  set("gender", "����");
  set("age", 28);
  set("title", "��������֮");
  set("class","dragon");
  set("attitude", "peaceful");
  set("max_kee", 1000);
  set("max_sen", 700);
  set("force", 900);
  set("max_force", 900);
  set("force_factor", 60);
  set("max_mana", 900);
  set("mana", 900);
  set("mana_factor",30);

  set("str",30);
  set("con",30);
  set("per",10+random(10));
  set("bellicosity",500);
  set("cor",30);

  set("combat_exp", 900000+random(100000));
  set_skill("unarmed", 140);
  set_skill("dodge", 150);
  set_skill("force", 150);
  set_skill("parry", 140);
  set_skill("staff", 150);
  set_skill("spells", 120);
  set_skill("seashentong", 100);
  set_skill("dragonfight", 130);
  set_skill("dragonforce", 120);
  set_skill("lunhui-zhang", 150);
  set_skill("dragonstep", 150);
  map_skill("spells", "seashentong");
  map_skill("unarmed", "dragonfight");
  map_skill("force", "dragonforce");
  map_skill("staff","lunhui-zhang");
  map_skill("parry", "lunhui-zhang");
  map_skill("dodge", "dragonstep");

        set("nkgain", 400);

  set("chat_chance_combat", 20);
  set("chat_msg_combat", ({
    (: cast_spell, "hufa" :),
    "�����૵������ˣ����ˣ����ҵ㶫�����ˡ�\n",
  }) );

  setup();  

  carry_object("/d/obj/armor/yinjia")->wear();
  carry_object("/d/sea/obj/dragonstaff")->wield();
  carry_object("/d/sea/obj/longzhu6");
}

int accept_fight(object me)
{
  command("consider "+me->query("id"));
  command("jealous");
  command("grin");
  command("say �����Ҷ��ˣ��Եľ����������ˣ�");
  command("kill "+me->query("id"));
  return 1;
}



void die()
{
     object me,who,longzhu,longjin;
     string whoid;
	  me=this_object();
	  if(me->query_temp("longzhu_kill"))
	{
	  sscanf(me->query_temp("longzhu_kill"),"%s",whoid);
	  if (!present(whoid,environment()))
	  return ::die();
	  who=present(whoid,environment());
     if((who->query("fangcun/panlong_longgong")=="begin")&&(who->query_temp("fangcun/panlong_longgong_longzhu")!="done")&&(environment()))
	  {
	       message_vision("\n\n���ѹ��ֵ���"  + RANK_D->query_respect(who) + "�书��ǿ�������������͸����ˣ�\n\n",who);
           message_vision("���Ѹ�$Nһ����ɫ�����飮\n", who);
	 	   message_vision(HIC"�����૵����˼������\n"NOR, who);
    	   message_vision(HIC"\nֻ��$N����ͻȻӿ��һ��ˮ����ˮ������$N��֮�����ˣ�\n"NOR,me,who);
           longzhu=new("/d/sea/obj/longzhu6");
		   longzhu->move(who);
		   destruct(me);
		   return;    
	  }
	}
	 if(me->query_temp("longjin_kill"))
	{
		  whoid=me->query_temp("longjin_kill");
    	  if (!present(whoid,environment()))
        	  return ::die();
	  	  who=present(whoid,environment());
          if((who->query("fangcun/panlong_hell_18")=="done")&&(who->query("fangcun/panlong_hell_longjin")=="begin")&&(environment()))
		{
			  longjin=new("/d/sea/obj/longjin");
			  longjin->move(me);
			  ::die();
			  return; 
		}
	}
      ::die();

}




