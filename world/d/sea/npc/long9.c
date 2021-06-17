// long1.c
// created 6-6-97 pickle
// by take 2001.8.12
#include <ansi.h>

#include <skill.h>

inherit NPC;
//inherit F_MASTER;
int begin_go();

void create()
{
  set_name("��ͼ",({"shu tu","shu","tu","long","shutu","dragon"}));
  set("long","�������Ӳ��������������ã���ͼ�˵ھ��ӣ�ƽ���ñա�\n");
  set("gender", "����");
  set("age", 41);
  set("title", "��������֮");
  set("class","dragon");
  set("attitude", "peaceful");
  set("max_kee", 1200);
  set("max_sen", 900);
  set("force", 900);
  set("max_force", 900);
  set("force_factor", 80);
  set("max_mana", 900);
  set("mana", 900);
  set("force_factor",50);

  set("str",30);
  set("con",30);
  set("per",10+random(10));
  set("bellicosity",500);
  set("cor",30);

  set("combat_exp", 900000+random(100000));
  set_skill("unarmed", 140);
  set_skill("dodge", 140);
  set_skill("force", 140);
  set_skill("parry", 140);
  set_skill("sword", 150);
  set_skill("spells", 120);
  set_skill("seashentong", 120);
  set_skill("dragonfight", 140);
  set_skill("dragonforce", 140);
  set_skill("sanqing-jian", 150);
  set_skill("dragonstep", 150);
  map_skill("spells", "seashentong");
  map_skill("unarmed", "dragonfight");
  map_skill("force", "dragonforce");
  map_skill("sword","sanqing-jian");
  map_skill("parry", "sanqing-jian");
  map_skill("dodge", "dragonstep");

        set("nkgain", 400);

  set("inquiry", ([
                 "whokillme"    : (: begin_go :),
		               ]) );
  setup();  

  carry_object("/d/obj/armor/yinjia")->wear();
  carry_object("/d/sea/obj/dragonsword")->wield();
  carry_object("/d/sea/obj/longzhu9");
}

int accept_fight(object me)
{
  command("fear");
  command("say ����ϲ����������ţ�������ϲ����ܡ�");
  command("say ������Ȼ" + RANK_D->query_respect(me) + "��Ȼ����У���Ҳֻ�÷����ˡ�");
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
	       message_vision("\n\n��ͼ���ֵ���"  + RANK_D->query_respect(who) + "�书��ǿ�������������͸����ˣ�\n\n",who);
           message_vision("��ͼ��$Nһ����ɫ�����飮\n", who);
	 	   message_vision(HIC"��ͼ�૵����˼������\n"NOR, who);
    	   message_vision(HIC"\nֻ��$N����ͻȻӿ��һ��ˮ����ˮ������$N��֮�����ˣ�\n"NOR,me,who);
           longzhu=new("/d/sea/obj/longzhu9");
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

int begin_go()
{
     object me;
     string whoid;
	  me=this_player();
   if(environment())
	{   
    //   whoid=*explode( me->query_temp("kill/last_killer"), " " );
		sscanf(me->query("kill/last_killer"),"%s",whoid);
        tell_object(me, RED"�ҿ�����" + whoid
      + "ɱ����,һ�������\n"NOR);
	return 1;
	}
 return 0;
}